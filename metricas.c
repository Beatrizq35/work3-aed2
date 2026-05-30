#include "metricas.h"
#include <string.h>

double metricasMedia(double *tempos, int n) {
    if (n <= 0) return 0.0;
    double soma = 0.0;
    int i;
    for (i = 0; i < n; i++) soma += tempos[i];
    return soma / n;
}

long lerMemoriaKB(void) {
    long kb = -1;
    FILE *f = fopen("/proc/self/status", "r");
    if (!f) return kb;
    char linha[256];
    while (fgets(linha, sizeof(linha), f)) {
        if (strncmp(linha, "VmRSS:", 6) == 0) {
            sscanf(linha + 6, "%ld", &kb);
            break;
        }
    }
    fclose(f);
    return kb;
}
