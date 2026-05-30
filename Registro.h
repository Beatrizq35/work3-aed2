#ifndef REGISTRO_H
#define REGISTRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================
 * TAD Registro
 * Representa um aluno gravado em disco.
 * Campos:
 *   id          — chave primária única (int)
 *   nome        — char[40]
 *   curso       — char[20]
 *   cr          — double (usado em consultas > < >= <=)
 *   ano_ingresso— int
 * Tamanho fixo: ~80 bytes por registro.
 * ================================================================ */

#define REG_TAM_NOME   40
#define REG_TAM_CURSO  20

typedef struct {
    int    id;
    char   nome[REG_TAM_NOME];
    char   curso[REG_TAM_CURSO];
    double cr;
    int    ano_ingresso;
} Registro;

void registroEscrever(FILE *arq, long pos, const Registro *r);
void registroLer     (FILE *arq, long pos, Registro *r);
void registroImprimir(const Registro *r);
int  registroTamanho (void);

#endif /* REGISTRO_H */
