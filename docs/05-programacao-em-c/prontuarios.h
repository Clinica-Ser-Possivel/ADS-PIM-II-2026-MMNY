#ifndef PRONTUARIOS_H
#define PRONTUARIOS_H

#include "tipos.h"

/*
 * RF03.1 - Registra uma evolucao tecnica.
 * Permitido: somente o psicologo vinculado ao paciente.
 *
 * Confere paciente, vinculo, data e descricao.
 * Gera o ID da evolucao.
 * A matricula do autor vem do usuario conectado.
 *
 * Retornos: 1 = sucesso; 0 = recusado; -1 = erro de arquivo.
 */
int registrarEvolucao(const Usuario *usuarioLogado,
                      Evolucao *evolucao);

/*
 * RF03.2 - Exibe o historico de evolucoes do paciente,
 * organizado por data.
 *
 * Permitido: somente o psicologo vinculado ao paciente.
 * Administrador e recepcionista nao acessam o conteudo.
 *
 * Retornos:
 *  1 = encontrou e exibiu;
 *  0 = sem evolucoes ou acesso recusado;
 * -1 = erro de arquivo.
 */
int consultarProntuario(const Usuario *usuarioLogado,
                        int idPaciente);

#endif