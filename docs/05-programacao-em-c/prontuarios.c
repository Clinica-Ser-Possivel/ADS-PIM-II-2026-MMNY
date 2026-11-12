#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#include "prontuarios.h"
#include "pacientes.h"

#define ARQUIVO_EVOLUCOES "evolucoes.dat"

/* =====================================================
   FUNCOES AUXILIARES
   ===================================================== */

/* Valida uma data no formato DD/MM/AAAA. */
static int validarData(const char *data) {
    int dia, mes, ano;

    int diasMes[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (data == NULL ||
        memchr(data, '\0', 11) == NULL ||
        strlen(data) != 10 ||
        data[2] != '/' ||
        data[5] != '/') {
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            continue;
        }

        if (!isdigit((unsigned char)data[i])) {
            return 0;
        }
    }

    dia = (data[0] - '0') * 10 + (data[1] - '0');
    mes = (data[3] - '0') * 10 + (data[4] - '0');

    ano = (data[6] - '0') * 1000 +
          (data[7] - '0') * 100 +
          (data[8] - '0') * 10 +
          (data[9] - '0');

    if (ano < 1900 || mes < 1 || mes > 12 || dia < 1) {
        return 0;
    }

    if (ano % 400 == 0 ||
        (ano % 4 == 0 && ano % 100 != 0)) {
        diasMes[1] = 29;
    }

    return dia <= diasMes[mes - 1];
}

/* Verifica se a descricao possui conteudo e terminacao valida. */
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

/* Valida um registro lido do arquivo. */
static int evolucaoValida(const Evolucao *evolucao) {
    return evolucao != NULL &&
           evolucao->id > 0 &&
           evolucao->idPaciente > 0 &&
           evolucao->matriculaPsicologo > 0 &&
           validarData(evolucao->data) &&
           descricaoValida(evolucao->descricao);
}

/*
 * Carrega todas as evolucoes do arquivo.
 *
 * Retornos:
 *  1 = leitura realizada;
 * -1 = erro de arquivo, memoria ou registro invalido.
 *
 * Arquivo inexistente significa lista vazia.
 */
