# Diagramas de Casos de Uso (UML)

Este documento apresenta os atores e os casos de uso do sistema de gerenciamento da **Clínica Ser Possível**, conforme os requisitos funcionais definidos no [Product Backlog](../Backlog/BACKLOG.md).

Os diagramas representam as funcionalidades disponíveis para cada perfil de usuário e as regras de acesso às informações administrativas e clínicas.

## RF01 — Gerenciamento de Usuários

### Atores

- **Administrador:** responsável pelo cadastro e pela inativação dos colaboradores.
- **Recepção:** utiliza a autenticação para acessar as funcionalidades administrativas autorizadas.
- **Psicólogo(a):** utiliza a autenticação para acessar as funcionalidades autorizadas de atendimento e acompanhamento clínico.

### Casos de uso

- **RF01.1 — Cadastrar usuário:** permite ao administrador cadastrar colaboradores, informando sua função como Administrador, Recepção ou Psicólogo. O sistema atribui automaticamente o perfil correspondente à função cadastrada, com permissões fixas previamente definidas.
- **RF01.2 — Efetuar login:** permite aos três perfis autenticar-se por matrícula e senha. O sistema verifica as credenciais e o status ativo do usuário, liberando somente as funcionalidades autorizadas para seu perfil.
- **RF01.3 — Inativar usuário:** permite ao administrador alterar o status de um colaborador para inativo, impedindo novos acessos sem excluir seu histórico de registros.

### Regras de acesso

- Somente o Administrador pode cadastrar e inativar usuários.
- O perfil é atribuído automaticamente conforme a função informada no cadastro.
- As permissões de cada perfil são fixas e definidas no sistema.
- Não existe caso de uso independente para gerenciar ou personalizar permissões.
- Credenciais inválidas ou cadastro inativo impedem o login.
- A autorização deve ser verificada antes da execução de cada operação restrita.
- O perfil de Administrador não concede acesso ao conteúdo clínico dos prontuários.

## RF02 — Gestão de Pacientes e Responsáveis

### Atores

- **Administrador:** pode cadastrar, consultar e atualizar informações cadastrais dos pacientes e responsáveis.
- **Recepção:** pode cadastrar, consultar e atualizar informações cadastrais dos pacientes e responsáveis.
- **Psicólogo(a):** pode consultar os dados cadastrais necessários ao atendimento dos pacientes vinculados ao seu acompanhamento.

### Casos de uso

- **RF02.1 — Cadastrar paciente e responsável:** permite registrar os dados do paciente infanto-juvenil e vinculá-lo ao seu responsável legal.
- **RF02.2 — Consultar dados cadastrais:** permite pesquisar e visualizar informações cadastrais dos pacientes e responsáveis por nome ou CPF.
- **RF02.3 — Atualizar dados:** permite alterar informações de contato e endereço dos pacientes e responsáveis.

### Regras de acesso

- Administrador e Recepção podem cadastrar, consultar e atualizar informações cadastrais.
- O Psicólogo pode consultar os dados cadastrais necessários ao atendimento, respeitando seu vínculo com o paciente.
- O acesso aos dados cadastrais não concede acesso automático ao conteúdo clínico do prontuário.
- Todas as operações devem respeitar as permissões fixas do perfil autenticado.

## RF03 — Prontuário Eletrônico

### Ator

- **Psicólogo(a):** responsável pelo registro das evoluções técnicas e pela consulta aos prontuários dos pacientes vinculados ao seu acompanhamento.

### Casos de uso

- **RF03.1 — Registrar evolução técnica:** permite ao psicólogo autorizado registrar a evolução técnica que compõe o prontuário, vinculando o registro ao paciente, ao profissional responsável e à data do atendimento.
- **RF03.2 — Consultar prontuário:** permite ao psicólogo autorizado visualizar o histórico de evoluções técnicas do paciente.

### Regras de acesso e sigilo

- Somente psicólogos autorizados podem registrar evoluções técnicas e consultar prontuários.
- A autorização depende do perfil e do vínculo profissional com o paciente.
- Administrador e Recepção não possuem acesso ao conteúdo clínico dos prontuários.
- Os registros devem manter a identificação do paciente e do profissional responsável.
- O protótipo deve utilizar exclusivamente informações clínicas fictícias.

