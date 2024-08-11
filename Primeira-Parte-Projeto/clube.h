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