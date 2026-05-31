#include "Registro.h"
#include <stdlib.h>
#include <string.h>

void criarArquivoTeste(const char* nomeArquivo, int quantidade) {
    FILE *arq = fopen(nomeArquivo, "wb");
    if (!arq) return;

    // 1. Criando os vetores base (adicione quantos quiser)
    const char *nomes[] = {"Maria", "Debora", "Joao", "Ana", "Carlos", "Beatriz", "Lucas", "Fernanda", "Rafael",
    "Juliana", "Pedro", "Mariana", "Gabriel", "Camila", "Mateus", "Leticia", "Thiago", "Amanda", "Rodrigo", "Bruna", 
    "Felipe", "Jessica", "Guilherme", "Natalia", "Marcelo", "Vanessa", "Bruno", "Aline", "Gustavo", "Carolina", 
    "Eduardo", "Patricia", "Leonardo", "Bianca", "Diego", "Gabriela", "Vitor", "Larissa", "Henrique", "Renata"};
    
    const char *sobrenomes[] = {"Silva", "Rodrigues", "Santos", "Oliveira", "Souza", "Lima", "Ferreira", "Costa", "Gomes", "Martins",
    "Pereira", "Almeida", "Carvalho", "Ribeiro", "Mendes", "Alves", "Rocha", "Pinto", "Monteiro", "Castro", 
    "Araujo", "Barros", "Freitas", "Barbosa", "Cardoso", "Teixeira", "Cavalcanti", "Dias", "Moreira", "Nogueira", 
    "Vieira", "Machado", "Neves", "Batista", "Borges", "Marques", "Moraes", "Ramos", "Farias", "Correia"
    };
    
    // Novo vetor com as opções de curso
    const char *cursos[] = {"Computacao", "Arquitetura", "Psicologia", "Design", "Matematica",
    "Design","Nutricao", "Enfermagem", "Eletrotecnica", "Mecatronica", "Gastronomia", "Estetica"
    };

    // Calcula automaticamente o tamanho dos vetores para o rand()
    int qtdNomes = sizeof(nomes) / sizeof(nomes[0]);
    int qtdSobrenomes = sizeof(sobrenomes) / sizeof(sobrenomes[0]);
    int qtdCursos = sizeof(cursos) / sizeof(cursos[0]); // Calcula a quantidade de cursos

    for (int i = 0; i < quantidade; i++) {
        Registro r;
        r.matricula = 1000 + i; 
        r.idade = 18 + (rand() % 40); 

        // 2. Sorteando índices aleatórios baseados no tamanho dos vetores
        int indiceNome = rand() % qtdNomes;
        int indiceSobrenome = rand() % qtdSobrenomes;
        int indiceCurso = rand() % qtdCursos; // Sorteia o curso

        // 3. Juntando o nome e o sobrenome com um espaço no meio usando %s
        sprintf(r.nome, "%s %s", nomes[indiceNome], sobrenomes[indiceSobrenome]);
        
        // Usando o %s para injetar o curso sorteado
        sprintf(r.curso, "%s", cursos[indiceCurso]);
        
        // Mantendo o email com a matrícula para garantir que seja único e evitar e-mails repetidos
        sprintf(r.email, "aluno%d@ufam.edu.br", r.matricula);
        
        fwrite(&r, sizeof(Registro), 1, arq);
    }
    fclose(arq);
}

void imprimirRegistro(Registro r) {
    printf("Matricula: %d | Idade: %d | Nome: %s\n", r.matricula, r.idade, r.nome);
}



