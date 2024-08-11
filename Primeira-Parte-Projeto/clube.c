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

void salvaClube(TClube *clube, FILE *out){
    fwrite(&clube->id, sizeof(int), 1, out);
    fwrite(clube->nome, sizeof(char), sizeof(clube->nome), out);
}

void *leClube(FILE *out){
    TClube *clube = (TClube *) malloc(sizeof(TClube));
    if (0 >= fread(&clube->id, sizeof(int), 1, out)) {
        free(clube);
        return NULL;
    }
    fread(clube->nome, sizeof(char), sizeof(clube->nome), out);
    return clube;
}

void insereClubes(FILE *out){

    int ids [] = {4,11,9,1,15,10,2,3,7,17,5,20,13,6,16,12,19,8,14,18};
    char *nomes[ ] = {"Botafogo","Flamengo","Fortaleza","Palmeiras","Cruzeiro","Sao Paulo","Bahia","CAP","Atletico-MG","Bragantino","Vasco","Criciuma","Juventude","Gremio","Vitoria","Internacional","Fluminense","Corinthians","Cuiaba","Atletico-GO"};

    int numClubes = sizeof(ids)/sizeof(ids[0]);

    for (int i = 0; i < numClubes; i++){
        TClube*clube = criarClube(ids[i],nomes[i]);
        salvaClube(clube,out);
        free(clube);
        fflush(out);
    }
}

void leClubesEImprime(FILE *in){
    printf("\n\nLendo clubes do arquivo...\n\n");
    rewind(in);
    TClube *c;
    while ((c = leClube(in)) != NULL){
        imprimeClube(c);
        free(c);
    }
}

void imprimeClube(TClube *clube){
    printf("\n------CLUBE------");
	printf("\nCodigo do Clube: ");
    printf("%d", clube->id);
	printf("\nNome do Clube: ");
    printf("%s", clube->nome);
    printf("\n-------------------------------\n");
}