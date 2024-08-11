#include "jogador.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

TJogador *criaJogador(int id, char *nome, char *posicao, int idade, double salario,double valorMercado, float score, char *contrato, TClube *clube) {
    TJogador *jogador = (TJogador *) malloc(sizeof(TJogador));
    if (jogador) memset(jogador, 0, sizeof(TJogador));
    jogador->id = id;
    strcpy(jogador->nome, nome);
    strcpy(jogador->posicao, posicao);
	jogador->idade = idade;
	jogador->salario = salario;
	jogador->valorDeMercado = valorMercado;
	jogador->nota = score;
    strcpy(jogador->contrato, contrato);

	jogador->clube.id = clube->id;
	strcpy(jogador->clube.nome, clube->nome);
    return jogador;
}

