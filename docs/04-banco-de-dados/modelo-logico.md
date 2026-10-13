# Modelo Lógico — Clínica Ser Possível

## 1. Objetivo

O modelo lógico organiza os dados da clínica em tabelas relacionadas, definindo seus atributos, chaves primárias (PK) e chaves estrangeiras (FK). A proposta utiliza o modelo relacional, considerando o Microsoft SQL Server como SGBD.

## 2. Tabela USUARIO

Armazena os dados de acesso ao sistema e o perfil de cada usuário.

| Campo | Tipo sugerido | Restrição |
|---|---|---|
| id_usuario | INT | PK |
| login | VARCHAR(50) | NOT NULL, UNIQUE |
| senha_hash | VARCHAR(255) | NOT NULL |
| perfil | VARCHAR(20) | NOT NULL |

Os perfis previstos são ADMIN, RECEPCAO, PACIENTE e PSICOLOGO. A senha deve ser armazenada como hash seguro, nunca em texto puro.

## 3. Tabela PACIENTE

Armazena os dados cadastrais dos pacientes.

| Campo | Tipo sugerido | Restrição |
|---|---|---|
| id_paciente | INT | PK |
| id_usuario | INT | FK, UNIQUE, opcional conforme o cadastro |
| nome | VARCHAR(100) | NOT NULL |
| cpf | VARCHAR(14) | UNIQUE |
| data_nascimento | DATE | — |
| telefone | VARCHAR(20) | — |
| email | VARCHAR(100) | — |
| endereco | VARCHAR(200) | — |

O relacionamento com USUARIO permite vincular o cadastro do paciente à conta de acesso quando o paciente utilizar o sistema.

## 4. Tabela PSICOLOGO

Armazena os dados dos profissionais responsáveis pelos atendimentos.

| Campo | Tipo sugerido | Restrição |
|---|---|---|
| id_psicologo | INT | PK |
| id_usuario | INT | FK, UNIQUE |
| nome | VARCHAR(100) | NOT NULL |
| registro_profissional | VARCHAR(30) | NOT NULL, UNIQUE |
| telefone | VARCHAR(20) | — |
| email | VARCHAR(100) | — |

## 5. Tabela CONSULTA

Registra os agendamentos e relaciona o paciente ao psicólogo responsável.

| Campo | Tipo sugerido | Restrição |
|---|---|---|
| id_consulta | INT | PK |
| id_paciente | INT | FK, NOT NULL |
| id_psicologo | INT | FK, NOT NULL |
| data_consulta | DATE | NOT NULL |
| horario | TIME | NOT NULL |
| status | VARCHAR(20) | NOT NULL |

O status poderá representar situações como agendada, realizada ou cancelada, conforme as regras definidas pelo grupo.

## 6. Tabela PRONTUARIO

Representa o prontuário principal de cada paciente.

| Campo | Tipo sugerido | Restrição |
|---|---|---|
| id_prontuario | INT | PK |
| id_paciente | INT | FK, NOT NULL, UNIQUE |
| data_criacao | DATE | NOT NULL |

A restrição UNIQUE em id_paciente representa a decisão de manter um prontuário principal por paciente nesta proposta.

## 7. Tabela EVOLUCAO

Armazena os registros relacionados ao acompanhamento psicológico.

| Campo | Tipo sugerido | Restrição |
|---|---|---|
| id_evolucao | INT | PK |
| id_prontuario | INT | FK, NOT NULL |
| id_psicologo | INT | FK, NOT NULL |
| data_evolucao | DATE | NOT NULL |
| descricao | VARCHAR(1000) | NOT NULL |

A descrição poderá conter informações sensíveis. Seu acesso deve ser restrito a profissionais autorizados, com proteção adequada dos dados.

## 8. Relacionamentos e cardinalidades

- USUARIO e PACIENTE: uma conta pode estar vinculada a um cadastro de paciente; o vínculo é opcional enquanto o cadastro não possuir acesso ao sistema.
- USUARIO e PSICOLOGO: uma conta de acesso está vinculada a um cadastro de psicólogo.
- PACIENTE e CONSULTA: 1:N — um paciente pode ter várias consultas.
- PSICOLOGO e CONSULTA: 1:N — um psicólogo pode realizar várias consultas.
- PACIENTE e PRONTUARIO: 1:1 — cada paciente possui no máximo um prontuário principal nesta proposta.
- PRONTUARIO e EVOLUCAO: 1:N — um prontuário pode possuir várias evoluções.
- PSICOLOGO e EVOLUCAO: 1:N — um psicólogo pode registrar várias evoluções.

## 9. Normalização

A separação das informações em tabelas evita repetir os dados completos do paciente e do psicólogo em cada consulta. As chaves estrangeiras permitem relacionar os registros sem duplicar desnecessariamente os dados cadastrais. A estrutura deverá ser validada pelo grupo para confirmar as regras de negócio e as formas normais exigidas na disciplina.

## 10. Observações de segurança

O sistema deverá aplicar permissões de acordo com o perfil de cada usuário. O paciente deve consultar apenas suas próprias consultas; o psicólogo deve acessar apenas os prontuários autorizados; e a recepção deve acessar somente os dados necessários às suas funções. Por envolver dados pessoais e informações de saúde, o projeto deve considerar os requisitos de confidencialidade e proteção de dados.

## 11. Próxima etapa

O arquivo `modelo-fisico.sql` apresentará a implementação das tabelas e dos relacionamentos no SQL Server. O DER visual será disponibilizado em `der-clinica.png`.
