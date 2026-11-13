
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "pacientes.h"
#include "usuarios.h"

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

/* Valida CPF no formato 000.000.000-00. */
static int cpfValido(const char *cpf, size_t tamanho) {
    int digitos[11];
    int i, soma, resto;
    int d1, d2;

    if (cpf == NULL || tamanho < 15 ||
        memchr(cpf, '\0', tamanho) == NULL)
        return 0;

    if (strlen(cpf) != 14 ||
        cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-')
        return 0;

    for (i = 0; i < 14; i++) {
        if (i == 3 || i == 7 || i == 11)
            continue;

        if (cpf[i] < '0' || cpf[i] > '9')
            return 0;
    }

    digitos[0] = cpf[0] - '0';
    digitos[1] = cpf[1] - '0';
    digitos[2] = cpf[2] - '0';
    digitos[3] = cpf[4] - '0';
    digitos[4] = cpf[5] - '0';
    digitos[5] = cpf[6] - '0';
    digitos[6] = cpf[8] - '0';
    digitos[7] = cpf[9] - '0';
    digitos[8] = cpf[10] - '0';
    digitos[9] = cpf[12] - '0';
    digitos[10] = cpf[13] - '0';

    for (i = 1; i < 11; i++) {
        if (digitos[i] != digitos[0])
            break;
    }

    if (i == 11)
        return 0;

    soma = 0;

    for (i = 0; i < 9; i++)
        soma += digitos[i] * (10 - i);

    resto = soma % 11;
    d1 = (resto < 2) ? 0 : 11 - resto;

    if (digitos[9] != d1)
        return 0;

    soma = 0;

    for (i = 0; i < 10; i++)
        soma += digitos[i] * (11 - i);

    resto = soma % 11;
    d2 = (resto < 2) ? 0 : 11 - resto;

    return digitos[10] == d2;
}

/* Verifica se o ano e bissexto. */
static int anoBissexto(int ano) {
    return (ano % 400 == 0) ||
           (ano % 4 == 0 && ano % 100 != 0);
}

/* Valida data no formato DD/MM/AAAA. */
static int dataValida(const char *data, size_t tamanho) {
    int dia, mes, ano;
    int diasNoMes;
    int i;

    if (data == NULL || tamanho < 11 ||
        memchr(data, '\0', tamanho) == NULL)
        return 0;

    if (strlen(data) != 10 ||
        data[2] != '/' || data[5] != '/')
        return 0;

    for (i = 0; i < 10; i++) {
        if (i == 2 || i == 5)
            continue;

        if (data[i] < '0' || data[i] > '9')
            return 0;
    }

    dia = (data[0] - '0') * 10 + data[1] - '0';
    mes = (data[3] - '0') * 10 + data[4] - '0';
    ano = (data[6] - '0') * 1000 +
          (data[7] - '0') * 100 +
          (data[8] - '0') * 10 +
          (data[9] - '0');

    if (ano < 1900 || mes < 1 || mes > 12 || dia < 1)
        return 0;

    diasNoMes = 31;

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasNoMes = 30;
    } else if (mes == 2) {
        diasNoMes = anoBissexto(ano) ? 29 : 28;
    }

    return dia <= diasNoMes;
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

/* Le um registro de paciente com verificacao de integridade. */
static int lerPaciente(FILE *arquivo, Paciente *paciente) {
    size_t lidos;

    lidos = fread(paciente, 1, sizeof(*paciente), arquivo);

    if (lidos == 0)
        return feof(arquivo) ? 0 : -1;

    if (lidos != sizeof(*paciente))
        return -1;

    return registroValido(paciente) ? 1 : -1;
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
            contemTexto(atual.cpf, busca)) {

            printf("\nID: %d\n", atual.id);
            printf("Nome: %s\n", atual.nome);
            printf("CPF: %s\n", atual.cpf);
            printf("Nascimento: %s\n", atual.dataNascimento);
            printf("Telefone: %s\n", atual.telefone);
            printf("Endereco: %s\n", atual.endereco);
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
 * RF02.3 - Busca paciente pelo ID.
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
        (dados == NULL || !dadosValidos(dados)))
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
                /*
                 * Atualiza somente os dados pessoais e
                 * os dados do responsavel, preservando
                 * ID e vinculo com o psicologo.
                 */
                atual = *dados;
                atual.id = idPaciente;
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

    if (lidos != 0 || ferror(origem))
        erro = 1;

    if (fclose(origem) != 0)
        erro = 1;

    if (fclose(temporario) != 0)
        erro = 1;

    if (erro || !encontrou) {
        remove(ARQUIVO_TEMPORARIO);
        return erro == 1 ? -1 : 0;
    }

    if (rename(ARQUIVO_TEMPORARIO, ARQUIVO_PACIENTES) != 0) {
        remove(ARQUIVO_TEMPORARIO);
        return -1;
    }

    return 1;
}

/*
 * RF02.4 - Atualiza contato do paciente.
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
 * RF02.5 - Vincula psicologo ao paciente.
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
