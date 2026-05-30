#include "IndiceArvBST.h"

static NoBST *criarNoBST(int chave, long num_reg) {
    NoBST *novo = (NoBST *) malloc(sizeof(NoBST));
    if (!novo) { perror("malloc NoBST"); exit(EXIT_FAILURE); }
    novo->chave   = chave;
    novo->num_reg = num_reg;
    novo->esq     = NULL;
    novo->dir     = NULL;
    return novo;
}

NoBST *bstInserir(NoBST *raiz, int chave, long num_reg) {
    if (raiz == NULL)
        return criarNoBST(chave, num_reg);
    if (chave < raiz->chave)
        raiz->esq = bstInserir(raiz->esq, chave, num_reg);
    else if (chave > raiz->chave)
        raiz->dir = bstInserir(raiz->dir, chave, num_reg);
    /* duplicata: ignora */
    return raiz;
}

long bstBuscar(NoBST *raiz, int chave) {
    if (raiz == NULL)          return -1;
    if (chave == raiz->chave)  return raiz->num_reg;
    if (chave < raiz->chave)   return bstBuscar(raiz->esq, chave);
    return bstBuscar(raiz->dir, chave);
}

void bstEmOrdem(NoBST *raiz) {
    if (raiz == NULL) return;
    bstEmOrdem(raiz->esq);
    printf("  <chave=%d, reg=%ld>\n", raiz->chave, raiz->num_reg);
    bstEmOrdem(raiz->dir);
}

void bstDestruir(NoBST *raiz) {
    if (raiz == NULL) return;
    bstDestruir(raiz->esq);
    bstDestruir(raiz->dir);
    free(raiz);
}
