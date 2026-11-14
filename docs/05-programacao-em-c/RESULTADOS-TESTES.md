# Resultados da verificação local

Verificação original: 12/11/2026.
Revalidação na cópia vinculada ao repositório: 14/11/2026.
Ambiente: Windows deste notebook, GCC do Code::Blocks, C11.
Bases sintéticas em pastas temporárias isoladas; nenhum arquivo de dados do projeto foi utilizado.

## Resultado

- Compilação de todos os módulos e dos testes com -Wall -Wextra -Wpedantic -Werror: passou sem avisos.
- Cenário funcional: 78 verificações passaram.
- Persistência em novo processo: 14 verificações passaram.
- Falhas e preservação de arquivos: 42 verificações passaram.
- Fluxos pelos menus dos três perfis: passaram.
- Nova tentativa de CPF inválido do paciente e do responsável, sem repetir nomes nem perder dados: passou.
- CPF de paciente duplicado corrigido no próprio formulário: passou.
- Correção de data e horário no próprio campo: passou.
- Mensagens de psicólogo inexistente, perfil incorreto, inativo e conflito de horário: passaram.
- Encerramento da entrada durante correção de CPF sem gravar cadastro parcial: passou.

As 134 verificações em C incluem condições de apoio à preparação e leitura dos arquivos; não representam 134 requisitos diferentes.

## Cobertura

- Login correto, senha incorreta e bloqueio de usuário inativo.
- Cadastro duplicado e tentativa de inativar o próprio administrador.
- Busca de colaborador sem devolver senha.
- Cadastro de paciente, CPF inválido e duplicado.
- Busca por nome e CPF do responsável e exibição de seus dados.
- Atualização parcial de contato e preservação dos demais campos, mesmo quando o chamador envia outros dados alterados.
- Primeiro agendamento e gravação do vínculo no Windows.
- Preservação do psicólogo vinculado nos agendamentos seguintes.
- Datas e horários inválidos, conflitos e remarcação sem conflito.
- Cancelamento com preservação do registro e liberação do horário.
- Bloqueio por perfil e de prontuário de paciente sem vínculo.
- Autor da evolução obtido da sessão e histórico ordenado por data.
- Reabertura do programa com recuperação dos dados gravados.
- Falha de vínculo após gravar consulta: consulta desfeita, sem confirmação.
- Destino bloqueado no Windows: falha informada, original preservado e nova tentativa bem-sucedida após desbloquear.
- Arquivos de pacientes/agendamentos truncados: falha detectada.
- Menus: cadastro, contato, busca, agenda, evolução, prontuário, troca de perfil e inativação.
- Entrada numérica inválida, texto longo e encerramento da entrada durante cadastro.

## Limites

Não houve ensaio de queda de energia, disco cheio, uso simultâneo ou medição de tempo com 100 registros.
Os testes validam os cenários descritos, sem substituir a revisão da equipe ou garantir ausência de outros defeitos.
