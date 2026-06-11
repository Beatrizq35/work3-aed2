//rodar o código: gcc main.c Registro.c IndiceArvBST.c IndiceHash.c BuscaSeq.c metricas.c -o prog
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Registro.h"
#include "IndiceArvBST.h"
#include "IndiceHash.h"
#include "BuscaSeq.h"
#include "metricas.h"

#define QTD_REGISTROS 5000 
#define QTD_BUSCAS 30      
#define NOME_ARQ "dados.bin"

// Função auxiliar para buscar o registro no disco a partir do RRN
Registro lerRegistroPorRRN(FILE* arq, int rrn) {
    Registro r;
    fseek(arq, rrn * sizeof(Registro), SEEK_SET);
    fread(&r, sizeof(Registro), 1, arq);
    return r;
}

// --- FUNÇÕES PARA DESENHAR AS TABELAS NO TERMINAL ---

void imprimirTabelaChave(const char* titulo, Registro regs[], double tempos[], int qtd) {
    printf("\n");
    printf("+---------------------------------------------------------------------------------------+\n");
    printf("| %-85s |\n", titulo);
    printf("+----+-----------+--------------------+-------+------+--------------+-------------------+\n");
    printf("| Ex | Matricula | Nome               | Idade | CR   | Curso        | Tempo (segs)      |\n");
    printf("+----+-----------+--------------------+-------+------+--------------+-------------------+\n");
    
    double soma = 0;
    for (int i = 0; i < qtd; i++) {
        // Os modificadores como .18s truncam strings muito grandes para nao quebrar a tabela
        printf("| %-2d | %-9d | %-18.18s | %-5d | %-4.1f | %-12.12s | %-17.6f |\n", 
               i + 1, regs[i].matricula, regs[i].nome, regs[i].idade, regs[i].cr, regs[i].curso, tempos[i]);
        soma += tempos[i];
    }
    
    printf("+----+-----------+--------------------+-------+------+--------------+-------------------+\n");
    printf("| Tempo Medio: %-72.6f |\n", soma / qtd);
    printf("+---------------------------------------------------------------------------------------+\n");
}

