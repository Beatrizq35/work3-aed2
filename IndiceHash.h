#ifndef INDICEHASH_H
#define INDICEHASH_H

#include <stdio.h>
#include <stdlib.h>

/* ================================================================
 * TAD IndiceHash
 * Tabela hash com encadeamento separado.
 * Armazena pares <chave (int), num_registro (long)>.
 * Tamanho primo escolhido para provocar algumas colisões
 * com TOTAL_REGS registros.
 * ================================================================ */

#define HASH_TAM 4999   /* primo; com 5000 regs gera ~1 colisão */

typedef struct NoCelula {
    int             chave;
    long            num_reg;
    struct NoCelula *prox;
} NoCelula;

typedef struct {
    NoCelula *tabela[HASH_TAM];
    int       totalColisoes;
} IndiceHash;

IndiceHash *hashCriar   (void);
void        hashInserir (IndiceHash *h, int chave, long num_reg);
long        hashBuscar  (IndiceHash *h, int chave); /* -1 se nao encontrado */
void        hashImprimir(IndiceHash *h);
int         hashColisoes(IndiceHash *h);
void        hashDestruir(IndiceHash *h);

#endif /* INDICEHASH_H */
