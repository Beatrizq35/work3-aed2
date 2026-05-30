#include "BuscaSeq.h"

long buscaSeqChave(FILE *arq, long totalRegs, int id) {
    Registro r;
    long i;
    for (i = 0; i < totalRegs; i++) {
        registroLer(arq, i, &r);
        if (r.id == id) return i;
    }
    return -1;
}

int buscaSeqMaiorQue(FILE *arq, long totalRegs, double valor, long *resultado, int cap) {
    Registro r;
    long i;
    int qtd = 0;
    for (i = 0; i < totalRegs && qtd < cap; i++) {
        registroLer(arq, i, &r);
        if (r.cr > valor) resultado[qtd++] = i;
    }
    return qtd;
}
#Foi escolhido o maior igual (Depois apagar o resto)
int buscaSeqMaiorIgual(FILE *arq, long totalRegs, double valor, long *resultado, int cap) {
    Registro r;
    long i;
    int qtd = 0;
    for (i = 0; i < totalRegs && qtd < cap; i++) {
        registroLer(arq, i, &r);
        if (r.cr >= valor) resultado[qtd++] = i;
    }
    return qtd;
}

int buscaSeqMenorQue(FILE *arq, long totalRegs, double valor, long *resultado, int cap) {
    Registro r;
    long i;
    int qtd = 0;
    for (i = 0; i < totalRegs && qtd < cap; i++) {
        registroLer(arq, i, &r);
        if (r.cr < valor) resultado[qtd++] = i;
    }
    return qtd;
}

int buscaSeqMenorIgual(FILE *arq, long totalRegs, double valor, long *resultado, int cap) {
    Registro r;
    long i;
    int qtd = 0;
    for (i = 0; i < totalRegs && qtd < cap; i++) {
        registroLer(arq, i, &r);
        if (r.cr <= valor) resultado[qtd++] = i;
    }
    return qtd;
}
