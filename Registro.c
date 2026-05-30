#include "Registro.h"

void registroEscrever(FILE *arq, long pos, const Registro *r) {
    fseek(arq, pos * sizeof(Registro), SEEK_SET);
    fwrite(r, sizeof(Registro), 1, arq);
}

void registroLer(FILE *arq, long pos, Registro *r) {
    fseek(arq, pos * sizeof(Registro), SEEK_SET);
    fread(r, sizeof(Registro), 1, arq);
}

void registroImprimir(const Registro *r) {
    printf("  ID: %5d | Nome: %-38s | Curso: %-19s | CR: %4.2f | Ano: %d\n",
           r->id, r->nome, r->curso, r->cr, r->ano_ingresso);
}

int registroTamanho(void) {
    return (int) sizeof(Registro);
}
