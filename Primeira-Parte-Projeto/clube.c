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

int tamanhoRegistroClube(){
    return sizeof(int)
    + sizeof(char) * 100;
}

int tamanhoArquivoClube(FILE *arq){
  fseek(arq, 0, SEEK_END);
  int tam = trunc(ftell(arq) / tamanhoRegistroClube());
  return tam;
}

TClube *buscaSequencialClube(int chave, FILE *in){

    TClube *clube;
    int achou,contador = 0;
    rewind(in);
    clock_t start, end;
    while ((clube = leClube(in)) != NULL){
        contador ++;
        start = clock();
        if(clube->id == chave){
          printf("Clube Encontrado!\n");
            imprimeClube(clube);
            achou = 1;
            break;
        }
    }
    free(clube);
    end = clock();
    double tempo = (double)(end- start) / CLOCKS_PER_SEC;
    if(achou){
    printf("\nTempo de execucao da busca: %.2f segundos\n", tempo);
    printf("Numero de comparacoes: %d\n", contador);
    } else {
        printf("Clube nao pertence a base de dados!...");
        printf("\nNumero de comparacoes: %d\n", contador);
    }
}

TClube *buscaBinariaClube(int chave, FILE *in, int inicio, int fim) {

    TClube *clube = NULL;
    int cod = -1;
    int contador = 0;
    clock_t start,end;

    start = clock();
    while (inicio <= fim && cod != chave) {

        int meio = (inicio + fim) / 2;
        fseek(in,meio* tamanhoRegistroClube(),SEEK_SET);
        clube= leClube(in);
        cod = clube->id;

        if (clube) {
            if (cod > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
    }

    if (cod == chave) {
        printf("\nClube Encontrado!\n");
        imprimeClube(clube);
        end = clock();
        double tempo = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\nTempo de execucao: %.2f segundos\n", tempo);
        printf("Numero de comparacoes: %d\n", contador);
        return clube;
    }
    else{
        printf("Clube nao pertence a base de dados!...\n");
        printf("Numero de comparacoes: %d\n", contador);
        return NULL;
    }

    free(clube);
}

