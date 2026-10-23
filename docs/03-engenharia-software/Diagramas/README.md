
# Diagramas de Casos de Uso (UML)

Este documento apresenta os atores e os casos de uso do sistema de gerenciamento da **Clínica Ser Possível**, organizados de acordo com os requisitos funcionais definidos no Product Backlog.

Os diagramas representam as funcionalidades disponíveis para cada perfil de usuário, considerando suas responsabilidades e as regras de acesso às informações cadastrais e clínicas.

---

## RF01 — Gerenciamento de Usuários

### ATORES

**Administrador (Admin)** — Responsável pelo cadastro, inativação e gerenciamento das permissões de acesso dos colaboradores. Não possui acesso ao conteúdo clínico dos prontuários.

**Psicólogo(a)** — Profissional responsável pelos atendimentos clínicos, com acesso aos prontuários dos pacientes vinculados ao seu acompanhamento, respeitando as permissões e o sigilo profissional.

**Recepção** — Responsável pelo agendamento dos pacientes e pela consulta às informações administrativas necessárias ao atendimento.

### CASOS DE USO

- **RF01.1 — Cadastrar usuário:** Permite ao administrador registrar novos colaboradores no sistema, definindo seu perfil como Administrador, Recepção ou Psicólogo.

- **RF01.2 — Efetuar login:** Permite a autenticação dos usuários por meio de matrícula e senha, com identificação do perfil e aplicação das respectivas permissões.

- **RF01.3 — Gerenciar permissões:** Permite definir e controlar o acesso às funcionalidades do sistema conforme o perfil cadastrado. O acesso do psicólogo ao prontuário depende de seu vínculo com o paciente.

- **RF01.4 — Inativar usuário:** Permite ao administrador alterar o status de um colaborador para inativo, impedindo novos acessos sem excluir seu histórico de registros.

### REGRAS DE ACESSO

- O administrador é responsável pelo cadastro, gerenciamento das permissões e inativação dos usuários.
- Os perfis de acesso são definidos no momento do cadastro do colaborador.
- A recepção e o psicólogo possuem acesso apenas às funcionalidades autorizadas para seus respectivos perfis.
- O administrador não possui acesso ao conteúdo clínico dos prontuários.
- O psicólogo autorizado pode consultar os registros clínicos dos pacientes vinculados ao seu atendimento.
- Usuários inativos não poderão realizar novos acessos ao sistema.

---

## RF02 — Gestão de Pacientes e Responsáveis

### ATORES

**Administrador (Admin)** — Responsável pela gestão administrativa, podendo cadastrar, consultar e atualizar informações cadastrais dos pacientes e responsáveis.

**Psicólogo(a)** — Profissional autorizado a consultar os dados cadastrais necessários à identificação e ao acompanhamento dos pacientes.

**Recepção** — Responsável pelo cadastro, consulta e atualização das informações administrativas dos pacientes e de seus responsáveis legais.

### CASOS DE USO

- **RF02.1 — Cadastrar paciente e responsável:** Permite registrar os dados de identificação do paciente infanto-juvenil e vinculá-lo ao seu responsável legal.

- **RF02.2 — Consultar dados cadastrais:** Permite pesquisar e visualizar informações cadastrais dos pacientes e responsáveis por nome ou CPF, sem disponibilizar o conteúdo clínico do prontuário.

- **RF02.3 — Atualizar dados:** Permite alterar informações cadastrais, como telefone, endereço e outros dados de contato de pacientes e responsáveis.

### REGRAS DE ACESSO

- Administrador e Recepção podem cadastrar, consultar e atualizar informações cadastrais.
- O Psicólogo pode consultar os dados cadastrais necessários ao atendimento.
- O acesso aos dados cadastrais não concede acesso automático às informações clínicas do prontuário.
- As permissões devem respeitar o perfil de cada usuário.

---

## RF03 — Prontuário Eletrônico

### ATORES

**Psicólogo(a)** — Profissional responsável pelo registro das evoluções técnicas dos atendimentos e pela consulta aos prontuários dos pacientes vinculados ao seu acompanhamento.

### CASOS DE USO

- **RF03.1 — Registrar evolução técnica:** Permite ao psicólogo autorizado registrar a evolução técnica oficial do atendimento, compondo o prontuário clínico do paciente.

- **RF03.2 — Consultar prontuário:** Permite ao psicólogo autorizado consultar o histórico de evoluções técnicas registradas no prontuário do paciente.

### REGRAS DE ACESSO E SIGILO

- Somente psicólogos autorizados podem registrar evoluções técnicas nos prontuários.
- O psicólogo poderá consultar os prontuários dos pacientes vinculados ao seu acompanhamento.
- O administrador e a recepção não possuem acesso ao conteúdo clínico dos prontuários.
- Os registros clínicos deverão respeitar as regras de confidencialidade e proteção de dados aplicáveis.
- O sistema deverá restringir o acesso às informações clínicas conforme o perfil e o vínculo profissional com o paciente.

---

## RF04 — Agendamento de Consultas

### ATORES

**Administrador (Admin)** — Responsável pela gestão administrativa das agendas, podendo registrar, remarcar, cancelar e consultar agendamentos dos profissionais.

**Recepção** — Responsável pela organização cotidiana dos atendimentos, incluindo agendamentos, remarcações, cancelamentos e consulta às agendas dos psicólogos.

**Psicólogo(a)** — Profissional que poderá consultar os compromissos e horários de atendimento vinculados à sua própria agenda.

### CASOS DE USO

- **RF04.1 — Agendar consulta:** Permite à recepção ou ao administrador registrar uma nova consulta, selecionando paciente, psicólogo, data e horário disponível.

- **RF04.2 — Remarcar ou cancelar:** Permite à recepção ou ao administrador alterar a data ou o horário de uma consulta ou realizar seu cancelamento, considerando a disponibilidade do profissional.

- **RF04.3 — Visualizar agenda:** Permite consultar os agendamentos por data e profissional. O psicólogo visualiza seus próprios atendimentos, enquanto a recepção e o administrador podem consultar as agendas dos profissionais da clínica.

### REGRAS DE AGENDAMENTO

- Recepção e Administrador podem agendar, remarcar ou cancelar consultas.
- O agendamento deverá considerar a disponibilidade do psicólogo.
- Não deverá ser permitido registrar duas consultas para o mesmo psicólogo na mesma data e horário.
- Cada psicólogo poderá visualizar sua própria agenda.
- Recepção e Administrador poderão consultar as agendas dos psicólogos da clínica.
- O agendamento inicial estabelece o vínculo entre paciente e psicólogo responsável, conforme as regras de gerenciamento de permissões.

---

## CONSIDERAÇÕES GERAIS

Os diagramas de casos de uso representam as interações entre os atores e as funcionalidades do sistema, conforme as regras de negócio estabelecidas para a Clínica Ser Possível.

A aplicação será desenvolvida em **linguagem C**, utilizando programação estruturada, com interação exclusivamente por meio do terminal, sem interface gráfica.

O desenvolvimento utilizará conceitos como estruturas de dados (`struct`), funções, estruturas condicionais, laços de repetição e manipulação de arquivos para organizar e executar as funcionalidades.

As funcionalidades deverão respeitar os níveis de acesso dos usuários, a separação entre informações administrativas e clínicas e a confidencialidade dos registros psicológicos.

O sistema será desenvolvido como um protótipo acadêmico, utilizando dados fictícios para testes e demonstrações.

A representação dos atores e suas associações nos diagramas UML deverá corresponder aos casos de uso documentados neste arquivo e aos requisitos funcionais definidos no Product Backlog.
