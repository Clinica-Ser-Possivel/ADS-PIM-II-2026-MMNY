
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#include "prontuarios.h"
#include "pacientes.h"

#define ARQUIVO_EVOLUCOES "evolucoes.dat"

/*
 * Verifica se a data esta no formato DD/MM/AAAA
 * e se representa uma data valida no calendario.
 */
static int validarData(const char *data) {
    if (data == NULL ||
        memchr(data, '\0', 11) == NULL ||
        strlen(data) != 10) {
        return 0;
    }

    if (data[2] != '/' || data[5] != '/') {
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && !isdigit((unsigned char)data[i])) {
            return 0;
        }
    }

    int dia = (data[0] - '0') * 10 + (data[1] - '0');
    int mes = (data[3] - '0') * 10 + (data[4] - '0');

    int ano = (data[6] - '0') * 1000 +
              (data[7] - '0') * 100 +
              (data[8] - '0') * 10 +
              (data[9] - '0');

    if (ano < 1 || mes < 1 || mes > 12 || dia < 1) {
        return 0;
    }

    int diasMes[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    /* Verifica se o ano e bissexto. */
    if ((ano % 400 == 0) ||
        (ano % 4 == 0 && ano % 100 != 0)) {
        diasMes[1] = 29;
    }

    return dia <= diasMes[mes - 1];
}

/*
 * Verifica se a descricao possui algum conteudo.
 */
static int descricaoValida(const char *descricao) {
    if (descricao == NULL ||
        memchr(descricao, '\0', 2000) == NULL) {
        return 0;
    }

    for (int i = 0; descricao[i] != '\0'; i++) {
        if (!isspace((unsigned char)descricao[i])) {
            return 1;
        }
    }

    return 0;
}

/*
 * Carrega todas as evolucoes do arquivo.
 *
 * Retornos:
 *  1 = leitura realizada;
 * -1 = erro de arquivo ou memoria.
 *
 * Se o arquivo ainda nao existir, considera
 * que nao existem evolucoes cadastradas.
 */
static int carregarEvolucoes(Evolucao **lista,
                            size_t *quantidade) {

    if (lista == NULL || quantidade == NULL) {
        return -1;
    }

    *lista = NULL;
    *quantidade = 0;

    FILE *arquivo = fopen(ARQUIVO_EVOLUCOES, "rb");

    if (arquivo == NULL) {
        return errno == ENOENT ? 1 : -1;
    }

    Evolucao evolucao;
    size_t capacidade = 0;

    while (1) {
        size_t lidos = fread(&evolucao, 1,
                             sizeof(Evolucao), arquivo);

        if (lidos == 0) {
            if (ferror(arquivo)) {
                free(*lista);
                *lista = NULL;
                fclose(arquivo);
                return -1;
            }

            break;
        }

        /* Impede a leitura de registros incompletos. */
        if (lidos != sizeof(Evolucao)) {
            free(*lista);
            *lista = NULL;
            fclose(arquivo);
            return -1;
        }

        /* Aumenta o espaco da lista quando necessario. */
        if (*quantidade == capacidade) {
            size_t novaCapacidade = capacidade == 0
                ? 10
                : capacidade * 2;

            if (novaCapacidade < capacidade ||
                novaCapacidade > (size_t)-1 / sizeof(Evolucao)) {
                free(*lista);
                *lista = NULL;
                fclose(arquivo);
                return -1;
            }

            Evolucao *novaLista = realloc(
                *lista,
                novaCapacidade * sizeof(Evolucao)
            );

            if (novaLista == NULL) {
                free(*lista);
                *lista = NULL;
                fclose(arquivo);
                return -1;
            }

            *lista = novaLista;
            capacidade = novaCapacidade;
        }

        (*lista)[*quantidade] = evolucao;
        (*quantidade)++;
    }

    if (fclose(arquivo) != 0) {
        free(*lista);
        *lista = NULL;
        *quantidade = 0;
        return -1;
    }

    return 1;
}

/*
 * Transforma DD/MM/AAAA em um numero AAAAMMDD
 * para permitir a organizacao cronologica.
 */
static int converterData(const char *data) {
    int dia = (data[0] - '0') * 10 + (data[1] - '0');
    int mes = (data[3] - '0') * 10 + (data[4] - '0');

    int ano = (data[6] - '0') * 1000 +
              (data[7] - '0') * 100 +
              (data[8] - '0') * 10 +
              (data[9] - '0');

    return ano * 10000 + mes * 100 + dia;
}

/*
 * Compara duas evolucoes pela data.
 * A ordem sera da mais antiga para a mais recente.
 */
static int compararEvolucoes(const void *a, const void *b) {
    const Evolucao *e1 = a;
    const Evolucao *e2 = b;

    int data1 = converterData(e1->data);
    int data2 = converterData(e2->data);

    if (data1 < data2) return -1;
    if (data1 > data2) return 1;

    if (e1->id < e2->id) return -1;
    if (e1->id > e2->id) return 1;

    return 0;
}

/*
 * RF03.1
 * Registra uma evolucao tecnica.
 *
 * Somente o psicologo ativo vinculado ao paciente
 * pode registrar uma evolucao.
 */
