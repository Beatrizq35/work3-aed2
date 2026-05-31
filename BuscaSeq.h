#ifndef BUSCA_SEQ_H
#define BUSCA_SEQ_H
#include "Registro.h"

int buscaSequencialChave(const char* nomeArquivo, int chaveDesejada, Registro* outReg);
void buscaSequencialIntervalo(const char* nomeArquivo, int idadeMin, int idadeMax, Registro* resultados, int* qtd);

#endif