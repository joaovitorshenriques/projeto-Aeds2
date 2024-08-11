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
    int qtdClubes;

    printf("Quantas vezes deseja criar o conjunto de 20 clubes: ");
    scanf("%d",&qtdClubes);

    for(int i = 0; i < qtdClubes; i++){
        for (int j = 0; j < numClubes; j++){
            TClube*clube = criarClube(ids[j],nomes[j]);
            salvaClube(clube,out);
            free(clube);
            fflush(out);
        }
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

void mergeClube(FILE *arq, int left, int mid, int right){
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
        fseek(arq, (left + i) * tamanhoRegistroClube(), SEEK_SET);
        TClube *clube = leClube(arq);
        if (clube == NULL) {
            perror("Erro ao ler Clube");
            exit(1);
        }
        salvaClube(clube, tempFile1);
        free(clube);
    }

    for (int j = 0; j < n2; j++) {
        fseek(arq, (mid + 1 + j) * tamanhoRegistroClube(), SEEK_SET);
        TClube *clube = leClube(arq);
        if (clube == NULL) {
            perror("Erro ao ler Clube");
            exit(1);
        }
        salvaClube(clube, tempFile2);
        free(clube);
    }

    rewind(tempFile1);
    rewind(tempFile2);

    int i = 0, j = 0;
    int k = left;

    TClube *clube1 = leClube(tempFile1);
    TClube *clube2 = leClube(tempFile2);

    // Mesclando os arquivos de volta no arquivo original
    while (i < n1 && j < n2) {
        if (clube1->id <= clube2->id) {

            fseek(arq, k * tamanhoRegistroClube(), SEEK_SET);
            salvaClube(clube1, arq);
            i++;
            if (i < n1) {
                clube1 = leClube(tempFile1);
            }
        } else {

            fseek(arq, k * tamanhoRegistroClube(), SEEK_SET);
            salvaClube(clube2, arq);
            j++;
            if (j < n2) {
                clube2 = leClube(tempFile2);
            }
        }
        k++;
    }

    // Copiando os elementos restantes de tempFile1, se houver
    while (i < n1) {
        fseek(arq, k * tamanhoRegistroClube(), SEEK_SET);
        salvaClube(clube1, arq);
        i++;
        if (i < n1) {
            clube1 = leClube(tempFile1);
        }
        k++;
    }

    // Copiando os elementos restantes de tempFile2, se houver
    while (j < n2) {
        fseek(arq, k * tamanhoRegistroClube(), SEEK_SET);
        salvaClube(clube2, arq);
        j++;
        if (j < n2) {
            clube2 = leClube(tempFile2);
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
void mergeSortClube(FILE *arq, int left, int right) {


    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordena a primeira metade
        mergeSortClube(arq, left, mid);

        // Ordena a segunda metade
        mergeSortClube(arq, mid + 1, right);

        // Mescla as duas metades
        mergeClube(arq, left, mid, right);
    }

}

// Função a ser chamada
void mergeSortDiscoClube(FILE *arq) {
    clock_t start,end;
    start = clock();
    int tam = tamanhoArquivoClube(arq);

    mergeSortClube(arq, 0, tam - 1);
    fflush(arq);
    end = clock();
    double tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTempo de ordenacao: %.2f segundos\n", tempo);
}

TClube* pesquisarClubePorCodigo(FILE *in, int codigoClube){
    int flag = 0;

    rewind(in);
    TClube *clube;
    while ((clube = leClube(in)) != NULL){
        if(clube->id == codigoClube){
            imprimeClube(clube);
            return clube;
        }
    }
    clube->id = -1;
    return clube;
}