## RF04 — Agendamento de Consultas

### Atores

- **Administrador:** pode agendar, remarcar, cancelar e consultar os agendamentos dos profissionais.
- **Recepção:** pode agendar, remarcar, cancelar e consultar os agendamentos dos profissionais.
- **Psicólogo(a):** pode consultar sua própria agenda de atendimentos.

### Casos de uso

- **RF04.1 — Agendar consulta:** permite à Recepção ou ao Administrador registrar uma nova consulta, selecionando paciente, psicólogo, data e horário disponível.
- **RF04.2 — Remarcar ou cancelar:** permite à Recepção ou ao Administrador alterar a data ou o horário de uma consulta ou realizar seu cancelamento, respeitando a disponibilidade do psicólogo.
- **RF04.3 — Visualizar agenda:** permite consultar os agendamentos por data e profissional. O Psicólogo visualiza seus próprios atendimentos, enquanto Recepção e Administrador podem consultar as agendas dos profissionais da clínica.

### Regras de agendamento

- Somente Recepção e Administrador podem agendar, remarcar ou cancelar consultas.
- O agendamento e a remarcação devem considerar a disponibilidade do psicólogo.
- Não é permitido registrar duas consultas para o mesmo psicólogo na mesma data e horário.
- Cada Psicólogo pode visualizar somente sua própria agenda.
- Recepção e Administrador podem consultar as agendas dos psicólogos da clínica.
- Cada agendamento deve identificar o paciente e o psicólogo responsável.
- O acesso ao prontuário deve respeitar o vínculo profissional com o paciente, conforme as regras de RF03.

## Associações entre atores e casos de uso

A tabela orienta a representação das associações nos diagramas UML.

| ID | Caso de uso | Administrador | Recepção | Psicólogo(a) |
| :--- | :--- | :---: | :---: | :---: |
| RF01.1 | Cadastrar usuário | Sim | — | — |
| RF01.2 | Efetuar login | Sim | Sim | Sim |
| RF01.3 | Inativar usuário | Sim | — | — |
| RF02.1 | Cadastrar paciente e responsável | Sim | Sim | — |
| RF02.2 | Consultar dados cadastrais | Sim | Sim | Sim, conforme vínculo |
| RF02.3 | Atualizar dados | Sim | Sim | — |
| RF03.1 | Registrar evolução técnica | — | — | Sim, conforme vínculo |
| RF03.2 | Consultar prontuário | — | — | Sim, conforme vínculo |
| RF04.1 | Agendar consulta | Sim | Sim | — |
| RF04.2 | Remarcar ou cancelar | Sim | Sim | — |
| RF04.3 | Visualizar agenda | Todas as agendas | Todas as agendas | Somente a própria |

## Orientações para os diagramas UML

- Representar Administrador, Recepção e Psicólogo(a) como atores externos ao limite do sistema.
- Utilizar os nomes e identificadores dos casos de uso apresentados neste documento.
- Associar cada ator somente aos casos de uso autorizados na tabela.
- Tratar a atribuição automática do perfil como parte de **RF01.1 — Cadastrar usuário**.
- Tratar a validação das credenciais e do status ativo como parte de **RF01.2 — Efetuar login**.
- Considerar a autenticação como precondição das demais funcionalidades protegidas.
- Não representar “Gerenciar permissões” como caso de uso.
- Documentar as restrições de vínculo profissional e de visualização da própria agenda nas regras dos respectivos casos de uso.

## Considerações técnicas e escopo acadêmico

A aplicação será desenvolvida em **linguagem C**, utilizando programação estruturada e interação por meio do terminal.

Os dados serão armazenados localmente em arquivos **`.dat`**, com leitura e gravação realizadas pelo programa. Os registros gravados com sucesso deverão permanecer disponíveis após encerrar e reabrir o sistema.

A implementação deverá atender aos requisitos não funcionais definidos no Product Backlog:

- **RNF01 — Segurança e controle de acesso:** validar autenticação, perfil e vínculo profissional nas operações protegidas.
- **RNF02 — Persistência local:** armazenar e recuperar os dados em arquivos `.dat`, sem integração com banco de dados neste semestre.
- **RNF03 — Integridade de dados:** validar entradas e referências
