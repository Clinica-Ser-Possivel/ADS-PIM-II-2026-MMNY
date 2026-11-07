#include <stdio.h>
#include "tipos.h"

int main(void) {
    Usuario administrador = {
        .matricula = 1001,
        .nome = "Administrador Teste",
        .senha = "1234",
        .perfil = 1,
        .crp = "",
        .ativo = 1
    };

    FILE *arquivo = fopen("usuarios.dat", "wbx");

    if (arquivo == NULL) {
        printf("Arquivo ja existe ou nao foi possivel cria-lo.\n");
        return 1;
    }

    int gravou = fwrite(&administrador, sizeof(Usuario), 1, arquivo);
    int fechou = fclose(arquivo);

    if (gravou != 1 || fechou != 0) {
        printf("Erro ao salvar o usuario.\n");
        return 1;
    }

    printf("Usuario de teste salvo com sucesso.\n");

    return 0;
}