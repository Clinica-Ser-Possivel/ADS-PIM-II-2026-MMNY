
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "agendamentos.h"
#include "pacientes.h"
#include "usuarios.h"

#define ARQUIVO_AGENDAMENTOS "agendamentos.dat"
#define ARQUIVO_TEMPORARIO "agendamentos.tmp"

/* Verifica se o usuario pode gerenciar a agenda. */
static int usuarioPodeGerenciarAgenda(const Usuario *usuarioLogado) {

    if (usuarioLogado == NULL) {
        return 0;
    }

    if (usuarioLogado->ativo != 1) {
        return 0;
    }

    if (usuarioLogado->perfil != 1 &&
        usuarioLogado->perfil != 2) {
        return 0;
    }

    return 1;
}

/* Verifica se a data informada e valida. */
static int dataValida(const char *data) {
    int dia, mes, ano;
    int diasNoMes;

    if (data == NULL || strlen(data) != 10) {
        return 0;
    }

    if (sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano) != 3) {
        return 0;
    }

    if (data[2] != '/' || data[5] != '/') {
        return 0;
    }

    if (ano < 1900 || mes < 1 || mes > 12) {
        return 0;
    }

    diasNoMes = 31;

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasNoMes = 30;
    } else if (mes == 2) {
        diasNoMes = 28;

        if ((ano % 400 == 0) ||
            (ano % 4 == 0 && ano % 100 != 0)) {
            diasNoMes = 29;
        }
    }

    if (dia < 1 || dia > diasNoMes) {
        return 0;
    }

    return 1;
}

/* Verifica se o horario informado e valido. */
static int horarioValido(const char *horario) {
    int hora, minuto;

    if (horario == NULL || strlen(horario) != 5) {
        return 0;
    }

    if (horario[2] != ':') {
        return 0;
    }

    if (sscanf(horario, "%2d:%2d", &hora, &minuto) != 2) {
        return 0;
    }

    if (hora < 0 || hora > 23) {
        return 0;
    }

    if (minuto < 0 || minuto > 59) {
        return 0;
    }

    return 1;
}

/* Gera o proximo ID disponivel para um agendamento. */
static int gerarProximoId(int *proximoId) {
    FILE *arquivo;
    Agendamento atual;
    int maiorId = 0;
    size_t bytes;

    if (proximoId == NULL) {
        return -1;
    }

    arquivo = fopen(ARQUIVO_AGENDAMENTOS, "rb");

    if (arquivo == NULL) {
        if (errno == ENOENT) {
            *proximoId = 1;
            return 1;
        }

        return -1;
    }

    while ((bytes = fread(&atual, 1, sizeof(Agendamento), arquivo))
           == sizeof(Agendamento)) {

        if (atual.id > maiorId) {
            maiorId = atual.id;
        }
    }

    if (bytes != 0 || ferror(arquivo)) {
        fclose(arquivo);
        return -1;
    }

    if (fclose(arquivo) != 0) {
        return -1;
    }

    if (maiorId == INT_MAX) {
        return -1;
    }

    *proximoId = maiorId + 1;

    return 1;
}

/* Verifica se existe conflito de horario na agenda. */
static int horarioDisponivel(const char *data,
                             const char *horario,
                             int idIgnorado) {
    FILE *arquivo;
    Agendamento atual;
    size_t bytes;

    if (!dataValida(data) || !horarioValido(horario)) {
        return 0;
    }

    arquivo = fopen(ARQUIVO_AGENDAMENTOS, "rb");

    if (arquivo == NULL) {
        if (errno == ENOENT) {
            return 1;
        }

        return -1;
    }

    while ((bytes = fread(&atual, 1, sizeof(Agendamento), arquivo))
           == sizeof(Agendamento)) {

        if (atual.id != idIgnorado &&
            atual.situacao == 1 &&
            strcmp(atual.data, data) == 0 &&
            strcmp(atual.horario, horario) == 0) {

            fclose(arquivo);
            return 0;
        }
    }

    if (bytes != 0 || ferror(arquivo)) {
        fclose(arquivo);
        return -1;
    }

    if (fclose(arquivo) != 0) {
        return -1;
    }

    return 1;
}

/* Busca um agendamento pelo seu ID. */
static int buscarAgendamentoPorId(int id,
                                  Agendamento *encontrado) {
    FILE *arquivo;
    Agendamento atual;
    size_t bytes;

    if (id <= 0 || encontrado == NULL) {
        return 0;
    }

    arquivo = fopen(ARQUIVO_AGENDAMENTOS, "rb");

    if (arquivo == NULL) {
        if (errno == ENOENT) {
            return 0;
        }

        return -1;
    }

    while ((bytes = fread(&atual, 1, sizeof(Agendamento), arquivo))
           == sizeof(Agendamento)) {

        if (atual.id == id) {
            *encontrado = atual;

            if (fclose(arquivo) != 0) {
                return -1;
            }

            return 1;
        }
    }

    if (bytes != 0 || ferror(arquivo)) {
        fclose(arquivo);
        return -1;
    }

    if (fclose(arquivo) != 0) {
        return -1;
    }

    return 0;
}

