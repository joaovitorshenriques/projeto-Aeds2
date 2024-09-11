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
// Função para embaralhar um array
void embaralhar(int *array, int tamanho) {
    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int insereMultiplosJogadores(FILE *out) {
    int contador = 0;
    printf("Informe quantos jogadores deseja inserir: ");
    scanf("%d", &contador);

    if (contador <= 0) {
        printf("Número de jogadores deve ser maior que zero.\n");
        return 1;
    }

    srand(time(NULL));

    int *numeros = malloc(contador * sizeof(int));
    if (numeros == NULL) {
        printf("Erro ao alocar memória para números.\n");
        return 1;
    }

    for (int i = 0; i < contador; i++) {
        numeros[i] = i + 1;
    }

    embaralhar(numeros, contador);

    // Carregando clubes do arquivo
    FILE *clubesFileRead = fopen("clubes.dat", "rb");
    if (clubesFileRead == NULL) {
        printf("Erro ao abrir arquivo para leitura de clubes.\n");
        free(numeros);
        return 1;
    }

    int numClubes = tamanhoArquivoClube(clubesFileRead);
    if (numClubes <= 0) {
        printf("Nenhum clube encontrado no arquivo.\n");
        free(numeros);
        fclose(clubesFileRead);
        return 1;
    }

    TClube *clubes[numClubes];

    for (int i = 0; i < numClubes; i++) {
        clubes[i] = (TClube *)leClube(clubesFileRead);
        if (clubes[i] == NULL) {
            printf("Erro ao ler clube %d do arquivo.\n", i + 1);
            for (int j = 0; j < i; j++) {
                free(clubes[j]);
            }
            free(numeros);
            fclose(clubesFileRead);
            return 1;
        }
    }
    fclose(clubesFileRead);

    int x = 0;
    for (int i = 0; i < contador; i++) {
        TClube *clube = clubes[rand() % numClubes];
        if (clube == NULL) {
            printf("Erro: Clube selecionado é NULL.\n");
            continue;
        }

        TJogador *jogador = criaJogador(
            numeros[x], "Jogador", "Posicao", 25, 35000, 150000, 7.0, "Contrato", clube
        );
        if (jogador == NULL) {
            printf("Erro ao criar jogador com número %d\n", numeros[x]);
            continue;
        }
        x++;
        salvaJogador(jogador, out);
        free(jogador);
    }

    // Libera a memória alocada para os clubes
    for (int i = 0; i < numClubes; i++) {
        free(clubes[i]);
    }
    free(numeros);

    return 0;
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
    clock_t start,end;
    start = clock();
    int tam = tamanhoArquivoJogador(arq);

    mergeSortJogador(arq, 0, tam - 1);
    fflush(arq);
    end = clock();
    double tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTempo de ordenacao: %.2f segundos\n", tempo);
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

void transferenciaDeJogador(FILE *in, FILE *clube) {
    int contador = 0;
    int flag = 0;
    int codigoClube;

    printf("Informe o codigo do jogador que deseja contratar: \n");
    scanf("%d", &contador);

    rewind(in);
    TJogador *jogador;
    while ((jogador = leJogador(in)) != NULL) {
        if (jogador->id == contador) {
            imprime(jogador);

                printf("Deseja realizar a contratacao do jogador?: \n");
                printf("1 SIM\n");
                printf("2 NAO\n");
                scanf("%d", &flag);

                if (flag == 1) {
                    printf("Informe o codigo do clube para finalizar a contratacao do jogador: \n");
                    scanf("%d", &codigoClube);

                    TClube *clubeTransferencia = pesquisarClubePorCodigo(clube, codigoClube);

                    if (clubeTransferencia != NULL && clubeTransferencia->id != -1) {
                        strcpy(jogador->clube.nome, clubeTransferencia->nome);
                        jogador->clube.id = clubeTransferencia->id;
                        printf("\n\n\t---------------------- Jogador transferido ----------------------\n");
                        imprime(jogador);
                        printf("Contratacao realizada com sucesso!\n");
                    } else {
                        printf("Clube nao encontrado, transacao cancelada!\n");
                    }
                    return;
                } else if (flag == 2) {
                    printf("Contratacao cancelada!\n");
                    return;
                }
            }
        }
        printf("Jogador nao encontrado na base de dados\n");
    }

int registroMemoria (int vet[6]) {

        int cont = 0;

        for (int i = 0; i < 6; ++i) {
            if (vet[i] == 1) {
                cont++;
            }
        }

        if (cont == 6) {
            return 1;
        } else {
            return 0;
        }
}

int tamanhoArquivoParticao(FILE *file) {
    int contSizeFile = 0;
    int bytesAUX = 0;

    while (1) {
        fseek(file, bytesAUX * sizeof(TJogador), SEEK_SET);
        TJogador *j = leJogador(file);
        if (j == NULL) {
            break;
        }
        free(j);
        contSizeFile++;
        bytesAUX++;
    }

    return contSizeFile;
}

void imprimeParticoes(FILE *file, char nomeParticao[]) {
    printf("PARTICAO: %s \n\n", nomeParticao);

    int totalPlayers = tamanhoArquivoParticao(file);

    for (int i = 0; i < totalPlayers; ++i) {
        fseek(file, i * tamanhoRegistroJogador(), SEEK_SET);
        TJogador *j = leJogador(file);

        if (j != NULL) {
            printf("%d ", j->id);
            free(j); // Liberar a mem�ria alocada por le()
        }
    }

    printf("\n");
    printf("\n**********************************************************************************************\n");

}