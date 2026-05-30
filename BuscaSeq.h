#ifndef BUSCASEQ_H
#define BUSCASEQ_H

#include <stdio.h>
#include "Registro.h"

/* ================================================================
 * TAD BuscaSeq
 * Busca sequencial diretamente no arquivo em disco.
 * ================================================================ */

/* Busca pelo id (chave). Retorna numero do registro ou -1. */
long buscaSeqChave(FILE *arq, long totalRegs, int id);

/* Buscas pelo CR. Preenchem vetor resultado (cap = capacidade).
 * Retornam a quantidade encontrada. */
int buscaSeqMaiorQue  (FILE *arq, long totalRegs, double valor, long *resultado, int cap);
int buscaSeqMaiorIgual(FILE *arq, long totalRegs, double valor, long *resultado, int cap);
int buscaSeqMenorQue  (FILE *arq, long totalRegs, double valor, long *resultado, int cap);
int buscaSeqMenorIgual(FILE *arq, long totalRegs, double valor, long *resultado, int cap);

#endif /* BUSCASEQ_H */
