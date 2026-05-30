#ifndef INDICEARV_BST_H
#define INDICEARV_BST_H

#include <stdio.h>
#include <stdlib.h>

/* ================================================================
 * TAD IndiceArvBST
 * Árvore binária de pesquisa que armazena pares
 * <chave (int), numero_registro (long)>.
 * Usada como índice do atributo chave (id).
 * ================================================================ */

typedef struct NoBST {
    int           chave;
    long          num_reg;
    struct NoBST *esq;
    struct NoBST *dir;
} NoBST;

NoBST *bstInserir(NoBST *raiz, int chave, long num_reg);
long   bstBuscar (NoBST *raiz, int chave);   /* retorna num_reg ou -1 */
void   bstEmOrdem(NoBST *raiz);              /* imprime pares em ordem */
void   bstDestruir(NoBST *raiz);

#endif /* INDICEARV_BST_H */
