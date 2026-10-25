# Banco de Dados — Clínica Ser Possível

## 1. Objetivo e escopo

Esta pasta documenta a modelagem relacional proposta para apoiar os requisitos do sistema da Clínica Ser Possível. A modelagem é uma entrega acadêmica independente: neste semestre, o protótipo será desenvolvido em linguagem C e armazenará os dados localmente em arquivos `.dat`. **Não haverá integração do programa em C com SQL Server nesta etapa.**

O modelo deve ser lido em conjunto com o Product Backlog. São considerados os cadastros de colaboradores, pacientes e responsáveis legais, o vínculo profissional que autoriza o acesso clínico, as consultas e as evoluções técnicas. Devem ser usados exclusivamente dados fictícios em documentação, testes e demonstrações.

## 2. SGBD de referência

O arquivo `modelo-fisico.sql` apresenta uma implementação de referência para Microsoft SQL Server. O script serve para demonstrar as tabelas, restrições e relacionamentos; não representa o armazenamento utilizado pelo protótipo em C.

## 3. Entidades e finalidade

- **USUARIO:** credenciais, matrícula, perfil fixo e situação ativa/inativa dos colaboradores que acessam o sistema.
- **PACIENTE:** dados cadastrais do paciente infantojuvenil.
- **RESPONSAVEL:** dados cadastrais do responsável legal.
- **PSICOLOGO:** dados profissionais do psicólogo vinculado a uma conta de usuário.
- **VINCULO_PACIENTE_PSICOLOGO:** vínculo profissional ativo que define quais pacientes podem ter suas informações clínicas acessadas pelo psicólogo.
- **CONSULTA:** agendamento, paciente, psicólogo, data, horário e situação.
- **PRONTUARIO:** prontuário principal do paciente.
- **EVOLUCAO:** evolução técnica, com a data do atendimento separada da data em que o registro foi lançado.

## 4. Relacionamentos e cardinalidades

- Um usuário pode estar associado a um cadastro de psicólogo; cada psicólogo deve estar associado a uma conta de usuário.
- Um paciente pode ter várias consultas; cada consulta pertence a um paciente.
- Um psicólogo pode ter várias consultas; cada consulta é atribuída a um psicólogo.
- Cada paciente possui no máximo um prontuário principal; cada prontuário pertence a um paciente.
- Um prontuário pode conter várias evoluções; cada evolução pertence a um prontuário e identifica o psicólogo autor.
- Pacientes e psicólogos podem estar relacionados por meio de `VINCULO_PACIENTE_PSICOLOGO`. O vínculo deve estar ativo para autorizar o acesso clínico, independentemente de existir consulta agendada.
- Nesta versão do escopo, cada paciente é cadastrado com um responsável legal principal. Se o grupo decidir que vários responsáveis legais por paciente são requisito, será necessário alterar o relacionamento para uma associação muitos-para-muitos.
- O responsável legal é cadastral; o backlog não define uma conta de acesso para o responsável, portanto ele não é um perfil de `USUARIO`.

## 5. Regras de negócio representadas

1. Os únicos perfis autenticáveis são `ADMIN`, `RECEPCAO` e `PSICOLOGO`.
2. O login utiliza matrícula e senha. A conta precisa estar ativa; a senha é representada por um hash, nunca por texto puro.
3. A inativação de usuário não apaga seu histórico.
4. A recepção e o administrador podem agendar, remarcar e cancelar consultas. Remarcar significa atualizar data e/ou horário de uma consulta ainda agendada; cancelar altera seu status para `CANCELADA`.
5. Não se deve permitir que o mesmo psicólogo tenha duas consultas não canceladas na mesma data e horário. O script também evita que o mesmo paciente tenha duas consultas não canceladas no mesmo horário. Como a duração da consulta não está especificada no backlog, a regra cobre igualdade de data e horário, não sobreposição de intervalos.
6. O psicólogo só pode consultar ou registrar evoluções de pacientes com vínculo profissional ativo. O perfil de administrador, por si só, não autoriza acesso ao conteúdo clínico.
7. A evolução registra separadamente `data_atendimento` e `data_registro`.

## 6. Arquivos desta pasta

- `README.md`: visão geral, escopo e regras principais.
- `der.md`: Diagrama Entidade-Relacionamento em Mermaid.
- `modelo-logico.md`: tabelas, atributos, chaves e cardinalidades.
- `modelo-fisico.sql`: script de referência para SQL Server.

## 7. Segurança e dados pessoais

Informações de saúde são sensíveis. O projeto deve restringir o acesso às informações clínicas, validar permissões antes de operações protegidas e usar somente dados fictícios no protótipo. O modelo documental não substitui uma avaliação de segurança nem a validação das regras pelo grupo.

## 8. Decisões para confirmar com o grupo

- **Responsável legal:** este modelo considera um responsável principal por paciente, porque o requisito está redigido no singular. Confirmar se o grupo precisa registrar mais de um.
- **Conflito de agenda:** o modelo impede igualdade exata de data e horário. A duração da consulta e a regra para sobreposição de horários não foram definidas no backlog.
- **Login/matrícula:** o campo `matricula` foi adotado como identificador de login, conforme RF01.2.
- **Vínculo profissional:** o modelo permite registrar/inativar um vínculo psicólogo-paciente; o procedimento operacional de criação desse vínculo precisa ser confirmado pelo grupo.
- **Registro clínico:** o backlog exige evolução técnica. Não foi criada uma entidade separada para anotações privadas, pois essa funcionalidade não está especificada como requisito funcional no backlog fornecido.
