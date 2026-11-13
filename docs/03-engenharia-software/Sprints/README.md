# Planejamento das Sprints — Clínica Ser Possível

Desenvolvimento do protótipo acadêmico em linguagem C, com interação pelo terminal e armazenamento local em arquivos `.dat`.

**Previsão original de entrega final:** 10/11/2026. Prazo transcorrido; nova data e situação da entrega devem ser confirmadas pela equipe.

Os períodos abaixo preservam o planejamento original. A presença de código ou documentação no repositório não comprova aceite ou realização das cerimônias.

## Equipe

| Integrante | Papel |
| :--- | :--- |
| Natalia Cristina Torres | Product Owner (PO) |
| Yasmin Silva Bonfim dos Santos | Scrum Master (SM) |
| Marcela Bueno dos Santos | Desenvolvedora (Dev) |
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
**Documentação relacionada:** [Documentação inicial do projeto](../../01-organizacao/README.md)

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
**Responsáveis:** Natalia Cristina Torres (PO) e Marcela Bueno dos Santos (Dev).

**Objetivo:** representar a solução e planejar sua implementação.

**Atividades previstas:**

- Elaboração dos diagramas de casos de uso e de sequência.
- Modelagem das entidades e dos relacionamentos no DER.
- Planejamento dos módulos, das estruturas de dados e dos menus.
- Definição da persistência local e dos cenários de teste.

**Entrega prevista:** diagramas e planejamento técnico da implementação.  
**Situação: Em andamento. (Atrasado)**  
**Documentação relacionada:** [Diagramas do sistema](../Diagramas/)

## Sprint 04 — Implementação de usuários e pacientes

**Período previsto:** 20/10/2026 a 27/10/2026.  
**Responsáveis:** Natalia Cristina Torres (PO), Yasmin Silva Bonfim dos Santos (SM), Marcela Bueno dos Santos (Dev) e Maria Victória Vieira Lopes (Dev).

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
**Responsáveis:** Natalia Cristina Torres (PO), Yasmin Silva Bonfim dos Santos (SM), Marcela Bueno dos Santos (Dev) e Maria Victória Vieira Lopes (Dev).

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
**Responsáveis:** Natalia Cristina Torres (PO), Yasmin Silva Bonfim dos Santos (SM), Marcela Bueno dos Santos (Dev) e Maria Victória Vieira Lopes (Dev).

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

## Acompanhamento da implementação — verificação em 12/11/2026

| Sprint | Evidência disponível | Pendências para encerramento |
| --- | --- | --- |
| 01 | Documentação inicial disponível no repositório. | Registrar data, participantes e resultado da Review e da Retrospectiva, se realizadas. |
| 02 | Product Backlog documentado. | Registrar validação e decisões da equipe. |
| 03 | Quatro diagramas de sequência com READMEs, casos de uso e modelagem de dados disponíveis. | Revisar coerência com o código e registrar aceite; a publicação recente não altera o período originalmente planejado. |
| 04 | Login, cadastro e inativação de usuários disponíveis no menu; busca de usuário implementada; rotinas de pacientes presentes. | Integrar pacientes ao menu, corrigir atualização e preservação do vínculo e validar no Windows. |
| 05 | Rotinas de agendamento e prontuário presentes e compiladas com os demais módulos. | Integrar menus e testar fluxos, permissões, persistência e substituição de arquivos no Windows. |
| 06 | Compilação conjunta realizada nesta verificação, com aviso de função não utilizada. | Registrar testes completos, correções, aceite, vídeo e entrega; confirmar prazo atualizado. |

Compilar não comprova que os fluxos estejam funcionando corretamente. As rotinas ainda precisam de validação integrada.

## Cerimônias e registros

Os modelos de cada sprint estão em [Registros das cerimônias](CERIMONIAS.md). Campos pendentes devem ser preenchidos com fatos e evidências reais.

- **Sprint Planning:** definir objetivo, itens do backlog, responsáveis e critérios de aceite antes de iniciar o trabalho.
- **Daily Scrum:** inspeção breve do progresso em direção ao objetivo da sprint e ajuste do plano de trabalho. Registrar avanço, próximo passo, impedimento e encaminhamento. Quando o alinhamento ocorrer por mensagens, indicar o canal e registrar como alinhamento assíncrono.
- **Sprint Review:** apresentar o incremento, comparar com o objetivo e os critérios de aceite, colher feedback e atualizar o backlog. Código publicado não equivale a incremento aceito.
- **Sprint Retrospective:** avaliar a forma de trabalho e combinar melhorias concretas com responsável e acompanhamento na próxima sprint.

Não criar datas, presenças ou aprovações retroativas. Quando uma reunião não tiver ocorrido, registrar “não realizada”; quando não houver informação, registrar “a confirmar”.
