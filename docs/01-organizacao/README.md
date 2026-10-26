# Organização do Projeto — Clínica Ser Possível

## 1. Caracterização da organização

A Clínica Ser Possível é o cenário organizacional utilizado para o desenvolvimento deste Projeto Integrado Multidisciplinar II (PIM II). O projeto considera uma clínica fictícia de pequeno porte, com uma unidade, voltada ao atendimento psicológico infantojuvenil.

A proposta é desenvolver um sistema que auxilie na organização de algumas das atividades administrativas e clínicas, principalmente o cadastro de pacientes e responsáveis, o gerenciamento de consultas e o registro de evoluções técnicas.

Por se tratar de um cenário acadêmico, as características apresentadas são utilizadas como base para o desenvolvimento da solução e não representam um levantamento realizado em uma clínica real.

## 2. Problema identificado

O projeto parte da possibilidade de que o controle manual ou a distribuição de informações em diferentes registros possa dificultar a localização de cadastros, o acompanhamento dos agendamentos e a organização dos registros de atendimento.

Nesse contexto, a proposta é reunir algumas dessas atividades em um único programa, com operações definidas e regras de acesso conforme o perfil do usuário.

A questão principal do projeto é: como desenvolver um protótipo simples que ajude a organizar cadastros, consultas e evoluções técnicas, mantendo as informações estruturadas e respeitando as permissões estabelecidas?

O problema apresentado é uma premissa do projeto, não uma conclusão baseada em entrevistas, auditorias ou medições realizadas na clínica.

## 3. Objetivos

### 3.1. Objetivo geral

Desenvolver um protótipo acadêmico em linguagem C, executado pelo terminal e com armazenamento local em arquivos `.dat`, para auxiliar no gerenciamento de pacientes e responsáveis, agendamentos e evoluções técnicas, seguindo os requisitos e as regras de negócio definidos no projeto.

### 3.2. Objetivos específicos

- Implementar o login dos usuários por matrícula e senha, considerando o status da conta.
- Organizar o cadastro e a inativação de usuários, respeitando os perfis definidos.
- Permitir o cadastro, a consulta e a atualização dos dados de pacientes e responsáveis.
- Implementar o agendamento, a consulta, a remarcação e o cancelamento de consultas.
- Aplicar as regras de disponibilidade e prevenção de conflitos de agendamento previstas no backlog.
- Permitir o registro e a consulta de evoluções técnicas por psicólogos autorizados.
- Aplicar as regras de acesso aos dados clínicos, considerando o vínculo profissional com o paciente.
- Armazenar e recuperar os registros utilizando arquivos `.dat`.
- Realizar testes funcionais e de persistência, registrando os resultados obtidos.
- Documentar os requisitos, os diagramas, as decisões técnicas e as limitações do protótipo.

## 4. Justificativa

A organização de informações é importante em cenários que envolvem cadastros, agendamentos e registros de atendimento. Quando essas atividades dependem de controles separados, podem surgir dificuldades para localizar dados, acompanhar alterações e manter uma rotina organizada.

Por isso, o projeto propõe um protótipo que reúna funcionalidades básicas em um único programa, permitindo demonstrar como a programação pode auxiliar na organização dessas atividades.

A escolha da linguagem C e da execução pelo terminal também permite trabalhar conceitos de lógica de programação, estruturas de dados, validações e persistência em arquivos, relacionando os conteúdos estudados no curso de Análise e Desenvolvimento de Sistemas.

Além disso, por envolver um cenário de atendimento psicológico infantojuvenil, o projeto permite discutir a importância da privacidade, do sigilo profissional e do controle de acesso às informações.

A solução tem finalidade acadêmica e não pretende substituir sistemas profissionais de gestão clínica ou prontuários eletrônicos.

## 5. Escopo do projeto

### 5.1. Funcionalidades previstas para a entrega

O protótipo contempla os seguintes grupos de funcionalidades:

**Gerenciamento de usuários**
- Login por matrícula e senha.
- Cadastro e inativação de usuários.
- Atribuição de perfis conforme a função cadastrada.

**Gerenciamento de pacientes e responsáveis**
- Cadastro.
- Consulta por nome ou CPF.
- Atualização de dados cadastrais.
- Organização dos dados dos responsáveis legais.

**Gerenciamento de agendamentos**
- Agendamento de consultas.
- Consulta da agenda por data e profissional.
- Remarcação e cancelamento.
- Verificação dos conflitos previstos nas regras de negócio.

**Gerenciamento de prontuários**
- Registro de evoluções técnicas.
- Consulta de evoluções conforme as permissões.
- Respeito ao vínculo profissional com o paciente.

**Persistência e validações**
- Gravação e leitura de registros em arquivos `.dat`.
- Validação de campos e entradas.
- Verificação das regras de negócio.
- Testes dos fluxos implementados.

A inclusão de cada funcionalidade na lista de escopo não significa que ela já esteja concluída. O andamento deverá ser acompanhado nas sprints e confirmado por meio de evidências.

### 5.2. Recursos fora do escopo atual

Não fazem parte da entrega prevista neste semestre:

- Calendário visual.
- Lembretes automáticos por e-mail, SMS ou WhatsApp.
- Autossalvamento.
- Backup automático.
- Aplicação web.
- API REST e servidor central.
- Sistema distribuído em produção.
- Integração operacional com banco de dados SQL.
- Integração com escolas ou serviços externos.
- Relatórios analíticos avançados.
- Gráficos de resultados de testes padronizados.
- Emissão automatizada de laudos.
- Utilização operacional com dados reais de pacientes.

