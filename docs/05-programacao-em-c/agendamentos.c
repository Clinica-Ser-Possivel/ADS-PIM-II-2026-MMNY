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