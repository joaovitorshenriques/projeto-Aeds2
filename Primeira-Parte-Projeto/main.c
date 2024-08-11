#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
int main(int argc, char**argv){
    FILE *out;
    FILE *clube;
    FILE *admin;

    if((out = fopen("jogador.dat","w+b"))==NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    if((clube = fopen("clubes.dat","w+b"))==NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    if ((admin = fopen("admin.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }else {
        MENU(out, clube, admin);
        fclose(out);
        fclose(clube);
        fclose(admin);
    }
}
