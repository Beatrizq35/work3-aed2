#ifndef METRICAS_H
#define METRICAS_H

#include <stdio.h>
#include <time.h>

/* ================================================================
 * TAD Metricas
 * Medição de tempo usando time() conforme orientação do professor.
 * start = time(NULL)  /  end = time(NULL)
 * diferença em segundos = (double)(end - start) / CLOCKS_PER_SEC
 * ================================================================ */

double metricasMedia(double *tempos, int n);

long lerMemoriaKB(void);

#endif /* METRICAS_H */
