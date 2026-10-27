# Componentes e Perfis de Acesso

Os módulos e perfis abaixo seguem o backlog e a organização do código em C (Sprint 4).

## Componentes do protótipo

| Componente | O que faz | Situação |
|---|---|---|
| Usuários (`usuarios.c`) | Login, cadastro e inativação de colaboradores | Implementação parcial |
| Pacientes e responsáveis (`pacientes.c`) | Cadastro, busca por nome ou CPF e atualização de contato e endereço | Pendente |
| Agendamentos (`agendamentos.c`) | Agendar, remarcar, cancelar, consultar agenda e verificar conflitos | Pendente |
| Prontuários (`prontuarios.c`) | Registrar evoluções e consultar o histórico, validando o vínculo profissional | Pendente |
| Autenticação e autorização | Login e verificação de permissões antes de cada operação restrita | Parcial (login implementado) |

## Perfis de acesso

| Perfil | O que pode fazer |
|---|---|
| Administrador | Gerenciar usuários; registrar, remarcar e cancelar consultas; consultar agendas. **Não acessa o conteúdo clínico por si só** |
| Recepção | Cadastrar, consultar e atualizar pacientes e responsáveis; gerenciar a agenda. Não acessa o conteúdo clínico |
| Psicólogo | Ver a própria agenda; registrar e consultar evoluções **somente dos seus pacientes** |

As permissões são fixas e atribuídas automaticamente conforme a função cadastrada.

## Regras que valem para todos os módulos

- Todo paciente possui um responsável legal cadastrado.
- O cadastro do paciente começa sem psicólogo vinculado; o primeiro agendamento concluído com sucesso estabelece o vínculo (regra descrita na documentação de Programação em C).
- Os agendamentos seguintes usam o mesmo psicólogo vinculado.
- O sistema impede dois agendamentos no mesmo horário para o mesmo psicólogo.

## Melhorias futuras (fora do escopo atual)

- Lembretes automáticos por e-mail, SMS ou WhatsApp.
- Calendário visual.
- Evolução para cliente-servidor, conforme `arquitetura.md`.

Esses itens não fazem parte do protótipo entregue.
