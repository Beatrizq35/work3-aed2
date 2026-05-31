//rodar o código: gcc main.c Registro.c IndiceArvBST.c IndiceHash.c BuscaSeq.c metricas.c -o pro
#include <stdio.h>
#include <stdlib.h>
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
    printf("+-------------------------------------------------------------------------------+\n");
    printf("| %-77s |\n", titulo);
    printf("+----+-----------+--------------------+-------+--------------+------------------+\n");
    printf("| Ex | Matricula | Nome               | Idade | Curso        | Tempo (segs)     |\n");
    printf("+----+-----------+--------------------+-------+--------------+------------------+\n");
    
    double soma = 0;
    for (int i = 0; i < qtd; i++) {
        // Os modificadores como .18s truncam strings muito grandes para nao quebrar a tabela
        printf("| %-2d | %-9d | %-18.18s | %-5d | %-12.12s | %-16.6f |\n", 
               i + 1, regs[i].matricula, regs[i].nome, regs[i].idade, regs[i].curso, tempos[i]);
        soma += tempos[i];
    }
    
    printf("+----+-----------+--------------------+-------+--------------+------------------+\n");
    printf("| Tempo Medio: %-64.6f |\n", soma / qtd);
    printf("+-------------------------------------------------------------------------------+\n");
}

