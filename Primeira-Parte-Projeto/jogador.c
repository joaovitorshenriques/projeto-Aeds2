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

void salvaJogador(TJogador *jogador, FILE *out) {
    fwrite(&jogador->id, sizeof(int), 1, out);
    fwrite(jogador->nome, sizeof(char), sizeof(jogador->nome), out);
    fwrite(jogador->posicao, sizeof(char), sizeof(jogador->posicao), out);
    fwrite(&jogador->idade, sizeof(int), 1, out);
    fwrite(&jogador->salario, sizeof(double), 1, out);
	fwrite(&jogador->valorDeMercado, sizeof(double), 1, out);
	fwrite(&jogador->nota, sizeof(float), 1, out);
	fwrite(jogador->contrato, sizeof(char), sizeof(jogador->contrato), out);

	fwrite(&jogador->clube.id, sizeof(int), 1, out);
	fwrite(jogador->clube.nome, sizeof(char), sizeof(jogador->clube.nome), out);
}

TJogador *leJogador(FILE *out) {
    TJogador *jogador = (TJogador *) malloc(sizeof(TJogador));
    if (0 >= fread(&jogador->id, sizeof(int), 1, out)) {
        free(jogador);
        return NULL;
    }
    fread(jogador->nome, sizeof(char), sizeof(jogador->nome), out);
    fread(jogador->posicao, sizeof(char), sizeof(jogador->posicao), out);
    fread(&jogador->idade, sizeof(int), 1, out);
    fread(&jogador->salario, sizeof(double), 1, out);
	fread(&jogador->valorDeMercado, sizeof(double), 1, out);
	fread(&jogador->nota, sizeof(float), 1, out);
	fread(jogador->contrato, sizeof(char), sizeof(jogador->contrato), out);

	fread(&jogador->clube.id, sizeof(int), 1, out);
	fread(jogador->clube.nome, sizeof(char), sizeof(jogador->clube.nome), out);
    return jogador;
}

void imprime(TJogador *jogador) {
	printf("\n------------JOGADOR------------");

   printf("\nCodigo: ");
    printf("%d", jogador->id);
    printf("\nNome: ");
    printf("%s", jogador->nome);
    printf("\nPosicao: ");
    printf("%s", jogador->posicao);
    printf("\nIdade: ");
    printf("%d", jogador->idade);
    printf("\nSalario R$: ");
    printf("%4.2f", jogador->salario);
	printf("\nValor de Mercado R$: ");
    printf("%4.2f", jogador->valorDeMercado);
	printf("\nNota: ");
    printf("%4.2f", jogador->nota);
	printf("\nContrato: ");
    printf("%s", jogador->contrato);

	printf("\n------------CLUBE------------");
	printf("\nID do Clube: ");
    printf("%d", jogador->clube.id);
	printf("\nNome do Clube: ");
    printf("%s", jogador->clube.nome);
    printf("\n------------------------------------\n");
}

void leJogadoresEImprime(FILE *in) {
    printf("\n\nLendo jogadores do arquivo...\n\n");
    rewind(in);
    TJogador *f;
    while ((f = leJogador(in)) != NULL) {
        imprime(f);
        free(f);
    }
}

