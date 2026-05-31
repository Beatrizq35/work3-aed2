#ifndef REGISTRO_H
#define REGISTRO_H

#include <stdio.h>

// Tamanho aproximado: 4 + 4 + 50 + 30 + 40 = 128 bytes
typedef struct {
    int matricula;      // Atributo Chave
    int idade;          // Atributo não-chave (para consultas de intervalo)
    char nome[50];
    char curso[30];
    char email[40];
} Registro;

void criarArquivoTeste(const char* nomeArquivo, int quantidade);
void imprimirRegistro(Registro r);

#endif