void imprimirTabelaIntervalo(const char* titulo, int idades[], int qtdResultados[], double tempos[], int qtd) {
    printf("\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("| %-68s |\n", titulo);
    printf("+----------+---------------+-----------------+-------------------------+\n");
    printf("| Execucao | Idade (>= X)  | Qtd Encontrada  | Tempo de Execucao (segs)|\n");
    printf("+----------+---------------+-----------------+-------------------------+\n");
    
    double soma = 0;
    for (int i = 0; i < qtd; i++) {
        printf("| %-8d | %-13d | %-15d | %-23.6f |\n", i + 1, idades[i], qtdResultados[i], tempos[i]);
        soma += tempos[i];
    }
    
    printf("+----------+---------------+-----------------+-------------------------+\n");
    printf("| Tempo Medio: %-55.6f |\n", soma / qtd);
    printf("+----------------------------------------------------------------------+\n");
}

// ----------------------------------------------------

int main() {
    printf("-> Criando arquivo com %d registros...\n", QTD_REGISTROS);
    criarArquivoTeste(NOME_ARQ, QTD_REGISTROS);

    FILE* arq = fopen(NOME_ARQ, "rb");
    
    NoBST* arvChave = NULL;  
    TabelaHash hashChave;    
    NoBST* arvIdade = NULL;  
    
    inicializarHash(&hashChave);

    printf("-> Carregando indices na memoria RAM...\n");
    Registro r;
    int rrnAtual = 0;
    while (fread(&r, sizeof(Registro), 1, arq)) {
        arvChave = inserirBST(arvChave, r.matricula, rrnAtual);
        inserirHash(&hashChave, r.matricula, rrnAtual);
        arvIdade = inserirBST(arvIdade, r.idade, rrnAtual);
        rrnAtual++;
    }
    
    printf("-> Colisoes totais na Tabela Hash: %d\n", hashChave.colisoes);
    
    // --- PREPARAÇÃO DOS DADOS DE TESTE ---
    int chavesParaBuscar[QTD_BUSCAS];
    int idadesParaBuscar[QTD_BUSCAS];
    for(int i=0; i<QTD_BUSCAS; i++) {
        chavesParaBuscar[i] = 1000 + (rand() % QTD_REGISTROS);
        idadesParaBuscar[i] = 18 + (rand() % 30);
    }
    
    double tInicio, tFim;
    double tempos[QTD_BUSCAS];
    int qtdEncontrada[QTD_BUSCAS];

    // =======================================================================
    // ESTRATÉGIA 1: Busca usando a árvore binária de pesquisa para atributo chave
    // =======================================================================
    Registro regsEstrategia1[QTD_BUSCAS];
    for(int i=0; i<QTD_BUSCAS; i++) {
        tInicio = obterTempoAtual();
        int rrnEncontrado = buscarBST(arvChave, chavesParaBuscar[i]);
        if (rrnEncontrado != -1) {
            regsEstrategia1[i] = lerRegistroPorRRN(arq, rrnEncontrado); // Busca o dado real no disco
        }
        tFim = obterTempoAtual();
        tempos[i] = tFim - tInicio;
    }
    imprimirTabelaChave("1) Arvore Binaria de Pesquisa (Atributo Chave: Matricula)", regsEstrategia1, tempos, QTD_BUSCAS);

    // =======================================================================
    // ESTRATÉGIA 2: Busca usando hashing para o atributo chave
    // =======================================================================
    Registro regsEstrategia2[QTD_BUSCAS];
    for(int i=0; i<QTD_BUSCAS; i++) {
        tInicio = obterTempoAtual();
        int rrnEncontrado = buscarHash(&hashChave, chavesParaBuscar[i]);
        if (rrnEncontrado != -1) {
            regsEstrategia2[i] = lerRegistroPorRRN(arq, rrnEncontrado);
        }
        tFim = obterTempoAtual();
        tempos[i] = tFim - tInicio;
    }
    imprimirTabelaChave("2) Tabela Hash (Atributo Chave: Matricula)", regsEstrategia2, tempos, QTD_BUSCAS);

    // =======================================================================
    // ESTRATÉGIA 3: Busca sequencial no arquivo para o atributo chave
    // =======================================================================
    Registro regsEstrategia3[QTD_BUSCAS];
    for(int i=0; i<QTD_BUSCAS; i++) {
        tInicio = obterTempoAtual();
        // A busca sequencial já retorna o registro preenchido no terceiro parâmetro
        buscaSequencialChave(NOME_ARQ, chavesParaBuscar[i], &regsEstrategia3[i]);
        tFim = obterTempoAtual();
        tempos[i] = tFim - tInicio;
    }
    imprimirTabelaChave("3) Busca Sequencial em Disco (Atributo Chave: Matricula)", regsEstrategia3, tempos, QTD_BUSCAS);

    // =======================================================================
    // ESTRATÉGIA 4: Busca de intervalo (>=) usando BST para atributo nao-chave
    // =======================================================================
    int resultadosRRN[QTD_REGISTROS];
    for(int i=0; i<QTD_BUSCAS; i++) {
        int qtd = 0;
        tInicio = obterTempoAtual();
        buscarIntervaloBST(arvIdade, idadesParaBuscar[i], idadesParaBuscar[i]+5, resultadosRRN, &qtd);
        tFim = obterTempoAtual();
        tempos[i] = tFim - tInicio;
        qtdEncontrada[i] = qtd;
    }
    imprimirTabelaIntervalo("4) Arvore Binaria (Atributo Nao-Chave: Idade)", idadesParaBuscar, qtdEncontrada, tempos, QTD_BUSCAS);

    // =======================================================================
    // ESTRATÉGIA 5: Busca de intervalo (>=) usando sequencial no arquivo
    // =======================================================================
    Registro resultadosSeq[QTD_REGISTROS];
    for(int i=0; i<QTD_BUSCAS; i++) {
        int qtd = 0;
        tInicio = obterTempoAtual();
        buscaSequencialIntervalo(NOME_ARQ, idadesParaBuscar[i], idadesParaBuscar[i]+5, resultadosSeq, &qtd);
        tFim = obterTempoAtual();
        tempos[i] = tFim - tInicio;
        qtdEncontrada[i] = qtd;
    }
    imprimirTabelaIntervalo("5) Busca Sequencial (Atributo Nao-Chave: Idade)", idadesParaBuscar, qtdEncontrada, tempos, QTD_BUSCAS);

    fclose(arq);
    return 0;
}