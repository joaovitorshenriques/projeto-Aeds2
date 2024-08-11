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
    printf("\n***********************Administrador*******************************");
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
    printf("Informe quantos administradores deseja cadastrar: ");
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
    printf("\n\nLendo administradores do arquivo...\n\n");
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
          printf("Administrador Encontrado!\n");
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
        printf("Administrador nao pertence a base de dados!...");
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
        printf("\nAdministrador Encontrado!\n");
        imprimeAdmin(admin);
        end = clock();
        double tempo = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\nTempo de execucao: %.2f segundos\n", tempo);
        printf("Numero de comparacoes: %d\n", contador);
        return admin;
    }
    else{
        printf("Administrador nao pertence a base de dados!...\n");
        printf("Numero de comparacoes: %d\n", contador);
        return NULL;
    }

    free(admin);
}

void mergeAdmin(FILE *arq, int left, int mid, int right){
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
        fseek(arq, (left + i) * tamanhoRegistroAdmin(), SEEK_SET);
        TAdmin *admin = leAdmin(arq);
        if (admin == NULL) {
            perror("Erro ao ler Admin");
            exit(1);
        }
        salvaAdmin(admin, tempFile1);
        free(admin);
    }

    for (int j = 0; j < n2; j++) {
        fseek(arq, (mid + 1 + j) * tamanhoRegistroAdmin(), SEEK_SET);
        TAdmin *admin = leAdmin(arq);
        if (admin == NULL) {
            perror("Erro ao ler Admin");
            exit(1);
        }
        salvaAdmin(admin, tempFile2);
        free(admin);
    }

    rewind(tempFile1);
    rewind(tempFile2);

    int i = 0, j = 0;
    int k = left;

    TAdmin *admin1 = leAdmin(tempFile1);
    TAdmin *admin2 = leAdmin(tempFile2);

    // Mesclando os arquivos de volta no arquivo original
    while (i < n1 && j < n2) {
        if (admin1->id <= admin2->id) {

            fseek(arq, k * tamanhoRegistroAdmin(), SEEK_SET);
            salvaAdmin(admin1, arq);
            i++;
            if (i < n1) {
                admin1 = leAdmin(tempFile1);
            }
        } else {

            fseek(arq, k * tamanhoRegistroAdmin(), SEEK_SET);
            salvaAdmin(admin2, arq);
            j++;
            if (j < n2) {
                admin2 = leAdmin(tempFile2);
            }
        }
        k++;
    }

    // Copiando os elementos restantes de tempFile1, se houver
    while (i < n1) {
        fseek(arq, k * tamanhoRegistroAdmin(), SEEK_SET);
        salvaAdmin(admin1, arq);
        i++;
        if (i < n1) {
            admin1 = leAdmin(tempFile1);
        }
        k++;
    }

    // Copiando os elementos restantes de tempFile2, se houver
    while (j < n2) {
        fseek(arq, k * tamanhoRegistroAdmin(), SEEK_SET);
        salvaAdmin(admin2, arq);
        j++;
        if (j < n2) {
            admin2 = leAdmin(tempFile2);
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
void mergeSortAdmin(FILE *arq, int left, int right) {


    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordena a primeira metade
        mergeSortAdmin(arq, left, mid);

        // Ordena a segunda metade
        mergeSortAdmin(arq, mid + 1, right);

        // Mescla as duas metades
        mergeAdmin(arq, left, mid, right);
    }

}

// Função a ser chamada
void mergeSortDiscoAdmin(FILE *arq) {
    int tam = tamanhoArquivoAdmin(arq);

    mergeSortAdmin(arq, 0, tam - 1);

    fflush(arq);
}

int validarAdmin(FILE *in){
    int codigo = 0;
    printf("Informe seu codigo de administrador: \n");
    scanf("%d", &codigo);

    rewind(in);
    TAdmin *admin;
    while ((admin = leAdmin(in)) != NULL) {
        if(admin->id == codigo){
            imprimeAdmin(admin);
            free(admin);
            return 0;
        }
    }
    printf("Administrador nao cadastrado ou incorreto!\n");
    return 1;
}