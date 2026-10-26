<div align="center">

# Sistema de Cadastro de Pacientes e Prontuários

### Clínica Ser Possível

**Projeto Integrado Multidisciplinar II — PIM II**  
Análise e Desenvolvimento de Sistemas — UNIP  
2026

</div>

---

## Sobre o projeto

O projeto propõe o desenvolvimento de um **sistema de cadastro de pacientes e prontuários para a Clínica Ser Possível**, uma clínica fictícia de pequeno porte, com uma única unidade, voltada ao atendimento psicológico e de saúde mental infanto-juvenil.

Hoje, a operação da clínica é feita de forma manual, o que traz riscos como perda de documentos confidenciais, dificuldade para buscar históricos (o CFP exige a guarda do prontuário por 5 anos) e possibilidade de vazamento de informações sensíveis. A solução permitirá centralizar o cadastro de pacientes e responsáveis, o agendamento de consultas e o registro da evolução técnica em um ambiente único, com acesso controlado por perfil.

O sistema é desenvolvido em **Linguagem C**, com interação pelo terminal, em conformidade com as normas éticas do **Conselho Federal de Psicologia (CFP)** e com a **Lei Geral de Proteção de Dados (LGPD)**.

---

## Objetivo

Desenvolver uma solução computacional capaz de auxiliar no cadastro de pacientes e responsáveis legais, no agendamento de consultas e no registro de evoluções técnicas, protegendo o sigilo das informações clínicas e reduzindo a dependência de processos manuais.

---

## Escopo do protótipo

- Aplicação em C, executada no terminal.
- Dados armazenados localmente em arquivos `.dat`, com leitura e gravação feitas pelo próprio programa.
- Banco de dados modelado separadamente (DER, modelo lógico e modelo físico de referência), sem integração com o programa neste semestre.
- Uso exclusivo de dados fictícios em cadastros, testes, documentação e demonstrações.

---

## Principais funcionalidades

- Cadastro de usuários com atribuição automática do perfil conforme a função
- Login por matrícula e senha, com verificação de cadastro ativo
- Inativação de usuários sem apagar o histórico
- Cadastro de pacientes infanto-juvenis e de seus responsáveis legais
- Consulta de dados cadastrais por nome ou CPF
- Atualização de dados de contato e endereço
- Registro de evolução técnica pelo psicólogo
- Consulta do prontuário respeitando o vínculo profissional
- Agendamento de consultas com validação de conflito de horário
- Remarcação e cancelamento de consultas
- Visualização da agenda por data e profissional
- Persistência dos dados em arquivos `.dat`

---

## Perfis do sistema

| Perfil | Responsabilidades |
|---|---|
| **Administrador** | Cadastrar e inativar usuários, cadastrar e consultar pacientes e responsáveis, agendar, remarcar, cancelar e consultar as agendas |
| **Recepção** | Cadastrar, consultar e atualizar pacientes e responsáveis, agendar, remarcar, cancelar e consultar as agendas |
| **Psicólogo(a)** | Consultar a própria agenda, consultar dados cadastrais dos seus pacientes, registrar evoluções técnicas e consultar prontuários |

### Regras de acesso

As permissões de cada perfil são **fixas** e o perfil é atribuído automaticamente conforme a função informada no cadastro do colaborador.

O acesso ao conteúdo clínico do prontuário é permitido **somente ao psicólogo vinculado ao paciente**. Os perfis de Administrador e de Recepção **não acessam** as evoluções técnicas.

O vínculo entre paciente e psicólogo é estabelecido no primeiro agendamento concluído com sucesso.

---

## Andamento do projeto

| Etapa | Status |
|---|---|
| Organização, problema e justificativa | Concluído |
| Pesquisa e Inovação | Em andamento |
| Requisitos funcionais e não funcionais (Product Backlog) | Concluído |
| Diagramas de Casos de Uso | Concluído |
| Diagrama de Classe | Concluído |
| Diagramas de Sequência | Em andamento |
| Banco de Dados (DER, modelo lógico e físico) | Concluído |
| Programação Estruturada em C | Em andamento |
| Redes e Sistemas Distribuídos | Em andamento |
| Direitos Humanos | Em andamento |
| Validação, vídeo de demonstração e entrega final | Previsto (até 10/11/2026) |