int registrarEvolucao(const Usuario *usuarioLogado,
                      Evolucao *evolucao) {

    /* Confere se existe um usuario conectado e ativo. */
    if (usuarioLogado == NULL || evolucao == NULL) {
        return 0;
    }

    /* Somente psicologos ativos podem registrar evolucoes. */
    if (usuarioLogado->perfil != 3 ||
        usuarioLogado->ativo != 1 ||
        usuarioLogado->matricula <= 0) {
        return 0;
    }

    /* Confere os dados obrigatorios. */
    if (evolucao->idPaciente <= 0 ||
        !validarData(evolucao->data) ||
        !descricaoValida(evolucao->descricao)) {
        return 0;
    }

    Paciente paciente;

    /*
     * Busca o paciente pelo ID.
     * A funcao tambem respeita as permissoes do modulo
     * de pacientes.
     */
    int resultado = buscarPacientePorId(
        usuarioLogado,
        evolucao->idPaciente,
        &paciente
    );

    if (resultado == -1) {
        return -1;
    }

    if (resultado != 1) {
        return 0;
    }

    /*
     * Confere se o paciente esta vinculado
     * ao psicologo que esta conectado.
     */
    if (paciente.matriculaPsicologo != usuarioLogado->matricula) {
        return 0;
    }

    /* Carrega os registros existentes para gerar um ID unico. */
    Evolucao *lista = NULL;
    size_t quantidade = 0;

    if (carregarEvolucoes(&lista, &quantidade) != 1) {
        return -1;
    }

    int maiorId = 0;

    for (size_t i = 0; i < quantidade; i++) {
        if (lista[i].id > maiorId) {
            maiorId = lista[i].id;
        }
    }

    free(lista);

    if (maiorId == INT_MAX) {
        return -1;
    }

    /* Prepara uma copia para preservar os dados originais. */
    Evolucao novaEvolucao = *evolucao;

    /* Gera o ID e identifica automaticamente o autor. */
    novaEvolucao.id = maiorId + 1;
    novaEvolucao.matriculaPsicologo = usuarioLogado->matricula;

    /* Abre o arquivo para acrescentar uma nova evolucao. */
    FILE *arquivo = fopen(ARQUIVO_EVOLUCOES, "ab");

    if (arquivo == NULL) {
        return -1;
    }

    int gravou = fwrite(
        &novaEvolucao,
        sizeof(Evolucao),
        1,
        arquivo
    );

    int fechou = fclose(arquivo);

    if (gravou != 1 || fechou != 0) {
        return -1;
    }

    /* Devolve os dados efetivamente registrados. */
    *evolucao = novaEvolucao;

    return 1;
}

/*
 * RF03.2
 * Consulta o historico de evolucoes de um paciente.
 *
 * Somente o psicologo vinculado pode consultar
 * o conteudo clinico.
 */
int consultarProntuario(const Usuario *usuarioLogado,
                        int idPaciente) {

    /* Confere o usuario conectado. */
    if (usuarioLogado == NULL || idPaciente <= 0) {
        return 0;
    }

    /* Administradores e recepcionistas nao acessam prontuarios. */
    if (usuarioLogado->perfil != 3 ||
        usuarioLogado->ativo != 1 ||
        usuarioLogado->matricula <= 0) {
        return 0;
    }

    Paciente paciente;

    /* Localiza o paciente pelo identificador. */
    int resultado = buscarPacientePorId(
        usuarioLogado,
        idPaciente,
        &paciente
    );

    if (resultado == -1) {
        return -1;
    }

    if (resultado != 1) {
        return 0;
    }

    /* Confere o vinculo entre paciente e psicologo. */
    if (paciente.matriculaPsicologo != usuarioLogado->matricula) {
        return 0;
    }

    Evolucao *lista = NULL;
    size_t quantidade = 0;

    /* Carrega as evolucoes salvas. */
    if (carregarEvolucoes(&lista, &quantidade) != 1) {
        return -1;
    }

    /* Organiza os registros pela data. */
    qsort(
        lista,
        quantidade,
        sizeof(Evolucao),
        compararEvolucoes
    );

    int encontrou = 0;

    printf("\n====================================\n");
    printf("       PRONTUARIO DO PACIENTE\n");
    printf("====================================\n");

    printf("Paciente: %s\n", paciente.nome);
    printf("ID: %d\n", paciente.id);

    printf("------------------------------------\n");

    /* Exibe somente as evolucoes do paciente e do psicologo. */
    for (size_t i = 0; i < quantidade; i++) {

        if (lista[i].idPaciente == idPaciente &&
            lista[i].matriculaPsicologo == usuarioLogado->matricula) {

            encontrou = 1;

            printf("\nEvolucao ID: %d\n", lista[i].id);
            printf("Data: %s\n", lista[i].data);
            printf("Psicologo: %s\n", usuarioLogado->nome);
            printf("Descricao:\n%s\n", lista[i].descricao);

            printf("------------------------------------\n");
        }
    }

    free(lista);

    if (!encontrou) {
        printf("Nenhuma evolucao encontrada para este paciente.\n");
        return 0;
    }

    printf("\nFim do historico do paciente.\n");

    return 1;
}
