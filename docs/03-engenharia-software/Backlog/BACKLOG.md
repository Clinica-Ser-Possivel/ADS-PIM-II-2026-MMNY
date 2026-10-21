#  Product Backlog - Clínica Ser Possível

##  Requisitos Funcionais (RF)
Descrevem as funcionalidades e ações que o sistema deve executar para o usuário.

| Épico / Módulo | ID | Requisito Funcional | Descrição | Prioridade |
| :--- | :--- | :--- | :--- | :--- |
| **1. Gerenciar Usuários** | RF01.1 | Cadastrar usuário | Inserir novo colaborador (Admin, Recepção ou Psicólogo) no sistema. | Alta |
| | RF01.2 | Efetuar login | Autenticar usuário através de matrícula e senha com validação de perfil. | Alta |
| | RF01.3 | Gerenciar permissões | Restringir o acesso a prontuários apenas ao Psicólogo de referência. | Alta |
| | RF01.4 | Inativar usuário | Alterar o status do colaborador para inativo sem excluir o histórico do banco. | Média |
| **2. Gestão de Pacientes** | RF02.1 | Cadastrar paciente e responsável | Registrar dados do paciente infanto-juvenil e do seu responsável legal. | Alta |
| | RF02.2 | Consultar dados cadastrais | Permitir a busca e visualização dos dados cadastrais de pacientes e responsáveis por nome ou CPF. | Média |
| | RF02.3 | Atualizar dados | Alterar dados de contato e endereço de pacientes e responsáveis. | Média |
| **3. Prontuário Eletrônico** | RF03.1 | Selecionar formato da sessão | Permitir escolher modalidade (online, presencial) e formato no início do registro. | Média |
| | RF03.2 | Registrar anotação privada | Criar campo de anotações pessoais do psicólogo (sigiloso, apenas para o profissional). | Alta |
| | RF03.3 | Registrar evolução técnica | Criar campo da evolução técnica oficial que compõe o prontuário do paciente. | Alta |
| | RF03.4 | Anexar documentos | Permitir upload e armazenamento de laudos, testes e relatórios escolares em PDF. | Média |
| | RF03.5 | Consultar prontuário | Buscar e visualizar todo o histórico de evoluções, anotações e documentos do paciente. | Alta |
| | RF03.6 | Inserir Avaliação Psicológica | Registrar dados, testes e resultados referentes ao processo de avaliação psicológica do paciente. | Média |
| **4. Agendamento** | RF04.1 | Agendar consulta | Registrar nova consulta selecionando paciente, psicólogo, data e horário. | Alta |
| | RF04.2 | Remarcar ou cancelar | Permitir alterar a data/horário de um agendamento ou efetuar cancelamento. | Alta |
| | RF04.3 | Visualizar agenda | Exibir a grade de horários diária/semanal filtrada pelo psicólogo logado. | Média |

---

##  Requisitos Não Funcionais (RNF)
Descrevem as restrições, premissas de qualidade e requisitos técnicos do sistema.

| Categoria | ID | Requisito Técnico | Descrição | Prioridade |
| :--- | :--- | :--- | :--- | :--- |
| **Segurança e LGPD** | RNF01 | Criptografia e Acesso | Implementar mecanismos de proteção de dados e controle estrito de acesso aos prontuários. | Alta |
| **Guarda Temporal** | RNF02 | Controle de Retenção | Garantir a integridade e guarda temporal do banco de dados e prontuários por no mínimo 5 anos. | Alta |
| **Usabilidade** | RNF03 | Interface de Usuário | Desenvolver telas limpas e responsivas para agilizar o atendimento, dispensando o uso de manual. | Média |
| **Desempenho** | RNF04 | Otimização de Consultas | Garantir tempo de resposta inferior a 2 segundos nas pesquisas de banco de dados e gravações. | Média |
