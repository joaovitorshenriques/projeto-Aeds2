#include <stdlib.h>
#include <stdio.h>

typedef struct Admin{
    int id;
    int cpf;
    char nome[100];
    char email[200];
} TAdmin;

TAdmin *criarAdmin(int id, int cpf, char *nome, char *email);

void salvaAdmin(TAdmin *admin, FILE *out);

void imprimeAdmin(TAdmin *admin);

void *leAdmin(FILE *out);

int insereMultiplosAdmins(FILE *out);

void *leAdminsEImprime(FILE *in);

int tamanhoRegistroAdmin();

int tamanhoArquivoAdmin(FILE *arq);

TAdmin *buscaSequencialAdmin(int chave, FILE *in);

TAdmin *buscaBinariaAdmin(int chave, FILE *in, int inicio, int fim);
