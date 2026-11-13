# Diagrama de sequência — RF02.1: Cadastrar paciente e responsável

## Objetivo

Representar a interação entre o usuário, a interface, as rotinas de gestão e o acesso aos arquivos para cadastrar paciente e responsável no sistema da Clínica Ser Possível.

## Diagrama

![Diagrama de sequência RF02.1 — Cadastrar paciente e responsável](<DS_RF02.1 - Cadastrar paciente e responsavel.png>)

## Pré-condições

O usuário deve estar autenticado e possuir perfil autorizado.

## Participantes

| Participante | Responsabilidade |
| --- | --- |
| Recepção ou Administrador | Iniciar a operação e fornecer os dados necessários. |
| `form_Entrada` | Receber os dados e apresentar o resultado ao usuário. |
| `GestaoPacientes` | Validar as regras e coordenar a operação. |
| `ArquivosPacientes` | Consultar e gravar os dados em arquivos locais. |

## Fluxo representado

1. A Recepção ou o Administrador informa os dados do paciente e do responsável.
2. A interface solicita `cadastrarPaciente()`.
3. A gestão executa `validarPermissaoEDados()`.
4. A gestão gera um identificador único e inicia o paciente sem psicólogo vinculado (`psicologo = 0`).
5. Os dados do paciente e do responsável são gravados em `pacientes.dat`.
6. Após a gravação bem-sucedida, a interface apresenta o cadastro concluído.

## Regras e condições

- Validar permissão, campos obrigatórios e formatos.
- Gerar um identificador único para o paciente.
- O paciente inicia sem vínculo com psicólogo.
- Em caso de falha, informar o erro e não confirmar o cadastro.

## Escopo do desenho

O desenho representa o fluxo principal de sucesso. As falhas e validações são descritas na nota, sem ramificações `alt` ou `break` explícitas.

## Observação técnica

Os participantes representam responsabilidades das rotinas do programa em C. Os nomes com prefixo `form_` representam a interação com o usuário pelo terminal. A persistência utiliza arquivos locais `.dat`.
