#include "BuscaSeq.h"
#include <stdio.h>

int buscaSequencialChave(const char* nomeArquivo, int chaveDesejada, Registro* outReg) {
    FILE *arq = fopen(nomeArquivo, "rb");
    if (!arq) return -1;
    
    Registro r;
    int rrn = 0;
    while (fread(&r, sizeof(Registro), 1, arq)) {
        if (r.matricula == chaveDesejada) {
            *outReg = r;
            fclose(arq);
            return rrn;
        }
        rrn++;
    }
    fclose(arq);
    return -1;
}

void buscaSequencialIntervalo(const char* nomeArquivo, int idadeMin, int idadeMax, Registro* resultados, int* qtd) {
    FILE *arq = fopen(nomeArquivo, "rb");
    if (!arq) return;
    
    Registro r;
    *qtd = 0;
    while (fread(&r, sizeof(Registro), 1, arq)) {
        if (r.idade >= idadeMin && r.idade <= idadeMax) {
            resultados[*qtd] = r;
            (*qtd)++;
        }
    }
    fclose(arq);
}