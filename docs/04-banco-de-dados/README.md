# Banco de Dados — Clínica Ser Possível

## 1. Objetivo

Esta seção apresenta a modelagem do banco de dados proposto para o sistema da Clínica Ser Possível. O objetivo é organizar as informações de pacientes, psicólogos, consultas, prontuários, evoluções e usuários, de acordo com as funcionalidades previstas para o sistema.

## 2. Sistema Gerenciador de Banco de Dados

Para a proposta, considera-se o Microsoft SQL Server como Sistema Gerenciador de Banco de Dados (SGBD), utilizando a linguagem SQL para definição e manipulação dos dados.

## 3. Entidades principais

- **USUARIO:** identifica as pessoas que acessam o sistema e seus perfis de permissão.
- **PACIENTE:** armazena os dados cadastrais dos pacientes.
- **PSICOLOGO:** armazena os dados dos profissionais responsáveis pelos atendimentos.
- **CONSULTA:** registra os agendamentos, incluindo data, horário, situação, paciente e psicólogo.
- **PRONTUARIO:** representa o prontuário associado ao paciente e ao profissional responsável.
- **EVOLUCAO:** armazena os registros realizados durante o acompanhamento psicológico.

## 4. Relacionamentos e cardinalidades

- Um paciente pode ter várias consultas; cada consulta pertence a um paciente (1:N).
- Um psicólogo pode realizar várias consultas; cada consulta é atribuída a um psicólogo (1:N).
- Para a primeira versão, considera-se um prontuário principal por paciente (1:1).
- Um prontuário pode possuir várias evoluções (1:N).
- Um psicólogo pode registrar várias evoluções; cada evolução identifica o profissional responsável (1:N).

## 5. Modelo lógico e normalização

As entidades serão organizadas em tabelas relacionadas por chaves primárias (PK) e chaves estrangeiras (FK). A separação dos dados de pacientes, psicólogos, consultas e evoluções busca reduzir duplicidade e facilitar a manutenção das informações.

## 6. Modelo físico e scripts SQL

O arquivo `modelo-fisico.sql` conterá os comandos SQL para criação das tabelas e definição de suas chaves e relacionamentos.

## 7. Diagrama Entidade-Relacionamento (DER)

O diagrama será disponibilizado no arquivo `der-clinica.png` e representa visualmente as principais entidades e seus relacionamentos.

## 8. Segurança e controle de acesso

O sistema deverá respeitar os perfis de administrador, recepção, paciente e psicólogo. O acesso aos prontuários deverá ser restrito aos profissionais autorizados, e cada paciente deverá visualizar somente suas próprias consultas. As permissões deverão ser aplicadas pela aplicação e, quando configurado, pelo SGBD.

## 9. Arquivos desta pasta

- `README.md` — visão geral da modelagem.
- `modelo-logico.md` — descrição das tabelas, atributos, PKs, FKs e cardinalidades.
- `modelo-fisico.sql` — script de criação do banco.
- `der-clinica.png` — diagrama visual.

## 10. Observação

Este material descreve uma proposta acadêmica para o PIM II. Os modelos e scripts deverão ser revisados e testados antes de uma eventual implementação.
