# ifndef INTERFACE_H_INCLUDED
# define INTERFACE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "jogador.h"
#include "admin.h"

void MSG_MENU(); // MENSAGEM PARA EXIBIR O MENU PRINCIPAL

void MENU(FILE *out, FILE *clube,FILE *admin); // MÓDULO DE MENU

# endif // INTERFACE_H_INCLUDED

//FIM