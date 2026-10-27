# Privacidade e proteção de dados

## Por que isso importa

O prontuário eletrônico guarda dados sensíveis de saúde. A privacidade é um direito humano, e a **LGPD (Lei nº 13.709/2018)** trata dados de saúde com proteção reforçada.

## Como o projeto se relaciona com a proteção de dados

| Direito ou princípio | Aplicação no projeto |
|---|---|
| Privacidade | O acesso aos dados deve ser restrito a pessoas autorizadas. |
| Sigilo profissional | O projeto prevê cuidados com o registro e o acesso às informações clínicas. |
| Finalidade e necessidade | A coleta e o uso dos dados devem se limitar ao que for adequado para as finalidades legítimas do atendimento. |
| Segurança | O protótipo possui autenticação básica, mas ainda necessita de melhorias e testes para proteger adequadamente as informações. |
| Transparência | A futura implantação deverá informar, de forma adequada, como os dados são utilizados e quais são os direitos dos titulares. |

## Situação atual e limitações

O protótipo é desenvolvido em C e utiliza arquivos locais `.dat`, com dados fictícios. O módulo de usuários possui autenticação básica, mas isso não significa que exista proteção completa dos prontuários.

O controle de permissões por paciente, a proteção adequada das senhas, os registros de acesso e outras medidas de segurança precisam ser avaliados, implementados ou testados conforme o escopo.

Para uma futura implantação, será necessário definir responsabilidades pelo tratamento dos dados, medidas de segurança, procedimentos de atendimento aos direitos dos titulares e resposta a incidentes.

A utilização de dados reais de saúde não deve ocorrer no protótipo sem uma avaliação prévia de segurança, privacidade e requisitos legais.

## Cuidados jurídicos

O tratamento de dados de crianças e adolescentes exige análise do melhor interesse do titular e da hipótese legal adequada. Não se deve afirmar que o consentimento do responsável é sempre a única base legal possível.

O sigilo profissional também possui situações e limites previstos nas normas aplicáveis, e não deve ser tratado como absoluto.

Este material tem finalidade acadêmica e não substitui análise jurídica.

## Normas relacionadas

- Lei nº 13.709/2018 (LGPD).
- Lei nº 8.069/1990 (ECA).
- Código de Ética Profissional do Psicólogo (Resolução CFP nº 010/2005) e demais normas profissionais aplicáveis.