Esses recursos poderão ser avaliados como melhorias futuras, desde que sejam definidos novos requisitos, analisada sua viabilidade e realizado um novo planejamento.

## 6. Usuários e permissões

O sistema considera três perfis principais:

| Perfil | Responsabilidades previstas |
|---|---|
| Administrador | Gerenciamento de usuários e operações administrativas previstas, incluindo as operações cadastrais e de agenda autorizadas. |
| Recepção | Cadastro, consulta e atualização de pacientes e responsáveis, além do gerenciamento da agenda. |
| Psicólogo(a) | Consulta da própria agenda, acesso aos dados cadastrais necessários e registro e consulta de evoluções técnicas de pacientes vinculados. |

As permissões devem ser verificadas pelo programa antes da execução das operações restritas.

O perfil de Administrador não concede acesso ao conteúdo clínico das evoluções. O acesso aos prontuários deve respeitar as regras de vínculo profissional estabelecidas no projeto.

O vínculo entre paciente e psicólogo deve seguir a regra de negócio definida no backlog, incluindo o estabelecimento do vínculo no primeiro agendamento concluído com sucesso, caso essa regra seja mantida na versão aprovada dos requisitos.

## 7. Tecnologias e armazenamento

O protótipo será desenvolvido com as seguintes tecnologias e ferramentas:

- **Linguagem C:** desenvolvimento da aplicação.
- **Terminal:** interface de interação com o usuário.
- **Arquivos `.dat`:** armazenamento local dos registros.
- **Git e GitHub:** versionamento e organização dos arquivos.
- **Astah UML:** elaboração dos diagramas.
- **Mermaid:** documentação de diagramas, quando aplicável.
- **Microsoft SQL Server:** referência para a modelagem física do banco de dados, sem integração com o programa nesta entrega.

A persistência local em arquivos `.dat` atende à proposta acadêmica do protótipo, mas possui limitações em relação a transações, concorrência, recuperação de falhas e controle de acesso aos arquivos.

## 8. Privacidade, segurança e limitações

O projeto considera como referências a Lei Geral de Proteção de Dados Pessoais (LGPD), o Estatuto da Criança e do Adolescente (ECA) e as normas profissionais aplicáveis ao contexto psicológico.

Como o cenário envolve dados de saúde e informações de crianças e adolescentes, serão utilizados exclusivamente dados fictícios no desenvolvimento, nos testes e nas apresentações.

A proposta inclui autenticação e regras de autorização, mas essas medidas não garantem, isoladamente, a segurança integral do sistema.

A avaliação dos controles dependerá de testes específicos, incluindo tentativas de acesso indevido, verificação das permissões e análise da persistência dos registros.

Da mesma forma, a facilidade de uso deverá ser avaliada por critérios definidos, e a conformidade com a legislação não poderá ser afirmada apenas com base na existência das funcionalidades previstas.

O protótipo não foi planejado para uso clínico real. Uma eventual utilização profissional exigiria avaliação técnica, organizacional e normativa, além de controles adicionais de proteção, armazenamento, acesso, guarda e recuperação das informações.

## 9. Organização e acompanhamento

O desenvolvimento é organizado em requisitos, backlog, diagramas, sprints, implementação e testes.

O Product Backlog é a referência principal para as funcionalidades e regras de negócio. Os diagramas devem representar os mesmos processos, enquanto as sprints registram o planejamento e o andamento das atividades.

As tarefas deverão ser classificadas conforme sua situação real:

- **Planejada:** atividade prevista.
- **Em andamento:** atividade iniciada.
- **Concluída:** atividade entregue e verificável.
- **Pendente:** atividade ainda não iniciada.
- **Testada:** atividade com testes executados e resultados registrados.

Uma funcionalidade implementada não deve ser considerada validada sem os testes correspondentes.

## 10. Resultado esperado

Ao final do projeto, espera-se apresentar um protótipo em C, executado pelo terminal, capaz de demonstrar os fluxos priorizados de gerenciamento de usuários, pacientes e responsáveis, agendamentos e evoluções técnicas, com persistência local em arquivos `.dat`.

Também se espera entregar a documentação dos requisitos, diagramas, planejamento das sprints e registros dos testes realizados.

O resultado será avaliado de acordo com o escopo acadêmico definido, considerando as funcionalidades efetivamente implementadas e suas limitações.

---

## Referências de apoio

BRASIL. **Lei nº 13.709, de 14 de agosto de 2018.** Lei Geral de Proteção de Dados Pessoais (LGPD). Disponível em: https://www.planalto.gov.br/ccivil_03/_ato2015-2018/2018/lei/l13709.htm. Acesso em: 26 out. 2026.

BRASIL. **Lei nº 8.069, de 13 de julho de 1990.** Estatuto da Criança e do Adolescente (ECA). Disponível em: https://www.planalto.gov.br/ccivil_03/leis/l8069.htm. Acesso em: 26 out. 2026.

CONSELHO FEDERAL DE PSICOLOGIA. **Código de Ética Profissional do Psicólogo.** Resolução CFP nº 010/2005. Disponível em: https://site.cfp.org.br/legislacao/. Acesso em: 26 out. 2026.

CONSELHO FEDERAL DE PSICOLOGIA. **Resolução CFP nº 001/2009.** Disponível em: https://site.cfp.org.br/legislacao/. Acesso em: 26 out. 2026.
