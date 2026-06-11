#ifndef INDICE_HASH_H
#define INDICE_HASH_H

#define HASH_SIZE 4493 // Tamanho primo para gerar algumas colisões

typedef struct NoHash {
    int chave;
    int rrn;
    struct NoHash* prox;
} NoHash;

typedef struct {
    NoHash* tabela[HASH_SIZE];
    int colisoes; // Contador de colisões
} TabelaHash;

void inicializarHash(TabelaHash* th);
void inserirHash(TabelaHash* th, int chave, int rrn);
int buscarHash(TabelaHash* th, int chave);
void imprimirHash(TabelaHash* th);

#endif
