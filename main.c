#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Registro.h"
#include "IndiceArvBST.h"
#include "IndiceArvCR.h"
#include "IndiceHash.h"
#include "BuscaSeq.h"
#include "metricas.h"

/* ================================================================
 * Configurações
 * ================================================================ */
#define NOME_ARQUIVO  "alunos.dat"
#define TOTAL_REGS    5000
#define NUM_BUSCAS    30

/* ================================================================
 * Dados para geração do arquivo
 * ================================================================ */
static const char *NOMES[] = {
    "Ana Lima","Bruno Costa","Carlos Souza","Diana Ferreira","Eduardo Nunes",
    "Fernanda Gomes","Gabriel Alves","Helena Rocha","Igor Mendes","Julia Pereira",
    "Kaio Santos","Laura Oliveira","Marcos Dias","Natalia Cunha","Otavio Pires",
    "Patricia Leal","Quintino Barros","Raquel Farias","Samuel Torres","Tatiane Cruz",
    "Ulisses Moura","Vanessa Ramos","Wagner Freitas","Ximena Vieira","Yago Andrade",
    "Zelia Monteiro","Andre Correia","Beatriz Carvalho","Caio Rezende","Debora Melo"
};
#define N_NOMES 30

static const char *CURSOS[] = {
    "Ciencia Computacao","Eng. Software","Sistemas Informacao",
    "Redes Computadores","Intel. Artificial"
};
#define N_CURSOS 5

/* ================================================================
 * Geração do arquivo binário em disco
 * ================================================================ */
static void gerarArquivo(void) {
    FILE *arq = fopen(NOME_ARQUIVO, "wb");
    if (!arq) { perror("fopen gerarArquivo"); exit(EXIT_FAILURE); }

    int *ids = (int *) malloc(TOTAL_REGS * sizeof(int));
    if (!ids) { perror("malloc ids"); exit(EXIT_FAILURE); }

    int i;
    for (i = 0; i < TOTAL_REGS; i++) ids[i] = i + 1;

    /* Embaralha IDs (Fisher-Yates) para que a BST nao fique degenerada */
    srand(42);
    for (i = TOTAL_REGS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = ids[i]; ids[i] = ids[j]; ids[j] = tmp;
    }

    for (i = 0; i < TOTAL_REGS; i++) {
        Registro r;
        r.id = ids[i];
        strncpy(r.nome,  NOMES [i % N_NOMES ], REG_TAM_NOME  - 1);
        r.nome[REG_TAM_NOME - 1] = '\0';
        strncpy(r.curso, CURSOS[i % N_CURSOS], REG_TAM_CURSO - 1);
        r.curso[REG_TAM_CURSO - 1] = '\0';
        r.cr           = (double)(rand() % 1001) / 100.0; /* 0.00 a 10.00 */
        r.ano_ingresso = 2015 + (rand() % 10);
        fwrite(&r, sizeof(Registro), 1, arq);
    }

    fclose(arq);
    free(ids);

    printf("[OK] Arquivo '%s' gerado: %d registros x %d bytes = %d bytes.\n",
           NOME_ARQUIVO, TOTAL_REGS, registroTamanho(),
           TOTAL_REGS * registroTamanho());
}

/* ================================================================
 * Construção dos três índices
 * ================================================================ */
static void construirIndices(FILE *arq,
                              NoBST      **bstId,
                              IndiceHash **hashId,
                              NoCR       **bstCr) {
    *bstId  = NULL;
    *hashId = hashCriar();
    *bstCr  = NULL;

    Registro r;
    long i;
    for (i = 0; i < TOTAL_REGS; i++) {
        registroLer(arq, i, &r);
        *bstId  = bstInserir (*bstId,  r.id, i);
        hashInserir(*hashId,  r.id, i);
        *bstCr  = crInserir  (*bstCr,  r.cr, i);
    }

    printf("[OK] Indices construidos. Colisoes na hash: %d\n",
           hashColisoes(*hashId));
}

/* ================================================================
 * Validação cruzada BST x Hash (igual ao TP2: compara resultados)
 * ================================================================ */
