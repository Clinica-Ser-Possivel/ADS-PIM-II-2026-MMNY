# Sprint 05 — Implementação de agendamento e prontuário

[Voltar ao planejamento](README.md)

**Período planejado:** 28/10/2026 a 04/11/2026  
**Meta:** Integrar agenda e prontuário aos módulos e regras de acesso.

## Identificação dos registros

As datas abaixo são propostas de agenda elaboradas em 12/11/2026. A realização, os participantes e as decisões devem ser confirmados pela equipe. O período planejado não é evidência de que o trabalho terminou nessa data.

## Sprint Planning

**Data sugerida:** 28/10/2026  
**Participantes efetivos:** a confirmar.

### Itens propostos

- Agendamento, remarcação, cancelamento e consulta de agenda.
- Registro e consulta de evolução técnica.
- Validação de vínculo profissional, conflitos e persistência.

**Referência:** [Código em C](../../05-programacao-em-c/).

### Critérios de verificação

- Agendamento respeita profissional ativo e horários disponíveis.
- Prontuário é acessível somente ao psicólogo vinculado.

### Distribuição de atividades

- **Maria Victória Vieira Lopes (Dev): implementação do módulo 4 — agendamento**, incluindo agendar, consultar agenda, remarcar, cancelar e conferir conflitos.
- **Marcela Bueno dos Santos (Dev): implementação do módulo 3 — prontuários**, incluindo registrar evolução, consultar histórico e respeitar o vínculo profissional.
- Natalia (PO e Dev de usuários): acompanhar prioridades e apoiar as dependências de login, perfis e busca de colaboradores.
- Yasmin (SM e Dev de pacientes): facilitar alinhamentos e apoiar as dependências de busca e vínculo do paciente.
- Giulianna (Dev): testes e revisão atribuídos a agenda, prontuário e permissões; resultados individuais a registrar.
- A autoria da implementação foi informada por Natalia; a data de conclusão de cada atividade precisa ser confirmada.

- Decisões do Planning e mudanças no escopo: a registrar após confirmação.

## Alinhamentos semanais da equipe

**Proposta de acompanhamento:** datas, integrantes e pautas abaixo organizam a discussão; não são declarações de presença ou de tarefas concluídas. Nos encontros confirmados, preencher avanço real, impedimento e decisão. As datas espaçadas são exemplos de registros, sem representar todas as dailies.

| Data sugerida | Integrante / área | Atividade a acompanhar | Próximo passo proposto | Avanço real, impedimento e decisão |
| --- | --- | --- | --- | --- |
| 29/10/2026 | Maria Victória — Dev de agendamento | Cadastro de consulta e conflitos | Conferir profissional ativo e disponibilidade | A confirmar e registrar |
| 29/10/2026 | Marcela — Dev de prontuários | Registro da evolução técnica | Conferir autor da sessão e vínculo com paciente | A confirmar e registrar |
| 30/10/2026 | Maria Victória — Dev de agendamento | Remarcação e cancelamento | Conferir persistência e preservação do vínculo | A confirmar e registrar |
| 30/10/2026 | Marcela — Dev de prontuários | Consulta do histórico | Conferir ordenação e bloqueio de acesso indevido | A confirmar e registrar |
| 30/10/2026 | Natalia e Yasmin — apoio às dependências | Integração com usuários e pacientes | Encaminhar ajustes nas funções compartilhadas | A confirmar e registrar |
| 03/11/2026 | Giulianna — Dev de testes e revisão | Cenários de agenda, prontuário e permissões | Registrar falhas para Maria Victória e Marcela | A confirmar e registrar |
| 03/11/2026 | Yasmin — SM | Impedimentos e pendências para a Review | Organizar encaminhamentos com as responsáveis | A confirmar e registrar |

**Canal e frequência confirmados por Natalia:** WhatsApp, com alinhamentos semanais sobre o andamento do trabalho. Datas exatas, participantes e encaminhamentos de cada conversa: a confirmar.

**Pauta proposta para organizar o registro:** progresso em relação à meta, próximas tarefas, dificuldades e ajustes. Os encontros semanais descritos não equivalem a um histórico de Daily Scrum diária.

