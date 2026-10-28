# Arquitetura em Camadas e Modularização
## Clínica Ser Possível — PIM II

### 1. Introdução

O sistema Clínica Ser Possível é um protótipo acadêmico desenvolvido em linguagem C, executado por meio de terminal, com o objetivo de apoiar o gerenciamento de usuários, pacientes, agendamentos e prontuários psicológicos.

O projeto foi planejado utilizando conceitos de Engenharia de Software, com destaque para a **arquitetura em camadas** e a **modularização**, buscando promover a separação de responsabilidades, a organização do código e a facilidade de manutenção.

O armazenamento dos dados é realizado localmente por meio de arquivos `.dat`, enquanto a modelagem do banco de dados relacional é desenvolvida separadamente, sem integração nesta versão do protótipo.

### 2. Arquitetura em Camadas

A arquitetura proposta está organizada em três camadas principais:

#### 2.1. Camada de Apresentação

Responsável pela interação entre o usuário e o sistema.

**Principais responsabilidades:**
- Exibir menus e opções no terminal.
- Receber informações digitadas pelos usuários.
- Apresentar mensagens de confirmação e erro.
- Encaminhar solicitações às funções responsáveis pelo processamento.

**Exemplo:** a recepcionista acessa o menu de agendamentos e informa os dados necessários para marcar uma consulta.

#### 2.2. Camada de Regras de Negócio

Responsável pelo processamento das operações e pela aplicação das regras definidas nos requisitos do sistema.

**Principais responsabilidades:**
- Validar credenciais e perfis de acesso.
- Verificar a existência de pacientes e profissionais.
- Validar a disponibilidade de horários.
- Impedir agendamentos conflitantes.
- Verificar a autorização para acesso aos prontuários.
- Controlar o vínculo entre pacientes e psicólogos.

**Exemplo:** antes de registrar uma evolução, o sistema verifica se o usuário autenticado é um psicólogo autorizado a acessar o prontuário do paciente.

As verificações de autorização devem ocorrer nas funções responsáveis pelas operações, não apenas na exibição dos menus.

#### 2.3. Camada de Persistência de Dados

Responsável pelo armazenamento e recuperação das informações.

**Principais responsabilidades:**
- Gravar dados nos arquivos `.dat`.
- Consultar registros armazenados.
- Atualizar informações persistidas.
- Recuperar os dados após o encerramento e a reinicialização do programa.

**Exemplo:** após a validação de um agendamento, as informações são gravadas no arquivo correspondente.

#### 2.4. Representação da Arquitetura

```text
+----------------------------------+
|     CAMADA DE APRESENTAÇÃO        |
|                                  |
|       Menus e Terminal           |
+----------------------------------+
                |
                v
+----------------------------------+
|    CAMADA DE REGRAS DE NEGÓCIO    |
|                                  |
| Validações, Permissões e Fluxos   |
+----------------------------------+
                |
                v
+----------------------------------+
|     CAMADA DE PERSISTÊNCIA        |
|                                  |
|    Leitura e Gravação .dat        |
+----------------------------------+
```

O fluxo representa a separação lógica das responsabilidades. A implementação deve ser verificada no código-fonte para confirmar que as funções respeitam essa organização.

### 3. Modularização do Sistema

A modularização consiste na divisão do sistema em componentes funcionais, permitindo que cada módulo concentre operações relacionadas a uma responsabilidade específica.

O projeto foi organizado em quatro módulos principais.

#### 3.1. Módulo de Usuários

Responsável pelo gerenciamento dos colaboradores e pelo processo de autenticação.

**Funcionalidades previstas:**
- Cadastrar usuários.
- Identificar os perfis Administrador, Recepção e Psicólogo.
- Registrar o CRP dos usuários com perfil Psicólogo.
- Realizar login por matrícula e senha.
- Verificar a situação ativa ou inativa do usuário.
- Aplicar as permissões de acesso conforme o perfil.

#### 3.2. Módulo de Pacientes

Responsável pelo gerenciamento das informações cadastrais de pacientes e responsáveis.

**Funcionalidades previstas:**
- Cadastrar pacientes.
- Cadastrar responsáveis.
- Consultar dados cadastrais.
- Atualizar informações conforme os requisitos.
- Disponibilizar os identificadores necessários aos demais módulos.

#### 3.3. Módulo de Agendamentos

Responsável pelo gerenciamento dos horários de atendimento.

