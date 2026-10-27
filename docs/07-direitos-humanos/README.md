# Direitos humanos

Este material relaciona o sistema da **Clínica Ser Possível** com os direitos humanos, principalmente os direitos de crianças e adolescentes atendidos em saúde mental.

## Resumo

O PIM II desenvolve um protótipo para a Clínica Ser Possível, uma clínica fictícia de atendimento psicológico e de saúde mental infanto-juvenil. O sistema prevê o cadastro de pacientes e seus responsáveis legais, o agendamento de consultas e o registro de evoluções técnicas no prontuário.

Esses dados estão entre os mais sensíveis que existem: dizem respeito à saúde mental de crianças e adolescentes, um grupo que tem proteção especial na lei. Por isso, o projeto não é só uma questão técnica. Cada decisão tomada no sistema afeta direitos como a privacidade, o sigilo, a dignidade e o acesso à saúde.

Na prática, o projeto procura respeitar esses direitos da seguinte forma:

- **Controle de acesso:** o protótipo possui autenticação básica de usuários (login por matrícula e senha, com verificação de cadastro ativo). O controle completo das permissões de acesso aos prontuários ainda precisa ser implementado e testado.
- **Sigilo profissional:** a documentação prevê a separação entre as anotações privadas do psicólogo e a evolução oficial do paciente, como objetivo de proteção das informações. Essa separação ainda não consta como requisito no backlog do protótipo.
- **Responsável legal:** o cadastro prevê um responsável legal para cada paciente, conforme a regra do projeto, o que contribui para a organização das informações e do acompanhamento.
- **Conformidade com normas:** o projeto considera a LGPD, o ECA e as orientações éticas aplicáveis à atuação profissional. A conformidade integral depende de medidas técnicas, organizacionais e validações que ainda precisam ser realizadas.
- **Uso responsável dos dados:** as informações devem ser utilizadas para finalidades legítimas relacionadas ao atendimento, com respeito à privacidade, à dignidade e à não discriminação.

## Situação atual do protótipo

O protótipo é desenvolvido em linguagem C, executado pelo terminal, com arquivos locais `.dat` e **somente dados fictícios**. Não há aplicação web, servidor central nem banco de dados integrado. Por isso, os cuidados descritos nesta pasta são princípios que orientam o projeto, e não garantias já implementadas. Os detalhes estão em [privacidade e LGPD](01-privacidade-e-lgpd.md).

## Regras do projeto ligadas aos direitos

- Todo paciente deve ter um responsável legal cadastrado.
- Administrador e recepção não acessam o conteúdo clínico dos prontuários.
- O psicólogo consulta e registra evoluções somente dos seus pacientes, conforme o vínculo profissional.
- As permissões devem ser verificadas dentro das funções do programa, e não apenas nos menus.

## Como esta parte se conecta às outras

- **Direitos Humanos** define o que precisa ser respeitado: privacidade, dignidade, sigilo e proteção integral.
- **Redes** propõe, para uma futura implantação, separação de redes, firewall, proteção das comunicações e outras medidas de segurança.
- **Programação em C e Banco de Dados** precisam aplicar controle de acesso, validações, proteção dos dados e as regras de vínculo e prontuário.

Uma parte não substitui a outra. Por exemplo: Direitos Humanos aponta que o prontuário contém informações sensíveis; Redes recomenda medidas para proteger a comunicação e os dispositivos; e a programação precisa garantir que um usuário não consulte informações clínicas fora de sua autorização.

Um sistema de saúde precisa ir além da parte técnica. Cada decisão de projeto, como o login com matrícula e senha ou a restrição de acesso às evoluções, é uma forma de aplicar direitos humanos na prática, desde que seja de fato implementada e testada.
