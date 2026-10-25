## Diagrama de sequência — RF01.1: Cadastrar usuário

### Objetivo

Representar o cadastro de um novo colaborador no sistema da Clínica Ser Possível, incluindo verificação de permissão, validação dos dados, consulta de matrícula e gravação em arquivo local.

### Pré-condição

O Administrador deve estar autenticado. O cenário apresentado considera que a verificação de permissão autoriza o cadastro.

### Participantes

| Participante | Responsabilidade |
| :--- | :--- |
| Administrador | Solicitar o cadastro e informar os dados do novo colaborador. |
| form_Entrada | Representar a interação pelo terminal, receber os dados e apresentar mensagens. |
| GestaoUsuarios | Verificar a permissão, validar os dados e coordenar o cadastro. |
| ArquivosUsuarios | Consultar matrículas e gravar os usuários em arquivo local `.dat`. |

### Descrição do fluxo

1. O Administrador seleciona a opção **Cadastrar usuário**.
2. O `form_Entrada` solicita à `GestaoUsuarios` a verificação da permissão do usuário conectado.
3. Após a autorização, o Administrador informa nome, matrícula, senha e função do novo colaborador.
4. O `form_Entrada` encaminha os dados para `cadastrarUsuario(dados)`.
5. A `GestaoUsuarios` valida o preenchimento e os formatos dos campos.
6. Se os dados forem inválidos, o fragmento `break` apresenta uma mensagem de erro e interrompe a tentativa de cadastro.
7. Se os dados forem válidos, a `GestaoUsuarios` solicita a consulta da matrícula ao `ArquivosUsuarios`.
8. O primeiro fragmento `alt` separa os resultados da consulta:
   - **Matrícula encontrada:** retorna o erro de matrícula duplicada, sem realizar o cadastro.
   - **Matrícula disponível:** prepara o usuário, gerando seu identificador, atribuindo o perfil conforme a função e definindo sua situação como ativa.
9. A `GestaoUsuarios` solicita a gravação do usuário ao `ArquivosUsuarios`.
10. O segundo fragmento `alt` trata o resultado da gravação:
    - **Sucesso:** apresenta a mensagem “Usuário cadastrado com sucesso”.
    - **Falha:** apresenta a mensagem “Não foi possível salvar o usuário”.

### Regras representadas

- Somente o Administrador pode cadastrar colaboradores.
- Dados inválidos impedem a continuidade do cadastro.
- Não é permitido cadastrar usuários com matrícula duplicada.
- O perfil é atribuído conforme a função informada.
- O novo usuário é cadastrado como ativo.
- O sucesso só é informado após a confirmação da gravação.

### Resultado esperado

O novo usuário fica disponível no arquivo local após a gravação bem-sucedida. Em caso de dados inválidos, matrícula duplicada ou falha de gravação, o sistema informa o problema e não confirma o cadastro.

### Observação técnica

Os participantes `GestaoUsuarios` e `ArquivosUsuarios` representam responsabilidades das rotinas do programa em C. A interação ocorre pelo terminal, e os dados são persistidos em arquivos locais `.dat`.
