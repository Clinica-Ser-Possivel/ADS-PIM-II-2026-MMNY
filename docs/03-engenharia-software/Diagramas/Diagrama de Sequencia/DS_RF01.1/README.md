# Diagrama de sequência — RF01.1: Cadastrar usuário

## Objetivo

Representar a interação entre o usuário, a interface, as rotinas de gestão e o acesso aos arquivos para cadastrar usuário no sistema da Clínica Ser Possível.

## Diagrama

![Diagrama de sequência RF01.1 — Cadastrar usuário](<RF01.1 - Cadastrar usuario.png>)

## Pré-condições

O Administrador deve estar autenticado e autorizado a cadastrar usuários.

## Participantes

| Participante | Responsabilidade |
| --- | --- |
| Administrador | Iniciar a operação e fornecer os dados necessários. |
| `form_Entrada` | Receber os dados e apresentar o resultado ao usuário. |
| `GestaoUsuarios` | Validar as regras e coordenar a operação. |
| `ArquivosUsuarios` | Consultar e gravar os dados em arquivos locais. |

## Fluxo representado

1. O Administrador seleciona o cadastro e informa nome, matrícula, senha e função.
2. A gestão verifica a permissão e valida os campos recebidos.
3. Se os dados forem inválidos, o fragmento `break` interrompe a tentativa e apresenta uma mensagem.
4. A gestão consulta a matrícula. O fragmento `alt` distingue matrícula duplicada de matrícula disponível.
5. Com matrícula disponível, o usuário é preparado com perfil conforme a função e situação ativa.
6. O usuário é salvo em `usuarios.dat`. Outro fragmento `alt` apresenta sucesso ou falha conforme o resultado da gravação.

## Regras e condições

- Somente o Administrador pode cadastrar usuários.
- Dados inválidos ou matrícula duplicada impedem o cadastro.
- A confirmação depende da gravação bem-sucedida.

## Escopo do desenho

O diagrama apresenta o fluxo de sucesso e os principais caminhos de erro, utilizando os fragmentos `break` e `alt`.

## Observação técnica

Os participantes representam responsabilidades das rotinas do programa em C. Os nomes com prefixo `form_` representam a interação com o usuário pelo terminal. A persistência utiliza arquivos locais `.dat`.

