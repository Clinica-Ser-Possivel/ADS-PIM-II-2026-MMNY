# Documentação do Banco de Dados — Clínica Ser Possível

## 1. Apresentação

Esta pasta reúne a documentação da estrutura de dados proposta para o sistema Clínica Ser Possível, desenvolvido como projeto acadêmico do curso de Análise e Desenvolvimento de Sistemas.

O modelo de dados foi elaborado para representar as principais informações relacionadas aos usuários do sistema, pacientes, responsáveis legais, psicólogos, consultas, vínculos profissionais e registros de prontuário.

**Importante:** o modelo relacional documentado nesta pasta representa uma proposta de estrutura para um banco de dados SQL. O protótipo atual do sistema utiliza a linguagem C e arquivos locais com extensão `.dat`. Portanto, a existência dos modelos e do script SQL não significa que o programa já esteja integrado a um SGBD.

## 2. Arquivos desta documentação

### [Diagrama Entidade-Relacionamento (DER)](der.md)

Apresenta as entidades do sistema, seus atributos e os relacionamentos entre elas. O diagrama serve como representação conceitual das informações necessárias ao domínio do projeto.

### [Modelo lógico](modelo-logico.md)

Descreve a organização relacional dos dados, incluindo tabelas, atributos, chaves primárias, chaves estrangeiras, cardinalidades e regras de integridade previstas.

### [Modelo físico SQL](modelo-fisico.sql)

Contém uma proposta de implementação do modelo relacional em SQL, utilizando a sintaxe de referência do Microsoft SQL Server. O script apresenta a definição das tabelas, os tipos de dados, as restrições e os relacionamentos previstos.

O script é documental e não está integrado ao protótipo em C neste momento.

## 3. Principais entidades

O modelo contempla as seguintes entidades:

- **USUARIO:** dados de acesso e perfil de usuários do sistema.
- **RESPONSAVEL:** informações do responsável legal associado ao paciente.
- **PACIENTE:** dados cadastrais dos pacientes.
- **PSICOLOGO:** informações dos profissionais e sua associação a uma conta de usuário.
- **VINCULO_PACIENTE_PSICOLOGO:** histórico dos vínculos entre pacientes e psicólogos.
- **CONSULTA:** agendamentos, horários e situação das consultas.
- **PRONTUARIO:** registro principal associado ao paciente.
- **EVOLUCAO:** registros relacionados aos atendimentos e ao prontuário.

## 4. Regras de negócio representadas

A documentação considera as seguintes regras:

1. Todo paciente deve possuir um responsável legal cadastrado.
2. Um paciente pode ter consultas com psicólogos diferentes ao longo do tempo.
3. A realização da primeira consulta entre um paciente e um psicólogo estabelece o vínculo profissional previsto nas regras do sistema.
4. O histórico de vínculos deve permitir representar vínculos encerrados e ativos.
5. Uma consulta possui data, horário de início, horário de término e situação.
6. Um paciente pode possuir, no máximo, um prontuário no modelo proposto.
7. Cada evolução está associada a um prontuário e identifica o psicólogo responsável pelo registro.

As regras que dependem do comportamento da aplicação, como a criação automática do vínculo após a primeira consulta realizada e a prevenção de conflitos de horário, precisam ser implementadas e testadas antes de serem consideradas funcionalidades concluídas.

## 5. Relação com o protótipo

O modelo de dados orienta a organização conceitual das informações do projeto, mas não deve ser confundido com a estrutura efetivamente utilizada pelo programa.

No escopo atual documentado:

- o protótipo é desenvolvido em C;
- os dados são armazenados em arquivos locais `.dat`;
- o script SQL representa uma proposta de implementação relacional;
- a integração com Microsoft SQL Server não é declarada como concluída;
- as restrições descritas no modelo SQL não são automaticamente aplicadas aos arquivos `.dat`.

Assim, qualquer afirmação sobre funcionalidades implementadas deve ser confirmada pela análise do código e pelos testes correspondentes.

## 6. Limitações e evolução futura

A adoção de um banco de dados relacional poderá ser avaliada em etapas futuras do projeto. Essa evolução exigirá, entre outras atividades, integração com o SGBD escolhido, migração dos dados, implementação das regras de integridade, definição de permissões e testes.

O modelo documental, por si só, não comprova segurança adequada para dados clínicos, conformidade legal ou prontidão para uso em um ambiente real de atendimento.

## 7. Conclusão

Os documentos desta pasta apresentam uma visão conceitual, lógica e física proposta para os dados da Clínica Ser Possível. Em conjunto, eles ajudam a manter a estrutura de dados planejada consistente com as entidades e regras de negócio descritas no projeto, sem afirmar que uma integração com banco de dados SQL já tenha sido implementada.
