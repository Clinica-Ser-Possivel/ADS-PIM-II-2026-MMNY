# Clínica Ser Possível — módulos integrados

Protótipo acadêmico em C, com terminal e persistência em arquivos locais .dat.
Esta versão integra usuários, pacientes, agendamentos e prontuários nos menus dos três perfis.

## Como experimentar

1. Extraia o pacote em uma pasta separada do projeto que já utiliza.
2. Abra essa pasta no VS Code ou no terminal.
3. Compile os cinco arquivos de implementação com o comando abaixo.
4. Execute o programa nessa mesma pasta, usando somente dados fictícios.

No PowerShell, utilizando o GCC do Code::Blocks instalado neste notebook:

~~~powershell
& "C:\Program Files\CodeBlocks\MinGW\bin\gcc.exe" -std=c11 -Wall -Wextra -Wpedantic -Werror main.c usuarios.c pacientes.c agendamentos.c prontuarios.c -o clinica.exe
.\clinica.exe
~~~

Se o GCC já estiver disponível no terminal:

~~~powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror main.c usuarios.c pacientes.c agendamentos.c prontuarios.c -o clinica.exe
.\clinica.exe
~~~

Não compile todos os .c com um curinga se houver utilitários adicionais que também tenham uma função main.
O arquivo auxiliar gerar_usuarios.c do repositório original não é necessário para executar esta versão.

## Primeiro acesso

Quando usuarios.dat ainda não existe, o programa cria o administrador de demonstração:

| Campo | Valor |
| --- | --- |
| Matrícula | 1001 |
| Senha | 1234 |

Se o arquivo já existir, os cadastros são preservados.
As senhas permanecem armazenadas no formato do protótipo original, sem criptografia; utilize apenas credenciais fictícias.

## Menus e permissões

| Operação | Administrador | Recepção | Psicólogo |
| --- | --- | --- | --- |
| Cadastrar e inativar colaborador | Sim | Não | Não |
| Buscar colaborador por matrícula | Sim | Sim | Não aparece no menu |
| Cadastrar paciente e responsável | Sim | Sim | Não |
| Consultar paciente e responsável | Todos | Todos | Somente pacientes vinculados |
| Atualizar contato e endereço | Sim | Sim | Não |
| Agendar, remarcar e cancelar | Sim | Sim | Não |
| Consultar agenda | Qualquer psicólogo | Qualquer psicólogo | Somente a própria |
| Registrar evolução e consultar prontuário | Não | Não | Somente pacientes vinculados |
| Trocar usuário e sair | Sim | Sim | Sim |

As funções também verificam permissões, além das opções apresentadas no menu.
Na primeira consulta agendada com sucesso, o paciente recebe o vínculo com o psicólogo.
As próximas consultas usam esse mesmo vínculo. Cancelar uma consulta não apaga o vínculo.

## Organização

| Arquivo | Responsabilidade |
| --- | --- |
| main.c | Leitura de entradas, login e menus integrados dos três perfis. |
| tipos.h | Estruturas compartilhadas, mantidas sem alteração. |
| usuarios.c e usuarios.h | Login, cadastro, inativação e busca de colaboradores. |
| pacientes.c e pacientes.h | Cadastro, consulta, atualização de contato e vínculo profissional. |
| agendamentos.c e agendamentos.h | Agendamento, remarcação, cancelamento e consulta de agenda. |
| prontuarios.c e prontuarios.h | Registro e consulta de evoluções técnicas. |
| arquivos.h | Substituição do arquivo temporário pelo arquivo de dados no Windows e em outros sistemas. |
| testes/ | Verificações automatizadas com dados sintéticos e pastas isoladas. |

O novo arquivo arquivos.h precisa ficar junto dos demais cabeçalhos.
O arquivo validacoes.h também precisa estar nessa pasta; ele compartilha as regras de CPF, data e horário com os formulários.

## Correção de preenchimento

- CPF inválido solicita novamente somente o CPF, preservando os dados já digitados.
- CPF do paciente já cadastrado também pode ser corrigido no próprio campo.
- Data ou horário inválidos são solicitados novamente antes de continuar.
- No agendamento, recusas identificam psicólogo inexistente, inativo, com perfil incorreto ou horário ocupado.
- Uma recusa de agendamento devolve ao menu. Erros de preenchimento de CPF, data e horário ficam no próprio formulário.
- CPF continua exigindo pontuação e dígitos verificadores válidos.

Para atualizar uma cópia já utilizada, encerre o programa, substitua os arquivos .c e .h pelos desta versão (incluindo os novos cabeçalhos) e recompile. Preserve seus arquivos .dat.

## Dados

O programa usa usuarios.dat, pacientes.dat, agendamentos.dat e evolucoes.dat na pasta de execução.
Não foram incluídos cadastros de teste no pacote. Os testes criam e descartam suas próprias bases.
As estruturas e assinaturas das funções existentes foram preservadas. Arquivos binários .dat dependem das estruturas e do compilador: mantenha cópias de segurança antes de trocar de versão.

Use uma instância do programa por pasta de dados. A persistência não fornece transações entre arquivos nem proteção para uso simultâneo.
Se o vínculo falhar após salvar uma consulta, o programa tenta desfazer a consulta. Se essa recuperação também falhar, ele informa a inconsistência para conferência, sem confirmar sucesso.

## Testes

No Windows, com Python e GCC instalados:

~~~powershell
python testes/executar.py
~~~

O teste encontra o GCC no terminal ou na instalação do Code::Blocks. Também é possível definir a variável CLINICA_GCC.
Consulte [RESULTADOS-TESTES.md](RESULTADOS-TESTES.md) para os resultados e limites.

## Histórico da revisão

Consulte [ALTERACOES.md](ALTERACOES.md) para conferir os ajustes.
A revisão foi incorporada nesta pasta em 14/11/2026 e validada novamente com a suíte de testes.
Não envie executáveis, arquivos de dados ou temporários ao GitHub. O envio do commit ao GitHub depende de autorização.
