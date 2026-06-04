#ifndef INDICE_ARV_BST_H
#define INDICE_ARV_BST_H

typedef struct NoBST {
    float valor; // <-- MUDOU PARA FLOAT para aceitar o CR (ex: 8.5)
    int rrn;   
    struct NoBST *esq, *dir;
} NoBST;

NoBST* inserirBST(NoBST* raiz, float valor, int rrn);
int buscarBST(NoBST* raiz, float valor); 
void emOrdemBST(NoBST* raiz); 
void buscarIntervaloBST(NoBST* raiz, float min, float max, int* resultados, int* qtd); 

#endif
