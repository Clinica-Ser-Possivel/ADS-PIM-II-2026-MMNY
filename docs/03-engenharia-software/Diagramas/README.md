# Diagramas de Casos de Uso (UML)

Este documento apresenta os atores e os casos de uso do sistema de gerenciamento da Clínica Ser Possível, organizados de acordo com os requisitos funcionais definidos no Product Backlog.

Os diagramas representam as funcionalidades disponíveis para cada perfil de usuário, considerando suas responsabilidades e as regras de acesso às informações cadastrais e clínicas.

---

## RF01 — Gerenciamento de Usuários

### ATORES

**Administrador (Admin)** — Responsável pelo cadastro, inativação e gerenciamento das permissões de acesso dos colaboradores. Também poderá autorizar encaminhamentos internos de pacientes, sem acesso ao conteúdo clínico dos prontuários.

**Psicólogo(a)** — Profissional responsável pelos atendimentos clínicos, com acesso aos prontuários dos pacientes vinculados ao seu acompanhamento, respeitando as permissões e o sigilo profissional.

**Recepção** — Responsável pelo agendamento dos pacientes e pela consulta às informações administrativas necessárias ao atendimento.

### CASOS DE USO

- **RF01.1 — Cadastrar usuário:** Permite ao administrador registrar novos colaboradores no sistema, definindo seu perfil como Administrador, Recepção ou Psicólogo.

- **RF01.2 — Efetuar login:** Permite a autenticação dos usuários por meio de matrícula e senha, com identificação do perfil e aplicação das respectivas permissões.

- **RF01.3 — Gerenciar permissões:** Permite controlar o acesso às funcionalidades e aos prontuários conforme o perfil do usuário e o vínculo do psicólogo com o paciente. O vínculo inicial é estabelecido a partir do agendamento, e o acesso aos registros técnicos poderá ser atualizado mediante encaminhamento interno autorizado pelo psicólogo responsável ou administrador.

- **RF01.4 — Inativar usuário:** Permite ao administrador alterar o status de um colaborador para inativo, impedindo novos acessos sem excluir seu histórico de registros.

### REGRAS DE ACESSO

- A recepção e o psicólogo possuem acesso apenas às funcionalidades autorizadas para seus respectivos perfis.
- O administrador gerencia as permissões, mas não possui acesso ao conteúdo clínico dos prontuários.
- O psicólogo responsável pode consultar os registros clínicos dos pacientes vinculados ao seu atendimento.
- Em caso de encaminhamento interno, o novo psicólogo recebe acesso aos registros técnicos necessários à continuidade do tratamento.
- As anotações privadas permanecem acessíveis exclusivamente ao profissional que as registrou.

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

## RF03 — Prontuário Eletrônico e Avaliação Psicológica

### ATORES

**Psicólogo(a)** — Responsável pelo registro das informações clínicas, evoluções técnicas, avaliações psicológicas, documentos e anotações privadas. Também poderá registrar e autorizar encaminhamentos dos pacientes sob sua responsabilidade.

**Administrador (Admin)** — Poderá registrar e autorizar encaminhamentos internos entre psicólogos, sem acesso às evoluções clínicas, avaliações, documentos sigilosos ou anotações privadas.

### CASOS DE USO

- **RF03.1 — Registrar modalidade do atendimento:** Permite ao psicólogo identificar, durante o registro da sessão, se o atendimento ocorreu presencialmente ou online.

- **RF03.2 — Registrar anotação privada:** Permite ao psicólogo registrar anotações pessoais relacionadas ao atendimento, acessíveis exclusivamente ao profissional que as produziu, inclusive após eventual encaminhamento do paciente.

- **RF03.3 — Registrar evolução técnica:** Permite ao psicólogo registrar a evolução técnica oficial da sessão, compondo o prontuário clínico do paciente.

- **RF03.4 — Anexar documentos ao prontuário:** Permite ao psicólogo autorizado vincular documentos em formato PDF, como laudos, relatórios escolares e documentos relacionados à avaliação psicológica.

- **RF03.5 — Consultar prontuário:** Permite ao psicólogo autorizado consultar o histórico de evoluções técnicas e documentos clínicos, respeitando as permissões de acesso e preservando a privacidade das anotações de outros profissionais.

- **RF03.6 — Inserir Avaliação Psicológica:** Permite ao psicólogo registrar dados, instrumentos utilizados e resultados relacionados ao processo de avaliação psicológica ou neuropsicológica do paciente.

- **RF03.7 — Encaminhar paciente para outro psicólogo:** Permite ao psicólogo responsável ou ao administrador registrar e autorizar o encaminhamento de um paciente para outro psicólogo da clínica, atualizando o vínculo profissional e concedendo ao novo responsável acesso aos registros técnicos do prontuário, sem disponibilizar as anotações privadas do profissional anterior.

### REGRAS DE ACESSO E SIGILO

- Somente psicólogos autorizados podem consultar ou registrar informações clínicas.
- As anotações privadas são exclusivas do psicólogo que as produziu.
- O psicólogo que recebe um paciente encaminhado poderá consultar os registros técnicos necessários à continuidade do tratamento.
- O encaminhamento deverá ser registrado e autorizado pelo psicólogo responsável ou administrador.
- A autorização administrativa de um encaminhamento não concede ao administrador acesso ao conteúdo clínico do prontuário.
- Os documentos e registros clínicos deverão respeitar as regras de confidencialidade e proteção de dados aplicáveis.

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
- Cada psicólogo poderá visualizar sua própria agenda.
- Recepção e Administrador poderão consultar as agendas dos psicólogos da clínica.
- O agendamento inicial estabelece o vínculo entre paciente e psicólogo responsável, conforme as regras de gerenciamento de permissões.

---

## CONSIDERAÇÕES GERAIS

Os diagramas de casos de uso representam as interações entre os atores e as funcionalidades do sistema, conforme as regras de negócio estabelecidas para a Clínica Ser Possível.

A aplicação será desenvolvida em linguagem C, com interação por meio do terminal, sem interface gráfica.

As funcionalidades descritas deverão respeitar os níveis de acesso dos usuários, a separação entre informações administrativas e clínicas e a confidencialidade dos registros psicológicos.

A representação dos atores e suas associações nos diagramas UML deverá corresponder aos casos de uso documentados neste arquivo e aos requisitos funcionais definidos no Product Backlog.
