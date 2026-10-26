#include <stdio.h>
#include "usuarios.h"

int main(void) {
    /* Dados digitados na tela de login. */
    int matricula;
    char senha[20];

    /* Recebe os dados do usuario autorizado. */
    Usuario usuarioLogado;

    /* Cria o primeiro administrador se o arquivo ainda nao existir. */
    if (inicializarUsuarios() != 1) {
        printf("Erro ao preparar o arquivo de usuarios.\n");
        return 1;
    }

    printf("=== Clinica Ser Possivel ===\n");
    printf("Login\n\n");

    /* Recebe a matricula. */
    printf("Matricula: ");
    if (scanf("%d", &matricula) != 1) {
        printf("Matricula invalida.\n");
        return 1;
    }

    /* Recebe uma senha de ate 19 caracteres, sem espacos. */
    printf("Senha: ");
    if (scanf("%19s", senha) != 1) {
        printf("Erro ao ler a senha.\n");
        return 1;
    }

    /* Verifica matricula, senha e status no arquivo de usuarios. */
    int resultado = efetuarLogin(matricula, senha, &usuarioLogado);

    if (resultado == 1) {
        printf("\nLogin realizado com sucesso!\n");
        printf("Bem-vindo(a), %s.\n", usuarioLogado.nome);

        /* Somente administradores acessam este menu. */
        if (usuarioLogado.perfil == 1) {
            int opcao;

            /* Mantem o menu aberto ate a escolha da opcao zero. */
            do {
                printf("\n=== Menu do Administrador ===\n");
                printf("1 - Cadastrar usuario\n");
                printf("2 - Inativar usuario\n");
                printf("0 - Sair\n");
                printf("Escolha uma opcao: ");

                if (scanf("%d", &opcao) != 1) {
                    printf("Entrada invalida. Encerrando.\n");
                    return 1;
                }

                /* Executa a opcao escolhida. */
                switch (opcao) {
                    case 1: {
                        /* Inicia todos os campos vazios ou com zero. */
                        Usuario novoUsuario = {0};

                        printf("\n=== Cadastrar usuario ===\n");

                        printf("Matricula: ");
                        if (scanf("%d", &novoUsuario.matricula) != 1) {
                            printf("Entrada invalida. Encerrando.\n");
                            return 1;
                        }

                        /* Permite espacos no nome, com limite de 99 caracteres. */
                        printf("Nome: ");
                        if (scanf(" %99[^\n]", novoUsuario.nome) != 1) {
                            printf("Erro ao ler o nome.\n");
                            return 1;
                        }

                        printf("Senha (ate 19 caracteres, sem espacos): ");
                        if (scanf("%19s", novoUsuario.senha) != 1) {
                            printf("Erro ao ler a senha.\n");
                            return 1;
                        }

                        printf("\nPerfis:\n");
                        printf("1 - Administrador\n");
                        printf("2 - Recepcionista\n");
                        printf("3 - Psicologo\n");
                        printf("Escolha o perfil: ");

                        if (scanf("%d", &novoUsuario.perfil) != 1) {
                            printf("Entrada invalida. Encerrando.\n");
                            return 1;
                        }

                        /* O CRP e solicitado somente para psicologos. */
                        if (novoUsuario.perfil == 3) {
                            printf("CRP: ");
                            if (scanf("%19s", novoUsuario.crp) != 1) {
                                printf("Erro ao ler o CRP.\n");
                                return 1;
                            }
                        }

                        /* Todo novo cadastro comeca ativo. */
                        novoUsuario.ativo = 1;

                        /* Valida a permissao e os dados antes de gravar. */
                        int cadastro = cadastrarUsuario(
                            &usuarioLogado,
                            &novoUsuario
                        );

                        if (cadastro == 1) {
                            printf("Usuario cadastrado com sucesso!\n");
                        } else if (cadastro == 0) {
                            printf("Cadastro recusado: confira permissao, "
                                   "dados e matricula duplicada.\n");
                        } else {
                            printf("Erro ao acessar ou gravar "
                                   "o arquivo de usuarios.\n");
                        }

                        break;
                    }

                    case 2: {
                        /* Guarda a matricula de quem sera inativado. */
                        int matriculaInativar;

                        printf("\n=== Inativar usuario ===\n");
                        printf("Matricula do usuario: ");

                        if (scanf("%d", &matriculaInativar) != 1) {
                            printf("Entrada invalida. Encerrando.\n");
                            return 1;
                        }

                        /* A funcao verifica a permissao e atualiza o arquivo. */
                        int inativacao = inativarUsuario(
                            &usuarioLogado,
                            matriculaInativar
                        );

                        if (inativacao == 1) {
                            printf("Usuario inativado com sucesso!\n");
                        } else if (inativacao == 0) {
                            printf("Inativacao recusada: usuario inexistente, ja inativo, "
                                "sem permissao ou tentativa de inativar a si mesmo.\n");
                        } else {
                            printf("Erro ao acessar ou atualizar o arquivo de usuarios.\n");
                        }

                        break;
                    }

                    case 0:
                        printf("Encerrando o sistema.\n");
                        break;

                    default:
                        printf("Opcao invalida.\n");
                        break;
                }
            } while (opcao != 0);

        } else {
            /* Os menus dos outros perfis serao acrescentados depois. */
            printf("Menu deste perfil ainda em desenvolvimento.\n");
        }

    } else if (resultado == 0) {
        printf("\nMatricula ou senha incorreta, ou usuario inativo.\n");

    } else {
        printf("\nErro ao ler o arquivo de usuarios.\n");
    }

    return 0;
}