int insereMultiplosJogadores(FILE *out){

    int contador = 0;
    printf("Informe quantos jogadores deseja inserir: ");
    scanf("%d",&contador);

    srand(time(NULL));

    int *numeros = malloc(contador*sizeof(int));

    for(int i = 0; i < contador; i++){
        numeros[i] = i + 1;
    }

    //Embaralha os números
    for(int i = contador - 1; i > 0; i--){
        int j = rand()%(i+1);
        int temp = numeros[i];
        numeros[i] = numeros[j];
        numeros[j] = temp;
    }

    int x = 0;
    for(int i = 0; i < contador; i = i + 10){
        TClube *clube1 = criarClube(4,"Botafogo");
        TClube *clube2 = criarClube(11,"Flamengo");
        TClube *clube3 = criarClube(9,"Fortaleza");
        TClube *clube4 = criarClube(1,"Palmeiras");
        TClube *clube5 = criarClube(15,"Cruzeiro");
        TClube *clube6 = criarClube(10,"São Paulo");
        TClube *clube7 = criarClube(2,"Bahia");
        TClube *clube8 = criarClube(3,"CAP");
        TClube *clube9 = criarClube(7,"Atletico-MG");
        TClube *clube10 = criarClube(17,"Bragantino");
        TClube *clube11 = criarClube(5,"Vasco");
        TClube *clube12 = criarClube(20,"Criciuma");
        TClube *clube13 = criarClube(13,"Juventude");
        TClube *clube14 = criarClube(6,"Gremio");
        TClube *clube15 = criarClube(16,"Vitoria");
        TClube *clube16 = criarClube(12,"Internacional");
        TClube *clube17 = criarClube(19,"Fluminense");
        TClube *clube18 = criarClube(8,"Corithians");
        TClube *clube19 = criarClube(14,"Cuiaba");
        TClube *clube20 = criarClube(18,"Atletico-GO");
        TClube *clube21 = criarClube(0,"");

        if(x<contador){
        TJogador *jogador1 = criaJogador(numeros[x],"Joao","Goleiro",24,37000,190000,7.3,"Livre no Mercado",clube7);
        x++;
        salvaJogador(jogador1,out);
        free(jogador1);
        }

        if(x<contador){
        TJogador *jogador2 = criaJogador(numeros[x],"Junnyor","Zagueiro",30,35000,189000,7.5,"Contrato ate 2025",clube5);
        x++;
        salvaJogador(jogador2,out);
        free(jogador2);
        }

        if(x<contador){
        TJogador *jogador3 = criaJogador(numeros[x],"Lucas","Atacante",22,42000,220000,8.0,"Contrato ate 2025",clube1);
         x++;
        salvaJogador(jogador3,out);
        free(jogador3);
        }

        if(x<contador){
        TJogador *jogador4 = criaJogador(numeros[x],"Amaral","Lateral-Direito",21,32500,190000,6.2,"Fim de 2024",clube10);
         x++;
        salvaJogador(jogador4,out);
        free(jogador4);
        }

        if(x<contador){
        TJogador *jogador5 = criaJogador(numeros[x],"Athus","Lateral-Esquerdo",20,39000,192000,4.5,"Contrato ate 2026",clube20);
         x++;
        salvaJogador(jogador5,out);
        free(jogador5);
        }

        if(x<contador){
        TJogador *jogador6 = criaJogador(numeros[x],"Mayke","Meio-Campo",21,40000,21000,5.5,"Livre no mercado",clube21);
         x++;
        salvaJogador(jogador6,out);
        free(jogador6);
        }

        if(x<contador){
        TJogador *jogador7 = criaJogador(numeros[x],"Richardy","Volante",21,33000,195000,7.2,"Fim de 2024",clube14);
         x++;
        salvaJogador(jogador7,out);
        free(jogador7);
        }

        if(x<contador){
        TJogador *jogador8 = criaJogador(numeros[x],"Emerson","Zagueiro",26,34000,178000,5.6,"Livre no mercado",clube21);
         x++;
        salvaJogador(jogador8,out);
        free(jogador8);
        }

        if(x<contador){
        TJogador *jogador9 = criaJogador(numeros[x],"Leonardo","Goleiro",23,39000,192000,6.8,"Contrato ate 2025",clube12);
         x++;
        salvaJogador(jogador9,out);
        free(jogador9);
        }

        if(x<contador){
        TJogador *jogador10 = criaJogador(numeros[x],"Mateus","Atacante",24,43000,215000,6.7,"Contrato ate 2026",clube19);
         x++;
        salvaJogador(jogador10,out);
        free(jogador10);
        }
    }

}
