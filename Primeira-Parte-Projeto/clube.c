#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include "clube.h"


TClube *criarClube(int id, char *nome){
    TClube *clube = (TClube *) malloc(sizeof(TClube));
    if (clube) memset(clube, 0, sizeof(TClube));
    clube->id = id;
    strcpy(clube->nome, nome);
    return clube;
}