# Planejamento das Sprints — Clínica Ser Possível

Desenvolvimento do protótipo acadêmico em linguagem C, com interação pelo terminal e armazenamento local em arquivos `.dat`.

**Previsão de entrega final:** 10/11/2026.

## Equipe

| Integrante | Papel |
| :--- | :--- |
| Natalia Cristina Torres | Product Owner (PO) |
| Yasmin Silva Bonfim dos Santos | Scrum Master (SM) |
| Marcela Bueno dos Santos Scrum | Desenvolvedora (Dev) |
| Maria Victória Vieira Lopes | Desenvolvedora (Dev) |

## Sprint 01 — Identificação do problema e definição do projeto

**Período previsto:** 21/08/2026 a 09/09/2026.  
**Responsável:** Natalia Cristina Torres (PO).

**Objetivo:** compreender o contexto da clínica e definir o problema, os objetivos e o escopo inicial.

**Atividades previstas:**

- Caracterização da clínica e identificação das necessidades.
- Definição do problema, da justificativa e dos objetivos.
- Delimitação do escopo.
- Organização inicial do projeto e do repositório.

**Entrega concluída:** documentação inicial do projeto.  
**Documentação relacionada:** [Documentação inicial do projeto](docs/01-organizacao/README.md)

## Sprint 02 — Levantamento e análise de requisitos

**Período previsto:** 10/09/2026 a 29/09/2026.  
**Responsável:** Natalia Cristina Torres (PO).

**Objetivo:** definir as funcionalidades, as regras de negócio e as restrições do sistema.

**Atividades previstas:**

- Levantamento dos requisitos funcionais e não funcionais.
- Definição dos perfis de acesso.
- Documentação das regras de negócio.
- Organização e priorização do Product Backlog.

**Entrega concluída:** Product Backlog e regras de negócio documentadas.  
**Documentação relacionada:** [Product Backlog](../Backlog/BACKLOG.md)

## Sprint 03 — Modelagem e planejamento técnico

**Período previsto:** 30/09/2026 a 19/10/2026.  
**Responsáveis:** Natalia Cristina Torres (PO) e Marcela Bueno dos Santos Scrum (Dev).

**Objetivo:** representar a solução e planejar sua implementação.

**Atividades previstas:**

- Elaboração dos diagramas de casos de uso e de sequência.
- Modelagem das entidades e dos relacionamentos no DER.
- Planejamento dos módulos, das estruturas de dados e dos menus.
- Definição da persistência local e dos cenários de teste.

**Entrega prevista:** diagramas e planejamento técnico da implementação.
**Situação: Em andamento.**
**Documentação relacionada:** [Diagramas do sistema](../Diagramas/README.md)

## Sprint 04 — Implementação de usuários e pacientes

**Período previsto:** 20/10/2026 a 27/10/2026.  
**Responsáveis:** Natalia Cristina Torres (PO), Yasmin Silva Bonfim dos Santos (SM), Marcela Bueno dos Santos Scrum (Dev) e Maria Victória Vieira Lopes (Dev).

**Objetivo:** implementar a autenticação, o controle de acesso e os cadastros básicos.

**Atividades previstas:**

- Organização do programa em arquivos `.c` e `.h`.
- Implementação do cadastro, login e inativação de usuários.
- Atribuição automática dos perfis de acesso.
- Implementação do cadastro, consulta e atualização de pacientes e responsáveis.
- Gravação e recuperação dos dados em arquivos `.dat`.
- Validação dos dados e testes das funcionalidades.
- Continuidade da modelagem e revisão dos diagramas de sequência.

**Entrega prevista:** módulos de usuários e pacientes com persistência local.
**Situação: Iniciada. Em andamento.**

## Sprint 05 — Implementação de agendamento e prontuário

**Período previsto:** 28/10/2026 a 04/11/2026.  
**Responsáveis:** Natalia Cristina Torres (PO), Yasmin Silva Bonfim dos Santos (SM), Marcela Bueno dos Santos Scrum (Dev) e Maria Victória Vieira Lopes (Dev).

**Objetivo:** implementar as funcionalidades de agenda e registro dos atendimentos.

**Atividades previstas:**

- Implementação do agendamento, remarcação e cancelamento.
- Consulta de agendas e validação de conflitos de horário.
- Implementação do registro de evolução técnica e consulta ao prontuário.
- Aplicação das restrições por perfil e vínculo profissional.
- Persistência dos registros e testes de integração.

**Entrega prevista:** quatro módulos integrados: usuários, pacientes, agendamento e prontuário.

## Sprint 06 — Validação, documentação e entrega final

**Período previsto:** 05/11/2026 a 10/11/2026.  
**Responsáveis:** Natalia Cristina Torres (PO), Yasmin Silva Bonfim dos Santos (SM), Marcela Bueno dos Santos Scrum (Dev) e Maria Victória Vieira Lopes (Dev).

**Objetivo:** validar o protótipo e organizar a entrega final.

**Atividades previstas:**

- Testes das funcionalidades, do controle de acesso, da persistência e da integridade dos dados.
- Correção das falhas identificadas.
- Revisão do backlog, dos diagramas e da documentação.
- Preparação das instruções de compilação e execução.
- Gravação do vídeo de demonstração com dados fictícios.
- Preparação da apresentação e organização da versão final.

**Entrega prevista:** MVP acadêmico em C, documentação, resultados dos testes e vídeo de demonstração.

---

O detalhamento das atividades, os resultados e as evidências serão acrescentados nos registros completos de cada sprint.
