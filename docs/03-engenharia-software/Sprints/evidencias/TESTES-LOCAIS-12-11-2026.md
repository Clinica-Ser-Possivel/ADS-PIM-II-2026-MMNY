# Verificação local assistida — 12/11/2026

## Origem

Foi executada uma cópia da versão revisada extraída no notebook, com dados fictícios em uma pasta de demonstração separada. Os cadastros de trabalho foram preservados.

A verificação foi executada com apoio da ferramenta nesta conversa. Não há confirmação de que Giulianna tenha participado desse teste; seu registro individual está separado.

## Resultados observados

| Área | Cenários executados | Resultado |
| --- | --- | --- |
| Compilação | Compilação conjunta em C11 com avisos tratados como erros. | Passou sem avisos |
| Usuários | Cadastro, busca, login por perfil e opção restrita. | Passou |
| Pacientes | CPF inválido, correção no campo, cadastro, consulta e atualização de contato. | Passou |
| Agenda | Agendamento, conflito, remarcação e cancelamento. | Passou |
| Prontuário | Registro e consulta de evolução e bloqueio pelo perfil. | Passou |
| Persistência e inativação | Reabrir, recuperar os dados e recusar login de usuário inativo. | Passou |

## Limites

Os resultados se aplicam aos cenários executados na versão local. Não comprovam publicação dessa versão no GitHub, realização de reunião da equipe ou validação completa de todos os requisitos não funcionais.

O teste de desempenho com 100 registros e os ensaios de queda de energia, disco cheio e concorrência não foram realizados.

A publicação do código final, a revisão de Giulianna, a preparação do vídeo e a entrega devem ser confirmadas separadamente.

