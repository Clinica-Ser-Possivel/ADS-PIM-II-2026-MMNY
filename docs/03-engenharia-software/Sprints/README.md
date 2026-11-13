# Planejamento das Sprints — Clínica Ser Possível

Desenvolvimento do protótipo acadêmico em linguagem C, com interação pelo terminal e armazenamento local em arquivos `.dat`.

**Entrega final atualizada: 13/11/2026.** Prazo confirmado por Natalia em 12/11/2026. A previsão anterior era 10/11/2026; a Sprint 06 foi estendida até 13/11/2026.

Os períodos abaixo preservam o planejamento original. A presença de código ou documentação no repositório não comprova aceite ou realização das cerimônias.

## Equipe

| Integrante | Papel |
| :--- | :--- |
| Natalia Cristina Torres | Product Owner (PO) e Dev — módulo 1: usuários |
| Yasmin Silva Bonfim dos Santos | Scrum Master (SM) e Dev — módulo 2: pacientes e responsáveis |
| Marcela Bueno dos Santos | Dev — módulo 3: prontuários |
| Maria Victória Vieira Lopes | Dev — módulo 4: agendamento |
| Giulianna Menezes Paes Landim | Desenvolvedora (Dev), com foco em testes e revisão |

## Autoria e distribuição por módulo

Divisão de implementação informada por Natalia:

| Módulo | Responsável pela implementação | Sprint de referência | Responsabilidade na validação final |
| --- | --- | --- | --- |
| 1 — Usuários | Natalia Cristina Torres | 04 | Corrigir login, cadastro, inativação e busca de usuários. |
| 2 — Pacientes e responsáveis | Yasmin Silva Bonfim dos Santos | 04 | Corrigir cadastro, busca, contato e vínculo do paciente. |
| 3 — Prontuários | Marcela Bueno dos Santos | 05 | Corrigir registro e consulta de evoluções e restrições por vínculo. |
| 4 — Agendamento | Maria Victória Vieira Lopes | 05 | Corrigir agenda, conflitos, remarcação e cancelamento. |
| Testes e revisão dos quatro módulos | Giulianna Menezes Paes Landim — responsabilidade atribuída | 04 a partir de 25/10; apoio na 05 e consolidação na 06 | Executar casos, registrar falhas e conferir correções. |

Natalia também responde pelas prioridades e pelo backlog como PO; Yasmin também facilita o acompanhamento como SM. A autoria dos módulos não comprova sua conclusão dentro das datas originalmente planejadas. A revisão e as correções assistidas posteriores são registradas separadamente.

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
**Responsáveis:** Natalia (PO e referência do módulo de usuários), Yasmin (SM e referência de pacientes), Marcela (prontuários) e Maria Victória (agendamento), para alinhamento técnico dos módulos.

**Objetivo:** representar a solução e planejar sua implementação.

**Atividades previstas:**

- Elaboração dos diagramas de casos de uso e de sequência.
- Modelagem das entidades e dos relacionamentos no DER.
- Planejamento dos módulos, das estruturas de dados e dos menus.
- Definição da persistência local e dos cenários de teste.

**Entrega prevista:** diagramas e planejamento técnico da implementação.  
**Acompanhamento:** artefatos disponíveis; revisão de coerência e encerramento formal a confirmar.  
**Documentação relacionada:** [Diagramas do sistema](../Diagramas/)

## Sprint 04 — Implementação de usuários e pacientes

**Período previsto:** 20/10/2026 a 27/10/2026.  
**Responsáveis:** Natalia Cristina Torres (PO e Dev — usuários) e Yasmin Silva Bonfim dos Santos (SM e Dev — pacientes e responsáveis). Giulianna: apoio atribuído a testes e revisão somente a partir de 25/10/2026.

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
**Acompanhamento:** versão integrada testada localmente em 12/11; atualização do repositório e revisão da equipe pendentes.

## Sprint 05 — Implementação de agendamento e prontuário

**Período previsto:** 28/10/2026 a 04/11/2026.  
**Responsáveis:** Maria Victória Vieira Lopes (Dev — agendamento) e Marcela Bueno dos Santos (Dev — prontuários). Natalia: prioridades e dependência de usuários; Yasmin: facilitação e dependência de pacientes; Giulianna: apoio atribuído a testes e revisão.

**Objetivo:** implementar as funcionalidades de agenda e registro dos atendimentos.

**Atividades previstas:**

