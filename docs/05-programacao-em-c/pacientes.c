
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#include "pacientes.h"
#include "usuarios.h"

#define ARQUIVO_PACIENTES "pacientes.dat"
#define ARQUIVO_TEMPORARIO "pacientes.tmp"

/* =====================================================
   FUNCOES AUXILIARES
   ===================================================== */

/* Verifica se o usuario esta ativo e possui perfil valido. */
static int usuarioValido(const Usuario *usuario) {
    return usuario != NULL &&
           usuario->matricula > 0 &&
           usuario->ativo == 1 &&
           usuario->perfil >= 1 &&
           usuario->perfil <= 3;
}

/* Somente administrador e recepcionista podem gerenciar. */
static int usuarioPodeGerenciar(const Usuario *usuario) {
    return usuarioValido(usuario) &&
           (usuario->perfil == 1 || usuario->perfil == 2);
}

/* Verifica se o campo possui texto e terminacao valida. */
static int textoValido(const char *texto, size_t tamanho) {
    return texto != NULL &&
           memchr(texto, '\0', tamanho) != NULL &&
           texto[0] != '\0';
}

/* Valida o formato 000.000.000-00. */
static int cpfValido(const char *cpf) {
    int i;

    if (cpf == NULL || strlen(cpf) != 14) {
        return 0;
    }

    for (i = 0; i < 14; i++) {
        if (i == 3 || i == 7) {
            if (cpf[i] != '.') {
                return 0;
            }
        } else if (i == 11) {
            if (cpf[i] != '-') {
                return 0;
            }
        } else if (cpf[i] < '0' || cpf[i] > '9') {
            return 0;
        }
    }

    return 1;
}

/* Verifica se o ano e bissexto. */
static int anoBissexto(int ano) {
    return ano % 400 == 0 ||
           (ano % 4 == 0 && ano % 100 != 0);
}

/* Valida a data no formato DD/MM/AAAA. */
static int dataValida(const char *data) {
    int dia, mes, ano;

    int diasMes[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (data == NULL || strlen(data) != 10 ||
        data[2] != '/' || data[5] != '/') {
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            continue;
        }

        if (data[i] < '0' || data[i] > '9') {
            return 0;
        }
    }

    dia = (data[0] - '0') * 10 + data[1] - '0';

    mes = (data[3] - '0') * 10 + data[4] - '0';

    ano = (data[6] - '0') * 1000 +
          (data[7] - '0') * 100 +
          (data[8] - '0') * 10 +
          (data[9] - '0');

    if (ano < 1900 || mes < 1 || mes > 12) {
        return 0;
    }

    if (anoBissexto(ano)) {
        diasMes[1] = 29;
    }

    return dia >= 1 && dia <= diasMes[mes - 1];
}

/* Compara textos ignorando maiusculas e minusculas. */
static int contemTexto(const char *texto, const char *busca) {
    size_t i, j;

    if (texto == NULL || busca == NULL) {
        return 0;
    }

    if (busca[0] == '\0') {
        return 1;
    }

    for (i = 0; texto[i] != '\0'; i++) {
        for (j = 0;
             busca[j] != '\0' &&
             texto[i + j] != '\0' &&
             tolower((unsigned char) texto[i + j]) ==
             tolower((unsigned char) busca[j]);
             j++) {
        }

        if (busca[j] == '\0') {
            return 1;
        }
    }

    return 0;
}

/*
 * Le um registro completo.
 * 1 = registro lido.
 * 0 = fim normal do arquivo.
 * -1 = erro ou registro incompleto.
 */
static int lerPaciente(FILE *arquivo, Paciente *paciente) {
    size_t lidos;

    lidos = fread(paciente, 1, sizeof(Paciente), arquivo);

    if (lidos == sizeof(Paciente)) {
        return 1;
    }

    if (lidos == 0 && feof(arquivo) && !ferror(arquivo)) {
        return 0;
    }

    return -1;
}

/* Confere os campos obrigatorios do cadastro. */
static int dadosValidos(const Paciente *paciente) {
    return paciente != NULL &&

           textoValido(paciente->nome,
                       sizeof paciente->nome) &&

           cpfValido(paciente->cpf) &&

           dataValida(paciente->dataNascimento) &&

           textoValido(paciente->telefone,
                       sizeof paciente->telefone) &&

           textoValido(paciente->endereco,
                       sizeof paciente->endereco) &&

           textoValido(paciente->responsavel.nome,
                       sizeof paciente->responsavel.nome) &&

           cpfValido(paciente->responsavel.cpf) &&

           textoValido(paciente->responsavel.telefone,
                       sizeof paciente->responsavel.telefone) &&

           textoValido(paciente->responsavel.parentesco,
                       sizeof paciente->responsavel.parentesco) &&

           textoValido(paciente->responsavel.endereco,
                       sizeof paciente->responsavel.endereco);
}

/* =====================================================
   RF02.1 - CADASTRAR PACIENTE E RESPONSAVEL
   ===================================================== */

