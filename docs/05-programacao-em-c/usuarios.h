#ifndef USUARIOS_H
#define USUARIOS_H

#include "tipos.h"

int efetuarLogin(int matricula, const char *senha, Usuario *usuarioLogado);

int inicializarUsuarios(void);
/*
 * Cadastra um usuario em usuarios.dat.
 * Somente um administrador pode executar esta operacao.
 *
 * usuarioLogado: administrador que esta usando o sistema.
 * novoUsuario: dados do colaborador que sera cadastrado.
 *
 * Retornos:
 *  1 = cadastro realizado;
 *  0 = cadastro recusado por permissao ou dados invalidos,
 *      incluindo matricula ja existente;
 * -1 = erro ao abrir, ler ou gravar o arquivo.
 */
int cadastrarUsuario(const Usuario *usuarioLogado,
                     const Usuario *novoUsuario);


                     /*
 * Inativa um usuario sem apagar seu cadastro.
 * Somente um administrador ativo pode executar esta operacao.
 *
 * usuarioLogado: administrador que solicita a inativacao.
 * matricula: identifica o usuario que sera inativado.
 *
 * Retornos:
 *  1 = usuario inativado;
 *  0 = operacao recusada: sem permissao, matricula inexistente,
 *      usuario ja inativo ou tentativa de inativar a si mesmo;
 * -1 = erro ao acessar ou atualizar o arquivo.
 */
int inativarUsuario(const Usuario *usuarioLogado, int matricula);
                     
/*
 * Busca um colaborador pela matricula.
 * Exige usuario conectado e ativo.
 *
 * Administrador e recepcionista podem localizar colaboradores.
 * Psicologo pode localizar apenas seu proprio cadastro.
 *
 * Preenche usuarioEncontrado somente quando retorna 1.
 * Nao exibe nem devolve a senha: deixa esse campo vazio.
 *
 * Retornos: 1 = encontrou; 0 = nao encontrou ou sem acesso;
 * -1 = erro de arquivo.
 */
int buscarUsuarioPorMatricula(const Usuario *usuarioLogado,
                             int matricula,
                             Usuario *usuarioEncontrado);
                     
#endif