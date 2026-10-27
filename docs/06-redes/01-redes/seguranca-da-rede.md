# Segurança da Rede

A clínica fictícia lida com dados pessoais e sensíveis de crianças e adolescentes, então a segurança é prioridade. Este documento separa o que existe no protótipo do que é apenas recomendado para uma implantação futura.

## 1. Medidas existentes no protótipo

Conforme o backlog (RNF01) e a Sprint 4, o módulo de usuários já implementa:

- Login por matrícula e senha, com verificação de cadastro ativo.
- Bloqueio de login de usuários inativados.
- Menu administrativo exibido somente para o perfil de administrador.

Previstas no backlog, mas ainda **pendentes** de implementação e teste (módulos de pacientes, agendamentos e prontuários):

- Acesso às evoluções somente pelo psicólogo vinculado ao paciente.
- Validação das permissões dentro das funções, e não só nos menus.

O protótipo usa exclusivamente dados fictícios.

## 2. Medidas recomendadas para uma implantação futura

Estas medidas **não estão implementadas**:

1. **Firewall** no roteador, liberando só o que é necessário.
2. **Redes separadas:** Wi-Fi dos visitantes isolado da rede dos funcionários.
3. **Senha forte no Wi-Fi** (WPA2 ou WPA3), trocada periodicamente.
4. **HTTPS**, caso o sistema evolua para cliente-servidor.
5. **Backup** dos dados, com cópia guardada em outro local e teste de restauração.
6. **Antivírus e atualizações** nos computadores.
7. **Registro de acessos (logs)** aos prontuários.
8. **Criptografia dos dados armazenados.**
9. **Guarda do prontuário** pelo prazo exigido pelo CFP (confirmar a norma a citar).

## 3. Cuidados que ainda precisam ser definidos e testados

- Arquivos `.dat` não oferecem, por si só, controle de concorrência, transações nem recuperação de falhas.
- Política de backup e de retenção dos dados.
- Procedimento em caso de incidente de segurança.

## 4. Referências normativas

- **LGPD:** proteção dos dados pessoais e sensíveis.
- **Resolução CFP nº 010/2005 (Código de Ética):** sigilo profissional.

A adoção das medidas acima, mesmo como proposta, não comprova conformidade legal nem prontidão para uso com dados reais.
