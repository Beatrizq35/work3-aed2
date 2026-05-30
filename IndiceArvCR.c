#include "IndiceArvCR.h"

static NoCR *criarNoCR(double chave, long num_reg) {
    NoCR *novo = (NoCR *) malloc(sizeof(NoCR));
    if (!novo) { perror("malloc NoCR"); exit(EXIT_FAILURE); }
    novo->chave   = chave;
    novo->num_reg = num_reg;
    novo->esq     = NULL;
    novo->dir     = NULL;
    return novo;
}

NoCR *crInserir(NoCR *raiz, double chave, long num_reg) {
    if (raiz == NULL)
        return criarNoCR(chave, num_reg);
    if (chave < raiz->chave)
        raiz->esq = crInserir(raiz->esq, chave, num_reg);
    else
        raiz->dir = crInserir(raiz->dir, chave, num_reg);
    return raiz;
}

/* ---- coletores ---- */

static int _maiorQue(NoCR *raiz, double valor, long *res, int cap, int qtd) {
    if (raiz == NULL || qtd >= cap) return qtd;
    if (raiz->chave > valor) {
        res[qtd++] = raiz->num_reg;
        qtd = _maiorQue(raiz->esq, valor, res, cap, qtd);
        qtd = _maiorQue(raiz->dir, valor, res, cap, qtd);
    } else {
        qtd = _maiorQue(raiz->dir, valor, res, cap, qtd);
    }
    return qtd;
}

static int _maiorIgual(NoCR *raiz, double valor, long *res, int cap, int qtd) {
    if (raiz == NULL || qtd >= cap) return qtd;
    if (raiz->chave >= valor) {
        res[qtd++] = raiz->num_reg;
        qtd = _maiorIgual(raiz->esq, valor, res, cap, qtd);
        qtd = _maiorIgual(raiz->dir, valor, res, cap, qtd);
    } else {
        qtd = _maiorIgual(raiz->dir, valor, res, cap, qtd);
    }
    return qtd;
}

static int _menorQue(NoCR *raiz, double valor, long *res, int cap, int qtd) {
    if (raiz == NULL || qtd >= cap) return qtd;
    if (raiz->chave < valor) {
        res[qtd++] = raiz->num_reg;
        qtd = _menorQue(raiz->esq, valor, res, cap, qtd);
        qtd = _menorQue(raiz->dir, valor, res, cap, qtd);
    } else {
        qtd = _menorQue(raiz->esq, valor, res, cap, qtd);
    }
    return qtd;
}

static int _menorIgual(NoCR *raiz, double valor, long *res, int cap, int qtd) {
    if (raiz == NULL || qtd >= cap) return qtd;
    if (raiz->chave <= valor) {
        res[qtd++] = raiz->num_reg;
        qtd = _menorIgual(raiz->esq, valor, res, cap, qtd);
        qtd = _menorIgual(raiz->dir, valor, res, cap, qtd);
    } else {
        qtd = _menorIgual(raiz->esq, valor, res, cap, qtd);
    }
    return qtd;
}

int crMaiorQue  (NoCR *raiz, double v, long *r, int c) { return _maiorQue  (raiz,v,r,c,0); }
int crMaiorIgual(NoCR *raiz, double v, long *r, int c) { return _maiorIgual(raiz,v,r,c,0); }
int crMenorQue  (NoCR *raiz, double v, long *r, int c) { return _menorQue  (raiz,v,r,c,0); }
int crMenorIgual(NoCR *raiz, double v, long *r, int c) { return _menorIgual(raiz,v,r,c,0); }

void crEmOrdem(NoCR *raiz) {
    if (raiz == NULL) return;
    crEmOrdem(raiz->esq);
    printf("  <cr=%.2f, reg=%ld>\n", raiz->chave, raiz->num_reg);
    crEmOrdem(raiz->dir);
}

void crDestruir(NoCR *raiz) {
    if (raiz == NULL) return;
    crDestruir(raiz->esq);
    crDestruir(raiz->dir);
    free(raiz);
}
