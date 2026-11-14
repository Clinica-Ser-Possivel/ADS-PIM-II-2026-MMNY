
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "pacientes.h"
#include "usuarios.h"
#include "arquivos.h"
#include "validacoes.h"

#define ARQUIVO_PACIENTES "pacientes.dat"
#define ARQUIVO_TEMPORARIO "pacientes.tmp"

/* Verifica se o usuario esta ativo e possui matricula valida. */
static int usuarioValido(const Usuario *usuario) {
    return usuario != NULL &&
           usuario->matricula > 0 &&
           usuario->ativo == 1;
}

/* Administrador e recepcionista podem gerenciar pacientes. */
static int usuarioPodeGerenciar(const Usuario *usuario) {
    return usuarioValido(usuario) &&
           (usuario->perfil == 1 || usuario->perfil == 2);
}

/* Verifica se um texto possui terminador e nao esta vazio. */
static int textoValido(const char *texto, size_t tamanho) {
    size_t i;

    if (texto == NULL || tamanho == 0 ||
        memchr(texto, '\0', tamanho) == NULL)
        return 0;

    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] != ' ' && texto[i] != '\t' &&
            texto[i] != '\n' && texto[i] != '\r')
            return 1;
    }

    return 0;
}

/* Verifica se um texto contem outro texto, sem diferenciar maiusculas. */
static int contemTexto(const char *texto, const char *busca) {
    size_t i, j;
    size_t tamanhoTexto, tamanhoBusca;

    if (texto == NULL || busca == NULL)
        return 0;

    tamanhoTexto = strlen(texto);
    tamanhoBusca = strlen(busca);

    if (tamanhoBusca == 0)
        return 1;

    if (tamanhoBusca > tamanhoTexto)
        return 0;

    for (i = 0; i <= tamanhoTexto - tamanhoBusca; i++) {
        for (j = 0; j < tamanhoBusca; j++) {
            char a = texto[i + j];
            char b = busca[j];

            if (a >= 'A' && a <= 'Z')
                a = (char)(a - 'A' + 'a');

            if (b >= 'A' && b <= 'Z')
                b = (char)(b - 'A' + 'a');

            if (a != b)
                break;
        }

        if (j == tamanhoBusca)
            return 1;
    }

    return 0;
}

/* Valida os dados pessoais e do responsavel. */
static int dadosValidos(const Paciente *paciente) {
    if (paciente == NULL)
        return 0;

    if (!textoValido(paciente->nome, sizeof(paciente->nome)) ||
        !cpfValido(paciente->cpf, sizeof(paciente->cpf)) ||
        !dataValida(paciente->dataNascimento,
                    sizeof(paciente->dataNascimento)) ||
        !textoValido(paciente->telefone,
                     sizeof(paciente->telefone)) ||
        !textoValido(paciente->endereco,
                     sizeof(paciente->endereco)))
        return 0;

    if (!textoValido(paciente->responsavel.nome,
                     sizeof(paciente->responsavel.nome)) ||
        !cpfValido(paciente->responsavel.cpf,
                   sizeof(paciente->responsavel.cpf)) ||
        !textoValido(paciente->responsavel.telefone,
                     sizeof(paciente->responsavel.telefone)) ||
        !textoValido(paciente->responsavel.parentesco,
                     sizeof(paciente->responsavel.parentesco)) ||
        !textoValido(paciente->responsavel.endereco,
                     sizeof(paciente->responsavel.endereco)))
        return 0;

    return 1;
}

/* Valida um registro completo lido do arquivo. */
static int registroValido(const Paciente *paciente) {
    return paciente != NULL &&
           paciente->id > 0 &&
           paciente->matriculaPsicologo >= 0 &&
           dadosValidos(paciente);
}

/* Verifica disponibilidade sem gravar nem alterar o cadastro. */
int cpfPacienteDisponivel(const Usuario *usuario, const char *cpf) {
    if (!usuarioPodeGerenciar(usuario) || !cpfValido(cpf, 15)) return 0;
    FILE *arquivo = fopen(ARQUIVO_PACIENTES, "rb");
    if (arquivo == NULL) return errno == ENOENT ? 1 : -1;
    Paciente atual;
    size_t lidos;
    int duplicado = 0;
    while ((lidos = fread(&atual, 1, sizeof atual, arquivo)) == sizeof atual) {
        if (!registroValido(&atual)) {
            fclose(arquivo);
            return -1;
        }
        if (strcmp(atual.cpf, cpf) == 0) duplicado = 1;
    }
    int erro = lidos != 0 || ferror(arquivo);
    if (fclose(arquivo) != 0) erro = 1;
    return erro ? -1 : !duplicado;
}

/*
 * RF02.1 - Cadastra paciente e responsavel.
 * Permitido: administrador e recepcionista.
 *
 * Retornos:
 * 1 = sucesso
 * 0 = recusado
 * -1 = erro de arquivo
 */