int cadastrarPaciente(const Usuario *usuarioLogado,
                      Paciente *paciente) {

    FILE *arquivo;
    Paciente atual;

    int maiorId = 0;
    int resultado;
    int erroFechamento;

    if (!usuarioPodeGerenciar(usuarioLogado) ||
        !dadosValidos(paciente)) {
        return 0;
    }

    /* O ID e o vinculo sao definidos pelo sistema. */
    paciente->id = 0;
    paciente->matriculaPsicologo = 0;

    arquivo = fopen(ARQUIVO_PACIENTES, "rb");

    if (arquivo != NULL) {

        while ((resultado = lerPaciente(arquivo, &atual)) == 1) {

            if (atual.id <= 0) {
                fclose(arquivo);
                return -1;
            }

            if (atual.id > maiorId) {
                maiorId = atual.id;
            }

            /* Impede CPF de paciente duplicado. */
            if (strcmp(atual.cpf, paciente->cpf) == 0) {
                fclose(arquivo);
                return 0;
            }
        }

        erroFechamento = fclose(arquivo);

        if (resultado == -1 || erroFechamento != 0) {
            return -1;
        }

    } else if (errno != ENOENT) {
        return -1;
    }

    if (maiorId == INT_MAX) {
        return -1;
    }

    /* Gera o proximo ID disponivel. */
    paciente->id = maiorId + 1;

    arquivo = fopen(ARQUIVO_PACIENTES, "ab");

    if (arquivo == NULL) {
        paciente->id = 0;
        return -1;
    }

    resultado = fwrite(paciente, sizeof(Paciente), 1, arquivo) == 1;

    erroFechamento = fclose(arquivo);

    if (!resultado || erroFechamento != 0) {
        paciente->id = 0;
        return -1;
    }

    return 1;
}

/* =====================================================
   RF02.2 - CONSULTAR PACIENTES
   ===================================================== */

int consultarPacientes(const Usuario *usuarioLogado,
                       const char *busca) {

    FILE *arquivo;
    Paciente paciente;

    int encontrou = 0;
    int resultado;
    int erroFechamento;

    if (!usuarioValido(usuarioLogado) ||
        busca == NULL || busca[0] == '\0') {
        return 0;
    }

    arquivo = fopen(ARQUIVO_PACIENTES, "rb");

    if (arquivo == NULL) {
        return errno == ENOENT ? 0 : -1;
    }

    while ((resultado = lerPaciente(arquivo, &paciente)) == 1) {

        /* Psicologo consulta somente seus pacientes. */
        if (usuarioLogado->perfil == 3 &&
            paciente.matriculaPsicologo != usuarioLogado->matricula) {
            continue;
        }

        if (contemTexto(paciente.nome, busca) ||
            contemTexto(paciente.cpf, busca) ||
            contemTexto(paciente.responsavel.nome, busca) ||
            contemTexto(paciente.responsavel.cpf, busca)) {

            printf("\n========== PACIENTE ==========\n");

            printf("ID: %d\n", paciente.id);
            printf("Nome: %s\n", paciente.nome);
            printf("CPF: %s\n", paciente.cpf);
            printf("Nascimento: %s\n", paciente.dataNascimento);
            printf("Telefone: %s\n", paciente.telefone);
            printf("Endereco: %s\n", paciente.endereco);

            printf("\n--- RESPONSAVEL ---\n");

            printf("Nome: %s\n", paciente.responsavel.nome);
            printf("CPF: %s\n", paciente.responsavel.cpf);

            printf("Telefone: %s\n",
                   paciente.responsavel.telefone);

            printf("Parentesco: %s\n",
                   paciente.responsavel.parentesco);

            printf("Endereco: %s\n",
                   paciente.responsavel.endereco);

            printf("\nMatricula do psicologo: %d\n",
                   paciente.matriculaPsicologo);

            encontrou = 1;
        }
    }

    erroFechamento = fclose(arquivo);

    if (resultado == -1 || erroFechamento != 0) {
        return -1;
    }

    return encontrou ? 1 : 0;
}

/* =====================================================
   BUSCAR PACIENTE PELO ID
   ===================================================== */

int buscarPacientePorId(const Usuario *usuarioLogado,
                        int idPaciente,
                        Paciente *pacienteEncontrado) {

    FILE *arquivo;
    Paciente paciente;

    int resultado;
    int erroFechamento;

    if (!usuarioValido(usuarioLogado) ||
        idPaciente <= 0 ||
        pacienteEncontrado == NULL) {
        return 0;
    }

    arquivo = fopen(ARQUIVO_PACIENTES, "rb");

    if (arquivo == NULL) {
        return errno == ENOENT ? 0 : -1;
    }

    while ((resultado = lerPaciente(arquivo, &paciente)) == 1) {

        if (paciente.id == idPaciente) {

            /* Psicologo nao acessa paciente de outro profissional. */
            if (usuarioLogado->perfil == 3 &&
                paciente.matriculaPsicologo != usuarioLogado->matricula) {

                fclose(arquivo);
                return 0;
            }

            erroFechamento = fclose(arquivo);

            if (erroFechamento != 0) {
                return -1;
            }

            *pacienteEncontrado = paciente;

            return 1;
        }
    }

    erroFechamento = fclose(arquivo);

    if (resultado == -1 || erroFechamento != 0) {
        return -1;
    }

    return 0;
}