static int carregarEvolucoes(Evolucao **lista,
                             size_t *quantidade) {
    FILE *arquivo;
    Evolucao evolucao;
    size_t capacidade = 0;

    if (lista == NULL || quantidade == NULL) {
        return -1;
    }

    *lista = NULL;
    *quantidade = 0;

    arquivo = fopen(ARQUIVO_EVOLUCOES, "rb");

    if (arquivo == NULL) {
        return errno == ENOENT ? 1 : -1;
    }

    while (1) {
        size_t lidos = fread(
            &evolucao,
            1,
            sizeof(Evolucao),
            arquivo
        );

        if (lidos == 0) {
            if (ferror(arquivo)) {
                free(*lista);
                *lista = NULL;
                *quantidade = 0;
                fclose(arquivo);
                return -1;
            }

            break;
        }

        /* Impede a leitura de registros incompletos. */
        if (lidos != sizeof(Evolucao) ||
            !evolucaoValida(&evolucao)) {
            free(*lista);
            *lista = NULL;
            *quantidade = 0;
            fclose(arquivo);
            return -1;
        }

        /* Aumenta a capacidade da lista quando necessario. */
        if (*quantidade == capacidade) {
            size_t novaCapacidade;

            if (capacidade == 0) {
                novaCapacidade = 10;
            } else {
                if (capacidade > (size_t)-1 / 2) {
                    free(*lista);
                    *lista = NULL;
                    *quantidade = 0;
                    fclose(arquivo);
                    return -1;
                }

                novaCapacidade = capacidade * 2;
            }

            if (novaCapacidade >
                (size_t)-1 / sizeof(Evolucao)) {
                free(*lista);
                *lista = NULL;
                *quantidade = 0;
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
                *quantidade = 0;
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

/* Converte DD/MM/AAAA em AAAAMMDD. */
static int converterData(const char *data) {
    int dia = (data[0] - '0') * 10 + (data[1] - '0');
    int mes = (data[3] - '0') * 10 + (data[4] - '0');

    int ano = (data[6] - '0') * 1000 +
              (data[7] - '0') * 100 +
              (data[8] - '0') * 10 +
              (data[9] - '0');

    return ano * 10000 + mes * 100 + dia;
}

/* Ordena evolucoes da mais antiga para a mais recente. */
static int compararEvolucoes(const void *a, const void *b) {
    const Evolucao *e1 = (const Evolucao *)a;
    const Evolucao *e2 = (const Evolucao *)b;

    int data1 = converterData(e1->data);
    int data2 = converterData(e2->data);

    if (data1 < data2) return -1;
    if (data1 > data2) return 1;

    if (e1->id < e2->id) return -1;
    if (e1->id > e2->id) return 1;

    return 0;
}

/* =====================================================
   RF03.1 - REGISTRAR EVOLUCAO
   ===================================================== */

int registrarEvolucao(const Usuario *usuarioLogado,
                      Evolucao *evolucao) {
    Paciente paciente;
    Evolucao *lista = NULL;
    Evolucao novaEvolucao;

    size_t quantidade = 0;

    int resultado;
    int maiorId = 0;

    /* Confere os argumentos. */
    if (usuarioLogado == NULL || evolucao == NULL) {
        return 0;
    }

    /* Somente psicologo ativo pode registrar evolucao. */
    if (usuarioLogado->perfil != 3 ||
        usuarioLogado->ativo != 1 ||
        usuarioLogado->matricula <= 0) {
        return 0;
    }

    /* Valida os dados informados. */
    if (evolucao->idPaciente <= 0 ||
        !validarData(evolucao->data) ||
        !descricaoValida(evolucao->descricao)) {
        return 0;
    }

    /* Localiza o paciente. */
    resultado = buscarPacientePorId(
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

    /* Confere o vinculo com o psicologo conectado. */
    if (paciente.matriculaPsicologo != usuarioLogado->matricula) {
        return 0;
    }

    /* Carrega as evolucoes para gerar o proximo ID. */
    resultado = carregarEvolucoes(&lista, &quantidade);

    if (resultado != 1) {
        return -1;
    }

    for (size_t i = 0; i < quantidade; i++) {
        if (lista[i].id > maiorId) {
            maiorId = lista[i].id;
        }
    }

    free(lista);

    if (maiorId == INT_MAX) {
        return -1;
    }

    /* Prepara o novo registro sem alterar os dados originais antes da gravacao. */
    novaEvolucao = *evolucao;

    novaEvolucao.id = maiorId + 1;
    novaEvolucao.matriculaPsicologo = usuarioLogado->matricula;

    /* Abre o arquivo para acrescentar a evolucao. */
    FILE *arquivo = fopen(ARQUIVO_EVOLUCOES, "ab");

    if (arquivo == NULL) {
        return -1;
    }

    resultado = fwrite(
        &novaEvolucao,
        sizeof(Evolucao),
        1,
        arquivo
    ) == 1;

    int erroFechamento = fclose(arquivo);

    if (!resultado || erroFechamento != 0) {
        return -1;
    }

    /* Devolve os dados gerados ao chamador. */
    *evolucao = novaEvolucao;

    return 1;
}

/* =====================================================
   RF03.2 - CONSULTAR PRONTUARIO
   ===================================================== */

int consultarProntuario(const Usuario *usuarioLogado,
                        int idPaciente) {
    Paciente paciente;
    Evolucao *lista = NULL;

    size_t quantidade = 0;

    int resultado;
    int encontrou = 0;

    /* Confere os argumentos. */
    if (usuarioLogado == NULL || idPaciente <= 0) {
        return 0;
    }

    /* Somente psicologo ativo pode consultar prontuario. */
    if (usuarioLogado->perfil != 3 ||
        usuarioLogado->ativo != 1 ||
        usuarioLogado->matricula <= 0) {
        return 0;
    }

    /* Busca o paciente pelo ID. */
    resultado = buscarPacientePorId(
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

    /* Carrega as evolucoes existentes. */
    resultado = carregarEvolucoes(&lista, &quantidade);

    if (resultado != 1) {
        return -1;
    }

    /* Ordena somente quando existem dois ou mais registros. */
    if (quantidade > 1) {
        qsort(
            lista,
            quantidade,
            sizeof(Evolucao),
            compararEvolucoes
        );
    }

    printf("\n====================================\n");
    printf("       PRONTUARIO DO PACIENTE\n");
    printf("====================================\n");

    printf("Paciente: %s\n", paciente.nome);
    printf("ID: %d\n", paciente.id);

    printf("------------------------------------\n");

    /* Exibe somente evolucoes do paciente e do psicologo conectado. */
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