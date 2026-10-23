# Product Backlog - Clínica Ser Possível

## Escopo do protótipo

O sistema será desenvolvido em linguagem C como um protótipo acadêmico para gerenciamento de usuários, pacientes, prontuários e agendamentos da Clínica Ser Possível.

Os dados serão armazenados localmente em arquivos `.dat`, com leitura e gravação realizadas pelo programa em C. O banco de dados será modelado separadamente por meio de um Diagrama Entidade-Relacionamento (DER), sem integração com o sistema neste semestre.

Serão utilizados exclusivamente dados fictícios em cadastros, testes, documentação e demonstrações.

## Requisitos Funcionais (RF)

Descrevem as funcionalidades e ações que o sistema deve executar para o usuário.

| Épico / Módulo | ID | Requisito Funcional | Descrição | Prioridade |
| :--- | :--- | :--- | :--- | :--- |
| **1. Gerenciar Usuários** | RF01.1 | Cadastrar usuário | Inserir novo colaborador no sistema, informando sua função (Administrador, Recepção ou Psicólogo). O sistema deverá atribuir automaticamente o perfil de acesso correspondente à função cadastrada, com permissões fixas previamente definidas, sem configuração individual de permissões. | Alta |
| | RF01.2 | Efetuar login | Autenticar usuário através de matrícula e senha, verificar se o cadastro está ativo e liberar somente as funcionalidades permitidas pelo perfil atribuído no cadastro. Impedir o acesso quando as credenciais forem inválidas ou o usuário estiver inativo. | Alta |
| | RF01.3 | Inativar usuário | Alterar o status do colaborador para inativo, impedindo novos acessos sem apagar seu histórico de registros. | Média |
| **2. Gestão de Pacientes** | RF02.1 | Cadastrar paciente e responsável | Registrar dados do paciente infanto-juvenil e do seu responsável legal. | Alta |
| | RF02.2 | Consultar dados cadastrais | Permitir a busca e visualização dos dados cadastrais de pacientes e responsáveis por nome ou CPF. | Média |
| | RF02.3 | Atualizar dados | Alterar dados de contato e endereço de pacientes e responsáveis. | Média |
| **3. Prontuário Eletrônico** | RF03.1 | Registrar evolução técnica | Permitir ao psicólogo autorizado registrar a evolução técnica que compõe o prontuário do paciente, vinculando o registro ao paciente, ao profissional responsável e à data do atendimento. | Alta |
| | RF03.2 | Consultar prontuário | Permitir ao psicólogo autorizado visualizar o histórico de evoluções técnicas do paciente, respeitando o vínculo profissional e as regras de acesso. | Alta |
| **4. Agendamento** | RF04.1 | Agendar consulta | Permitir que a recepção e o administrador registrem uma nova consulta, selecionando paciente, psicólogo, data e horário disponível. | Alta |
| | RF04.2 | Remarcar ou cancelar | Permitir que a recepção e o administrador alterem a data ou o horário de consultas agendadas ou realizem seu cancelamento, respeitando a disponibilidade do psicólogo. | Alta |
| | RF04.3 | Visualizar agenda | Permitir a consulta dos agendamentos por data e profissional, respeitando o perfil de acesso: o psicólogo visualiza seus próprios atendimentos, enquanto a recepção e o administrador podem consultar as agendas dos profissionais da clínica. | Média |

### Perfis e controle de acesso

- Os perfis de Administrador, Recepção e Psicólogo terão permissões fixas definidas no sistema.
- O perfil será atribuído automaticamente conforme a função informada no cadastro do colaborador.
- O sistema deverá validar a autorização antes de executar cada operação restrita.
- O acesso às evoluções técnicas será permitido somente ao psicólogo autorizado, conforme seu vínculo profissional com o paciente. O perfil de Administrador não concederá, por si só, acesso ao conteúdo clínico.
- Não haverá funcionalidade independente para gerenciar ou personalizar permissões.

## Requisitos Não Funcionais (RNF)

Descrevem as restrições, premissas de qualidade e requisitos técnicos do sistema.

| Categoria | ID | Requisito Técnico | Descrição | Prioridade |
| :--- | :--- | :--- | :--- | :--- |
| **Segurança** | RNF01 | Segurança e controle de acesso | Restringir as operações conforme o perfil fixo do usuário e o vínculo profissional com o paciente. Exigir autenticação e cadastro ativo para acessar funcionalidades protegidas e impedir acesso não autorizado às informações clínicas. Utilizar exclusivamente dados fictícios no protótipo. | Alta |
| **Armazenamento** | RNF02 | Persistência local | Armazenar os dados localmente em arquivos `.dat`, utilizando operações de leitura e gravação em C. Os registros gravados com sucesso deverão permanecer disponíveis após encerrar e reabrir o programa. Não haverá integração com banco de dados neste semestre. | Alta |
| **Confiabilidade** | RNF03 | Integridade de dados | Validar campos obrigatórios, formatos e referências entre registros antes da gravação. Impedir identificadores duplicados e vínculos com registros inexistentes, preservar o histórico dos usuários inativados e informar falhas de leitura ou gravação sem indicar sucesso indevidamente. | Alta |
| **Desempenho** | RNF04 | Tempo de resposta | Concluir cada operação de cadastro, consulta, atualização, inativação e agendamento em até 3 segundos, em testes locais com uma base de até 100 registros fictícios no total. A medição deverá considerar o intervalo entre a confirmação dos dados pelo usuário e a apresentação do resultado, incluindo a leitura ou gravação necessária nos arquivos. | Média |

## Modelagem do banco de dados

O banco de dados será modelado separadamente em um Diagrama Entidade-Relacionamento (DER), representando as entidades, seus atributos, identificadores, relacionamentos e cardinalidades.

A modelagem deverá ser coerente com os requisitos funcionais e com os vínculos entre usuários, pacientes, responsáveis, evoluções técnicas e agendamentos.

A entrega do DER é documental. A criação de um banco em um SGBD e sua integração com o programa em C ficam fora do escopo deste semestre.

## Critérios gerais de validação

- Confirmar a atribuição automática do perfil correspondente à função cadastrada.
- Validar o login com credenciais corretas, incorretas e de usuário inativo.
- Verificar se operações restritas são bloqueadas para perfis e vínculos sem autorização.
- Confirmar que a inativação preserva o histórico do colaborador.
- Gravar dados, encerrar o programa e reabri-lo para verificar a persistência.
- Testar entradas inválidas, identificadores duplicados e referências inexistentes.
- Medir o tempo das operações com uma base de até 100 registros fictícios no total, registrando a configuração do computador utilizado e os resultados obtidos.
- Utilizar exclusivamente dados fictícios em todas as validações.
