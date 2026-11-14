# Testes e revisão — Giulianna Menezes Paes Landim

**RA:** H9592E5  
**Papel:** Desenvolvedora (Dev)  
**Entrada na equipe:** 25/10/2026, conforme informado por Natalia. Apenas atividades a partir dessa data podem ser atribuídas à integrante.  
**Responsabilidades atribuídas:** testes funcionais, revisão do código e da documentação e registro de falhas.  
**Situação:** validação individual prevista para 13/11/2026, conforme informado por Natalia. Execução e resultados pendentes de confirmação.  
**Data prevista de realização:** 13/11/2026.

## Identificação da versão

- Versão programada para conferência: cópia local revisada v2. Ainda não foi comunicado um commit de código final publicado.
- Execução programada para 13/11/2026 no notebook Windows, com dados fictícios. O resultado da execução individual ainda não foi comunicado.
- Arquivos previstos na revisão: main.c, usuarios.c/.h, pacientes.c/.h, prontuarios.c/.h, agendamentos.c/.h, tipos.h, arquivos.h, validacoes.h e documentação correspondente.

## Casos a conferir

| ID | Módulo | Verificação | Resultado esperado | Resultado de Giulianna |
| --- | --- | --- | --- | --- |
| T01 | Usuários | Login correto e incorreto | Autorizar apenas credenciais válidas e usuário ativo. | Execução programada para 13/11; resultado não recebido |
| T02 | Usuários | Matrícula duplicada e inativação | Recusar duplicação; bloquear novo login do inativo. | Execução programada para 13/11; resultado não recebido |
| T03 | Pacientes | CPF inválido e correção | Explicar o erro e repetir somente o campo. | Execução programada para 13/11; resultado não recebido |
| T04 | Pacientes | CPF de paciente duplicado | Recusar duplicação, mantendo o formulário. | Execução programada para 13/11; resultado não recebido |
| T05 | Pacientes | Consulta por responsável | Localizar e mostrar paciente e responsável. | Execução programada para 13/11; resultado não recebido |
| T06 | Pacientes | Atualizar contato | Preservar identidade e vínculo com psicólogo. | Execução programada para 13/11; resultado não recebido |
| T07 | Agenda | Primeiro agendamento | Gerar consulta e gravar vínculo com profissional ativo. | Execução programada para 13/11; resultado não recebido |
| T08 | Agenda | Psicólogo inativo e conflito | Recusar e mostrar o motivo. | Execução programada para 13/11; resultado não recebido |
| T09 | Agenda | Remarcar e cancelar | Atualizar a consulta preservando registros e vínculo. | Execução programada para 13/11; resultado não recebido |
| T10 | Prontuário | Evolução e histórico | Registrar autor da sessão e mostrar o histórico. | Execução programada para 13/11; resultado não recebido |
| T11 | Acesso | Perfil ou vínculo sem permissão | Bloquear dados e operações restritas. | Execução programada para 13/11; resultado não recebido |
| T12 | Persistência | Fechar e reabrir | Manter os registros gravados. | Execução programada para 13/11; resultado não recebido |

## Revisão documental

- Conferir RF, menus, diagramas e instruções de compilação.
- Conferir os participantes, contribuições e prazo final.
- Registrar divergências entre documentação e programa.
- Confirmar que somente dados fictícios aparecem nas evidências.

## Falhas e encaminhamentos

| ID | Como reproduzir | Esperado | Obtido | Responsável pela correção | Reteste |
| --- | --- | --- | --- | --- | --- |
| Nenhuma ocorrência individual comunicada | Não se aplica antes da execução | Conforme casos acima | Resultado não recebido | Responsável pelo módulo, se houver falha | Após a execução |

## Conclusão da revisora

Execução individual programada para 13/11; conclusão ainda não recebida. Após a execução, registrar cenários aprovados, falhas abertas e limitações. Os resultados dos testes assistidos já existentes podem ser consultados, mas a conferência individual precisa ser registrada por quem a executar.


## Roteiro para conferir as correções de integração

As correções abaixo foram preparadas e revisadas por Natalia com apoio da ferramenta, antes desta validação. Giulianna deverá conferir seu funcionamento e registrar o resultado; não lhe são atribuídas a descoberta ou a implementação anteriores.

| Correção existente | Como foi resolvida | Como Giulianna pode conferir |
| --- | --- | --- |
| Funções não acessíveis pelos menus | O main.c passou a incluir os quatro módulos e oferecer operações conforme o perfil. A compilação reúne os cinco arquivos .c. | Entrar como Administrador, Recepção e Psicólogo e conferir as operações disponíveis e os bloqueios. |
| Atualização de paciente alterava campos além do contato | A cópia do cadastro inteiro foi substituída pela atualização apenas dos quatro campos de telefone e endereço. | Agendar uma consulta, atualizar o contato e verificar que o nome, CPF e psicólogo vinculado permanecem iguais. |
| Substituição de arquivos no Windows | O cabeçalho arquivos.h utiliza MoveFileExA com substituição do destino, após fechar o temporário. O original não é apagado antes da substituição. | Atualizar um paciente, remarcar e cancelar uma consulta; reabrir o programa e conferir a persistência. |
| Busca incompleta de responsáveis | A consulta passou a considerar nome e CPF do responsável e exibir seus dados. | Buscar usando o nome do responsável e conferir o paciente correspondente. |
| Recusas sem explicação e perda do formulário | As validações de CPF, data e horário foram compartilhadas com a interface; os campos inválidos são solicitados novamente. | Informar um CPF inválido, corrigir somente esse campo e concluir sem digitar o nome novamente. |
| Falha ao gravar o primeiro vínculo | O programa tenta desfazer a consulta se o vínculo falhar e verifica se a recuperação foi concluída. | Conferir a evidência automatizada desse cenário no relatório de testes; não simular falhas sobre a base utilizada pelo grupo. |

### Ao terminar

1. Identificar a versão e a data do teste.
2. Preencher o resultado de cada caso: passou, falhou ou não executado.
3. Se houver falha, informar os passos e encaminhar à responsável pelo módulo.
4. Repetir o teste após a correção, se necessária.
5. Registrar a conclusão somente após a execução.
