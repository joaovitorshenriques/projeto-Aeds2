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