void imprimirTabelaIntervaloCR(const char* titulo, float crs[], int qtdResultados[], double tempos[], int qtd) {
    printf("\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("| %-68s |\n", titulo);
    printf("+----------+---------------+-----------------+-------------------------+\n");
    printf("| Execucao | Intervalo CR  | Qtd Encontrada  | Tempo de Execucao (segs)|\n");
    printf("+----------+---------------+-----------------+-------------------------+\n");
    
    double soma = 0;
    for (int i = 0; i < qtd; i++) {
        printf("| %-8d | %.1f a %.1f     | %-15d | %-23.6f |\n", i + 1, crs[i], crs[i] + 2.0, qtdResultados[i], tempos[i]);
        soma += tempos[i];
    }
    
    printf("+----------+---------------+-----------------+-------------------------+\n");
    printf("| Tempo Medio: %-55.6f |\n", soma / qtd);
    printf("+----------------------------------------------------------------------+\n");
}

// ----------------------------------------------------

int main() {
    printf("-> Arquivo possui: %d registros.\n", QTD_REGISTROS);
    criarArquivoTeste(NOME_ARQ, QTD_REGISTROS);

    FILE* arq = fopen(NOME_ARQ, "rb");
    
    NoBST* arvChave = NULL;  
    TabelaHash hashChave;    
    NoBST* arvCR = NULL; 
    
    inicializarHash(&hashChave);

    Registro r;
    int rrnAtual = 0;
    while (fread(&r, sizeof(Registro), 1, arq)) {
        arvChave = inserirBST(arvChave, r.matricula, rrnAtual);
        inserirHash(&hashChave, r.matricula, rrnAtual);
        
        // Insere o CR na árvore de atributo não-chave
        arvCR = inserirBST(arvCR, r.cr, rrnAtual); 
        rrnAtual++;
    }
    
    printf("-> Colisoes totais na Tabela Hash: %d\n", hashChave.colisoes);
    
    // --- PREPARAÇÃO DOS DADOS DE TESTE ---
    int chavesParaBuscar[QTD_BUSCAS];
    float crsParaBuscar[QTD_BUSCAS]; // Vetor armazena os CRs sorteados
    
    for(int i=0; i<QTD_BUSCAS; i++) {
        chavesParaBuscar[i] = 1000 + (rand() % QTD_REGISTROS);
        crsParaBuscar[i] = (float)(rand() % 80) / 10.0; // Sorteia um CR de 0.0 a 8.0 para a busca
    }
    
    clock_t start, end; // Variáveis de tempo padronizadas
    double tempos[QTD_BUSCAS];
    int qtdEncontrada[QTD_BUSCAS];

    // =======================================================================
    // ESTRATÉGIA 1: Busca usando a árvore binária de pesquisa para atributo chave
    // =======================================================================
    Registro regsEstrategia1[QTD_BUSCAS];
    for(int i=0; i<QTD_BUSCAS; i++) {
        start = clock();
        int rrnEncontrado = buscarBST(arvChave, chavesParaBuscar[i]);
        if (rrnEncontrado != -1) {
            regsEstrategia1[i] = lerRegistroPorRRN(arq, rrnEncontrado); 
        }
        end = clock();
        tempos[i] = ((double) end - start) / CLOCKS_PER_SEC;
    }
    imprimirTabelaChave("1) Arvore Binaria de Pesquisa (Atributo Chave: Matricula)", regsEstrategia1, tempos, QTD_BUSCAS);

    // =======================================================================
    // ESTRATÉGIA 2: Busca usando hashing para o atributo chave
    // =======================================================================
    Registro regsEstrategia2[QTD_BUSCAS];
    for(int i=0; i<QTD_BUSCAS; i++) {
        start = clock();
        int rrnEncontrado = buscarHash(&hashChave, chavesParaBuscar[i]);
        if (rrnEncontrado != -1) {
            regsEstrategia2[i] = lerRegistroPorRRN(arq, rrnEncontrado);
        }
        end = clock();
        tempos[i] = ((double) end - start) / CLOCKS_PER_SEC;
    }
    imprimirTabelaChave("2) Tabela Hash (Atributo Chave: Matricula)", regsEstrategia2, tempos, QTD_BUSCAS);

    // =======================================================================
    // ESTRATÉGIA 3: Busca sequencial no arquivo para o atributo chave
    // =======================================================================
    Registro regsEstrategia3[QTD_BUSCAS];
    for(int i=0; i<QTD_BUSCAS; i++) {
        start = clock();
        buscaSequencialChave(NOME_ARQ, chavesParaBuscar[i], &regsEstrategia3[i]);
        end = clock();
        tempos[i] = ((double) end - start) / CLOCKS_PER_SEC;
    }
    imprimirTabelaChave("3) Busca Sequencial (Atributo Chave: Matricula)", regsEstrategia3, tempos, QTD_BUSCAS);

    // =======================================================================
    // ESTRATÉGIA 4: Busca de intervalo (>=) usando BST para atributo nao-chave (CR)
    // =======================================================================
    int resultadosRRN[QTD_REGISTROS];
    for(int i=0; i<QTD_BUSCAS; i++) {
        int qtd = 0;
        start = clock();
        
        // Busca alunos com CR maior que o sorteado até um limite de +2.0 pontos
        buscarIntervaloBST(arvCR, crsParaBuscar[i], crsParaBuscar[i] + 2.0, resultadosRRN, &qtd);
        
        end = clock();
        tempos[i] = ((double) end - start) / CLOCKS_PER_SEC;
        qtdEncontrada[i] = qtd;
    }
    imprimirTabelaIntervaloCR("4) Arvore Binaria (Atributo Nao-Chave: CR)", crsParaBuscar, qtdEncontrada, tempos, QTD_BUSCAS);

    // =======================================================================
    // ESTRATÉGIA 5: Busca de intervalo (>=) usando sequencial no arquivo (CR)
    // =======================================================================
    Registro resultadosSeq[QTD_REGISTROS];
    for(int i=0; i<QTD_BUSCAS; i++) {
        int qtd = 0;
        start = clock();
        
        buscaSequencialIntervalo(NOME_ARQ, crsParaBuscar[i], crsParaBuscar[i] + 2.0, resultadosSeq, &qtd);
        
        end = clock();
        tempos[i] = ((double) end - start) / CLOCKS_PER_SEC;
        qtdEncontrada[i] = qtd;
    }
    imprimirTabelaIntervaloCR("5) Busca Sequencial (Atributo Nao-Chave: CR)", crsParaBuscar, qtdEncontrada, tempos, QTD_BUSCAS);

    fclose(arq);
    return 0;
}
