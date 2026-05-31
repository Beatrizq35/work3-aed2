#ifndef INDICE_ARV_BST_H
#define INDICE_ARV_BST_H

typedef struct NoBST {
    int valor; // Pode ser a matrícula (chave) ou a idade
    int rrn;   // Número do registro no arquivo (Relative Record Number)
    struct NoBST *esq, *dir;
} NoBST;

NoBST* inserirBST(NoBST* raiz, int valor, int rrn);
int buscarBST(NoBST* raiz, int valor); // Retorna o RRN
void emOrdemBST(NoBST* raiz); // Para testes pequenos
void buscarIntervaloBST(NoBST* raiz, int min, int max, int* resultados, int* qtd); // Para >, <

#endif