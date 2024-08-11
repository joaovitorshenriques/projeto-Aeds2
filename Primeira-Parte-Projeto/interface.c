#include <stdio.h>
#include <stdlib.h>

#include "interface.h"

void MSG_MENU( )
{
    system("cls");
    printf("\n\n\t---------------------- SEJA BEM VINDO ----------------------");
    printf("\n\n\t---------------------- OPCOES DE MENU ----------------------");
    printf("\n\n\t1. Criar Jogadores");
    printf("  \n\t2. Criar Clubes");
    printf("  \n\t3. Criar Admins");
    printf("  \n\t4. Imprimir Jogadores");
    printf("  \n\t5. Imprimir Clubes");
    printf("  \n\t5. Imprimir Admins");
    printf("  \n\t7. Buscas Sequenciais");
    printf("  \n\t8. Ordenacao dos Arquivos");
    printf("  \n\t9. Buscas Binarias");

    printf("\n\n\t---------------------- PARA OS ADMINS ----------------------");
    printf("  \n\t10. Pesquisar jogadores por clubes");
    printf("  \n\t11. Realizar transferencia de jogadores entre clubes");

    printf("\n");
    printf(" \n\t12. Sair");
}

void MENU(FILE*out,FILE *clube,FILE *admin){
    int opcao1,opcao2 = 0;
    int validacao;

    do{
        MSG_MENU();
        printf("\nDigite uma Opcao: ");
        fflush(stdin);
        scanf("%d",&opcao1);
        switch(opcao1){
            case 1:
            insereMultiplosJogadores(out);
            system("PAUSE");
            break;

            case 2:
            insereClubes(clube);
            system("PAUSE");
            break;

            case 3:
            insereMultiplosAdmins(admin);
            system("PAUSE");
            break;

            case 4:
            leJogadoresEImprime(out);
            system("PAUSE");
            break;

            case 5:
            leClubesEImprime(clube);
            system("PAUSE");
            break;

            case 6:
            leAdminsEImprime(admin);
            system("PAUSE");
            break;

            case 7:
            printf("\n\n\t------------OPCOES------------");
            printf("\n\n\t1. Buscar Jogador");
            printf("  \n\t2. Buscar Clube");
            printf("  \n\t3. Buscar Admin");

            printf("\n\nDigite uma opcao: ");
            scanf("%d",&opcao2);

            if(opcao2 == 1){
                buscaSequencialJogador(10,out);
            }else if(opcao2 == 2){
                buscaSequencialClube(10,clube);
            }else if(opcao2 == 3){
                buscaSequencialAdmin(10,admin);
            }
            system("PAUSE");
            break;

            case 8:
            printf("\n\n\t------------OPCOES------------");
            printf("\n\n\t1. Ordenar Jogador");
            printf("  \n\t2. Ordenar Clube");
            printf("  \n\t3. Ordenar Admin");

            printf("\n\nDigite uma opcao: ");
            scanf("%d",&opcao2);

            if(opcao2 == 1){
                mergeSortDiscoJogador(out);
            }else if(opcao2 == 2){
                mergeSortDiscoClube(clube);
            }else if(opcao2 == 3){
                mergeSortDiscoAdmin(admin);
            }
            system("PAUSE");
            break;

            case 9:
            printf("\n\n\t------------OPCOES------------");
            printf("\n\n\t1. Buscar Jogador");
            printf("  \n\t2. Buscar Clube");
            printf("  \n\t3. Buscar Admin");

            printf("\n\nDigite uma opcao: ");
            scanf("%d",&opcao2);

            if(opcao2 == 1){
                buscaBinariaJogador(10,out,0,100);
            }else if(opcao2 == 2){
                buscaBinariaClube(10,clube,0,100);
            }else if(opcao2 == 3){
                buscaBinariaAdmin(10,admin,0,100);
            }
            system("PAUSE");
            break;

            case 10:
            pesquisarJogadoresPorClube(out);
            system("PAUSE");
            break;

            case 11:
            validacao = validarAdmin(admin);
            if(validacao == 0){
                transferenciaDeJogador(out,clube);
            }
            case 12:
            system("cls");
            printf("\n\t Saindo do Modulo");
            system("PAUSE");
            break;

            default:
                system("cls");
                printf("\n\n\n\t >>>>>> MSG: Digite uma opcao valida!!! <<<<<<");
                system("PAUSE");
        }
    }while(opcao1 != 12);
}


void MENU(FILE*out,FILE *clube,FILE *admin){
    
}