/* =====================================================
   FUNCAO AUXILIAR PARA ALTERAR REGISTROS
   ===================================================== */

/*
 * modo 1 = atualizacao de contatos.
 * modo 2 = vinculo com psicologo.
 */
static int alterarPaciente(int idPaciente,
                           const Paciente *dados,
                           int matriculaPsicologo,
                           int modo) {

    FILE *original;
    FILE *temporario;

    Paciente atual;

    int encontrou = 0;
    int resultado;
    int erro = 0;
    int erroFechamento;

    original = fopen(ARQUIVO_PACIENTES, "rb");

    if (original == NULL) {
        return errno == ENOENT ? 0 : -1;
    }

    temporario = fopen(ARQUIVO_TEMPORARIO, "wb");

    if (temporario == NULL) {
        fclose(original);
        return -1;
    }

    while ((resultado = lerPaciente(original, &atual)) == 1) {

        if (atual.id == idPaciente) {

            if (modo == 1) {

                /* Atualiza somente os contatos permitidos. */

                memcpy(atual.telefone,
                       dados->telefone,
                       sizeof atual.telefone);

                memcpy(atual.endereco,
                       dados->endereco,
                       sizeof atual.endereco);

                memcpy(atual.responsavel.telefone,
                       dados->responsavel.telefone,
                       sizeof atual.responsavel.telefone);

                memcpy(atual.responsavel.endereco,
                       dados->responsavel.endereco,
                       sizeof atual.responsavel.endereco);

            } else if (modo == 2) {

                /* Impede substituir um vinculo existente. */
                if (atual.matriculaPsicologo != 0) {
                    break;
                }

                atual.matriculaPsicologo = matriculaPsicologo;
            }

            encontrou = 1;
        }

        if (fwrite(&atual, sizeof(Paciente), 1, temporario) != 1) {
            erro = 1;
            break;
        }
    }

    if (resultado == -1) {
        erro = 1;
    }

    erroFechamento = fclose(original);

    if (erroFechamento != 0) {
        erro = 1;
    }

    erroFechamento = fclose(temporario);

    if (erroFechamento != 0) {
        erro = 1;
    }

    if (erro || !encontrou) {
        remove(ARQUIVO_TEMPORARIO);
        return erro ? -1 : 0;
    }

    /* Substitui o arquivo antigo pelo atualizado. */
    if (rename(ARQUIVO_TEMPORARIO, ARQUIVO_PACIENTES) != 0) {
        remove(ARQUIVO_TEMPORARIO);
        return -1;
    }

    return 1;
}

/* =====================================================
   RF02.3 - ATUALIZAR CONTATOS DO PACIENTE
   ===================================================== */

int atualizarContatoPaciente(const Usuario *usuarioLogado,
                             const Paciente *paciente) {

    if (!usuarioPodeGerenciar(usuarioLogado) ||
        paciente == NULL ||
        paciente->id <= 0 ||

        !textoValido(paciente->telefone,
                     sizeof paciente->telefone) ||

        !textoValido(paciente->endereco,
                     sizeof paciente->endereco) ||

        !textoValido(paciente->responsavel.telefone,
                     sizeof paciente->responsavel.telefone) ||

        !textoValido(paciente->responsavel.endereco,
                     sizeof paciente->responsavel.endereco)) {

        return 0;
    }

    return alterarPaciente(
        paciente->id,
        paciente,
        0,
        1
    );
}

/* =====================================================
   APOIO AO PRIMEIRO AGENDAMENTO - VINCULAR PSICOLOGO
   ===================================================== */

int vincularPsicologo(const Usuario *usuarioLogado,
                      int idPaciente,
                      int matriculaPsicologo) {

    Usuario psicologo;
    int resultado;

    if (!usuarioPodeGerenciar(usuarioLogado) ||
        idPaciente <= 0 ||
        matriculaPsicologo <= 0) {
        return 0;
    }

    /* Busca os dados do profissional pela matricula. */
    resultado = buscarUsuarioPorMatricula(
        usuarioLogado,
        matriculaPsicologo,
        &psicologo
    );

    if (resultado != 1) {
        return resultado;
    }

    /* Confere perfil e situacao do profissional. */
    if (psicologo.perfil != 3 || psicologo.ativo != 1) {
        return 0;
    }

    /* Grava o vinculo somente se ainda nao existir. */
    return alterarPaciente(
        idPaciente,
        NULL,
        matriculaPsicologo,
        2
    );
}
