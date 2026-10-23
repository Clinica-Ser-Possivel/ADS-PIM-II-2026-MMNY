
# Product Backlog - Clínica Ser Possível

## Requisitos Funcionais (RF)

Descrevem as funcionalidades e ações que o sistema deve executar para o usuário.

| Épico / Módulo | ID | Requisito Funcional | Descrição | Prioridade |
| :--- | :--- | :--- | :--- | :--- |
| **1. Gerenciar Usuários** | RF01.1 | Cadastrar usuário | Inserir novo colaborador (Administrador, Recepção ou Psicólogo) no sistema. | Alta |
| | RF01.2 | Efetuar login | Autenticar usuário através de matrícula e senha com validação de perfil. | Alta |
| | RF01.3 | Gerenciar permissões | Definir no cadastro o perfil (Administrador, Recepção ou Psicólogo) e restringir funcionalidades conforme perfil e vínculo do psicólogo ao paciente. | Alta |
| | RF01.4 | Inativar usuário | Alterar o status do colaborador para inativo sem apagar seu histórico de registros. | Média |
| **2. Gestão de Pacientes** | RF02.1 | Cadastrar paciente e responsável | Registrar dados do paciente infanto-juvenil e do seu responsável legal. | Alta |
| | RF02.2 | Consultar dados cadastrais | Permitir a busca e visualização dos dados cadastrais de pacientes e responsáveis por nome ou CPF. | Média |
| | RF02.3 | Atualizar dados | Alterar dados de contato e endereço de pacientes e responsáveis. | Média |
| **3. Prontuário Eletrônico** | RF03.3 | Registrar evolução técnica | Criar campo para registrar a evolução técnica oficial que compõe o prontuário do paciente. | Alta |
| | RF03.5 | Consultar prontuário | Permitir ao psicólogo autorizado visualizar o histórico de evoluções técnicas do paciente. | Alta |
| **4. Agendamento** | RF04.1 | Agendar consulta | Permitir que a recepção e o administrador registrem uma nova consulta, selecionando paciente, psicólogo, data e horário disponível. | Alta |
| | RF04.2 | Remarcar ou cancelar | Permitir que a recepção e o administrador alterem a data ou o horário de consultas agendadas ou realizem seu cancelamento, respeitando a disponibilidade do psicólogo. | Alta |
| | RF04.3 | Visualizar agenda | Permitir a consulta dos agendamentos por data e profissional, respeitando o perfil de acesso: o psicólogo visualiza seus próprios atendimentos, enquanto a recepção e o administrador podem consultar as agendas dos profissionais da clínica. | Média |

---

## Requisitos Não Funcionais (RNF)

Descrevem as restrições, premissas de qualidade e requisitos técnicos do sistema.

| Categoria | ID | Requisito Técnico | Descrição | Prioridade |
| :--- | :--- | :--- | :--- | :--- |
| **Segurança e LGPD** | RNF01 | Controle de acesso | Restringir operações por perfil e vínculo profissional, impedindo acesso não autorizado a informações clínicas. O protótipo acadêmico utilizará somente dados fictícios e não é adequado ao uso com prontuários reais. | Alta |
| **Guarda Temporal** | RNF02 | Retenção de registros | Prever preservação dos registros conforme prazos legais e profissionais aplicáveis; no protótipo, demonstrar apenas persistência básica em arquivos. | Alta |
| **Usabilidade** | RNF03 | Interface de Usuário | O sistema deverá apresentar menus textuais organizados, opções numeradas e mensagens claras de orientação e validação, permitindo que os usuários executem as funcionalidades por meio do terminal de maneira intuitiva. | Média |
