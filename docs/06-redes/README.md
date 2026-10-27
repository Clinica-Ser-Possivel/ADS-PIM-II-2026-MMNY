# Redes de Computador e Sistemas Distribuídos

Esta pasta reúne a parte de **redes de computador** e **sistemas distribuídos** do PIM II, o sistema de cadastro de pacientes e prontuários da **Clínica Ser Possível**.

## Escopo e situação atual

- O protótipo é **local**, desenvolvido em **linguagem C** e executado pelo **terminal**.
- O armazenamento atual é feito em **arquivos `.dat`**. Não há API, aplicação web, servidor central nem banco de dados SQL integrado.
- A **infraestrutura de rede** descrita nesta pasta é uma **proposta de implantação futura**, de caráter acadêmico. Ela não representa equipamentos instalados nem um levantamento real da clínica.
- A parte de **sistemas distribuídos** é apresentada como **estudo de uma possível evolução** do projeto, e não como tecnologia já utilizada.
- Todos os dados do projeto são **fictícios**.

## Objetivo

O objetivo desta parte do projeto é documentar como uma infraestrutura de rede e uma organização distribuída poderiam apoiar o sistema da Clínica Ser Possível em uma implantação futura, sem confundir essa proposta com o protótipo atual.

De forma mais específica, esta pasta busca:

- apresentar os conceitos de redes de computador que se aplicam ao cenário da clínica;
- explicar o que são sistemas distribuídos e de que forma esses conceitos se relacionam com o projeto;
- relacionar os requisitos do backlog com as decisões de rede, indicando o que existe hoje e o que é proposta futura;
- representar a infraestrutura proposta por meio de diagrama feito no Astah (pasta `04-diagramas`, a ser adicionada);
- reforçar a importância da segurança e da proteção dos dados dos pacientes, de acordo com a LGPD.

## Contexto do projeto

O PIM II foi desenvolvido por estudantes do curso de Análise e Desenvolvimento de Sistemas (ADS) da UNIP, em linguagem C, para a Clínica Ser Possível, uma clínica fictícia de pequeno porte, com uma unidade, voltada ao atendimento psicológico infantojuvenil.

O protótipo reúne, conforme o backlog:

- o gerenciamento de usuários, com login por matrícula e senha e perfis fixos (administrador, recepção e psicólogo);
- o cadastro de pacientes e dos seus responsáveis legais;
- o agendamento de consultas, com verificação de conflitos de horário;
- o registro de evoluções técnicas, com acesso restrito ao psicólogo vinculado ao paciente.

Como o cenário envolve dados sensíveis de saúde mental de crianças e adolescentes, a rede teria um papel importante em uma implantação futura: a comunicação entre computadores precisaria ser segura, o sistema precisaria estar disponível e o acesso às informações deveria ser limitado a quem tem autorização, de acordo com a LGPD e as normas éticas do Conselho Federal de Psicologia (CFP).

## Organização da pasta

| Pasta | Conteúdo |
|---|---|
| `01-redes` | Proposta de estrutura e de segurança da rede local |
| `02-sistemas-distribuidos` | Arquitetura atual, possível evolução cliente-servidor e componentes |
| `03-requisitos-de-rede` | Relação entre os requisitos do backlog e as decisões de rede |
| `04-diagramas` | Diagrama da infraestrutura de rede proposta (a fazer no Astah) |
