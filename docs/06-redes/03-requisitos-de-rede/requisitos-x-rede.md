# Requisitos x Rede e Sistemas Distribuídos

Os requisitos abaixo são os do backlog do grupo (PIM 2). A coluna da direita mostra como a rede e a arquitetura distribuída atendem cada um.

## Regras de Negócio

| ID | Regra de negócio | Como a rede e a arquitetura atendem |
|---|---|---|
| RN01 | No cadastro do paciente, o sistema deve verificar duplicidade pelo número do documento de identificação | O servidor consulta o banco pelo documento antes de gravar |
| RN02 | Nenhuma outra pessoa deve acessar a área de evolução de prontuário | Login, perfis de acesso e logs: só o psicólogo de referência entra |
| RN03 | O sistema deve impedir agendamentos no mesmo horário para o mesmo psicólogo | O banco trava o horário no momento da reserva (bloqueio transacional) |

## Requisitos Funcionais

| ID | Requisito | Como a rede e a arquitetura atendem |
|---|---|---|
| RF01 | Gerenciamento de usuários e cadastro (cadastrar e editar usuário) | O navegador envia os dados por HTTPS ao servidor, que grava no banco |
| RF02 | Vínculo psicólogo-paciente (função de associar e regra de autorização) | O módulo de autenticação libera o prontuário só para o psicólogo vinculado |
| RF03 | Consulta de disponibilidade e agendamento (visual de calendário e agenda com validação de horário) | O servidor lê a agenda no banco, mostra só os horários livres e valida antes de gravar |
| RF04 | Cancelamento ou reagendamento de sessões, com opção de justificativa | O módulo de agenda atualiza a sessão, libera o horário antigo e guarda a justificativa |
| RF05 | Confirmação e aviso de sessões (lembrete para psicólogo e pacientes) | O serviço de notificação manda o lembrete por e-mail (SMTP) quando a sessão é marcada, alterada ou está chegando |
| RFx | Validar novo cadastro (checar duplicidade) | O servidor confere no banco se os dados informados já existem |

## Requisitos Não Funcionais

| ID | Requisito | Como a rede e a arquitetura atendem |
|---|---|---|
| RNF01 | Segurança: restrição total de acesso às informações confidenciais do prontuário | Login individual, perfis de acesso, HTTPS, firewall e logs |
| RNF02 | Usabilidade: buscas e agendamentos com poucos cliques para evitar filas | Sistema web, acessado pelo navegador sem precisar instalar nada |
| RNF03 | Bloqueio transacional: bloquear o horário no momento da reserva | O banco usa transação para que duas pessoas não reservem o mesmo horário |
| RNFx | Desempenho: verificação de dados no banco em até 3 segundos | Rede cabeada nos computadores principais e banco indexado pelo documento |
| RNFy | Segurança: todos os dados do banco protegidos por criptografia AES-256 | Dados criptografados no armazenamento (AES-256) e durante o tráfego (HTTPS/TLS) |
