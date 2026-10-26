# Sprint 4 — Início do desenvolvimento em C

## Objetivo desta entrega

Iniciar a implementação do protótipo da **Clínica Ser Possível**, conforme o Product Backlog, preparando uma primeira versão executável no terminal e a estrutura compartilhada para o desenvolvimento dos quatro módulos.

A aplicação utiliza linguagem C e armazenamento local em arquivos `.dat`. Todos os dados utilizados são fictícios.

## Funcionalidades implementadas

Nesta etapa, foi desenvolvida a primeira versão do módulo de usuários:

- Criação automática de um administrador de teste quando o arquivo de usuários ainda não existe.
- Login por matrícula e senha, com verificação de cadastro ativo.
- Exibição do menu administrativo somente para o perfil de administrador.
- Cadastro de colaboradores com matrícula, nome, senha e perfil.
- Solicitação de CRP para colaboradores com perfil de psicólogo.
- Bloqueio de matrícula duplicada.
- Inativação de usuários sem excluir seus registros.
- Bloqueio de login de usuários inativos.
- Bloqueio da tentativa de inativar o próprio administrador conectado.
- Leitura e gravação dos cadastros em `usuarios.dat`.

Os menus operacionais de recepção e psicologia ainda serão desenvolvidos.

## Organização dos arquivos

| Arquivo | Responsabilidade | Situação |
|---|---|---|
| `main.c` | Entrada do programa, leitura do login, menu administrativo e interação para cadastro e inativação. | Primeira versão implementada |
| `tipos.h` | Estruturas compartilhadas: `Usuario`, `Responsavel`, `Paciente`, `Agendamento` e `Evolucao`. | Base definida |
| `usuarios.h` | Declarações das funções do módulo de usuários, parâmetros e retornos. | Interfaces definidas |
| `usuarios.c` | Implementação do login, inicialização, cadastro e inativação de usuários. | Implementação parcial |
| `pacientes.h` | Contratos para cadastro, consulta, atualização e vínculo do paciente com o psicólogo. | Implementação pendente |
| `agendamentos.h` | Contratos para agendamento, remarcação, cancelamento e consulta da agenda. | Implementação pendente |
| `prontuarios.h` | Contratos para registro de evolução e consulta ao prontuário. | Implementação pendente |

Os arquivos `.h` definem como as funções devem ser chamadas. A presença de uma declaração nesses arquivos não significa que a funcionalidade já esteja implementada.

No módulo de usuários, a função `buscarUsuarioPorMatricula` está declarada e ainda precisa ser implementada para apoiar os demais módulos.

## Divisão do desenvolvimento

| Módulo | Arquivo de implementação | Responsabilidades |
|---|---|---|
| Usuários | `usuarios.c` | Login, cadastro, inativação e busca de colaboradores. |
| Pacientes e responsáveis | `pacientes.c` | Cadastro, busca por nome ou CPF, atualização de contato e endereço e armazenamento do vínculo profissional. |
| Agendamentos | `agendamentos.c` | Agendar, remarcar, cancelar, consultar agendas e verificar conflitos. |
| Prontuários | `prontuarios.c` | Registrar evoluções e consultar o histórico, validando o vínculo profissional. |

A integração das operações com as telas será feita no `main.c`, em coordenação com as responsáveis pelos módulos.

## Regras compartilhadas

- Os perfis possuem permissões fixas: administrador, recepcionista e psicólogo.
- O cadastro de pacientes começa sem psicólogo vinculado.
- O primeiro agendamento concluído com sucesso estabelece o vínculo entre paciente e psicólogo.
- Os agendamentos seguintes utilizam o mesmo profissional vinculado.
- O psicólogo consulta somente sua própria agenda.
- O psicólogo consulta e registra evoluções somente dos seus pacientes.
- Administrador e recepcionista não acessam o conteúdo clínico dos prontuários.
- As permissões devem ser verificadas dentro das funções, além das opções exibidas nos menus.
- Os registros devem ser preservados após fechar e reabrir o programa.

## Armazenamento

| Arquivo de dados | Conteúdo | Situação |
|---|---|---|
| `usuarios.dat` | Cadastros dos colaboradores. | Utilizado nesta versão |
| `pacientes.dat` | Pacientes e seus responsáveis. | Previsto |
| `agendamentos.dat` | Consultas agendadas e canceladas. | Previsto |
| `evolucoes.dat` | Evoluções técnicas dos pacientes. | Previsto |

Os arquivos `.dat` são criados pelo programa e não precisam ser enviados ao repositório. Os executáveis `.exe` também são gerados localmente.

## Como compilar e executar

É necessário ter um compilador de C instalado.

No terminal, dentro da pasta que contém os arquivos:

```sh
gcc main.c usuarios.c -o clinica.exe
```

No PowerShell do Windows, execute:

```powershell
.\clinica.exe
```

Se o GCC estiver instalado pelo Code::Blocks, mas não estiver disponível pelo comando `gcc`, utilize o caminho correspondente à instalação. Exemplo:

```powershell
& "C:\Program Files\CodeBlocks\MinGW\bin\gcc.exe" main.c usuarios.c -o clinica.exe
```

A compilação atual utiliza somente `main.c` e `usuarios.c`. Os demais arquivos `.c` serão incluídos conforme forem implementados.

## Primeiro acesso de teste

Quando `usuarios.dat` ainda não existe, o programa cria:

| Campo | Valor |
|---|---|
| Matrícula | `1001` |
| Nome | `Administrador Teste` |
| Senha | `1234` |
| Perfil | Administrador |
| Situação | Ativo |

Se o arquivo já existir, a inicialização preserva os cadastros existentes.

Essas credenciais são destinadas exclusivamente à demonstração acadêmica com dados fictícios.

## Verificações manuais realizadas

- Login autorizado com matrícula e senha corretas.
- Login recusado com senha incorreta.
- Cadastro de recepcionista e psicóloga.
- Login com os novos cadastros após reabrir o programa.
- Ausência do menu administrativo para recepcionista e psicóloga.
- Recusa de matrícula duplicada.
- Inativação de usuário e bloqueio de login em nova execução.
- Recusa da tentativa de inativar o próprio administrador.

Essas verificações cobrem os fluxos iniciais do módulo de usuários. A validação completa dos requisitos não funcionais, incluindo formatos, integridade dos arquivos e tempo de resposta, permanece pendente.

## Orientações para o grupo

1. Utilizar a mesma versão de `tipos.h`.
2. Implementar as funções conforme os contratos dos arquivos `.h`.
3. Combinar alterações nas estruturas, nas assinaturas das funções e no `main.c`.
4. Testar com dados fictícios e verificar a persistência após reiniciar o programa.
5. Enviar somente os arquivos de código e documentação pertinentes.
6. Revisar e integrar as alterações de cada módulo pelo GitHub.

## Próximas etapas

- Implementar `buscarUsuarioPorMatricula`.
- Desenvolver os módulos de pacientes, agendamentos e prontuários.
- Integrar os menus dos três perfis.
- Completar as validações de entrada e de integridade.
- Testar os fluxos integrados conforme o backlog.

## Referência

[Product Backlog — Clínica Ser Possível](../03-engenharia-software/Backlog/BACKLOG.md)
