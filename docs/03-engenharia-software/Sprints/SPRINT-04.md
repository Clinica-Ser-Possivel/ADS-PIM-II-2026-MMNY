# Sprint 04 — Implementação de usuários e pacientes

[Voltar ao planejamento](README.md)

**Período planejado:** 20/10/2026 a 27/10/2026  
**Meta:** Implementar autenticação e cadastros básicos com persistência local.

## Identificação dos registros

As datas abaixo são propostas de agenda elaboradas em 12/11/2026. A realização, os participantes e as decisões devem ser confirmados pela equipe. O período planejado não é evidência de que o trabalho terminou nessa data.

## Sprint Planning

**Data sugerida:** 20/10/2026  
**Participantes efetivos:** a confirmar.

### Itens propostos

- Login, cadastro e inativação de usuários.
- Cadastro, consulta e atualização de pacientes e responsáveis.
- Testes das permissões, duplicação e persistência.

**Referência:** [Código em C](../../05-programacao-em-c/).

### Critérios de verificação

- Login recusa senha incorreta e usuário inativo.
- CPF duplicado é recusado e o contato pode ser atualizado sem perder o vínculo.

### Distribuição de atividades

- **Natalia Cristina Torres (PO e Dev): implementação do módulo 1 — usuários**, incluindo login, cadastro, inativação e busca. Como PO, acompanhar prioridades e coerência com o backlog.
- **Yasmin Silva Bonfim dos Santos (SM e Dev): implementação do módulo 2 — pacientes e responsáveis**, incluindo cadastro, consulta, atualização de contato e apoio ao vínculo. Como SM, facilitar o acompanhamento.
- **Giulianna Menezes Paes Landim (Dev, RA H9592E5): testes e revisão atribuídos** aos fluxos de usuários e pacientes **somente a partir de sua entrada em 25/10/2026**; resultados individuais a registrar. Não participou do início desta sprint ou das sprints anteriores.
- Marcela e Maria Victória: referências para conferir as dependências dos módulos seguintes, quando necessário.
- A autoria da implementação foi informada por Natalia; a data de conclusão de cada atividade precisa ser confirmada.

- Decisões do Planning e mudanças no escopo: a registrar após confirmação.

## Alinhamentos semanais da equipe

**Proposta de acompanhamento:** datas, integrantes e pautas abaixo organizam a discussão; não são declarações de presença ou de tarefas concluídas. Nos encontros confirmados, preencher avanço real, impedimento e decisão. As datas espaçadas são exemplos de registros, sem representar todas as dailies.

| Data sugerida | Integrante / área | Atividade a acompanhar | Próximo passo proposto | Avanço real, impedimento e decisão |
| --- | --- | --- | --- | --- |
| 21/10/2026 | Natalia — PO / Dev de usuários | Login e cadastro de usuários | Conferir matrícula duplicada e permissões | A confirmar e registrar |
| 21/10/2026 | Yasmin — SM / Dev de pacientes | Cadastro de paciente e responsável | Conferir campos obrigatórios e CPF | A confirmar e registrar |
| 23/10/2026 | Natalia — PO / Dev de usuários | Inativação de usuários | Testar bloqueio de login e preservação dos registros | A confirmar e registrar |
| 23/10/2026 | Yasmin — SM / Dev de pacientes | Consulta e atualização cadastral | Conferir preservação de identidade e vínculo | A confirmar e registrar |
| 26/10/2026 | Giulianna — Dev de testes e revisão | Cenários dos módulos de usuários e pacientes | Registrar falhas e encaminhar a Natalia ou Yasmin | A confirmar e registrar |
| 26/10/2026 | Natalia e Yasmin — responsáveis pelos módulos | Pendências apontadas na revisão | Priorizar correções e preparar demonstração | A confirmar e registrar |

**Canal e frequência confirmados por Natalia:** WhatsApp, com alinhamentos semanais sobre o andamento do trabalho. Datas exatas, participantes e encaminhamentos de cada conversa: a confirmar.

**Pauta proposta para organizar o registro:** progresso em relação à meta, próximas tarefas, dificuldades e ajustes. Os encontros semanais descritos não equivalem a um histórico de Daily Scrum diária.

**Como completar:** substituir o último campo por um registro breve, como avanço confirmado, dificuldade encontrada e quem realizará a próxima ação. Usar “sem impedimentos” somente quando isso tiver sido informado.

## Sprint Review

**Prática de revisão confirmada no projeto:** reuniões online pelo WhatsApp para apresentar os módulos em funcionamento, receber comentários e combinar correções. Cada responsável corrigia sua parte, com ajuda das colegas quando necessário. A data exata, a participação e os itens apresentados nesta sprint ainda precisam ser confirmados.

**Data sugerida:** 27/10/2026  
**Realização e participantes:** a confirmar.

### Roteiro proposto

**Apresentação proposta por responsável:** Natalia apresenta usuários; Yasmin apresenta pacientes e responsáveis; Giulianna apresenta os testes que tiver efetivamente realizado.

1. Apresentar a meta e os itens trabalhados.
2. Inspecionar os artefatos e resultados disponíveis.
3. Verificar os critérios acima e colher feedback.
4. Registrar itens concluídos e pendências a levar ao backlog.

| Item apresentado | Evidência / versão | Feedback recebido | Decisão e próximo passo |
| --- | --- | --- | --- |
| A confirmar | A informar | A registrar | A registrar |

A conclusão do teste local ou o envio de um arquivo não substitui o registro do feedback da equipe.

## Sprint Retrospective

**Data sugerida:** 27/10/2026 — após a Review  
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