**Como completar:** substituir o último campo por um registro breve, como avanço confirmado, dificuldade encontrada e quem realizará a próxima ação. Usar “sem impedimentos” somente quando isso tiver sido informado.

## Sprint Review

**Prática de revisão confirmada no projeto:** reuniões online pelo WhatsApp para apresentar os módulos em funcionamento, receber comentários e combinar correções. Cada responsável corrigia sua parte, com ajuda das colegas quando necessário. A data exata, a participação e os itens apresentados nesta sprint ainda precisam ser confirmados.

**Data sugerida:** 04/11/2026  
**Realização e participantes:** a confirmar.

### Roteiro proposto

**Apresentação proposta por responsável:** Maria Victória apresenta agendamento; Marcela apresenta prontuários; Giulianna apresenta os testes que tiver efetivamente realizado.

1. Apresentar a meta e os itens trabalhados.
2. Inspecionar os artefatos e resultados disponíveis.
3. Verificar os critérios acima e colher feedback.
4. Registrar itens concluídos e pendências a levar ao backlog.

| Item apresentado | Evidência / versão | Feedback recebido | Decisão e próximo passo |
| --- | --- | --- | --- |
| A confirmar | A informar | A registrar | A registrar |

A conclusão do teste local ou o envio de um arquivo não substitui o registro do feedback da equipe.

## Sprint Retrospective

**Data sugerida:** 04/11/2026 — após a Review  
**Realização e participantes:** a confirmar.

| Tema | Pergunta para a equipe | Registro real |
| --- | --- | --- |
| Acertos | O que ajudou a avançar? | A registrar |
| Dificuldades | Onde houve retrabalho, dúvidas ou impedimentos? | A registrar |
| Melhoria | Qual mudança será aplicada no próximo ciclo? | A definir |
| Acompanhamento | Quem acompanha a ação e até quando? | A definir |

### Observações sobre a colaboração

No acompanhamento geral do projeto, foram relatados atrasos, dúvidas de integração e necessidade de revisar validações e documentação. A equipe tratava os ajustes em reuniões online pelo WhatsApp; cada integrante corrigia sua parte e, em algumas situações, recebia ajuda das colegas.

Também foram discutidos o aviso antecipado de atrasos, o pedido de ajuda e a conferência das partes antes da integração. A associação de cada conversa a esta sprint e seus participantes ainda deve ser confirmada.

### Melhorias para acompanhamento

- Comunicar possíveis atrasos e dificuldades com antecedência.
- Solicitar apoio quando houver impedimento.
- Conferir o módulo antes de compartilhar a versão para integração.
- Revisar a documentação após as correções.

Como propostas adicionais, definir uma próxima ação ao final de cada alinhamento e consultar as responsáveis antes de alterar interfaces compartilhadas. Essas propostas não são registradas como acordos já realizados.

**Responsáveis por ações específicas e prazos:** a confirmar.

**Resultado relatado no projeto:** Natalia relatou que, após os combinados, as integrantes apresentaram resultados e houve melhora no andamento do trabalho. Essa percepção é qualitativa; não foram informadas medidas, datas ou exemplos individuais. A equipe pode acompanhar sua continuidade nas próximas revisões. A associação desse resultado a esta sprint específica permanece a confirmar.

## Encerramento

- Data real de conclusão: a confirmar.
- Entregas verificadas e evidências: a registrar.
- Pendências transferidas ao backlog: a registrar.
- Responsável pela atualização desta ata: a definir.


## Dificuldades confirmadas no projeto

Natalia confirmou atrasos nas entregas, dúvidas de integração entre arquivos .c e .h, dificuldades com CPF e permissões e divergências entre código e documentação. A associação de cada ocorrência a esta sprint e sua data exata permanece a confirmar; este registro não atribui atrasos a integrantes específicos.

**Encaminhamento confirmado:** Cada integrante corrigia os problemas da sua própria parte; em algumas situações, as colegas ajudavam na resolução. Natalia confirmou essa forma de colaboração. Novos prazos, retestes e decisões de casos específicos ainda precisam ser detalhados.