int cadastrarPaciente(const Usuario *usuarioLogado,
                      Paciente *paciente) {
    FILE *arquivo;
    Paciente atual;
    int maiorId = 0;
    size_t lidos;

    if (!usuarioPodeGerenciar(usuarioLogado) ||
        paciente == NULL)
        return 0;

    if (!dadosValidos(paciente))
        return 0;

    arquivo = fopen(ARQUIVO_PACIENTES, "rb");

    if (arquivo != NULL) {
        while ((lidos = fread(&atual, 1, sizeof(atual), arquivo)) ==
               sizeof(atual)) {

            if (!registroValido(&atual)) {
                fclose(arquivo);
                return -1;
            }

            if (strcmp(atual.cpf, paciente->cpf) == 0) {
                fclose(arquivo);
                puts("Paciente ja cadastrado com esse CPF.");
                return 0;
            }

            if (atual.id > maiorId)
                maiorId = atual.id;
        }

        if (lidos != 0 || ferror(arquivo)) {
            fclose(arquivo);
            return -1;
        }

        if (fclose(arquivo) != 0)
            return -1;
    } else if (errno != ENOENT) {
        return -1;
    }

    if (maiorId == INT_MAX)
        return -1;

    paciente->id = maiorId + 1;
    paciente->matriculaPsicologo = 0;

    arquivo = fopen(ARQUIVO_PACIENTES, "ab");

    if (arquivo == NULL)
        return -1;

    if (fwrite(paciente, sizeof(*paciente), 1, arquivo) != 1) {
        fclose(arquivo);
        return -1;
    }

    if (fclose(arquivo) != 0)
        return -1;

    return 1;
}

/*
 * RF02.2 - Consulta pacientes.
 * Administrador e recepcionista podem consultar todos.
 * Psicologo pode consultar pacientes vinculados a ele.
 */
int consultarPacientes(const Usuario *usuarioLogado,
                       const char *busca) {
    FILE *arquivo;
    Paciente atual;
    int encontrou = 0;
    size_t lidos;

    if (!usuarioValido(usuarioLogado))
        return 0;

    if (usuarioLogado->perfil != 1 &&
        usuarioLogado->perfil != 2 &&
        usuarioLogado->perfil != 3)
        return 0;

    if (busca == NULL || busca[0] == '\0')
        return 0;

    arquivo = fopen(ARQUIVO_PACIENTES, "rb");

    if (arquivo == NULL) {
        if (errno == ENOENT) {
            printf("Nenhum paciente cadastrado.\n");
            return 0;
        }

        return -1;
    }

    printf("\n===== PACIENTES =====\n");

    while ((lidos = fread(&atual, 1, sizeof(atual), arquivo)) ==
           sizeof(atual)) {

        if (!registroValido(&atual)) {
            fclose(arquivo);
            return -1;
        }

        if (usuarioLogado->perfil == 3 &&
            atual.matriculaPsicologo != usuarioLogado->matricula)
            continue;

        if (contemTexto(atual.nome, busca) ||
            contemTexto(atual.cpf, busca) ||
            contemTexto(atual.responsavel.nome, busca) ||
            contemTexto(atual.responsavel.cpf, busca)) {

            printf("\nID: %d\n", atual.id);
            printf("Nome: %s\n", atual.nome);
            printf("CPF: %s\n", atual.cpf);
            printf("Nascimento: %s\n", atual.dataNascimento);
            printf("Telefone: %s\n", atual.telefone);
            printf("Endereco: %s\n", atual.endereco);
            printf("Responsavel: %s\n", atual.responsavel.nome);
            printf("CPF do responsavel: %s\n", atual.responsavel.cpf);
            printf("Telefone do responsavel: %s\n", atual.responsavel.telefone);
            printf("Parentesco: %s\n", atual.responsavel.parentesco);
            printf("Endereco do responsavel: %s\n", atual.responsavel.endereco);
            printf("Psicologo: %d\n",
                   atual.matriculaPsicologo);

            encontrou = 1;
        }
    }

    if (lidos != 0 || ferror(arquivo)) {
        fclose(arquivo);
        return -1;
    }

    if (fclose(arquivo) != 0)
        return -1;

    if (!encontrou)
        printf("Nenhum paciente encontrado.\n");

    return encontrou ? 1 : 0;
}

/*
 * Apoio aos modulos - Busca paciente pelo ID.
 * Psicologo so pode acessar pacientes vinculados a ele.
 */
int buscarPacientePorId(const Usuario *usuarioLogado,
                        int idPaciente,
                        Paciente *pacienteEncontrado) {
    FILE *arquivo;
    Paciente atual;
    size_t lidos;

    if (!usuarioValido(usuarioLogado) ||
        idPaciente <= 0 ||
        pacienteEncontrado == NULL)
        return 0;

    if (usuarioLogado->perfil != 1 &&
        usuarioLogado->perfil != 2 &&
        usuarioLogado->perfil != 3)
        return 0;

    arquivo = fopen(ARQUIVO_PACIENTES, "rb");

    if (arquivo == NULL) {
        if (errno == ENOENT)
            return 0;

        return -1;
    }

    while ((lidos = fread(&atual, 1, sizeof(atual), arquivo)) ==
           sizeof(atual)) {

        if (!registroValido(&atual)) {
            fclose(arquivo);
            return -1;
        }

        if (atual.id == idPaciente) {
            if (usuarioLogado->perfil == 3 &&
                atual.matriculaPsicologo != usuarioLogado->matricula) {
                fclose(arquivo);
                return 0;
            }

            *pacienteEncontrado = atual;

            if (fclose(arquivo) != 0)
                return -1;

            return 1;
        }
    }

    if (lidos != 0 || ferror(arquivo)) {
        fclose(arquivo);
        return -1;
    }

    if (fclose(arquivo) != 0)
        return -1;

    return 0;
}