- Implementação do agendamento, remarcação e cancelamento.
- Consulta de agendas e validação de conflitos de horário.
- Implementação do registro de evolução técnica e consulta ao prontuário.
- Aplicação das restrições por perfil e vínculo profissional.
- Persistência dos registros e testes de integração.

**Entrega prevista:** quatro módulos integrados: usuários, pacientes, agendamento e prontuário.

## Sprint 06 — Validação, documentação e entrega final

**Período previsto:** 05/11/2026 a 13/11/2026.  
**Responsáveis:** Giulianna (testes e revisão); Natalia (PO e correções de usuários); Yasmin (SM e correções de pacientes); Maria Victória (correções de agendamento); Marcela (correções de prontuários).

**Objetivo:** validar o protótipo e organizar a entrega final.

**Atividades previstas:**

- Testes das funcionalidades, do controle de acesso, da persistência e da integridade dos dados.
- Correção das falhas identificadas.
- Revisão do backlog, dos diagramas e da documentação.
- Preparação das instruções de compilação e execução.
- Gravação do vídeo de demonstração com dados fictícios.
- Preparação da apresentação e organização da versão final.

**Entrega prevista:** MVP acadêmico em C, documentação, resultados dos testes e vídeo de demonstração.

## Registros de cada sprint

| Sprint | Registro de planejamento, acompanhamento, Review e Retrospectiva |
| --- | --- |
| 01 | [Identificação do problema e definição do projeto](SPRINT-01.md) |
| 02 | [Levantamento e análise de requisitos](SPRINT-02.md) |
| 03 | [Modelagem e planejamento técnico](SPRINT-03.md) |
| 04 | [Implementação de usuários e pacientes](SPRINT-04.md) |
| 05 | [Implementação de agendamento e prontuário](SPRINT-05.md) |
| 06 | [Validação, documentação e entrega final](SPRINT-06.md) |

A organização original por etapas foi preservada. Os arquivos detalham o acompanhamento, sem redistribuir retroativamente as entregas entre períodos.

## Alinhamentos, Daily Scrum, Sprint Review e Sprint Retrospective

**Prática informada por Natalia:** a equipe conversava semanalmente pelo WhatsApp sobre o andamento. Esses contatos serão documentados como alinhamentos semanais. Datas exatas, participantes e decisões específicas ainda precisam de confirmação.

- Daily Scrum: inspeção diária, pelos Developers, do avanço em direção à meta e ajuste do trabalho seguinte; duração de 15 minutos.
- Sprint Review: inspeção do resultado com equipe e partes interessadas, feedback e adaptação das próximas prioridades.
- Sprint Retrospective: análise da forma de trabalho e definição de melhorias práticas.

As datas nos registros são **sugestões retrospectivas de agenda**, preparadas para organização acadêmica em 12/11/2026. Não comprovam reuniões realizadas. As pautas são propostas e os resultados dependem de confirmação. As linhas de acompanhamento são exemplos de datas espaçadas, não um histórico completo de dailies. Alinhamentos por mensagem devem ser identificados como assíncronos.

Uma demonstração local com apoio da ferramenta não comprova participação da equipe em uma Sprint Review.

## Giulianna — testes e revisão

[Equipe e distribuição de responsabilidades](../../01-organizacao/EQUIPE.md).

Giulianna Menezes Paes Landim, RA H9592E5, passou a integrar a equipe em **25/10/2026**, como Dev, com foco em testes funcionais, revisão do código e da documentação e registro de falhas.

Nas Sprints 04 e 05, essas responsabilidades compõem a distribuição proposta de atividades; a realização histórica precisa ser confirmada. Na Sprint 06, Giulianna fica responsável pela conferência da versão final e pelo preenchimento de [seu registro de testes e revisão](TESTES-E-REVISAO-GIULIANNA.md).

## Situação em 12/11/2026

| Entrega | Evidência e situação |
| --- | --- |
| Documentação, backlog e diagramas | Presentes no repositório consultado; encerramento das sprints e feedback de equipe a confirmar. |
| Integração dos quatro módulos | Implementada na versão local revisada. Não foi publicada por esta conversa. |
| Testes locais dos módulos | Executados em base fictícia e isolada; [resumo e limites](evidencias/TESTES-LOCAIS-12-11-2026.md). |
| Conferência de Giulianna | Prevista para 13/11/2026; execução e resultados individuais aguardam confirmação. |
| Vídeo e apresentação | Conclusão a confirmar. |
| Entrega final | Prevista para 13/11/2026; ainda não declarada realizada. |

