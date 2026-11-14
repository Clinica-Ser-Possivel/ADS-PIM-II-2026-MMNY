
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "agendamentos.h"
#include "pacientes.h"
#include "usuarios.h"
#include "arquivos.h"

#define ARQUIVO_AGENDAMENTOS "agendamentos.dat"
#define ARQUIVO_TEMPORARIO "agendamentos.tmp"

/*
 * Verifica se o usuario pode gerenciar a agenda.
 * Perfis considerados:
 * 1 = administrador
 * 2 = recepcionista
 * 3 = psicologo
 */
static int usuarioValido(const Usuario *usuario) {
    return usuario != NULL &&
           usuario->matricula > 0 &&
           usuario->ativo == 1;
}

static int usuarioPodeGerenciarAgenda(const Usuario *usuario) {
    return usuarioValido(usuario) &&
           (usuario->perfil == 1 || usuario->perfil == 2);
}

/* Valida uma data no formato DD/MM/AAAA. */
static int dataValida(const char *data) {
    int dia, mes, ano;
    int diasNoMes;
    int i;

    if (data == NULL || memchr(data, '\0', 11) == NULL)
        return 0;

    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/')
        return 0;

    for (i = 0; i < 10; i++) {
        if (i != 2 && i != 5 &&
            (data[i] < '0' || data[i] > '9'))
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
        int bissexto = (ano % 400 == 0) ||
                       (ano % 4 == 0 && ano % 100 != 0);

        diasNoMes = bissexto ? 29 : 28;
    }

    return dia <= diasNoMes;
}

/* Valida um horario no formato HH:MM. */
static int horarioValido(const char *horario) {
    int hora, minuto;
    int i;

    if (horario == NULL || memchr(horario, '\0', 6) == NULL)
        return 0;

    if (strlen(horario) != 5 || horario[2] != ':')
        return 0;

    for (i = 0; i < 5; i++) {
        if (i != 2 &&
            (horario[i] < '0' || horario[i] > '9'))
            return 0;
    }

    hora = (horario[0] - '0') * 10 + horario[1] - '0';
    minuto = (horario[3] - '0') * 10 + horario[4] - '0';

    return hora >= 0 && hora <= 23 &&
           minuto >= 0 && minuto <= 59;
}

/* Valida um registro lido do arquivo. */
static int registroValido(const Agendamento *agendamento) {
    if (agendamento == NULL)
        return 0;

    return agendamento->id > 0 &&
           agendamento->idPaciente > 0 &&
           agendamento->matriculaPsicologo > 0 &&
           dataValida(agendamento->data) &&
           horarioValido(agendamento->horario) &&
           (agendamento->situacao == 1 ||
            agendamento->situacao == 2);
}

