#ifndef REGISTRO_H
#define REGISTRO_H

typedef struct {
    int matricula;      // Chave
    int idade;          // Atributo informativo
    float cr;           // Atributo Não-Chave
    char nome[50];
    char curso[30];
    char email[40];
} Registro;

void criarArquivoTeste(const char* nomeArquivo, int quantidade);
void imprimirRegistro(Registro r);

#endif
