#include "Registro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void criarArquivoTeste(const char* nomeArquivo, int quantidade) {
    FILE *arq = fopen(nomeArquivo, "wb");
    if (!arq) return;

    const char *nomes[] = {"Maria", "Debora", "Joao", "Ana", "Carlos", "Beatriz", "Lucas", "Fernanda", "Rafael", "Juliana"};
    const char *sobrenomes[] = {"Silva", "Rodrigues", "Santos", "Oliveira", "Souza", "Lima", "Ferreira", "Costa"};
    const char *cursos[] = {"Computacao", "Arquitetura", "Psicologia", "Design", "Matematica", "Nutricao"};

    for (int i = 0; i < quantidade; i++) {
        Registro r;
        r.matricula = 1000 + i;
        r.idade = 18 + (rand() % 40);
        r.cr = (float)(rand() % 100) / 10.0; // CR de 0.0 a 10.0
        
        sprintf(r.nome, "%s %s", nomes[rand() % 10], sobrenomes[rand() % 8]);
        sprintf(r.curso, "%s", cursos[rand() % 6]);
        sprintf(r.email, "aluno%d@ufam.edu.br", r.matricula);
        
        fwrite(&r, sizeof(Registro), 1, arq);
    }
    fclose(arq);
}

void imprimirRegistro(Registro r) {
    printf("Matrícula: %d | Idade: %d | CR: %.1f | Nome: %s\n", r.matricula, r.idade, r.cr, r.nome);
}
