#include <stdio.h>
#include <string.h>
#include "usuarios.h"
#include <errno.h>

int efetuarLogin(int matricula, const char *senha, Usuario *usuarioLogado) {
    FILE *arquivo = fopen("usuarios.dat", "rb");

    if (arquivo == NULL) {
        return -1;
    }

    Usuario usuario;

    while (fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
        if (usuario.matricula == matricula) {
            int autorizado = usuario.ativo == 1
                && strcmp(usuario.senha, senha) == 0;

            fclose(arquivo);

            if (autorizado) {
                *usuarioLogado = usuario;
                return 1;
            }

            return 0;
        }
    }

    int erroLeitura = ferror(arquivo);
    fclose(arquivo);

    if (erroLeitura) {
        return -1;
    }

    return 0;
}   

int inicializarUsuarios(void) {
    FILE *arquivo = fopen("usuarios.dat", "rb");

    if (arquivo != NULL) {
        return fclose(arquivo) == 0 ? 1 : -1;
    }

    if (errno != ENOENT) {
        return -1;
    }

    Usuario administrador = {
        .matricula = 1001,
        .nome = "Administrador Teste",
        .senha = "1234",
        .perfil = 1,
        .crp = "",
        .ativo = 1
    };

    arquivo = fopen("usuarios.dat", "wbx");

    if (arquivo == NULL) {
        return -1;
    }

    int gravou = fwrite(&administrador, sizeof(Usuario), 1, arquivo);
    int fechou = fclose(arquivo);

    if (gravou != 1 || fechou != 0) {
        return -1;
    }

    return 1;
}

int cadastrarUsuario(const Usuario *usuarioLogado,
                     const Usuario *novoUsuario) {
    /*
     * Confere se quem esta cadastrando e um administrador ativo.
     * A permissao e verificada aqui, alem do menu.
     */
    if (usuarioLogado == NULL || novoUsuario == NULL) {
        return 0;
    }

    if (usuarioLogado->perfil != 1 || usuarioLogado->ativo != 1) {
        return 0;
    }

    /* Confere os campos obrigatorios e os valores permitidos. */
    if (novoUsuario->matricula <= 0 ||
        novoUsuario->nome[0] == '\0' ||
        novoUsuario->senha[0] == '\0' ||
        novoUsuario->perfil < 1 ||
        novoUsuario->perfil > 3 ||
        novoUsuario->ativo != 1) {
        return 0;
    }

    /* Psicologos precisam ter o CRP preenchido. */
    if (novoUsuario->perfil == 3 && novoUsuario->crp[0] == '\0') {
        return 0;
    }

    /* Abre o arquivo existente para leitura e gravacao. */
    FILE *arquivo = fopen("usuarios.dat", "rb+");

    if (arquivo == NULL) {
        return -1;
    }

    Usuario usuarioExistente;

    /* Procura uma matricula igual para impedir duplicidade. */
    while (fread(&usuarioExistente, sizeof(Usuario), 1, arquivo) == 1) {
        if (usuarioExistente.matricula == novoUsuario->matricula) {
            fclose(arquivo);
            return 0;
        }
    }

    /* Verifica se a leitura terminou por algum erro. */
    if (ferror(arquivo)) {
        fclose(arquivo);
        return -1;
    }

    /* Posiciona a gravacao no final para preservar os cadastros. */
    if (fseek(arquivo, 0, SEEK_END) != 0) {
        fclose(arquivo);
        return -1;
    }

    /* Grava o novo usuario e fecha o arquivo. */
    int gravou = fwrite(novoUsuario, sizeof(Usuario), 1, arquivo);
    int fechou = fclose(arquivo);

    if (gravou != 1 || fechou != 0) {
        return -1;
    }

    return 1;
}

int inativarUsuario(const Usuario *usuarioLogado, int matricula) {
    /* Somente um administrador ativo pode inativar usuarios. */
    if (usuarioLogado == NULL) {
        return 0;
    }

    if (usuarioLogado->perfil != 1 || usuarioLogado->ativo != 1) {
        return 0;
    }

    /* Impede matricula invalida e a inativacao do proprio acesso. */
    if (matricula <= 0 || matricula == usuarioLogado->matricula) {
        return 0;
    }

    /* Abre o arquivo existente para leitura e atualizacao. */
    FILE *arquivo = fopen("usuarios.dat", "rb+");

    if (arquivo == NULL) {
        return -1;
    }

    Usuario usuario;

    while (1) {
        /* Guarda a posicao inicial do registro antes de le-lo. */
        long posicao = ftell(arquivo);

        if (posicao == -1L) {
            fclose(arquivo);
            return -1;
        }

        /* Le um usuario. Ao chegar ao fim, sai da repeticao. */
        if (fread(&usuario, sizeof(Usuario), 1, arquivo) != 1) {
            break;
        }

        if (usuario.matricula == matricula) {
            /* Recusa se o usuario ja estiver inativo. */
            if (usuario.ativo == 0) {
                fclose(arquivo);
                return 0;
            }

            /* Altera somente o status, preservando os outros dados. */
            usuario.ativo = 0;

            /* Volta ao inicio do registro encontrado. */
            if (fseek(arquivo, posicao, SEEK_SET) != 0) {
                fclose(arquivo);
                return -1;
            }

            /* Grava o registro atualizado na mesma posicao. */
            int gravou = fwrite(&usuario, sizeof(Usuario), 1, arquivo);
            int fechou = fclose(arquivo);

            if (gravou != 1 || fechou != 0) {
                return -1;
            }

            return 1;
        }
    }

    /* Distingue uma falha de leitura de uma matricula nao encontrada. */
    int erroLeitura = ferror(arquivo);
    int fechou = fclose(arquivo);

    if (erroLeitura || fechou != 0) {
        return -1;
    }

    return 0;
}