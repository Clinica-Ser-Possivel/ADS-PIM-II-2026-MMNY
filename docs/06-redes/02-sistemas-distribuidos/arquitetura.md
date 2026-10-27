# Arquitetura do Sistema e Possível Evolução Distribuída

## 1. Arquitetura atual

O protótipo da Clínica Ser Possível é desenvolvido em linguagem C, possui interface pelo terminal e utiliza arquivos locais `.dat` para armazenar os registros (`usuarios.dat` em uso; `pacientes.dat`, `agendamentos.dat` e `evolucoes.dat` previstos).

A aplicação reúne as funcionalidades de gerenciamento de usuários, pacientes e responsáveis, agendamentos e prontuários, respeitando as regras de acesso definidas no projeto.

Atualmente, o sistema não possui comunicação entre computadores por rede, aplicação web, API REST ou integração com banco de dados SQL. Por isso, a solução implementada não é considerada um sistema distribuído.

## 2. Proposta de infraestrutura

Considerando uma possível implantação futura na clínica, propõe-se uma rede local com topologia em estrela, utilizando switch, roteador com firewall e computadores destinados às atividades administrativas e clínicas (ver `01-redes/estrutura-da-rede.md`).

A rede de funcionários deverá ser separada da rede de visitantes, com regras de acesso apropriadas.

Essa infraestrutura é uma proposta acadêmica e não representa equipamentos instalados ou uma estrutura verificada na clínica.

## 3. Possível evolução para cliente-servidor

Em uma evolução futura, o sistema poderá ser adaptado para uma arquitetura cliente-servidor em 3 camadas:

| Camada | Componente | O que faria |
|---|---|---|
| Apresentação | Cliente (interface do usuário) | Telas usadas pela recepção, pelos psicólogos e pelo administrador |
| Aplicação | Servidor de aplicação (API) | Regras de negócio, validação de permissões e agendamentos |
| Dados | Banco de dados central | Armazenamento de usuários, pacientes, consultas e evoluções |

A comunicação entre cliente e servidor poderia utilizar HTTPS e uma API, e o servidor de aplicação acessaria o banco de dados por conexão interna.

Essa mudança exigiria adaptar a aplicação em C ou desenvolver uma nova interface, criar mecanismos de comunicação pela rede, definir uma API, integrar um banco de dados (o modelo SQL da pasta `04-banco-de-dados` é apenas documental) e implementar controles adicionais de segurança.

Esses recursos **não fazem parte da implementação atual** e estão fora do escopo do semestre.

## 4. Relação com os sistemas distribuídos

A arquitetura cliente-servidor é apresentada como uma possibilidade de evolução, permitindo estudar o compartilhamento de recursos, a comunicação entre componentes e os desafios de concorrência, disponibilidade, integridade e segurança.

| Característica | Como apareceria em uma evolução futura |
|---|---|
| Compartilhamento de recursos | Todos os computadores usariam a mesma base central |
| Consistência | O servidor impediria dois agendamentos no mesmo horário para o mesmo psicólogo |
| Segurança | Login, permissões por perfil e comunicação cifrada |
| Disponibilidade | Backup e nobreak ajudariam a reduzir paradas |

A adoção dessa arquitetura dependeria de planejamento, implementação e testes específicos.

## 5. Limitações

O protótipo atual possui limitações de armazenamento local, concorrência e compartilhamento dos dados entre computadores.

A utilização de arquivos `.dat` não oferece, por si só, mecanismos completos de transação, controle de concorrência e recuperação de falhas.

Por isso, a solução atual possui finalidade acadêmica e utiliza exclusivamente dados fictícios.
