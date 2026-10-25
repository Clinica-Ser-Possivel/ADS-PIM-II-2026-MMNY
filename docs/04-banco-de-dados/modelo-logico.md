# Modelo Lógico — Clínica Ser Possível

## 1. Escopo

Este modelo descreve a proposta relacional para a documentação do PIM II. O programa deste semestre será desenvolvido em C com armazenamento em arquivos `.dat`; não haverá integração com SQL Server. Os tipos indicados são de referência para o script físico.

## 2. Tabela USUARIO

Contém as contas dos colaboradores que podem autenticar no sistema.

| Campo | Tipo sugerido | Restrição / regra |
|---|---|---|
| id_usuario | INT | PK |
| matricula | VARCHAR(50) | NOT NULL, UNIQUE; identificador de login |
| senha_hash | VARCHAR(255) | NOT NULL; hash seguro, nunca senha em texto puro |
| perfil | VARCHAR(20) | NOT NULL; somente `ADMIN`, `RECEPCAO`, `PSICOLOGO` |
| ativo | BIT | NOT NULL, padrão 1 |

O login deve verificar a matrícula, a senha e se a conta está ativa. A inativação bloqueia novos acessos sem apagar o histórico do colaborador. O perfil é atribuído conforme a função cadastrada, sem configuração individual de permissões.

## 3. Tabela RESPONSAVEL

Armazena os dados cadastrais do responsável legal.

| Campo | Tipo sugerido | Restrição / regra |
|---|---|---|
| id_responsavel | INT | PK |
| nome | VARCHAR(100) | NOT NULL |
| cpf | VARCHAR(14) | NULL; UNIQUE filtrado quando informado |
| telefone | VARCHAR(20) | NULL |
| email | VARCHAR(100) | NULL |
| parentesco | VARCHAR(50) | NULL |

Nesta versão, o modelo considera um responsável legal principal por paciente, conforme a redação singular do requisito RF02.1. O grupo deve confirmar essa decisão.

## 4. Tabela PACIENTE

Armazena os dados cadastrais do paciente infantojuvenil.

| Campo | Tipo sugerido | Restrição / regra |
|---|---|---|
| id_paciente | INT | PK |
| id_responsavel | INT | FK, NOT NULL |
| nome | VARCHAR(100) | NOT NULL |
| cpf | VARCHAR(14) | NULL; UNIQUE filtrado quando informado |
| data_nascimento | DATE | NOT NULL |
| telefone | VARCHAR(20) | NULL |
| email | VARCHAR(100) | NULL |
| endereco | VARCHAR(200) | NULL |

O paciente não possui conta de usuário nesta proposta, pois os únicos perfis autenticáveis previstos no backlog são Administrador, Recepção e Psicólogo.

## 5. Tabela PSICOLOGO

| Campo | Tipo sugerido | Restrição / regra |
|---|---|---|
| id_psicologo | INT | PK |
| id_usuario | INT | FK, NOT NULL, UNIQUE |
| nome | VARCHAR(100) | NOT NULL |
| registro_profissional | VARCHAR(30) | NOT NULL, UNIQUE |
| telefone | VARCHAR(20) | NULL |
| email | VARCHAR(100) | NULL |

Cada psicólogo está associado a uma conta de usuário. A matrícula e o status ativo/inativo são mantidos em `USUARIO`.

## 6. Tabela VINCULO_PACIENTE_PSICOLOGO

Registra explicitamente o vínculo profissional que autoriza o acesso clínico.

| Campo | Tipo sugerido | Restrição / regra |
|---|---|---|
| id_vinculo | INT | PK |
| id_paciente | INT | FK, NOT NULL |
| id_psicologo | INT | FK, NOT NULL |
| data_inicio | DATE | NOT NULL |
| data_fim | DATE | NULL |
| ativo | BIT | NOT NULL, padrão 1 |