**Funcionalidades previstas:**
- Registrar agendamentos.
- Consultar horários.
- Reagendar e cancelar consultas, conforme o escopo implementado.
- Verificar a disponibilidade dos psicólogos.
- Impedir conflitos de horários.
- Relacionar pacientes aos profissionais responsáveis.

O módulo utiliza informações dos módulos de usuários e pacientes para realizar suas validações.

#### 3.4. Módulo de Prontuários

Responsável pelo registro e pela consulta de informações clínicas.

**Funcionalidades previstas:**
- Registrar evoluções técnicas.
- Consultar registros autorizados.
- Verificar o vínculo entre paciente e psicólogo.
- Restringir o acesso às informações técnicas.
- Preservar a separação entre informações administrativas e clínicas.

O acesso aos prontuários técnicos deve ser limitado aos profissionais autorizados, conforme as regras de negócio do projeto.

### 4. Comunicação Entre os Módulos

Os módulos precisam compartilhar informações para executar os processos do sistema.

| Módulo | Comunicação necessária |
|---|---|
| Usuários | Disponibiliza informações de autenticação, perfil e identificação do profissional. |
| Pacientes | Disponibiliza dados cadastrais e identificadores dos pacientes. |
| Agendamentos | Consulta informações de pacientes e psicólogos para registrar consultas. |
| Prontuários | Consulta vínculos e permissões para autorizar o registro e a visualização de evoluções. |

A comunicação deve ocorrer por meio de funções e interfaces definidas entre os módulos, evitando dependências desnecessárias.

### 5. Organização dos Arquivos em C

A linguagem C permite separar declarações e implementações utilizando arquivos `.h` e `.c`.

- **Arquivos `.h`:** contêm declarações de funções, estruturas e definições compartilhadas.
- **Arquivos `.c`:** contêm as implementações das funções e dos procedimentos do sistema.

Essa organização facilita a manutenção e o desenvolvimento colaborativo.

A distribuição exata das funções entre arquivos deve corresponder à estrutura efetivamente implementada no repositório.

### 6. Exemplo de Fluxo Integrado

**Processo: agendamento de uma consulta**

1. A recepcionista realiza o login no sistema.
2. O sistema valida suas credenciais e identifica seu perfil.
3. A recepcionista acessa o módulo de agendamentos.
4. O sistema consulta os dados do paciente e do psicólogo.
5. As regras de negócio verificam a disponibilidade do horário.
6. Se as validações forem atendidas, o agendamento é registrado.
7. A camada de persistência grava as informações no arquivo `.dat`.
8. O sistema apresenta uma mensagem confirmando a operação.

Esse fluxo demonstra como as camadas e os módulos devem colaborar para executar uma funcionalidade completa.

### 7. Diferença Entre Arquitetura em Camadas e Modularização

| Arquitetura em Camadas | Modularização |
|---|---|
| Organiza o sistema por responsabilidades técnicas. | Organiza o sistema por funcionalidades. |
| Separa apresentação, regras de negócio e persistência. | Separa usuários, pacientes, agendamentos e prontuários. |
| Define como as diferentes camadas interagem. | Define as responsabilidades e dependências entre módulos. |
| Favorece a separação de responsabilidades. | Favorece a manutenção e o desenvolvimento colaborativo. |

As duas abordagens são complementares e podem ser aplicadas simultaneamente no projeto.

### 8. Considerações Sobre o MVP

O protótipo da Clínica Ser Possível foi delimitado para demonstrar os principais processos administrativos e clínicos da instituição.

A utilização da linguagem C, da interface pelo terminal e do armazenamento local permite concentrar o desenvolvimento nas regras de negócio e na integração dos módulos.

A arquitetura e a modularização representam a organização planejada para o sistema. A conclusão das funcionalidades depende de implementação, integração e testes.

Por se tratar de um MVP acadêmico, o projeto utiliza dados fictícios e não deve ser considerado um sistema pronto para utilização com informações clínicas reais.

### 9. Conclusão

A adoção da arquitetura em camadas e da modularização busca proporcionar uma estrutura organizada para o desenvolvimento do sistema Clínica Ser Possível.

A arquitetura em camadas separa as responsabilidades de apresentação, processamento e persistência, enquanto a modularização divide as funcionalidades em componentes específicos.

Essas decisões contribuem para a clareza do projeto, a manutenção do código e a integração das funcionalidades essenciais do MVP.

A validação final da arquitetura será realizada por meio da análise da implementação e dos testes dos fluxos integrados.
