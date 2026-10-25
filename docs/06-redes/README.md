# Redes de Computador e Sistemas Distribuídos

Esta pasta reúne a parte de **redes de computador** e **sistemas distribuídos** do PIM II, o sistema de cadastro de pacientes e prontuários da **Clínica Ser Possível**.

## Objetivo

O objetivo desta parte do projeto é documentar como a infraestrutura de rede e a organização distribuída do sistema podem apoiar o funcionamento da Clínica Ser Possível no dia a dia.

De forma mais específica, esta pasta busca:

- apresentar os conceitos de redes de computador que se aplicam ao sistema da clínica;
- explicar o que são sistemas distribuídos e de que forma esses conceitos se relacionam com o projeto;
- definir os requisitos de rede necessários para que o sistema funcione de maneira estável, segura e disponível;
- representar a estrutura proposta por meio de diagramas feitos no Astah;
- reforçar a importância da segurança e da proteção dos dados dos pacientes, de acordo com a LGPD.

## Contexto do projeto

O PIM II foi desenvolvido por estudantes do curso de Análise e Desenvolvimento de Sistemas (ADS) da UNIP, em linguagem C, para a Clínica Ser Possível, uma clínica fictícia voltada ao atendimento psicológico e de saúde mental infanto-juvenil.

O sistema foi pensado para centralizar a gestão da clínica. Entre as suas funções estão:

- o cadastro de pacientes e dos seus responsáveis legais;
- o agendamento de consultas, com validação de conflitos de horário;
- o prontuário eletrônico, com controle de permissões por matrícula e senha;
- a separação entre as anotações privadas dos psicólogos e a evolução oficial dos pacientes.

Como o sistema trabalha com dados sensíveis de saúde mental de crianças e adolescentes, a parte de redes tem um papel importante. A comunicação entre os computadores da clínica precisa ser segura, o sistema precisa estar disponível quando os profissionais precisarem dele, e o acesso às informações deve ser limitado a quem tem autorização. Tudo isso deve estar de acordo com a LGPD e com as normas éticas do Conselho Federal de Psicologia (CFP).
