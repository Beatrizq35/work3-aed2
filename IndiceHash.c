#include "IndiceHash.h"
#include <stdio.h>
#include <stdlib.h>

void inicializarHash(TabelaHash* th) {
    for (int i = 0; i < HASH_SIZE; i++) th->tabela[i] = NULL;
    th->colisoes = 0;
}

void inserirHash(TabelaHash* th, int chave, int rrn) {
    int pos = chave % HASH_SIZE; // Função Hash simples
    
    NoHash* novo = (NoHash*)malloc(sizeof(NoHash));
    novo->chave = chave;
    novo->rrn = rrn;
    novo->prox = th->tabela[pos];
    
    if (th->tabela[pos] != NULL) th->colisoes++; // Colisão detectada
    
    th->tabela[pos] = novo;
}

int buscarHash(TabelaHash* th, int chave) {
    int pos = chave % HASH_SIZE;
    NoHash* atual = th->tabela[pos];
    while (atual != NULL) {
        if (atual->chave == chave) return atual->rrn;
        atual = atual->prox;
    }
    return -1;
}

void imprimirHash(TabelaHash* th) {
    for (int i = 0; i < HASH_SIZE; i++) {
        NoHash* atual = th->tabela[i];
        while (atual != NULL) {
            printf("<Chave: %d, RRN: %d> ", atual->chave, atual->rrn);
            atual = atual->prox;
        }
    }
    printf("\n");
}