/* Gera o proximo ID disponivel. */
static int gerarProximoId(void) {
    FILE *arquivo;
    Agendamento atual;
    int maiorId = 0;
    size_t lidos;

    arquivo = fopen(ARQUIVO_AGENDAMENTOS, "rb");

    if (arquivo == NULL) {
        if (errno == ENOENT)
            return 1;

        return -1;
    }

    while ((lidos = fread(&atual, 1, sizeof(atual), arquivo)) ==
           sizeof(atual)) {

        if (!registroValido(&atual)) {
            fclose(arquivo);
            return -1;
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

    if (maiorId == INT_MAX)
        return -1;

    return maiorId + 1;
}

/*
 * Verifica se o psicologo possui outro agendamento
 * ativo na mesma data e horario.
 *
 * Retornos:
 * 1 = horario disponivel
 * 0 = horario ocupado
 * -1 = erro de arquivo
 */
static int horarioDisponivel(int matriculaPsicologo,
                             const char *data,
                             const char *horario,
                             int idIgnorado) {
    FILE *arquivo;
    Agendamento atual;
    size_t lidos;

    if (matriculaPsicologo <= 0 ||
        !dataValida(data) ||
        !horarioValido(horario))
        return -1;

    arquivo = fopen(ARQUIVO_AGENDAMENTOS, "rb");

    if (arquivo == NULL) {
        if (errno == ENOENT)
            return 1;

        return -1;
    }

    while ((lidos = fread(&atual, 1, sizeof(atual), arquivo)) ==
           sizeof(atual)) {

        if (!registroValido(&atual)) {
            fclose(arquivo);
            return -1;
        }

        if (atual.id != idIgnorado &&
            atual.matriculaPsicologo == matriculaPsicologo &&
            atual.situacao == 1 &&
            strcmp(atual.data, data) == 0 &&
            strcmp(atual.horario, horario) == 0) {

            if (fclose(arquivo) != 0)
                return -1;

            return 0;
        }
    }

    if (lidos != 0 || ferror(arquivo)) {
        fclose(arquivo);
        return -1;
    }

    if (fclose(arquivo) != 0)
        return -1;

    return 1;
}

/* Procura um agendamento pelo ID. */
static int buscarAgendamentoPorId(int id, Agendamento *encontrado) {
    FILE *arquivo;
    Agendamento atual;
    size_t lidos;

    if (id <= 0 || encontrado == NULL)
        return -1;

    arquivo = fopen(ARQUIVO_AGENDAMENTOS, "rb");

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

        if (atual.id == id) {
            *encontrado = atual;

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
 * Remove um agendamento pelo ID.
 * Utilizado para tentar desfazer uma gravação
 * caso o vinculo do paciente nao seja realizado.
 */
static int removerAgendamentoPorId(int id) {
    FILE *origem;
    FILE *temporario;
    Agendamento atual;
    size_t lidos;
    int encontrou = 0;
    int erro = 0;

    origem = fopen(ARQUIVO_AGENDAMENTOS, "rb");

    if (origem == NULL)
        return 0;

    temporario = fopen(ARQUIVO_TEMPORARIO, "wb");

    if (temporario == NULL) {
        fclose(origem);
        return 0;
    }

    while ((lidos = fread(&atual, 1, sizeof(atual), origem)) ==
           sizeof(atual)) {

        if (!registroValido(&atual)) {
            erro = 1;
            break;
        }

        if (atual.id == id) {
            encontrou = 1;
            continue;
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
        return 0;
    }

    if (!substituirArquivo(ARQUIVO_TEMPORARIO, ARQUIVO_AGENDAMENTOS)) {
        remove(ARQUIVO_TEMPORARIO);
        return 0;
    }

    return 1;
}

/*
 * RF04.1 - Agendar consulta.
 * Permitido: administrador e recepcionista.
 *
 * Retornos:
 * 1 = sucesso
 * 0 = recusado
 * -1 = erro de arquivo
 */
int agendarConsulta(const Usuario *usuarioLogado,
                    Agendamento *agendamento) {
    FILE *arquivo;
    Paciente paciente;
    Usuario psicologo;
    Agendamento novo;
    int resultado;
    int novoId;

    if (!usuarioPodeGerenciarAgenda(usuarioLogado) || agendamento == NULL) {
        puts("Sem permissao para agendar: entre como Administrador ou Recepcao ativo.");
        return 0;
    }

    if (agendamento->idPaciente <= 0) {
        puts("ID do paciente invalido.");
        return 0;
    }
    if (!dataValida(agendamento->data)) {
        puts("Data invalida. Use DD/MM/AAAA e uma data existente.");
        return 0;
    }
    if (!horarioValido(agendamento->horario)) {
        puts("Horario invalido. Use HH:MM, de 00:00 a 23:59.");
        return 0;
    }

    resultado = buscarPacientePorId(
        usuarioLogado,
        agendamento->idPaciente,
        &paciente
    );

    if (resultado != 1) {
        if (resultado == 0) puts("Paciente nao encontrado.");
        return resultado == -1 ? -1 : 0;
    }

    if (paciente.matriculaPsicologo > 0) {
        agendamento->matriculaPsicologo =
            paciente.matriculaPsicologo;
    }

    if (agendamento->matriculaPsicologo <= 0) {
        puts("Matricula do psicologo invalida.");
        return 0;
    }

    resultado = buscarUsuarioPorMatricula(
        usuarioLogado,
        agendamento->matriculaPsicologo,
        &psicologo
    );

    if (resultado != 1) {
        if (resultado == 0) puts("Psicologo nao encontrado. Confira a matricula.");
        return resultado == -1 ? -1 : 0;
    }

    if (psicologo.perfil != 3) {
        puts("O colaborador informado nao tem perfil de Psicologo.");
        return 0;
    }
    if (!usuarioValido(&psicologo)) {
        puts("Psicologo inativo. Nao e possivel agendar com este profissional.");
        return 0;
    }

    resultado = horarioDisponivel(
        agendamento->matriculaPsicologo,
        agendamento->data,
        agendamento->horario,
        0
    );

    if (resultado != 1) {
        if (resultado == 0) puts("Horario ocupado. Escolha outra data ou horario.");
        return resultado == 0 ? 0 : -1;
    }

    novoId = gerarProximoId();

    if (novoId <= 0)
        return -1;

    novo = *agendamento;
    novo.id = novoId;
    novo.situacao = 1;

    arquivo = fopen(ARQUIVO_AGENDAMENTOS, "ab");

    if (arquivo == NULL)
        return -1;

    if (fwrite(&novo, sizeof(novo), 1, arquivo) != 1) {
        fclose(arquivo);
        return -1;
    }

    if (fclose(arquivo) != 0)
        return -1;

    /*
     * Se o paciente ainda nao possui psicologo,
     * realiza o vinculo depois de gravar a consulta.
     */
    if (paciente.matriculaPsicologo == 0) {
        resultado = vincularPsicologo(
            usuarioLogado,
            paciente.id,
            novo.matriculaPsicologo
        );

        if (resultado != 1) {
            if (!removerAgendamentoPorId(novo.id)) {
                fprintf(stderr, "Falha ao desfazer a consulta %d. "
                        "Confira os arquivos antes de tentar novamente.\n", novo.id);
                return -1;
            }
            return resultado == -1 ? -1 : 0;
        }
    }

    *agendamento = novo;

    return 1;
}

/*
 * RF04.2 - Remarcar consulta.
 * Permitido: administrador e recepcionista.
 */
int remarcarConsulta(const Usuario *usuarioLogado,
                     int idAgendamento,
                     const char *novaData,
                     const char *novoHorario) {
    FILE *origem;
    FILE *temporario;
    Agendamento atual;
    size_t lidos;
    int encontrou = 0;
    int erro = 0;
    int resultado;

    if (!usuarioPodeGerenciarAgenda(usuarioLogado)) {
        puts("Sem permissao para alterar a agenda.");
        return 0;
    }

    if (idAgendamento <= 0) {
        puts("ID do agendamento invalido.");
        return 0;
    }
    if (!dataValida(novaData)) {
        puts("Data invalida. Use DD/MM/AAAA e uma data existente.");
        return 0;
    }
    if (!horarioValido(novoHorario)) {
        puts("Horario invalido. Use HH:MM, de 00:00 a 23:59.");
        return 0;
    }

    resultado = buscarAgendamentoPorId(idAgendamento, &atual);

    if (resultado != 1) {
        if (resultado == 0) puts("Agendamento nao encontrado. Confira o ID.");
        return resultado == -1 ? -1 : 0;
    }

    if (atual.situacao != 1) {
        puts("Esta consulta ja esta cancelada.");
        return 0;
    }

    resultado = horarioDisponivel(
        atual.matriculaPsicologo,
        novaData,
        novoHorario,
        idAgendamento
    );

    if (resultado != 1) {
        if (resultado == 0) puts("Horario ocupado. Escolha outra data ou horario.");
        return resultado == 0 ? 0 : -1;
    }

    origem = fopen(ARQUIVO_AGENDAMENTOS, "rb");

    if (origem == NULL)
        return -1;

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

        if (atual.id == idAgendamento) {
            strcpy(atual.data, novaData);
            strcpy(atual.horario, novoHorario);
            encontrou = 1;
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
        return erro ? -1 : 0;
    }

    if (!substituirArquivo(ARQUIVO_TEMPORARIO, ARQUIVO_AGENDAMENTOS)) {
        remove(ARQUIVO_TEMPORARIO);
        return -1;
    }

    return 1;
}

/*
 * RF04.2 - Cancelar consulta.
 * Permitido: administrador e recepcionista.
 */
int cancelarConsulta(const Usuario *usuarioLogado,
                     int idAgendamento) {
    FILE *origem;
    FILE *temporario;
    Agendamento atual;
    size_t lidos;
    int encontrou = 0;
    int erro = 0;
    int resultado;

    if (!usuarioPodeGerenciarAgenda(usuarioLogado)) {
        puts("Sem permissao para alterar a agenda.");
        return 0;
    }

    if (idAgendamento <= 0)
        return 0;

    resultado = buscarAgendamentoPorId(idAgendamento, &atual);

    if (resultado != 1) {
        if (resultado == 0) puts("Agendamento nao encontrado. Confira o ID.");
        return resultado == -1 ? -1 : 0;
    }

    if (atual.situacao != 1) {
        puts("Esta consulta ja esta cancelada.");
        return 0;
    }

    origem = fopen(ARQUIVO_AGENDAMENTOS, "rb");

    if (origem == NULL)
        return -1;

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

        if (atual.id == idAgendamento) {
            atual.situacao = 2;
            encontrou = 1;
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
        return erro ? -1 : 0;
    }

    if (!substituirArquivo(ARQUIVO_TEMPORARIO, ARQUIVO_AGENDAMENTOS)) {
        remove(ARQUIVO_TEMPORARIO);
        return -1;
    }

    return 1;
}

/*
 * RF04.3 - Consultar agenda.
 *
 * Psicologo: consulta somente a propria agenda.
 * Administrador e recepcionista: podem consultar
 * a agenda de qualquer psicologo.
 */
int consultarAgenda(const Usuario *usuarioLogado,
                    const char *data,
                    int matriculaPsicologo) {
    FILE *arquivo;
    Agendamento atual;
    size_t lidos;
    int encontrou = 0;

    if (!usuarioValido(usuarioLogado))
        return 0;

    if (!dataValida(data) || matriculaPsicologo <= 0)
        return 0;

    if (usuarioLogado->perfil == 3) {
        if (usuarioLogado->matricula != matriculaPsicologo)
            return 0;
    } else if (!usuarioPodeGerenciarAgenda(usuarioLogado)) {
        return 0;
    }

    arquivo = fopen(ARQUIVO_AGENDAMENTOS, "rb");

    if (arquivo == NULL) {
        if (errno == ENOENT) {
            printf("Nenhum agendamento cadastrado.\n");
            return 0;
        }

        return -1;
    }

    printf("\n===== AGENDA =====\n");
    printf("Data: %s\n", data);

    while ((lidos = fread(&atual, 1, sizeof(atual), arquivo)) ==
           sizeof(atual)) {

        if (!registroValido(&atual)) {
            fclose(arquivo);
            return -1;
        }

        if (atual.data[0] != '\0' &&
            atual.matriculaPsicologo == matriculaPsicologo &&
            strcmp(atual.data, data) == 0) {

            printf("\nID: %d\n", atual.id);
            printf("Paciente: %d\n", atual.idPaciente);
            printf("Psicologo: %d\n", atual.matriculaPsicologo);
            printf("Horario: %s\n", atual.horario);
            printf("Situacao: %s\n",
                   atual.situacao == 1 ? "Agendado" : "Cancelado");

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
        printf("Nenhum agendamento encontrado para esta data.\n");

    return encontrou ? 1 : 0;
}
