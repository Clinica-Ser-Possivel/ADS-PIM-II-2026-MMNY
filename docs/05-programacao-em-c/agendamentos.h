#ifndef AGENDAMENTOS_H
#define AGENDAMENTOS_H

#include "tipos.h"

/*
 * RF04.1 - Agenda uma consulta.
 * Permitido: administrador e recepcionista.
 *
 * Confere paciente, psicologo ativo, data, horario e conflitos.
 * Gera o ID e inicia situacao com 1 (agendado).
 *
 * No primeiro agendamento, utiliza o psicologo selecionado
 * e estabelece o vinculo com o paciente.
 * Nos seguintes, utiliza o profissional ja vinculado.
 *
 * Retornos: 1 = sucesso; 0 = recusado; -1 = erro de arquivo.
 */
int agendarConsulta(const Usuario *usuarioLogado,
                    Agendamento *agendamento);

/*
 * RF04.2 - Altera data e horario de uma consulta agendada.
 * Permitido: administrador e recepcionista.
 *
 * Confere disponibilidade, desconsiderando o proprio
 * agendamento na verificacao de conflito.
 * Preserva ID, paciente e psicologo.
 *
 * Retornos: 1 = sucesso; 0 = recusado; -1 = erro de arquivo.
 */
int remarcarConsulta(const Usuario *usuarioLogado,
                     int idAgendamento,
                     const char *novaData,
                     const char *novoHorario);

/*
 * RF04.2 - Muda situacao para 2 (cancelado).
 * Permitido: administrador e recepcionista.
 * Preserva o registro e o vinculo do paciente.
 *
 * Retornos: 1 = sucesso; 0 = recusado; -1 = erro de arquivo.
 */
int cancelarConsulta(const Usuario *usuarioLogado,
                     int idAgendamento);

/*
 * RF04.3 - Exibe consultas por data e profissional.
 *
 * Administrador e recepcionista consultam qualquer psicologo.
 * Psicologo consulta somente sua propria agenda.
 *
 * Retornos:
 *  1 = encontrou e exibiu;
 *  0 = nenhum resultado ou acesso recusado;
 * -1 = erro de arquivo.
 */
int consultarAgenda(const Usuario *usuarioLogado,
                    const char *data,
                    int matriculaPsicologo);

#endif