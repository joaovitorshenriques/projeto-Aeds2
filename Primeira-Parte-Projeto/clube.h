#include <stdlib.h>
#include <stdio.h>

typedef struct Clube{
    int id;
    char nome[100];
} TClube;


TClube *criarClube(int id, char *nome);

void salvaClube(TClube *clube, FILE *out);

void *leClube(FILE *out);

void insereClubes(FILE *out);

void imprimeClube(TClube *clube);

void leClubesEImprime(FILE *in);

int tamanhoRegistroClube();

int tamanhoArquivoClube(FILE *arq);

TClube *buscaSequencialClube(int chave, FILE *in);

TClube *buscaBinariaClube(int chave, FILE *in, int inicio, int fim);

void mergeClube(FILE *arq, int left, int mid, int right);

void mergeSortClube(FILE *arq, int left, int right);

void mergeSortDiscoClube(FILE *arq);