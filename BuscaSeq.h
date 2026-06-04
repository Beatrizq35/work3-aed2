#ifndef BUSCA_SEQ_H
#define BUSCA_SEQ_H
#include "Registro.h"

int buscaSequencialChave(const char* nomeArquivo, int chaveDesejada, Registro* outReg);

// A declaração agora usa os floats corretamente
void buscaSequencialIntervalo(const char* nomeArquivo, float crMin, float crMax, Registro* resultados, int* qtd);

#endif
