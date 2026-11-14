# Sprint 04 — Desenvolvimento de usuários e pacientes

[Voltar ao planejamento](README.md)

**Período planejado:** 20/10 a 27/10/2026.  
**Meta:** Desenvolver usuários e pacientes com persistência local.  
**Organização e registro:** Natalia Cristina Torres.

## Origem e precisão do registro

Registro consolidado a partir das confirmações de Natalia em 13/11/2026, dos documentos e do histórico do GitHub. A equipe realizava alinhamentos semanais pelo WhatsApp, com referência a sextas ou sábados. Os períodos abaixo são aproximados; os dias exatos dos encontros não foram recuperados. Uma publicação no GitHub não é necessariamente a data da entrega interna ou da criação local.

## Sprint Planning — planejamento

**Referência temporal:** abertura do período da sprint; o dia específico da conversa não foi recuperado.  
**Equipe nos alinhamentos do período:** Natalia Cristina Torres, Yasmin Silva Bonfim dos Santos, Marcela Bueno dos Santos e Maria Victória Vieira Lopes; Giulianna participa somente a partir de 25/10/2026.  
**Responsabilidades:** Natalia (PO e Dev): módulo 1 — usuários. Yasmin (SM e Dev): módulo 2 — pacientes e responsáveis. Giulianna: apoio em testes e revisão atribuído somente a partir de 25/10/2026; sua validação individual final está programada para 13/11.

### Escopo de trabalho

- Login, cadastro, busca e inativação de usuários.
- Cadastro, consulta e atualização de pacientes e responsáveis.
- Permissões, duplicação e persistência.

O planejamento seguiu os requisitos do [Product Backlog](../Backlog/BACKLOG.md). Não foi relatada mudança importante adicional de escopo nas três primeiras sprints. Os itens incompletos das sprints de código continuaram no período seguinte.

## Alinhamentos semanais — WhatsApp

Todas as integrantes participavam dos encontros do respectivo período. Natalia organizava e registrava as decisões. As linhas são uma síntese reconstruída do acompanhamento do ciclo, sem atribuir reuniões a dias exatos.

| Período de referência | Trabalho acompanhado | Encaminhamento |
| --- | --- | --- |
| 20 a 24/10 | Natalia: usuários; Yasmin: pacientes e responsáveis. | Conferir campos, acesso e persistência. |
| 25 a 27/10 | Continuidade dos módulos; entrada de Giulianna em 25/10. | Revisar o resultado disponível e identificar o que continuaria na sprint seguinte. |

O formato relatado foi semanal; não é apresentado como realização de Daily Scrum todos os dias.

## Sprint Review — revisão das entregas

**Momento:** encerramento da sprint; dia exato da reunião não recuperado.  
**Canal:** reunião online pelo WhatsApp.  
**Participantes:** Natalia Cristina Torres, Yasmin Silva Bonfim dos Santos, Marcela Bueno dos Santos e Maria Victória Vieira Lopes; Giulianna participa somente a partir de 25/10/2026.  
**Organização e registro:** Natalia Cristina Torres.

### Resultado e entrega

Usuários: primeira versão publicada em 26/10/2026, dentro do período. Pacientes e responsáveis: entrega atrasada no início da semana de 09/11/2026, conforme relato de Natalia; publicação em 12/11.

A Review ocorreu no encerramento da sprint, com o resultado disponível. A parte de usuários estava disponível; o trabalho incompleto de pacientes continuou na sprint seguinte.

**Evidência:** [documentação ou código relacionado](../../05-programacao-em-c/).

### Continuidade e pendências

Conclusão de pacientes e responsáveis por Yasmin; posterior integração e testes. Não foi informado novo prazo intermediário.

## Sprint Retrospective — colaboração e melhorias

**Momento:** parte final da mesma reunião da Review, após a discussão das entregas.  
**Participantes:** equipe do período identificada acima.  
**Registro:** Natalia Cristina Torres.

No acompanhamento geral do desenvolvimento, Natalia relatou atrasos, dúvidas na integração entre arquivos, dificuldades com CPF e permissões e divergências entre código e documentação. Cada integrante corrigia sua parte e recebia ajuda das colegas quando necessário.

| Ponto discutido | Encaminhamento confirmado | Responsabilidade de acompanhamento |
| --- | --- | --- |
| Atrasos de entrega | Avisar dificuldades e possíveis atrasos com antecedência. | Cada responsável comunica sua parte; Natalia registra o encaminhamento. |
| Dúvidas de integração | Pedir ajuda e colaborar quando necessário. | Responsáveis pelos módulos envolvidos. |
| Falhas nos testes | Conferir cada parte antes da integração e corrigir os problemas. | Responsável pelo módulo; revisão e reteste conforme atividade atribuída. |
| Documentação divergente | Revisar os materiais após as correções. | Equipe, com organização de Natalia e revisão atribuída a Giulianna a partir de sua entrada. |

**Resultado relatado:** depois dos combinados, as integrantes apresentaram resultados e foi percebida melhora no andamento do trabalho. O relato é qualitativo; não foram fornecidas medidas ou ocorrências datadas para atribuir esse efeito a uma única reunião.

## Encerramento e situação

Usuários: primeira versão publicada em 26/10/2026, dentro do período. Pacientes e responsáveis: entrega atrasada no início da semana de 09/11/2026, conforme relato de Natalia; publicação em 12/11.

**Continuidade:** Conclusão de pacientes e responsáveis por Yasmin; posterior integração e testes. Não foi informado novo prazo intermediário.

## Histórico de entrega do código

- Usuários: [primeira publicação em 26/10](https://github.com/Clinica-Ser-Possivel/ADS-PIM-II-2026-MMNY/commit/8ad860c45b6a534172b8639d4624ce314322c25e), com [atualização em 07/11](https://github.com/Clinica-Ser-Possivel/ADS-PIM-II-2026-MMNY/commit/4d89cb789ec51e97abe407b36bdf3f7784559cd6).
- Pacientes (Yasmin), prontuários (Marcela) e agendamento (Maria Victória): entrega interna no início da semana de 09/11, segundo Natalia; publicação dos arquivos em 12/11.
- Integração, testes e correções finais: 12 e 13/11. A revisão e as correções assistidas anteriores foram realizadas por Natalia com apoio da ferramenta; não são atribuídas a Giulianna.