## Critérios para encerramento

1. Identificar a versão efetivamente entregue.
2. Conferir os requisitos e registrar resultados de testes, incluindo falhas e limites.
3. Atualizar a documentação para corresponder ao código entregue.
4. Confirmar os registros de encontros e contribuições dos integrantes.
5. Registrar feedback da Review e melhorias da Retrospectiva quando realizadas.
6. Confirmar vídeo, apresentação e entrega.

Referência: [Guia do Scrum — fonte oficial](https://scrumguides.org/scrum-guide.html).


## Dificuldades relatadas pela equipe

Natalia confirmou os seguintes problemas nos alinhamentos do grupo:

- Atrasos na entrega de partes dos módulos.
- Dúvidas na integração dos arquivos .c e .h.
- Dificuldades com validação de CPF e permissões de acesso.
- Divergências entre código e documentação que precisaram de revisão.

Datas, frequência e responsáveis por ocorrências específicas não foram informados. O canal confirmado foi WhatsApp, com acompanhamento semanal. Encaminhamento confirmado: cada integrante corrigia sua parte, com ajuda das colegas em algumas situações. Aprendizados e decisões de casos específicos ainda serão confirmados.

## Revisões das entregas confirmadas

Natalia informou que a equipe realizava reuniões online pelo WhatsApp para mostrar os módulos em funcionamento, receber comentários, combinar os ajustes e corrigir os problemas. Os registros de Sprint Review documentarão essa prática. Datas exatas, participantes de cada encontro e associação às sprints específicas ainda precisam ser confirmados. A participação de Giulianna é limitada ao período iniciado em 25/10/2026.

## Aprendizados e melhorias na colaboração

Nos relatos confirmados por Natalia, houve atrasos de entregas, dúvidas na integração e necessidade de revisar validações, permissões e documentação. As correções eram realizadas pela responsável de cada parte, com apoio das colegas quando necessário. Nas conversas do grupo, também foram tratados o aviso antecipado de atrasos, a busca de ajuda e a conferência de cada parte antes da integração.

| Ponto identificado no acompanhamento | Encaminhamento discutido pelo grupo | Como acompanhar |
| --- | --- | --- |
| Atrasos na entrega de partes dos módulos. | Comunicar dificuldades e possíveis atrasos com antecedência. | Registrar a pendência, a responsável e o prazo combinado. |
| Dúvidas na integração entre arquivos e módulos. | Pedir ajuda quando necessário e colaborar na resolução. | Registrar a dúvida e conferir a solução com a responsável pelo módulo. |
| Falhas em validações e permissões durante os testes. | Conferir as funcionalidades e corrigir a própria parte antes da integração. | Repetir o cenário após a correção e anotar o resultado. |
| Divergências entre código e documentação. | Revisar os materiais para que representem o funcionamento da versão entregue. | Conferir instruções, diagramas e requisitos na revisão final. |

### Melhorias adicionais propostas para discussão

- Encerrar cada alinhamento com uma próxima ação clara e uma responsável definida.
- Informar os testes já realizados ao compartilhar uma nova versão.
- Consultar as demais responsáveis antes de alterar estruturas ou funções compartilhadas.
- Confirmar o entendimento de dúvidas e sugestões antes de implementar os ajustes.

Essas propostas adicionais ainda não são apresentadas como comportamentos observados ou decisões tomadas. Datas e participantes das conversas de retrospectiva permanecem a confirmar.

### Resultado relatado após os combinados

Natalia relatou que, após os combinados, as integrantes apresentaram resultados e houve melhora no andamento do trabalho. Essa percepção é qualitativa; não foram informadas medidas, datas ou exemplos individuais. A equipe pode acompanhar sua continuidade nas próximas revisões.

## Atualização de 13/11/2026

Natalia informou que Giulianna realizará hoje a validação dos quatro módulos. A revisão e as correções assistidas anteriores permanecem atribuídas a Natalia com apoio da ferramenta. O registro individual contém o roteiro; resultados serão preenchidos após a execução.

## Organização da apresentação

Giulianna organiza os slides e o vídeo. Todas apresentam: Natalia (5 min), Yasmin (4 min), Marcela (3 min), Maria Victória (4 min) e Giulianna (4 min), totalizando 20 minutos. Perguntas da banca ficam fora desse tempo. Materiais e conclusão a confirmar; veja o [plano da apresentação](../../08-apresentacao/README.md).
