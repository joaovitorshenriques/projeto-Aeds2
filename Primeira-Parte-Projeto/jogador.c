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

TJogador *buscaSequencialJogador(int chave, FILE *in){

    TJogador *jogador;
    int achou,contador = 0;
    rewind(in);
    clock_t start, end;
    while ((jogador = leJogador(in)) != NULL){
        contador ++;
        start = clock();
        if(jogador->id == chave){
          printf("Jogador Encontrado!\n");
            imprime(jogador);
            achou = 1;
            break;
        }
    }
    free(jogador);
    end = clock();
    double tempo = (double)(end- start) / CLOCKS_PER_SEC;
    if(achou){
    printf("\nTempo de execucao da busca: %.2f segundos\n", tempo);
    printf("Numero de comparacoes: %d\n", contador);
    } else {
        printf("Jogador nao pertence a base de dados!...");
        printf("\nNumero de comparacoes: %d\n", contador);
    }
}

TJogador *buscaBinariaJogador(int chave, FILE *in, int inicio, int fim) {

    TJogador *jogador = NULL;
    int cod = -1;
    int contador = 0;
    clock_t start,end;

    start = clock();
    while (inicio <= fim && cod != chave) {

        int meio = (inicio + fim) / 2;
        fseek(in,meio* tamanhoRegistroJogador(),SEEK_SET);
        jogador= leJogador(in);
        cod = jogador->id;

        if (jogador) {
            if (cod > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
    }

    if (cod == chave) {
        printf("\nJogador Encontrado!\n");
        imprime(jogador);
        end = clock();
        double tempo = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\nTempo de execucao: %.2f segundos\n", tempo);
        printf("Numero de comparacoes: %d\n", contador);
        return jogador;
    }
    else{
        printf("Jogador nao pertence a base de dados!...\n");
        printf("Numero de comparacoes: %d\n", contador);
        return NULL;
    }

    free(jogador);
}



int tamanhoRegistroJogador() {
    return sizeof(int) + sizeof(char) * 100 + sizeof(char) * 50 + sizeof(int)
    + sizeof(double) * 2 + sizeof(float) + sizeof(char) * 100 + sizeof(TClube);
}

int tamanhoArquivoJogador(FILE *arq) {
  fseek(arq, 0, SEEK_END);
  int tam = trunc(ftell(arq) / tamanhoRegistroJogador());
  return tam;
}

void mergeJogador(FILE *arq, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    FILE *tempFile1 = fopen("temp1.dat", "wb+");
    if (tempFile1 == NULL) {
        perror("Erro ao abrir temp1.dat");
        exit(1);
    }
    FILE *tempFile2 = fopen("temp2.dat", "wb+");
    if (tempFile2 == NULL) {
        perror("Erro ao abrir temp2.dat");
        exit(1);
    }

    // Jogando os dados em arquivos temporários
    for (int i = 0; i < n1; i++) {
        fseek(arq, (left + i) * tamanhoRegistroJogador(), SEEK_SET);
        TJogador *jogador = leJogador(arq);
        if (jogador == NULL) {
            perror("Erro ao ler jogador");
            exit(1);
        }
        salvaJogador(jogador, tempFile1);
        free(jogador);
    }

    for (int j = 0; j < n2; j++) {
        fseek(arq, (mid + 1 + j) * tamanhoRegistroJogador(), SEEK_SET);
        TJogador *jogador = leJogador(arq);
        if (jogador == NULL) {
            perror("Erro ao ler jogador");
            exit(1);
        }
        salvaJogador(jogador, tempFile2);
        free(jogador);
    }

    rewind(tempFile1);
    rewind(tempFile2);

    int i = 0, j = 0;
    int k = left;

    TJogador *jogador1 = leJogador(tempFile1);
    TJogador *jogador2 = leJogador(tempFile2);

    // Mesclando os arquivos de volta no arquivo original
    while (i < n1 && j < n2) {
        if (jogador1->id <= jogador2->id) {

            fseek(arq, k * tamanhoRegistroJogador(), SEEK_SET);
            salvaJogador(jogador1, arq);
            i++;
            if (i < n1) {
                jogador1 = leJogador(tempFile1);
            }
        } else {

            fseek(arq, k * tamanhoRegistroJogador(), SEEK_SET);
            salvaJogador(jogador2, arq);
            j++;
            if (j < n2) {
                jogador2 = leJogador(tempFile2);
            }
        }
        k++;
    }

    // Copiando os elementos restantes de tempFile1, se houver
    while (i < n1) {
        fseek(arq, k * tamanhoRegistroJogador(), SEEK_SET);
        salvaJogador(jogador1, arq);
        i++;
        if (i < n1) {
            jogador1 = leJogador(tempFile1);
        }
        k++;
    }

    // Copiando os elementos restantes de tempFile2, se houver
    while (j < n2) {
        fseek(arq, k * tamanhoRegistroJogador(), SEEK_SET);
        salvaJogador(jogador2, arq);
        j++;
        if (j < n2) {
            jogador2 = leJogador(tempFile2);
        }
        k++;
    }

    fclose(tempFile1);
    fclose(tempFile2);

    if (remove("temp1.dat") != 0) {
        perror("Erro ao remover temp1.dat");
    }
    if (remove("temp2.dat") != 0) {
        perror("Erro ao remover temp2.dat");
    }

}

// Função principal do Merge Sort
void mergeSortJogador(FILE *arq, int left, int right) {


    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordena a primeira metade
        mergeSortJogador(arq, left, mid);

        // Ordena a segunda metade
        mergeSortJogador(arq, mid + 1, right);

        // Mescla as duas metades
        mergeJogador(arq, left, mid, right);
    }

}

// Função a ser chamada
void mergeSortDiscoJogador(FILE *arq) {
    int tam = tamanhoArquivoJogador(arq);

    mergeSortJogador(arq, 0, tam - 1);

    fflush(arq);
}

void pesquisarJogadoresPorClube(FILE *out){
    int contador = 0;
    printf("Informe o codigo do clube que deseja visualizar os jogadores: ");
    scanf("%d", &contador);

    rewind(out);
    TJogador *jogador;

    while ((jogador = leJogador(out)) != NULL) {
        if(jogador->clube.id == contador){
            imprime(jogador);
            free(jogador);
        }
    }
}

void transferenciaDeJogador(FILE *in, FILE * clube){
    int contador = 0;
    int flag = 0;
    int codigoClube;
    printf("Informe o codigo do jogador que deseja contratar: \n");
    scanf("%d", &contador);

    rewind(in);
    TJogador *jogador;
    while ((jogador = leJogador(in)) != NULL) {
        if(jogador->id == contador){
            imprime(jogador);

            printf("Deseja realizar a contratacao do jogador?: \n");
            printf("1 SIM\n");
            printf("2 NAO\n");
            scanf("%d", &flag);

            if(flag == 1){
                printf("Informe o codigo do clube para finalizar a contratacao do jogador: \n");
                scanf("%d", &codigoClube);

                TClube *clubeTransferencia = pesquisarClubePorCodigo(clube, codigoClube);

                if(clubeTransferencia->id != -1){
                    strcpy(jogador->clube.nome, clubeTransferencia->nome);
                    jogador->clube.id = clubeTransferencia->id;
                    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> JOGADOR TRANSFERIDO <<<<<<<<<<<<<<<<<<<<<<<<\n");
                    imprime(jogador);
                }

                } else {
                    printf("Clube nao encontrado, transacao cancelada! \n");
                }
                printf("Contratacao realizada com sucesso!\n");


                return ;
            } else if(flag == 2){
                printf("Contratacao cancelada!\n");
                return ;
            }
        }
        printf("Jogador nao encontrado na base de dados\n");
}