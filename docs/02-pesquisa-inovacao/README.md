# Pesquisa e Inovação — Clínica Ser Possível

## 1. Introdução

O projeto tem como proposta o desenvolvimento de um protótipo de sistema para auxiliar na organização das atividades de uma clínica fictícia de atendimento psicológico infantojuvenil.

A pesquisa busca entender como soluções tecnológicas podem contribuir para o gerenciamento de cadastros, agendamentos e registros de atendimento, considerando também os cuidados necessários com informações pessoais e clínicas.

O estudo está relacionado ao desenvolvimento de uma aplicação em linguagem C, executada pelo terminal e com armazenamento local em arquivos `.dat`. A proposta é desenvolver as funcionalidades priorizadas no Product Backlog, respeitando os limites definidos para a entrega acadêmica.

## 2. Problema de pesquisa

Como um protótipo simples, desenvolvido em C e executado pelo terminal, pode auxiliar na organização de cadastros, agendamentos e evoluções técnicas de uma clínica psicológica, considerando regras de negócio, controle de acesso e persistência local?

O problema parte de um cenário acadêmico em que informações podem estar distribuídas em registros separados ou depender de controles manuais. Essa situação é utilizada como hipótese de trabalho, sem afirmar que foi comprovada por entrevistas ou levantamento realizado em uma clínica real.

## 3. Objetivos

### 3.1. Objetivo geral

Desenvolver e avaliar um protótipo local que reúna as funcionalidades essenciais de gerenciamento de usuários, pacientes e responsáveis, agendamentos e evoluções técnicas, conforme os requisitos estabelecidos no backlog.

### 3.2. Objetivos específicos

- Estudar soluções existentes de gestão clínica e organização de prontuários.
- Identificar funcionalidades que tenham relação com a proposta do projeto.
- Definir os requisitos funcionais e não funcionais do protótipo.
- Desenvolver os fluxos priorizados em linguagem C.
- Implementar a persistência dos registros em arquivos `.dat`.
- Aplicar e testar as regras de acesso e as validações previstas.
- Avaliar o funcionamento dos fluxos desenvolvidos e documentar os resultados.
- Identificar limitações e possíveis melhorias para versões futuras.

## 4. Metodologia

O trabalho utiliza pesquisa bibliográfica e documental exploratória, análise de soluções existentes e desenvolvimento incremental do protótipo.

A pesquisa bibliográfica considera legislação, documentos profissionais e referências de engenharia de software. A análise de soluções existentes utiliza informações públicas disponibilizadas pelos próprios fornecedores, com a finalidade de identificar características e diferenças de escopo.

O desenvolvimento é orientado pelo Product Backlog, pelos diagramas e pelo planejamento das sprints.

A avaliação será realizada por meio de testes funcionais, testes de persistência e verificação das regras de negócio. Os resultados deverão ser registrados com os casos de teste, resultados esperados, resultados observados e evidências.

Não será realizada uma afirmação de superioridade em relação a outros sistemas, pois o projeto não contempla uma avaliação experimental comparativa entre produtos.

## 5. Fundamentação teórica e relação com o projeto

### 5.1. Proteção de dados pessoais

A Lei nº 13.709/2018, conhecida como Lei Geral de Proteção de Dados Pessoais (LGPD), estabelece regras para o tratamento de dados pessoais. Informações referentes à saúde são classificadas como dados pessoais sensíveis.

Essa referência se relaciona ao projeto porque o cenário envolve informações cadastrais e clínicas. Por isso, a proposta considera a necessidade de limitar acessos, definir finalidades para o tratamento e evitar a exposição desnecessária dos registros.

No protótipo, serão utilizados exclusivamente dados fictícios. A existência de login e de permissões não significa que o sistema esteja automaticamente adequado à LGPD.

### 5.2. Direitos de crianças e adolescentes

O Estatuto da Criança e do Adolescente (Lei nº 8.069/1990) é uma referência importante para a discussão sobre direitos, dignidade, privacidade e proteção de crianças e adolescentes.

Sua relação com o projeto está na necessidade de considerar os cuidados adicionais envolvidos em um cenário de atendimento infantojuvenil, principalmente em relação ao acesso e à exposição de informações.

A aplicação prática das normas exige análise do contexto e não pode ser garantida apenas pelas funcionalidades do protótipo.

### 5.3. Registros psicológicos e sigilo profissional

A Resolução CFP nº 001/2009 é uma referência para a discussão sobre registros documentais decorrentes dos serviços psicológicos. O documento aborda a organização e o caráter sigiloso dos registros.

Essa referência contribui para a definição da funcionalidade de evolução técnica, que deverá considerar a identificação do atendimento, o profissional responsável e o histórico do paciente, conforme os requisitos aprovados.

