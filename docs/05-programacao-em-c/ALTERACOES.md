# Alterações para revisão

Base: cópia dos arquivos consultados no repositório da Clínica Ser Possível em 12/11/2026.
Revisão incorporada à cópia vinculada ao repositório em 14/11/2026 para commit local. O envio ao GitHub é uma etapa separada.

## Arquivos modificados

### main.c

- Integra pacientes, agendamentos e prontuários aos menus dos três perfis.
- Mantém cadastro e inativação de usuários disponíveis ao Administrador.
- Permite trocar de usuário sem fechar o programa.
- Lê linhas inteiras, rejeita números inválidos e textos acima do limite.
- Encerra ao fechar a entrada, sem gravar um cadastro incompleto.
- Pede a matrícula do psicólogo somente no primeiro agendamento.
- Mostra os identificadores gerados e confirma somente quando a função retorna sucesso.

### pacientes.c

- Atualiza somente telefone e endereço do paciente e do responsável.
- Preserva nome, CPF, nascimento, identidade do responsável, identificador e vínculo profissional.
- Aceita o identificador e os quatro campos de contato, sem exigir o cadastro inteiro.
- Busca por nome ou CPF do paciente ou responsável e exibe os dados de ambos.
- Mantém o filtro por vínculo quando a consulta é feita pelo Psicólogo.
- Usa substituição de arquivos compatível com Windows.
- Corrige comentários de numeração dos RF e remove uma função auxiliar não utilizada.
- Diferencia a recusa de um segundo vínculo de uma falha de arquivo.

### agendamentos.c

- Usa substituição de arquivos compatível com Windows ao remarcar, cancelar ou desfazer consulta.
- Verifica a recuperação quando não consegue gravar o primeiro vínculo.
- Corrige comentários: remarcação/cancelamento são RF04.2 e consulta de agenda é RF04.3.

## Arquivos novos

- arquivos.h: usa a substituição de destino do Windows sem apagar previamente o original. Em outros sistemas, usa rename.
- testes/testes.c e testes/executar.py: regressão, integração, persistência, permissões e falhas.
- Documentação local de compilação e resultados.

## Arquivos preservados

usuarios.c, usuarios.h, tipos.h, agendamentos.h, prontuarios.c e prontuarios.h mantêm o conteúdo da cópia consultada.
Não foram alteradas estruturas de dados ou assinaturas das funções existentes.

## Atualização das mensagens e formulários

- validacoes.h compartilha as regras de CPF, data e horário com a interface.
- pacientes.h declara uma nova consulta de disponibilidade de CPF; as funções existentes mantêm seus contratos.
- CPF inválido ou duplicado repete somente o campo, mantendo os outros dados.
- Datas e horários inválidos também são solicitados novamente no próprio formulário.
- Agendamento explica psicólogo inexistente, perfil incorreto, psicólogo inativo e horário ocupado.
- Remarcação e cancelamento identificam agendamento inexistente ou já cancelado.
- Foram acrescentados testes de repetição de campo, nomes preservados, duplicação, encerramento durante correção e mensagens de recusa.

## Limites

- O programa continua sendo um protótipo acadêmico de terminal, com dados fictícios.
- Não foi adicionado banco de dados nem uso simultâneo.
- A evolução técnica é digitada em uma linha, com até 1999 caracteres.
- O ensaio de desempenho do RNF04 com 100 registros não foi realizado.
- A revisão da equipe continua recomendada antes da adoção definitiva.
