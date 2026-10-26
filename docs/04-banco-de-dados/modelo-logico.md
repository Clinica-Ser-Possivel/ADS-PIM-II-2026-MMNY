# Modelo Lógico — Clínica Ser Possível

## 1. Apresentação

Este documento apresenta o modelo lógico relacional proposto para organizar os dados do sistema da Clínica Ser Possível. Ele deriva do Diagrama Entidade-Relacionamento (DER) e descreve tabelas, chaves primárias, chaves estrangeiras e restrições de integridade.

O protótipo acadêmico deste semestre será desenvolvido em linguagem C, executado pelo terminal e utilizará arquivos locais `.dat` para armazenar os dados. Portanto, o modelo lógico é uma referência documental e não representa uma integração com SQL Server ou outro sistema gerenciador de banco de dados nesta entrega.

## 2. Estrutura das tabelas

### 2.1 USUARIO

Armazena as informações de acesso dos usuários do sistema.

| Campo | Tipo lógico | Restrições | Descrição |
|---|---|---|---|
| id_usuario | Inteiro | PK | Identificador do usuário |
| matricula | Texto | UK, obrigatório | Identificador de acesso único |
| senha_hash | Texto | Obrigatório no modelo | Representação de senha protegida, prevista para uma implementação segura |
| perfil | Texto | Obrigatório | Perfil de acesso do usuário |
| ativo | Booleano | Obrigatório | Indica se a conta está ativa |

Os perfis previstos devem corresponder aos requisitos do projeto, como administrador, recepção e psicólogo.

**Observação:** a presença do campo `senha_hash` no modelo não comprova que o código atual armazene senhas com hash. Isso deverá ser verificado separadamente na implementação em C.

### 2.2 RESPONSAVEL

Armazena os dados do responsável legal associado ao paciente.

| Campo | Tipo lógico | Restrições | Descrição |
|---|---|---|---|
| id_responsavel | Inteiro | PK | Identificador do responsável |
| nome | Texto | Obrigatório | Nome do responsável |
| cpf | Texto | UK, obrigatório | CPF do responsável |
| telefone | Texto | Obrigatório conforme requisitos | Telefone de contato |
| email | Texto | Opcional, conforme requisitos | E-mail de contato |
| parentesco | Texto | Obrigatório | Relação com o paciente |

### 2.3 PACIENTE

Armazena os dados cadastrais dos pacientes.

| Campo | Tipo lógico | Restrições | Descrição |
|---|---|---|---|
| id_paciente | Inteiro | PK | Identificador do paciente |
| id_responsavel | Inteiro | FK, obrigatório | Referência ao responsável legal |
| nome | Texto | Obrigatório | Nome do paciente |
| cpf | Texto | UK, obrigatório conforme requisitos | CPF do paciente |
| data_nascimento | Data | Obrigatório | Data de nascimento |
| telefone | Texto | Conforme requisitos | Telefone de contato |
| email | Texto | Opcional, conforme requisitos | E-mail de contato |
| endereco | Texto | Conforme requisitos | Endereço do paciente |

Cada paciente deverá estar associado a um responsável legal cadastrado, conforme a regra de negócio definida para o projeto.

### 2.4 PSICOLOGO

Armazena os dados profissionais dos psicólogos.

| Campo | Tipo lógico | Restrições | Descrição |
|---|---|---|---|
| id_psicologo | Inteiro | PK | Identificador do psicólogo |
| id_usuario | Inteiro | FK, UK, obrigatório | Conta de usuário associada |
| nome | Texto | Obrigatório | Nome do profissional |
| registro_profissional | Texto | UK, obrigatório | Registro profissional |
| telefone | Texto | Conforme requisitos | Telefone de contato |
| email | Texto | Conforme requisitos | E-mail profissional |

Cada cadastro de psicólogo deve estar associado a uma única conta de usuário. Uma conta de usuário poderá estar associada a, no máximo, um cadastro de psicólogo.

### 2.5 VINCULO_PACIENTE_PSICOLOGO

Registra os vínculos profissionais entre pacientes e psicólogos.

| Campo | Tipo lógico | Restrições | Descrição |
|---|---|---|---|
| id_vinculo | Inteiro | PK | Identificador do vínculo |
| id_paciente | Inteiro | FK, obrigatório | Paciente relacionado |
| id_psicologo | Inteiro | FK, obrigatório | Psicólogo relacionado |
| data_inicio | Data | Obrigatório | Data de início do vínculo |
| data_fim | Data | Opcional | Data de encerramento do vínculo |
| ativo | Booleano | Obrigatório | Indica se o vínculo está ativo |

**Regra de negócio:** o primeiro agendamento concluído entre um paciente e um psicólogo estabelece o vínculo profissional entre eles.

A operação de criação do vínculo deverá verificar se já existe um vínculo correspondente, evitando registros duplicados. O encerramento deverá atualizar a situação do vínculo e, quando aplicável, registrar a data de término.

As regras para impedir mais de um vínculo ativo para o mesmo paciente e psicólogo deverão ser detalhadas no modelo físico ou na lógica da aplicação.

### 2.6 CONSULTA

Armazena os agendamentos e seus estados.