O conteúdo e a estrutura dos registros do protótipo não devem ser considerados suficientes para atender automaticamente a todas as exigências profissionais. Uma utilização real exigiria avaliação das normas vigentes e dos requisitos aplicáveis.

O Código de Ética Profissional do Psicólogo, aprovado pela Resolução CFP nº 010/2005, também contribui para a discussão sobre sigilo e responsabilidade profissional.

### 5.4. Engenharia de software

Os conceitos de engenharia de software contribuem para organizar o desenvolvimento em etapas, definir requisitos, documentar regras e verificar o funcionamento da aplicação.

No projeto, essa abordagem é relacionada ao Product Backlog, aos diagramas e às sprints.

A definição dos requisitos antes da implementação ajuda a manter a coerência entre o que foi planejado, o que está sendo desenvolvido e o que será validado.

### 5.5. Persistência em arquivos

A documentação da linguagem C, incluindo as referências sobre operações de entrada e saída de arquivos, auxilia no estudo da leitura, gravação e tratamento de erros.

Essa fundamentação está relacionada à utilização de arquivos `.dat` para armazenar os registros do protótipo.

A persistência local foi escolhida para atender ao escopo acadêmico, mas apresenta limitações em relação à concorrência, recuperação de falhas, auditoria e proteção dos arquivos.

## 6. Trabalhos relacionados e comparação de soluções

Para compreender melhor a proposta, foram observadas informações públicas de sistemas voltados à gestão de clínicas psicológicas.

A comparação considera funcionalidades divulgadas pelos fornecedores, não testes realizados pelo grupo.

### 6.1. Clinio

O Clinio apresenta recursos como agenda, prontuário, agendamento online, lembretes pelo WhatsApp e controle financeiro.

A solução se relaciona ao projeto por reunir funcionalidades semelhantes às áreas de cadastro, agendamento e registros clínicos que estão sendo estudadas.

A principal diferença está na abrangência: o protótipo proposto será executado localmente pelo terminal e não contará com agendamento online, integração com calendário ou lembretes automáticos.

Fonte: https://clinio.com.br/

### 6.2. LucidDis

O LucidDis apresenta recursos de gestão clínica, incluindo agenda, prontuários eletrônicos, controle financeiro e gestão de múltiplas clínicas.

O exemplo demonstra uma proposta de gestão mais ampla, com recursos voltados à operação de clínicas.

Em comparação, o projeto da Clínica Ser Possível possui escopo reduzido e acadêmico, sem gestão financeira, múltiplas unidades ou aplicação web.

Fonte: https://www.lucidis.com.br/

### 6.3. Comparação com a proposta do projeto

| Critério | Clinio | LucidDis | Protótipo proposto |
|---|---|---|---|
| Cadastro e gestão de pacientes | Divulgado | Divulgado | Previsto no backlog |
| Agenda | Sim | Sim | Prevista no backlog |
| Prontuário e registros clínicos | Sim | Sim | Registro e consulta de evoluções previstos |
| Lembretes automáticos | Divulgados | Não considerados nesta comparação | Fora do escopo atual |
| Gestão financeira | Divulgada | Divulgada | Fora do escopo atual |
| Múltiplas clínicas | Não analisado aqui | Divulgado | Fora do escopo atual |
| Interface | Solução com interface gráfica e recursos online divulgados | Solução web divulgada | Terminal |
| Armazenamento | Não comparado tecnicamente | Não comparado tecnicamente | Arquivos locais `.dat` |

A tabela representa uma comparação de escopo, e não uma avaliação de segurança, desempenho, preço ou qualidade dos produtos.

As funcionalidades dos sistemas comerciais podem mudar conforme planos, configurações e atualizações. As informações utilizadas nesta comparação são as divulgadas publicamente pelos fornecedores.

### 6.4. Análise da comparação

A análise mostra que sistemas de gestão clínica podem reunir diversas atividades em uma única solução, incluindo recursos que não estão previstos no protótipo acadêmico.

A proposta da Clínica Ser Possível não busca reproduzir todas essas funcionalidades. Seu objetivo é desenvolver uma solução menor, que permita exercitar conceitos de programação, organização de dados, regras de negócio e controle de acesso.

O diferencial pretendido está na aplicação dos requisitos definidos para o cenário acadêmico, com atenção ao vínculo profissional, às permissões e à organização das evoluções técnicas.

Esse diferencial representa uma característica da proposta, e não uma vantagem de qualidade já comprovada em relação aos sistemas existentes.

## 7. Diferenciais da proposta

Dentro do escopo atual, destacam-se:

