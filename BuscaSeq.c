#include "BuscaSeq.h"
#include <stdio.h>

// Função 1: Busca a matrícula exata (Estratégia 3)
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

// Função 2: Busca por intervalo usando o CR (Estratégia 5)
void buscaSequencialIntervalo(const char* nomeArquivo, float crMin, float crMax, Registro* resultados, int* qtd) {
    FILE *arq = fopen(nomeArquivo, "rb");
    if (!arq) return;
    
    Registro r;
    *qtd = 0;
    while (fread(&r, sizeof(Registro), 1, arq)) {
        if (r.cr >= crMin && r.cr <= crMax) {
            resultados[*qtd] = r;
            (*qtd)++;
        }
    }
    fclose(arq);
}