| Campo | Tipo lógico | Restrições | Descrição |
|---|---|---|---|
| id_consulta | Inteiro | PK | Identificador da consulta |
| id_paciente | Inteiro | FK, obrigatório | Paciente agendado |
| id_psicologo | Inteiro | FK, obrigatório | Psicólogo responsável pelo atendimento |
| data_consulta | Data | Obrigatório | Data do atendimento |
| horario_inicio | Hora | Obrigatório | Horário previsto para início |
| horario_fim | Hora | Obrigatório | Horário previsto para término |
| status | Texto | Obrigatório | Situação do agendamento |

Os valores permitidos para `status` deverão ser definidos nos requisitos, contemplando somente as situações realmente utilizadas pelo sistema.

As regras de validação devem garantir que o horário de término seja posterior ao horário de início e devem considerar possíveis sobreposições de consultas. A simples combinação de data e horário de início não é suficiente para impedir todos os conflitos.

O agendamento inicial pode ocorrer antes da formação do vínculo. Quando uma consulta for concluída, a aplicação deverá verificar se é necessário criar o vínculo correspondente.

### 2.7 PRONTUARIO

Representa o prontuário associado ao paciente.

| Campo | Tipo lógico | Restrições | Descrição |
|---|---|---|---|
| id_prontuario | Inteiro | PK | Identificador do prontuário |
| id_paciente | Inteiro | FK, UK, obrigatório | Paciente associado |
| data_criacao | Data | Obrigatório | Data de criação do prontuário |

A restrição de unicidade em `id_paciente` permite, no modelo, no máximo um prontuário por paciente. A criação do prontuário poderá ocorrer posteriormente ao cadastro, conforme o fluxo definido nos requisitos.

### 2.8 EVOLUCAO

Armazena os registros de evolução vinculados ao prontuário.

| Campo | Tipo lógico | Restrições | Descrição |
|---|---|---|---|
| id_evolucao | Inteiro | PK | Identificador da evolução |
| id_prontuario | Inteiro | FK, obrigatório | Prontuário relacionado |
| id_psicologo | Inteiro | FK, obrigatório | Psicólogo autor do registro |
| data_atendimento | Data | Obrigatório | Data do atendimento |
| data_registro | Data e hora | Obrigatório | Data e hora de registro |
| descricao | Texto | Obrigatório | Conteúdo da evolução |

O acesso e a alteração das evoluções devem respeitar as permissões definidas para cada perfil. A estrutura do modelo, isoladamente, não implementa controle de acesso nem garante a integridade dos registros.

## 3. Relacionamentos e cardinalidades

| Relacionamento | Cardinalidade | Regra |
|---|---|---|
| RESPONSAVEL — PACIENTE | 1:N | Cada paciente possui um responsável; um responsável pode estar associado a vários pacientes. |
| USUARIO — PSICOLOGO | 1:0..1 | Uma conta pode estar associada a zero ou um cadastro de psicólogo; cada psicólogo tem uma conta. |
| PACIENTE — CONSULTA | 1:N | Um paciente pode possuir vários agendamentos. |
| PSICOLOGO — CONSULTA | 1:N | Um psicólogo pode possuir vários agendamentos. |
| PACIENTE — PRONTUARIO | 1:0..1 | Um paciente pode possuir zero ou um prontuário. |
| PRONTUARIO — EVOLUCAO | 1:N | Um prontuário pode conter várias evoluções. |
| PSICOLOGO — EVOLUCAO | 1:N | Um psicólogo pode registrar várias evoluções. |
| PACIENTE — VINCULO_PACIENTE_PSICOLOGO | 1:N | Um paciente pode ter vínculos registrados ao longo do tempo. |
| PSICOLOGO — VINCULO_PACIENTE_PSICOLOGO | 1:N | Um psicólogo pode ter vínculos registrados com vários pacientes. |

## 4. Regras de integridade

O modelo considera as seguintes regras:

1. Cada tabela possui uma chave primária para identificar seus registros.
2. As chaves estrangeiras representam os relacionamentos entre as tabelas.
3. Os campos identificados como únicos não devem possuir valores duplicados.
4. Cada paciente deverá referenciar um responsável legal.
5. O primeiro agendamento concluído estabelece o vínculo entre paciente e psicólogo, desde que não exista vínculo correspondente já registrado.
6. Os agendamentos devem respeitar as validações de datas, horários e situações definidas nos requisitos.
7. Cada prontuário pertence a um único paciente e pode conter várias evoluções.
8. O acesso às informações clínicas deve considerar as permissões de usuário e as regras de vínculo profissional definidas pelo projeto.

## 5. Limitações e relação com a implementação

O modelo lógico descreve uma organização relacional dos dados. No protótipo atual, os registros serão armazenados em arquivos `.dat`, utilizando estruturas e operações implementadas em C.

Consequentemente, as chaves estrangeiras, as restrições de unicidade e as demais regras relacionais descritas neste documento não serão aplicadas automaticamente por um SGBD. As validações que fizerem parte da entrega deverão ser implementadas na lógica do programa e verificadas por testes.

A existência deste modelo não comprova que todas as regras estejam implementadas ou testadas. O estado de cada funcionalidade deverá ser descrito com base no código e nas evidências de teste disponíveis.

Como o projeto envolve dados relacionados à saúde, os testes acadêmicos deverão utilizar dados fictícios. O protótipo não deve ser considerado pronto para uso clínico real sem avaliação técnica, de segurança e dos requisitos legais e profissionais aplicáveis.
