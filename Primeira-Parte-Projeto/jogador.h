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

