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