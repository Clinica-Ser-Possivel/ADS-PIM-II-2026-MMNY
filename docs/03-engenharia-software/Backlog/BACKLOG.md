# Product Backlog - Clínica Ser Possível

## Requisitos Funcionais (RF)

Descrevem as funcionalidades e ações que o sistema deve executar para o usuário.

| Épico / Módulo | ID | Requisito Funcional | Descrição | Prioridade |
| :--- | :--- | :--- | :--- | :--- |
| **1. Gerenciar Usuários** | RF01.1 | Cadastrar usuário | Inserir novo colaborador (Administrador, Recepção ou Psicólogo) no sistema. | Alta |
| | RF01.2 | Efetuar login | Autenticar usuário através de matrícula e senha com validação de perfil. | Alta |
| | RF01.3 | Gerenciar permissões | Vincular o paciente ao psicólogo responsável conforme o agendamento realizado pela recepção, permitindo acesso ao prontuário clínico durante o tratamento. Em caso de encaminhamento interno autorizado pelo psicólogo responsável ou administrador, conceder ao novo psicólogo acesso aos registros técnicos, preservando as anotações privadas do profissional anterior. | Alta |
| | RF01.4 | Inativar usuário | Alterar o status do colaborador para inativo sem excluir o histórico do banco de dados. | Média |
| **2. Gestão de Pacientes** | RF02.1 | Cadastrar paciente e responsável | Registrar dados do paciente infanto-juvenil e do seu responsável legal. | Alta |
| | RF02.2 | Consultar dados cadastrais | Permitir a busca e visualização dos dados cadastrais de pacientes e responsáveis por nome ou CPF. | Média |
| | RF02.3 | Atualizar dados | Alterar dados de contato e endereço de pacientes e responsáveis. | Média |
| **3. Prontuário Eletrônico** | RF03.1 | Registrar modalidade do atendimento | Permitir ao psicólogo identificar se o atendimento foi realizado na modalidade presencial ou online durante o registro da sessão. | Média |
| | RF03.2 | Registrar anotação privada | Permitir ao psicólogo registrar anotações privadas relacionadas ao atendimento, acessíveis exclusivamente ao profissional que as produziu, inclusive quando o paciente for encaminhado a outro psicólogo da clínica. | Alta |
| | RF03.3 | Registrar evolução técnica | Criar campo para registrar a evolução técnica oficial que compõe o prontuário do paciente. | Alta |
| | RF03.4 | Anexar documentos ao prontuário | Permitir ao psicólogo autorizado vincular documentos em formato PDF ao prontuário do paciente, como laudos, relatórios escolares e documentos relacionados à avaliação psicológica. | Média |
| | RF03.5 | Consultar prontuário | Permitir ao psicólogo autorizado consultar o histórico de evoluções técnicas e documentos clínicos do paciente, mantendo as anotações privadas acessíveis exclusivamente ao profissional que as registrou. | Alta |
| | RF03.6 | Inserir Avaliação Psicológica | Registrar dados, testes e resultados referentes ao processo de avaliação psicológica do paciente. | Média |
| | RF03.7 | Encaminhar paciente para outro psicólogo | Permitir que o psicólogo responsável ou o administrador registre e autorize o encaminhamento do paciente para outro psicólogo da clínica, concedendo ao novo profissional acesso aos registros técnicos do prontuário, sem permitir acesso às anotações privadas do profissional anterior. O administrador poderá autorizar a transferência sem acessar o conteúdo clínico do prontuário. | Alta |
| **4. Agendamento** | RF04.1 | Agendar consulta | Permitir que a recepção e o administrador registrem uma nova consulta, selecionando paciente, psicólogo, data e horário disponível. | Alta |
| | RF04.2 | Remarcar ou cancelar | Permitir que a recepção e o administrador alterem a data ou o horário de consultas agendadas ou realizem seu cancelamento, respeitando a disponibilidade do psicólogo. | Alta |
| | RF04.3 | Visualizar agenda | Permitir a consulta dos agendamentos por data e profissional, respeitando o perfil de acesso: o psicólogo visualiza seus próprios atendimentos, enquanto a recepção e o administrador podem consultar as agendas dos profissionais da clínica. | Média |

---

## Requisitos Não Funcionais (RNF)

Descrevem as restrições, premissas de qualidade e requisitos técnicos do sistema.

| Categoria | ID | Requisito Técnico | Descrição | Prioridade |
| :--- | :--- | :--- | :--- | :--- |
| **Segurança e LGPD** | RNF01 | Criptografia e Acesso | Implementar mecanismos de proteção de dados e controle de acesso aos prontuários conforme o perfil do usuário e o vínculo do psicólogo com o paciente, impedindo o acesso não autorizado a informações clínicas e anotações privadas. | Alta |
| **Guarda Temporal** | RNF02 | Controle de Retenção | Garantir a integridade e guarda temporal do banco de dados e prontuários por no mínimo 5 anos, observando os prazos legais e profissionais aplicáveis. | Alta |
| **Usabilidade** | RNF03 | Interface de Usuário | O sistema deverá apresentar menus textuais organizados, opções numeradas e mensagens claras de orientação e validação, permitindo que os usuários executem as funcionalidades por meio do terminal de maneira intuitiva. | Média |
