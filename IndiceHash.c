#include "IndiceHash.h"

static int hashFn(int chave) {
    int h = chave % HASH_TAM;
    if (h < 0) h += HASH_TAM;
    return h;
}

IndiceHash *hashCriar(void) {
    IndiceHash *h = (IndiceHash *) malloc(sizeof(IndiceHash));
    if (!h) { perror("malloc IndiceHash"); exit(EXIT_FAILURE); }
    int i;
    for (i = 0; i < HASH_TAM; i++) h->tabela[i] = NULL;
    h->totalColisoes = 0;
    return h;
}

void hashInserir(IndiceHash *h, int chave, long num_reg) {
    int idx = hashFn(chave);
    if (h->tabela[idx] != NULL)
        h->totalColisoes++;

    NoCelula *novo = (NoCelula *) malloc(sizeof(NoCelula));
    if (!novo) { perror("malloc NoCelula"); exit(EXIT_FAILURE); }
    novo->chave   = chave;
    novo->num_reg = num_reg;
    novo->prox    = h->tabela[idx];
    h->tabela[idx] = novo;
}

long hashBuscar(IndiceHash *h, int chave) {
    int idx = hashFn(chave);
    NoCelula *p = h->tabela[idx];
    while (p) {
        if (p->chave == chave) return p->num_reg;
        p = p->prox;
    }
    return -1;
}

void hashImprimir(IndiceHash *h) {
    int i;
    printf("=== Tabela Hash (buckets ocupados) ===\n");
    for (i = 0; i < HASH_TAM; i++) {
        if (h->tabela[i]) {
            printf("  [%4d]: ", i);
            NoCelula *p = h->tabela[i];
            while (p) {
                printf("<chave=%d, reg=%ld> ", p->chave, p->num_reg);
                p = p->prox;
            }
            printf("\n");
        }
    }
    printf("  Total de colisoes: %d\n", h->totalColisoes);
}

int hashColisoes(IndiceHash *h) {
    return h->totalColisoes;
}

void hashDestruir(IndiceHash *h) {
    int i;
    for (i = 0; i < HASH_TAM; i++) {
        NoCelula *p = h->tabela[i];
        while (p) {
            NoCelula *tmp = p->prox;
            free(p);
            p = tmp;
        }
    }
    free(h);
}
