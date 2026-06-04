#include "IndiceArvBST.h"
#include <stdio.h>
#include <stdlib.h>

NoBST* inserirBST(NoBST* raiz, float valor, int rrn) { // float aqui
    if (raiz == NULL) {
        NoBST* novo = (NoBST*)malloc(sizeof(NoBST));
        novo->valor = valor;
        novo->rrn = rrn;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    
    if (valor <= raiz->valor) 
        raiz->esq = inserirBST(raiz->esq, valor, rrn);
    else 
        raiz->dir = inserirBST(raiz->dir, valor, rrn);
    
    return raiz;
}

int buscarBST(NoBST* raiz, float valor) { // float aqui
    if (raiz == NULL) return -1;
    if (raiz->valor == valor) return raiz->rrn;
    if (valor < raiz->valor) return buscarBST(raiz->esq, valor);
    return buscarBST(raiz->dir, valor);
}

void buscarIntervaloBST(NoBST* raiz, float min, float max, int* resultados, int* qtd) { // float aqui
    if (raiz == NULL) return;
    
    if (raiz->valor >= min) buscarIntervaloBST(raiz->esq, min, max, resultados, qtd);
    
    if (raiz->valor >= min && raiz->valor <= max) {
        resultados[*qtd] = raiz->rrn;
        (*qtd)++;
    }
    
    if (raiz->valor <= max) buscarIntervaloBST(raiz->dir, min, max, resultados, qtd);
}

void emOrdemBST(NoBST* raiz) {
    if (raiz != NULL) {
        emOrdemBST(raiz->esq);
        printf("<Valor: %.1f, RRN: %d> ", raiz->valor, raiz->rrn);
        emOrdemBST(raiz->dir);
    }
}
