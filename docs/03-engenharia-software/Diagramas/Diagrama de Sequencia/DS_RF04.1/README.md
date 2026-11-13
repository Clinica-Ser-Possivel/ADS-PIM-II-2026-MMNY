# Diagrama de sequência — RF04.1: Agendar consulta

## Objetivo

Representar a interação entre o usuário, a interface, as rotinas de gestão e o acesso aos arquivos para agendar consulta no sistema da Clínica Ser Possível.

## Diagrama

![Diagrama de sequência RF04.1 — Agendar consulta](<RF04.1 - Agendar consulta.png>)

## Pré-condições

O usuário deve estar autenticado e autorizado. No cenário de primeiro agendamento apresentado, o paciente existe e ainda não possui psicólogo vinculado.

## Participantes

| Participante | Responsabilidade |
| --- | --- |
| Recepção ou Administrador | Iniciar a operação e fornecer os dados necessários. |
| `form_Agenda` | Receber os dados e apresentar o resultado ao usuário. |
| `GestaoAgendamentos` | Validar as regras e coordenar a operação. |
| `ArquivosClinica` | Consultar e gravar os dados em arquivos locais. |

## Fluxo representado

1. A Recepção ou o Administrador informa paciente, data e horário.
2. A interface solicita `agendarConsulta()`.
3. A gestão consulta os dados do paciente e do psicólogo selecionado.
4. A gestão valida perfil, vínculo, data e horário.
5. O acesso aos arquivos verifica conflitos de horário.
6. A consulta recebe identificador e situação `agendado`, e é salva.
7. No primeiro agendamento, é gravado o vínculo entre paciente e psicólogo.
8. A interface confirma o agendamento somente após ambas as gravações serem bem-sucedidas.

## Regras e condições

- O psicólogo selecionado deve estar ativo.
- Data e horário devem ser válidos e sem conflito.
- Nas próximas consultas, manter o psicólogo já vinculado ao paciente.
- `ArquivosClinica` representa o acesso a `usuarios.dat`, `pacientes.dat` e `agendamentos.dat`.
- Falhas devem ser informadas sem confirmar o agendamento.

## Escopo do desenho

O desenho representa o fluxo principal do primeiro agendamento. Os caminhos de falha são descritos na nota; o diagrama não detalha recuperação ou reversão em caso de gravação parcial.

## Observação técnica

Os participantes representam responsabilidades das rotinas do programa em C. Os nomes com prefixo `form_` representam a interação com o usuário pelo terminal. A persistência utiliza arquivos locais `.dat`.