---

## Equipe

| Integrante | Papel |
|---|---|
| **Natalia Cristina Torres** | Product Owner |
| **Yasmin Silva Bonfim dos Santos** | Scrum Master |
| **Marcela Bueno dos Santos** | Dev Team |
| **Maria Victória Vieira Lopes** | Dev Team |

---

## Diagramas

Os principais diagramas do sistema estão disponíveis na documentação:

- [Diagramas de Casos de Uso (RF01 a RF04)](docs/03-engenharia-software/Diagramas/Diagrama%20CasoDeUso/README.md)
- [Diagrama de Classe](docs/03-engenharia-software/Diagramas/Diagrama%20de%20Classe/Diagrama%20de%20Classe.png)
- [Diagrama de Sequência — RF01.1 Cadastrar usuário](docs/03-engenharia-software/Diagramas/Diagrama%20de%20Sequencia/DS_RF01.1/README.md)
- [Diagrama Entidade-Relacionamento (DER)](docs/04-banco-de-dados/der.md)

---

## Estrutura do repositório

```text
docs/
├── 01-organizacao/            → caracterização da clínica, problema e justificativa
├── 02-pesquisa-inovacao/      → pesquisa, fundamentação e diferenciais inovadores
├── 03-engenharia-software/    → backlog, sprints e diagramas UML
├── 04-banco-de-dados/         → DER, modelo lógico e modelo físico
├── 05-programacao-em-c/       → código-fonte do protótipo em C
├── 06-redes/                  → redes de computador e sistemas distribuídos
└── 07-direitos-humanos/       → privacidade, LGPD e direitos de crianças e adolescentes
```

---

## Navegação rápida

### Organização
- [Caracterização da clínica](docs/01-organizacao/README.md)

### Pesquisa e Inovação
- [Documentação](docs/02-pesquisa-inovacao/README.md)

### Engenharia de Software
- [Product Backlog](docs/03-engenharia-software/Backlog/BACKLOG.md)
- [Planejamento das Sprints](docs/03-engenharia-software/Sprints/README.md)
- [Diagramas de Casos de Uso](docs/03-engenharia-software/Diagramas/Diagrama%20CasoDeUso/README.md)
- [Diagrama de Sequência — RF01.1](docs/03-engenharia-software/Diagramas/Diagrama%20de%20Sequencia/DS_RF01.1/README.md)

### Banco de Dados
- [Visão geral e regras de negócio](docs/04-banco-de-dados/README.md)
- [DER](docs/04-banco-de-dados/der.md)
- [Modelo lógico](docs/04-banco-de-dados/modelo-logico.md)
- [Modelo físico (SQL)](docs/04-banco-de-dados/modelo-fisico.sql)

### Programação em C
- [Código-fonte e instruções de execução](docs/05-programacao-em-c/README.md)

### Redes e Sistemas Distribuídos
- [Documentação](docs/06-redes/README.md)

### Direitos Humanos
- [Documentação](docs/07-direitos-humanos/README.md)

---

## Como compilar e executar o protótipo

É necessário ter um compilador de C instalado. Dentro da pasta `docs/05-programacao-em-c`, execute:

```sh
gcc main.c usuarios.c -o clinica.exe
```

Os detalhes de execução, o primeiro acesso de teste e a divisão dos módulos estão no [README do código em C](docs/05-programacao-em-c/README.md).

---

## Tecnologias e ferramentas

- C (GCC)
- Arquivos `.dat` para persistência local
- Astah UML
- Mermaid (DER)
- Microsoft SQL Server (modelo físico de referência)
- Git / GitHub

---

## Instituição

**Universidade Paulista — UNIP**  
Campus São José dos Campos  
Curso Superior de Tecnologia em Análise e Desenvolvimento de Sistemas  
PIM II — 2026