- Organização das funcionalidades em um único protótipo local.
- Separação das responsabilidades conforme os perfis de usuário.
- Consideração do vínculo profissional para o acesso às informações clínicas.
- Organização dos agendamentos e prevenção de conflitos conforme as regras definidas.
- Registro de evoluções técnicas associado ao paciente e ao profissional responsável.
- Persistência em arquivos `.dat`, permitindo exercitar operações de leitura e gravação em C.

Esses pontos serão considerados diferenciais da proposta acadêmica. Sua efetividade dependerá da implementação e dos resultados dos testes.

## 8. Avaliação do protótipo

A avaliação será orientada pelos requisitos funcionais e não funcionais definidos no backlog.

Serão considerados:

**Funcionamento**
- Cadastro e consulta de usuários.
- Cadastro e atualização de pacientes e responsáveis.
- Agendamento, remarcação e cancelamento.
- Registro e consulta de evoluções técnicas.

**Regras de negócio**
- Validação dos campos obrigatórios.
- Verificação de conflitos de horário.
- Respeito às permissões dos perfis.
- Respeito ao vínculo profissional.

**Persistência**
- Verificação da gravação dos registros.
- Recuperação dos dados após encerrar e reabrir o programa.
- Tratamento de falhas e entradas inválidas.

**Requisitos não funcionais**
- Medição de desempenho, quando houver meta definida.
- Verificação das condições de uso pelo terminal.
- Avaliação dos controles de acesso por meio de testes específicos.

A facilidade de uso não será considerada comprovada apenas pela conclusão das funcionalidades. Caso seja realizada uma avaliação com participantes, deverão ser definidos critérios, procedimentos e cuidados com privacidade.

A segurança e a conformidade legal também não serão tratadas como garantidas apenas com a realização dos testes funcionais.

Os resultados deverão ser registrados conforme a execução real das atividades.

## 9. Melhorias futuras

As seguintes possibilidades não fazem parte da entrega atual:

- Calendário visual.
- Lembretes automáticos por e-mail, SMS ou WhatsApp.
- Autossalvamento.
- Backup automático.
- Relatórios gerenciais e indicadores.
- Integração com outros serviços.
- Aplicação web.
- API e arquitetura cliente-servidor.
- Banco de dados integrado ao sistema.
- Recursos avançados de auditoria e recuperação.

Essas ideias poderão ser avaliadas em versões futuras, considerando a prioridade, a viabilidade técnica, os riscos e os requisitos necessários.

## 10. Considerações finais

O projeto busca demonstrar como conceitos de desenvolvimento de software podem contribuir para a organização de atividades administrativas e clínicas em um cenário acadêmico.

A pesquisa e a análise de soluções existentes ajudam a delimitar o escopo, identificar necessidades e justificar as decisões tomadas durante o desenvolvimento.

A entrega será considerada de acordo com as funcionalidades realmente implementadas, os testes realizados e as limitações documentadas.

O protótipo não será apresentado como uma solução pronta para utilização profissional, nem como um sistema cuja segurança ou conformidade legal esteja garantida.

## Referências

BRASIL. **Lei nº 13.709, de 14 de agosto de 2018.** Lei Geral de Proteção de Dados Pessoais (LGPD). Disponível em: https://www.planalto.gov.br/ccivil_03/_ato2015-2018/2018/lei/l13709.htm. Acesso em: 26 out. 2026.

BRASIL. **Lei nº 8.069, de 13 de julho de 1990.** Estatuto da Criança e do Adolescente (ECA). Disponível em: https://www.planalto.gov.br/ccivil_03/leis/l8069.htm. Acesso em: 26 out. 2026.

CLINIO. **Software para psicólogos.** Disponível em: https://clinio.com.br/. Acesso em: 26 out. 2026.

CONSELHO FEDERAL DE PSICOLOGIA. **Código de Ética Profissional do Psicólogo.** Resolução CFP nº 010/2005. Disponível em: https://site.cfp.org.br/legislacao/. Acesso em: 26 out. 2026.

CONSELHO FEDERAL DE PSICOLOGIA. **Resolução CFP nº 001/2009.** Dispõe sobre a obrigatoriedade do registro documental decorrente da prestação de serviços psicológicos. Disponível em: https://site.cfp.org.br/wp-content/uploads/2009/04/resolucao2009_01.pdf. Acesso em: 26 out. 2026.

LUCIDDIS. **Sistema de Gestão para Clínicas Psicológicas.** Disponível em: https://www.lucidis.com.br/. Acesso em: 26 out. 2026.

SOMMERVILLE, Ian. **Engenharia de Software.** 10. ed. Pearson, 2019.

CPPREFERENCE. **C file input/output.** Disponível em: https://en.cppreference.com/w/c/io. Acesso em: 26 out. 2026.
