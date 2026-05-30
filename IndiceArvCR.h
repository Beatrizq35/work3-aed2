#ifndef INDICEARVCR_H
#define INDICEARVCR_H

#include <stdio.h>
#include <stdlib.h>

/* ================================================================
 * TAD IndiceArvCR
 * Árvore binária de pesquisa que armazena pares
 * <cr (double), num_registro (long)>.
 * Usada para consultas do tipo >, >=, <, <= sobre o atributo CR.
 * ================================================================ */

typedef struct NoCR {
    double        chave;
    long          num_reg;
    struct NoCR  *esq;
    struct NoCR  *dir;
} NoCR;

NoCR *crInserir(NoCR *raiz, double chave, long num_reg);

/* Cada função abaixo preenche o vetor 'resultado' (pre-alocado pelo
 * chamador com capacidade 'cap') e retorna a quantidade encontrada. */
int crMaiorQue    (NoCR *raiz, double valor, long *resultado, int cap);
int crMaiorIgual  (NoCR *raiz, double valor, long *resultado, int cap);
int crMenorQue    (NoCR *raiz, double valor, long *resultado, int cap);
int crMenorIgual  (NoCR *raiz, double valor, long *resultado, int cap);

void crEmOrdem (NoCR *raiz);
void crDestruir(NoCR *raiz);

#endif /* INDICEARVCR_H */
