#include "admin.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

TAdmin *criarAdmin(int id, int cpf, char *nome, char *email){
    TAdmin *admin = (TAdmin *) malloc(sizeof(TAdmin));
    if (admin) memset(admin, 0, sizeof(TAdmin));
    admin->id = id;
    admin->cpf = cpf;
    strcpy(admin->nome, nome);
    strcpy(admin->email, email);
    return admin;
}

TAdmin *criarAdmin(int id, int cpf, char *nome, char *email){
    TAdmin *admin = (TAdmin *) malloc(sizeof(TAdmin));
    if (admin) memset(admin, 0, sizeof(TAdmin));
    admin->id = id;
    admin->cpf = cpf;
    strcpy(admin->nome, nome);
    strcpy(admin->email, email);
    return admin;
}

void salvaAdmin(TAdmin *admin, FILE *out){
    fwrite(&admin->id, sizeof(int), 1, out);
    fwrite(&admin->cpf, sizeof(int), 1, out);
    fwrite(admin->nome, sizeof(char), sizeof(admin->nome), out);
    fwrite(admin->email, sizeof(char), sizeof(admin->email), out);
}

void imprimeAdmin(TAdmin *admin) {
    printf("\n***********************admin*******************************");
    printf("\nCodigo: ");
    printf("%d", admin->id);
    printf("\nNome: ");
    printf("%s", admin->nome);
    printf("\nCPF: ");
    printf("%d", admin->cpf);
    printf("\nEmail: ");
    printf("%s", admin->email);
    printf("\n*************************************************************\n");
}

void *leAdmin(FILE *out){
    TAdmin *admin = (TAdmin *) malloc(sizeof(TAdmin));
    if (0 >= fread(&admin->id, sizeof(int), 1, out)) {
        free(admin);
        return NULL;
    }
    fread(&admin->cpf, sizeof(int), 1, out);
    fread(admin->nome, sizeof(char), sizeof(admin->nome), out);
    fread(admin->email, sizeof(char), sizeof(admin->email), out);
    return admin;
}


int insereMultiplosAdmins(FILE *out) {
    int contador = 0;
    printf("Informe quantos olheiros deseja cadastrar: ");
    scanf("%d", &contador);

    srand(time(NULL));

    int *numeros = malloc(contador * sizeof(int));

    for (int i = 0; i < contador; i++) {
        numeros[i] = i + 1;
    }

    for (int i = contador - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = numeros[i];
        numeros[i] = numeros[j];
        numeros[j] = temp;
    }

    int x = 0;
    for (int i = 0; i < contador; i = i + 2) {
        TAdmin *admin1 = criarAdmin(numeros[x], 00-000-000-00, "Joao", "joao.com");
        x++;

        TAdmin *admin2 = criarAdmin(numeros[x], 00-000-000-00, "Junnyor", "junnyor.com");
        x++;

        salvaAdmin(admin1, out);
        salvaAdmin(admin2, out);
        free(admin1);
        free(admin2);
    }
    free(numeros);
    return contador;
}

void *leAdminsEImprime(FILE *in) {
    printf("\n\nLendo olheiros do arquivo...\n\n");
    rewind(in);
    TAdmin *admin;
    while ((admin = leAdmin(in)) != NULL) {
        imprimeAdmin(admin);
        free(admin);
    }
}

int tamanhoRegistroAdmin() {
    return sizeof(int) + sizeof(int) + sizeof(char) * 100 + sizeof(char) * 200;
}

int tamanhoArquivoAdmin(FILE *arq) {
  fseek(arq, 0, SEEK_END);
  int tam = trunc(ftell(arq) / tamanhoRegistroAdmin());
  return tam;
}

TAdmin *buscaSequencialAdmin(int chave, FILE *in){

    TAdmin *admin;
    int achou,contador = 0;
    rewind(in);
    clock_t start, end;
    while ((admin = leAdmin(in)) != NULL){
        contador ++;
        start = clock();
        if(admin->id == chave){
          printf("admin Encontrado!\n");
            imprimeAdmin(admin);
            achou = 1;
            break;
        }
    }
    free(admin);
    end = clock();
    double tempo = (double)(end- start) / CLOCKS_PER_SEC;
    if(achou){
    printf("\nTempo de execucao da busca: %.2f segundos\n", tempo);
    printf("Numero de comparacoes: %d\n", contador);
    } else {
        printf("admin nao pertence a base de dados!...");
        printf("\nNumero de comparacoes: %d\n", contador);
    }
}


TAdmin *buscaBinariaAdmin(int chave, FILE *in, int inicio, int fim) {

    TAdmin *admin = NULL;
    int cod = -1;
    int contador = 0;
    clock_t start,end;

    start = clock();
    while (inicio <= fim && cod != chave) {

        int meio = (inicio + fim) / 2;
        fseek(in,meio* tamanhoRegistroAdmin(),SEEK_SET);
        admin= leAdmin(in);
        cod = admin->id;

        if (admin) {
            if (cod > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
    }

    if (cod == chave) {
        printf("\nadmin Encontrado!\n");
        imprimeAdmin(admin);
        end = clock();
        double tempo = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\nTempo de execucao: %.2f segundos\n", tempo);
        printf("Numero de comparacoes: %d\n", contador);
        return admin;
    }
    else{
        printf("admin nao pertence a base de dados!...\n");
        printf("Numero de comparacoes: %d\n", contador);
        return NULL;
    }

    free(admin);
}
