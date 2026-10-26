#ifndef PACIENTES_H
#define PACIENTES_H

#include "tipos.h"

/*
 * RF02.1 - Cadastra paciente e responsavel.
 * Permitido: administrador e recepcionista.
 *
 * A funcao gera o ID e inicia matriculaPsicologo com 0.
 * O ID gerado e devolvido no campo paciente->id.
 *
 * Retornos: 1 = sucesso; 0 = recusado; -1 = erro de arquivo.
 */
int cadastrarPaciente(const Usuario *usuarioLogado, Paciente *paciente);

/*
 * RF02.2 - Exibe cadastros encontrados por nome ou CPF
 * do paciente ou do responsavel.
 *
 * Administrador e recepcionista consultam todos.
 * Psicologo consulta somente pacientes vinculados a ele.
 *
 * Retornos:
 *  1 = encontrou e exibiu;
 *  0 = nenhum resultado acessivel ou acesso recusado;
 * -1 = erro de arquivo.
 */
int consultarPacientes(const Usuario *usuarioLogado, const char *busca);

/*
 * Busca um paciente pelo ID para uso dos outros modulos.
 * Preenche pacienteEncontrado somente quando retorna 1.
 * Respeita as mesmas permissoes de consulta.
 *
 * Retornos: 1 = encontrou; 0 = nao encontrou ou sem acesso;
 * -1 = erro de arquivo.
 */
int buscarPacientePorId(const Usuario *usuarioLogado,
                       int idPaciente,
                       Paciente *pacienteEncontrado);

/*
 * RF02.3 - Atualiza somente telefone e endereco
 * do paciente e do responsavel.
 * Usa paciente->id para localizar o cadastro.
 *
 * Permitido: administrador e recepcionista.
 * Preserva os demais campos, incluindo o vinculo profissional.
 *
 * Retornos: 1 = sucesso; 0 = recusado; -1 = erro de arquivo.
 */
int atualizarContatoPaciente(const Usuario *usuarioLogado,
                             const Paciente *paciente);

/*
 * Apoio ao primeiro agendamento: grava o primeiro vinculo.
 * Permitido: administrador e recepcionista.
 *
 * Confere se o paciente esta sem vinculo e se o profissional
 * existe, esta ativo e possui perfil de psicologo.
 *
 * Retornos: 1 = sucesso; 0 = recusado; -1 = erro de arquivo.
 */
int vincularPsicologo(const Usuario *usuarioLogado,
                     int idPaciente,
                     int matriculaPsicologo);

#endif