static void validarIndices(FILE *arq, NoBST *bstId, IndiceHash *hashId) {
    printf("\n=== Validacao: BST e Hash devem retornar o mesmo num_reg ===\n");
    Registro r;
    long i;
    int ok = 1;
    for (i = 0; i < 10 && i < TOTAL_REGS; i++) {
        registroLer(arq, i, &r);
        long rb = bstBuscar (bstId,  r.id);
        long rh = hashBuscar(hashId, r.id);
        printf("  id=%4d | BST: reg=%ld | Hash: reg=%ld | %s\n",
               r.id, rb, rh, (rb == rh) ? "OK" : "DIVERGENCIA!");
        if (rb != rh) ok = 0;
    }
    printf("  Resultado geral: %s\n",
           ok ? "BST e Hash consistentes." : "ATENCAO: divergencia!");
}

/* ================================================================
 * Questão 1 — Busca pela BST no atributo chave (id)
 * ================================================================ */
static void estrategia1(FILE *arq, NoBST *bstId, int *chaves) {
    printf("\n===================================================\n");
    printf("Questão 1 - Busca BST pelo atributo chave (id)\n");
    printf("===================================================\n");

    time_t start, end;
    double tempos[NUM_BUSCAS];
    int i;

    printf("\n%-8s | %20s | %s\n", "Busca", "Tempo (s)", "Status");
    printf("%-8s-+-%20s-+-%s\n","--------","--------------------","---------------");

    for (i = 0; i < NUM_BUSCAS; i++) {
        start = time(NULL);
        long nr = bstBuscar(bstId, chaves[i]);
        end   = time(NULL);
        tempos[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf(" %6d  | %20.6f | %s\n",
               i + 1, tempos[i],
               nr >= 0 ? "Encontrado" : "Nao encontrado");
    }

    double media = metricasMedia(tempos, NUM_BUSCAS);
    printf("%-8s-+-%20s-+-%s\n","--------","--------------------","---------------");
    printf(" Media   | %20.6f |\n", media);

    /* Exemplo do primeiro valor encontrado */
    long nr = bstBuscar(bstId, chaves[0]);
    if (nr >= 0) {
        Registro r;
        registroLer(arq, nr, &r);
        printf("\nExemplo: id=%d encontrado no registro %ld:\n", chaves[0], nr);
        registroImprimir(&r);
    }
}

/* ================================================================
 * Questão 2 — Busca pela Hash no atributo chave (id)
 * ================================================================ */
static void estrategia2(FILE *arq, IndiceHash *hashId, int *chaves) {
    printf("\n===================================================\n");
    printf(" Questão 2 - Busca Hash pelo atributo chave (id)\n");
    printf("===================================================\n");

    printf("  Colisoes registradas durante a construcao: %d\n",
           hashColisoes(hashId));

    time_t start, end;
    double tempos[NUM_BUSCAS];
    int i;

    printf("\n%-8s | %20s | %s\n", "Busca", "Tempo (s)", "Status");
    printf("%-8s-+-%20s-+-%s\n","--------","--------------------","---------------");

    for (i = 0; i < NUM_BUSCAS; i++) {
        start = time(NULL);
        long nr = hashBuscar(hashId, chaves[i]);
        end   = time(NULL);
        tempos[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf(" %6d  | %20.6f | %s\n",
               i + 1, tempos[i],
               nr >= 0 ? "Encontrado" : "Nao encontrado");
    }

    double media = metricasMedia(tempos, NUM_BUSCAS);
    printf("%-8s-+-%20s-+-%s\n","--------","--------------------","---------------");
    printf(" Media   | %20.6f |\n", media);

    long nr = hashBuscar(hashId, chaves[0]);
    if (nr >= 0) {
        Registro r;
        registroLer(arq, nr, &r);
        printf("\nExemplo: id=%d encontrado no registro %ld:\n", chaves[0], nr);
        registroImprimir(&r);
    }
}

/* ================================================================
 * Questão 3 — Busca Sequencial no arquivo pelo atributo chave (id)
 * ================================================================ */
static void estrategia3(FILE *arq, int *chaves) {
    printf("\n===================================================\n");
    printf(" Questão 3 - Busca Sequencial pelo atributo chave (id)\n");
    printf("===================================================\n");

    time_t start, end;
    double tempos[NUM_BUSCAS];
    int i;

    printf("\n%-8s | %20s | %s\n", "Busca", "Tempo (s)", "Status");
    printf("%-8s-+-%20s-+-%s\n","--------","--------------------","---------------");

    for (i = 0; i < NUM_BUSCAS; i++) {
        start = time(NULL);
        long nr = buscaSeqChave(arq, TOTAL_REGS, chaves[i]);
        end   = time(NULL);
        tempos[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf(" %6d  | %20.6f | %s\n",
               i + 1, tempos[i],
               nr >= 0 ? "Encontrado" : "Nao encontrado");
    }

    double media = metricasMedia(tempos, NUM_BUSCAS);
    printf("%-8s-+-%20s-+-%s\n","--------","--------------------","---------------");
    printf(" Media   | %20.6f |\n", media);

    long nr = buscaSeqChave(arq, TOTAL_REGS, chaves[0]);
    if (nr >= 0) {
        Registro r;
        registroLer(arq, nr, &r);
        printf("\nExemplo: id=%d encontrado no registro %ld:\n", chaves[0], nr);
        registroImprimir(&r);
    }
}

/* ================================================================
 * Questão 4 — Busca por BST no atributo nao-chave CR (cr > valor)
 * ================================================================ */
static void estrategia4(FILE *arq, NoCR *bstCr, double *valores) {
    printf("\n===================================================\n");
    printf(" Questão 4 - Busca BST pelo atributo CR (cr > valor)\n");
    printf("===================================================\n");

    long *resultado = (long *) malloc(TOTAL_REGS * sizeof(long));
    if (!resultado) { perror("malloc resultado e4"); exit(EXIT_FAILURE); }

    time_t start, end;
    double tempos[NUM_BUSCAS];
    int i;

    printf("\n%-8s | %20s | %s\n", "Busca", "Tempo (s)", "Encontrados");
    printf("%-8s-+-%20s-+-%s\n","--------","--------------------","---------------");

    for (i = 0; i < NUM_BUSCAS; i++) {
        start = time(NULL);
        int qtd = crMaiorQue(bstCr, valores[i], resultado, TOTAL_REGS);
        end   = time(NULL);
        tempos[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf(" %6d  | %20.6f | %d registros (cr > %.2f)\n",
               i + 1, tempos[i], qtd, valores[i]);
    }

    double media = metricasMedia(tempos, NUM_BUSCAS);
    printf("%-8s-+-%20s-+-%s\n","--------","--------------------","---------------");
    printf(" Media   | %20.6f |\n", media);

    /* Mostrar os 3 primeiros do ultimo resultado */
    int qtd = crMaiorQue(bstCr, valores[0], resultado, TOTAL_REGS);
    printf("\nExemplo (cr > %.2f): %d registros. Primeiros 3:\n", valores[0], qtd);
    int show = qtd < 3 ? qtd : 3;
    for (i = 0; i < show; i++) {
        Registro r;
        registroLer(arq, resultado[i], &r);
        registroImprimir(&r);
    }

    free(resultado);
}

/* ================================================================
 * Questão 5 — Busca Sequencial no arquivo pelo atributo CR (cr > valor)
 * ================================================================ */
static void estrategia5(FILE *arq, double *valores) {
    printf("\n===================================================\n");
    printf(" Questão 5 - Busca Sequencial pelo atributo CR (cr > valor)\n");
    printf("===================================================\n");

    long *resultado = (long *) malloc(TOTAL_REGS * sizeof(long));
    if (!resultado) { perror("malloc resultado e5"); exit(EXIT_FAILURE); }

    time_t start, end;
    double tempos[NUM_BUSCAS];
    int i;

    printf("\n%-8s | %20s | %s\n", "Busca", "Tempo (s)", "Encontrados");
    printf("%-8s-+-%20s-+-%s\n","--------","--------------------","---------------");

    for (i = 0; i < NUM_BUSCAS; i++) {
        start = time(NULL);
        int qtd = buscaSeqMaiorQue(arq, TOTAL_REGS, valores[i], resultado, TOTAL_REGS);
        end   = time(NULL);
        tempos[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf(" %6d  | %20.6f | %d registros (cr > %.2f)\n",
               i + 1, tempos[i], qtd, valores[i]);
    }

    double media = metricasMedia(tempos, NUM_BUSCAS);
    printf("%-8s-+-%20s-+-%s\n","--------","--------------------","---------------");
    printf(" Media   | %20.6f |\n", media);

    int qtd = buscaSeqMaiorQue(arq, TOTAL_REGS, valores[0], resultado, TOTAL_REGS);
    printf("\nExemplo (cr > %.2f): %d registros. Primeiros 3:\n", valores[0], qtd);
    int show = qtd < 3 ? qtd : 3;
    for (i = 0; i < show; i++) {
        Registro r;
        registroLer(arq, resultado[i], &r);
        registroImprimir(&r);
    }

    free(resultado);
}

/* ================================================================
 * main
 * ================================================================ */
int main(void) {
    printf("============================================================\n");
    printf(" TP3 - AED2 - UFAM\n");
    printf(" Indexacao em Disco: BST | Hash | Busca Sequencial\n");
    printf(" Registro: %d bytes | Total: %d registros\n",
           registroTamanho(), TOTAL_REGS);
    printf("============================================================\n\n");

    /* --- Gerar arquivo --- */
    gerarArquivo();

    /* --- Abrir arquivo --- */
    FILE *arq = fopen(NOME_ARQUIVO, "rb");
    if (!arq) { perror("fopen rb"); return EXIT_FAILURE; }

    /* --- Construir indices --- */
    NoBST      *bstId  = NULL;
    IndiceHash *hashId = NULL;
    NoCR       *bstCr  = NULL;
    construirIndices(arq, &bstId, &hashId, &bstCr);

    /* --- Validação cruzada BST x Hash (10 primeiros registros) --- */
    validarIndices(arq, bstId, hashId);

    /* --- Imprimir amostra dos índices (poucos elementos, conforme enunciado) --- */
    printf("\n=== Amostra BST chave id (10 primeiros em ordem) ===\n");
    /* Imprime apenas os 10 primeiros da arvore: usamos os 10 ids menores */
    {
        int amostra[10] = {1,2,3,4,5,6,7,8,9,10};
        int i;
        for (i = 0; i < 10; i++) {
            long nr = bstBuscar(bstId, amostra[i]);
            printf("  BST: <chave=%d, reg=%ld>  |  Hash: <chave=%d, reg=%ld>\n",
                   amostra[i], nr, amostra[i], hashBuscar(hashId, amostra[i]));
        }
    }

    /* --- Definir 30 chaves distintas para buscas por id --- */
    int chaves[NUM_BUSCAS];
    srand(99);
    {
        int i;
        for (i = 0; i < NUM_BUSCAS; i++)
            chaves[i] = 1 + (rand() % TOTAL_REGS);
    }

    /* --- Definir 30 valores distintos de CR para consultas > --- */
    double valores[NUM_BUSCAS];
    {
        int i;
        for (i = 0; i < NUM_BUSCAS; i++)
            valores[i] = 1.0 + (double)(rand() % 700) / 100.0; /* 1.00 a 8.00 */
    }

    /* --- Memória antes das buscas --- */
    long memAntes = lerMemoriaKB();
    printf("\nMemoria antes das buscas: %ld KB\n", memAntes);

    /* ============================================================
     * Cinco estratégias de busca
     * ============================================================ */
    estrategia1(arq, bstId,  chaves);
    estrategia2(arq, hashId, chaves);
    estrategia3(arq,         chaves);
    estrategia4(arq, bstCr,  valores);
    estrategia5(arq,         valores);

    /* --- Memória depois das buscas --- */
    long memDepois = lerMemoriaKB();
    printf("\nMemoria apos as buscas:   %ld KB\n", memDepois);

    /* --- Resumo comparativo --- */
    printf("\n============================================================\n");
    printf(" RESUMO COMPARATIVO\n");
    printf("============================================================\n");
    printf("  Estrategia 1 - BST (chave id):           O(log n) por busca\n");
    printf("  Estrategia 2 - Hash (chave id):           O(1) amortizado\n");
    printf("  Estrategia 3 - Sequencial (chave id):     O(n) por busca\n");
    printf("  Estrategia 4 - BST (CR > valor):          O(k + log n)\n");
    printf("  Estrategia 5 - Sequencial (CR > valor):   O(n) por busca\n");
    printf("  Colisoes na hash: %d (tabela=%d, regs=%d)\n",
           hashColisoes(hashId), HASH_TAM, TOTAL_REGS);
    printf("  Arquivo: %d regs x %d bytes = %d bytes totais\n",
           TOTAL_REGS, registroTamanho(), TOTAL_REGS * registroTamanho());

    /* --- Liberação de memória --- */
    fclose(arq);
    bstDestruir (bstId);
    hashDestruir(hashId);
    crDestruir  (bstCr);

    printf("\n[FIM] Programa encerrado com sucesso.\n");
    return 0;
}
