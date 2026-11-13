# Diagrama de sequência — RF03.1: Registrar evolução técnica

## Objetivo

Representar a interação entre o usuário, a interface, as rotinas de gestão e o acesso aos arquivos para registrar evolução técnica no sistema da Clínica Ser Possível.

## Diagrama

![Diagrama de sequência RF03.1 — Registrar evolução técnica](<DS_RF03.1 - Registrar evolucao tecnica.png>)

## Pré-condições

O psicólogo deve estar autenticado e vinculado ao paciente.

## Participantes

| Participante | Responsabilidade |
| --- | --- |
| Psicólogo | Iniciar a operação e fornecer os dados necessários. |
| `form_Prontuario` | Receber os dados e apresentar o resultado ao usuário. |
| `GestaoProntuarios` | Validar as regras e coordenar a operação. |
| `ArquivosClinicos` | Consultar e gravar os dados em arquivos locais. |

## Fluxo representado

1. O psicólogo informa paciente, data e descrição da evolução.
2. A interface solicita `registrarEvolucao()`.
3. A gestão consulta o paciente e seu vínculo profissional.
4. A gestão valida perfil, vínculo e dados informados.
5. A evolução recebe um identificador único, e o autor é identificado pela matrícula da sessão autenticada.
6. A evolução é salva em `evolucoes.dat`.
7. Após a gravação bem-sucedida, a interface confirma o registro.

## Regras e condições

- Somente o psicólogo vinculado ao paciente pode registrar evoluções.
- Validar paciente, data e descrição.
- Consultar o vínculo em `pacientes.dat`.
- A matrícula do autor deve vir da sessão autenticada.
- Administrador e Recepção não acessam o conteúdo clínico do prontuário.
- Acesso negado ou falha de gravação devem gerar erro, sem confirmação.

## Escopo do desenho

O desenho representa o fluxo principal de sucesso. As restrições de acesso e os tratamentos de falha aparecem na nota, sem ramificações alternativas explícitas.

## Observação técnica

Os participantes representam responsabilidades das rotinas do programa em C. Os nomes com prefixo `form_` representam a interação com o usuário pelo terminal. A persistência utiliza arquivos locais `.dat`.

