# Arquitetura do Sistema Distribuído

## Modelo
O sistema usa o modelo **cliente-servidor em 3 camadas**. Cada parte fica separada e elas conversam pela rede.

| Camada | Componente | O que faz |
|---|---|---|
| Apresentação | Navegador (cliente) | Mostra as telas usadas pela recepção, pelos psicólogos e pelo administrativo |
| Aplicação | Servidor de aplicação (API) | Cuida das regras do sistema: cadastro, agendamento e permissões |
| Dados | Servidor de banco de dados | Guarda pacientes, psicólogos, sessões e prontuários |

Existe também um **serviço de notificação**, que manda os lembretes de sessão por e-mail (ou por SMS ou WhatsApp, se a clínica preferir).

## Como as partes conversam
- O navegador fala com o servidor de aplicação por **HTTPS**, usando uma **API REST** (os dados vão em formato JSON).
- O servidor de aplicação fala com o banco de dados por uma conexão interna.
- O servidor de aplicação chama o serviço de notificação quando uma sessão é marcada, cancelada ou está chegando.

## Exemplo: agendar uma consulta
1. A recepção entra no sistema com seu login.
2. O sistema busca no banco a agenda do psicólogo de referência.
3. A recepção escolhe um horário livre.
4. O servidor confere se não há conflito e grava a sessão.
5. O serviço de notificação manda o lembrete para o paciente ou responsável e para o psicólogo.

## Características de sistemas distribuídos no projeto

| Característica | Como aparece no projeto |
|---|---|
| Compartilhamento de recursos | Todo mundo usa a mesma base de dados central |
| Transparência | O usuário não precisa saber onde o servidor está |
| Segurança | Login, permissões e HTTPS |
| Consistência | Duas pessoas não conseguem marcar o mesmo horário do mesmo psicólogo |
| Disponibilidade | Backup e nobreak ajudam a evitar paradas |