/*
 * Altera os dados de um paciente no arquivo.
 * modo 1 = atualiza dados de contato.
 * modo 2 = vincula psicologo.
 */
static int alterarPaciente(const Usuario *usuarioLogado,
                           int idPaciente,
                           const Paciente *dados,
                           int matriculaPsicologo,
                           int modo) {
    FILE *origem;
    FILE *temporario;
    Paciente atual;
    size_t lidos;
    int encontrou = 0;
    int erro = 0;

    if (!usuarioPodeGerenciar(usuarioLogado) ||
        idPaciente <= 0)
        return 0;

    if (modo != 1 && modo != 2)
        return 0;

    if (modo == 1 &&
        (dados == NULL ||
         !textoValido(dados->telefone, sizeof(dados->telefone)) ||
         !textoValido(dados->endereco, sizeof(dados->endereco)) ||
         !textoValido(dados->responsavel.telefone,
                      sizeof(dados->responsavel.telefone)) ||
         !textoValido(dados->responsavel.endereco,
                      sizeof(dados->responsavel.endereco))))
        return 0;

    if (modo == 2 && matriculaPsicologo <= 0)
        return 0;

    origem = fopen(ARQUIVO_PACIENTES, "rb");

    if (origem == NULL) {
        if (errno == ENOENT)
            return 0;

        return -1;
    }

    temporario = fopen(ARQUIVO_TEMPORARIO, "wb");

    if (temporario == NULL) {
        fclose(origem);
        return -1;
    }

    while ((lidos = fread(&atual, 1, sizeof(atual), origem)) ==
           sizeof(atual)) {

        if (!registroValido(&atual)) {
            erro = 1;
            break;
        }

        if (atual.id == idPaciente) {
            encontrou = 1;

            if (modo == 1) {
                /* Copia somente os quatro campos permitidos pelo RF02.3.
                 * Identidade, nascimento, responsavel e vinculo sao preservados. */
                memcpy(atual.telefone, dados->telefone, sizeof(atual.telefone));
                memcpy(atual.endereco, dados->endereco, sizeof(atual.endereco));
                memcpy(atual.responsavel.telefone, dados->responsavel.telefone,
                       sizeof(atual.responsavel.telefone));
                memcpy(atual.responsavel.endereco, dados->responsavel.endereco,
                       sizeof(atual.responsavel.endereco));
            } else {
                if (atual.matriculaPsicologo != 0) {
                    erro = 2;
                    break;
                }

                atual.matriculaPsicologo = matriculaPsicologo;
            }
        }

        if (fwrite(&atual, sizeof(atual), 1, temporario) != 1) {
            erro = 1;
            break;
        }
    }

    if (ferror(origem) || (lidos != 0 && erro == 0))
        erro = 1;

    if (fclose(origem) != 0)
        erro = 1;

    if (fclose(temporario) != 0)
        erro = 1;

    if (erro || !encontrou) {
        remove(ARQUIVO_TEMPORARIO);
        return erro == 1 ? -1 : 0;
    }

    if (!substituirArquivo(ARQUIVO_TEMPORARIO, ARQUIVO_PACIENTES)) {
        remove(ARQUIVO_TEMPORARIO);
        return -1;
    }

    return 1;
}

/*
 * RF02.3 - Atualiza contato do paciente.
 * Permitido: administrador e recepcionista.
 */
int atualizarContatoPaciente(const Usuario *usuarioLogado,
                             const Paciente *paciente) {
    if (paciente == NULL)
        return 0;

    return alterarPaciente(
        usuarioLogado,
        paciente->id,
        paciente,
        0,
        1
    );
}

/*
 * Apoio ao RF04.1 - Vincula psicologo ao paciente.
 * Permitido: administrador e recepcionista.
 */
int vincularPsicologo(const Usuario *usuarioLogado,
                      int idPaciente,
                      int matriculaPsicologo) {
    Usuario psicologo;
    int resultado;

    if (!usuarioPodeGerenciar(usuarioLogado) ||
        idPaciente <= 0 ||
        matriculaPsicologo <= 0)
        return 0;

    resultado = buscarUsuarioPorMatricula(
        usuarioLogado,
        matriculaPsicologo,
        &psicologo
    );

    if (resultado != 1)
        return resultado == -1 ? -1 : 0;

    if (!usuarioValido(&psicologo) || psicologo.perfil != 3)
        return 0;

    return alterarPaciente(
        usuarioLogado,
        idPaciente,
        NULL,
        matriculaPsicologo,
        2
    );
}
