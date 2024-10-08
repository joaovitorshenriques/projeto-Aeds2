#include <stdlib.h>
#include <stdio.h>
#include "clube.h"

typedef struct Jogador{
    int id;
    char nome[100];
    char posicao[50];
    int idade;
    double salario;
    double valorDeMercado;
    float nota;
    char contrato[100];
    TClube clube;
} TJogador;

TJogador *criaJogador(int id, char *nome, char *posicao, int idade, double salario,double valorMercado, float score, char *contrato, TClube *clube);

void salvaJogador(TJogador *jogador, FILE *out);

TJogador *leJogador(FILE *out);

void leJogadoresEImprime(FILE *in);

void embaralhar(int *array, int tamanho);

int insereMultiplosJogadores(FILE *out);

void leJogadoresEImprime(FILE *in);

TJogador *buscaSequencialJogador(int chave, FILE *in);

TJogador *buscaBinariaJogador(int chave, FILE *in, int inicio, int fim);

int tamanhoRegistroJogador();

int tamanhoArquivoJogador(FILE *arq);

void mergeJogador(FILE *arq, int left, int mid, int right);

void mergeSortJogador(FILE *arq,int left,int right);

void mergeSortDiscoJogador(FILE*arq);

void pesquisarJogadoresPorClube(FILE *out);

void transferenciaDeJogador(FILE *in, FILE * clube);
