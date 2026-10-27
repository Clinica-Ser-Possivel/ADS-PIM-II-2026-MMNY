# Requisitos x Rede e Sistemas Distribuídos

Os requisitos abaixo são os do backlog do grupo (`docs/03-engenharia-software/Backlog/BACKLOG.md`). A tabela mostra o que cada requisito significaria para a rede em uma implantação futura e qual é a situação atual no protótipo. Não foram criados requisitos novos de rede.

## Requisitos Funcionais

| ID | Requisito | Relação com Redes (proposta futura) | Situação no protótipo |
|---|---|---|---|
| RF01.1 | Cadastrar usuário | Em cliente-servidor, o cadastro seria enviado ao servidor por conexão segura | Implementado (parcial), local |
| RF01.2 | Efetuar login | Autenticação centralizada no servidor, com comunicação cifrada | Implementado, local |
| RF01.3 | Inativar usuário | A inativação valeria para todos os computadores ao mesmo tempo | Implementado, local |
| RF02.1 | Cadastrar paciente e responsável | Dados sensíveis exigiriam proteção em trânsito e no armazenamento | Pendente |
| RF02.2 | Consultar dados cadastrais | Consultas de vários computadores à mesma base | Pendente |
| RF02.3 | Atualizar dados | Controle de concorrência em edições simultâneas | Pendente |
| RF03.1 | Registrar evolução técnica | Sigilo da evolução na transmissão e no armazenamento | Pendente |
| RF03.2 | Consultar prontuário | Acesso restrito ao psicólogo vinculado, validado no servidor | Pendente |
| RF04.1 | Agendar consulta | O servidor verificaria conflito de horário antes de gravar | Pendente |
| RF04.2 | Remarcar ou cancelar | Atualização da agenda visível a todos os usuários autorizados | Pendente |
| RF04.3 | Visualizar agenda | Agenda compartilhada, com visão limitada por perfil | Pendente |

## Requisitos Não Funcionais

| ID | Requisito | Relação com Redes (proposta futura) | Situação no protótipo |
|---|---|---|---|
| RNF01 | Segurança e controle de acesso | Firewall, redes separadas, comunicação cifrada e logs, como recomendação | Parcial: login e perfis; restante é proposta |
| RNF02 | Persistência local (`.dat`) | Em uma evolução, o armazenamento passaria para um banco central | Atual: arquivos `.dat` locais |
| RNF03 | Integridade de dados | Backup, transações e controle de concorrência em ambiente compartilhado | Validações a completar e testar |
| RNF04 | Tempo de resposta (até 3 s, base de até 100 registros) | Em rede, o desempenho dependeria também de latência e capacidade, a medir | Medição pendente |

## Recomendações fora do backlog atual

- Separação entre rede de funcionários e de visitantes.
- Backup com teste de restauração e registro de acessos.
- Comunicação cifrada (HTTPS) em uma eventual arquitetura cliente-servidor.
- Lembretes automáticos de sessão (melhoria futura).
