#include "metricas.h"
#include <time.h>

double obterTempoAtual() {
    // clock() retorna os ciclos de CPU. Dividimos por CLOCKS_PER_SEC 
    // logo na captura para retornar o tempo exato em segundos (com casas decimais).
    return ((double) clock()) / CLOCKS_PER_SEC;
}