Um paciente pode ter vínculos com diferentes psicólogos ao longo do tempo, e um psicólogo pode atender diferentes pacientes. Para um mesmo par paciente-psicólogo, deve existir no máximo um vínculo ativo. O acesso ao prontuário e o registro de evolução exigem vínculo ativo; a existência de consulta, por si só, não concede autorização. A implementação da validação de acesso é responsabilidade da aplicação.

## 7. Tabela CONSULTA

| Campo | Tipo sugerido | Restrição / regra |
|---|---|---|
| id_consulta | INT | PK |
| id_paciente | INT | FK, NOT NULL |
| id_psicologo | INT | FK, NOT NULL |
| data_consulta | DATE | NOT NULL |
| horario | TIME(0) | NOT NULL |
| status | VARCHAR(20) | NOT NULL; `AGENDADA`, `REALIZADA` ou `CANCELADA` |

A recepção e o administrador podem agendar, remarcar e cancelar consultas. A remarcação atualiza data e/ou horário da consulta agendada; o cancelamento altera o status para `CANCELADA`. O script impede que um mesmo psicólogo ou paciente tenha duas consultas não canceladas na mesma data e horário. O backlog não especifica a duração da sessão, portanto o modelo não valida sobreposição de intervalos.

## 8. Tabela PRONTUARIO

| Campo | Tipo sugerido | Restrição / regra |
|---|---|---|
| id_prontuario | INT | PK |
| id_paciente | INT | FK, NOT NULL, UNIQUE |
| data_criacao | DATE | NOT NULL, padrão data atual |

A restrição `UNIQUE` em `id_paciente` estabelece no máximo um prontuário principal por paciente.

## 9. Tabela EVOLUCAO

| Campo | Tipo sugerido | Restrição / regra |
|---|---|---|
| id_evolucao | INT | PK |
| id_prontuario | INT | FK, NOT NULL |
| id_psicologo | INT | FK, NOT NULL |
| data_atendimento | DATE | NOT NULL |
| data_registro | DATETIME2 | NOT NULL, padrão data/hora atual |
| descricao | VARCHAR(1000) | NOT NULL |

`data_atendimento` representa o dia da sessão clínica. `data_registro` representa quando a evolução foi lançada no sistema, permitindo distinguir a ocorrência do atendimento do momento do registro. O psicólogo precisa ter vínculo ativo com o paciente do prontuário para consultar ou registrar a evolução.

## 10. Relacionamentos e cardinalidades

- RESPONSAVEL 1:N PACIENTE: um responsável pode estar associado a vários pacientes; cada paciente tem um responsável principal neste escopo.
- USUARIO 1:0..1 PSICOLOGO: uma conta pode não ser de psicólogo ou estar vinculada a um único cadastro profissional; cada psicólogo possui uma conta.
- PACIENTE 1:N CONSULTA.
- PSICOLOGO 1:N CONSULTA.
- PACIENTE 1:0..1 PRONTUARIO.
- PRONTUARIO 1:N EVOLUCAO.
- PSICOLOGO 1:N EVOLUCAO.
- PACIENTE N:N PSICOLOGO por meio de VINCULO_PACIENTE_PSICOLOGO.

## 11. Normalização

A separação de usuários, pacientes, responsáveis, psicólogos, consultas, prontuários e evoluções reduz a repetição de dados cadastrais e permite que as relações sejam representadas por chaves estrangeiras. A tabela associativa de vínculo profissional evita repetir informações de paciente e psicólogo e registra o estado da autorização. A forma normal definitiva deve ser validada pelo grupo conforme o conteúdo exigido na disciplina.

## 12. Segurança e limites

Os dados clínicos devem ser acessíveis apenas a psicólogos com vínculo ativo com o paciente. O perfil de administrador não concede automaticamente acesso ao conteúdo da evolução. A recepção e o administrador acessam as funções de agenda conforme o backlog, sem autorização clínica implícita. Devem ser usados exclusivamente dados fictícios no protótipo.

A modelagem é documental e não substitui a validação das permissões no programa em C. Não foi criada uma tabela de anotações privadas separada porque esse item não aparece como requisito funcional no Product Backlog fornecido.
