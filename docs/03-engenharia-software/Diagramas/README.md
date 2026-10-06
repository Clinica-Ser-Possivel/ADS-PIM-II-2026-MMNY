# Diagramas de Casos de Uso (UML)

**RF01 — Gerenciamento de Usuários**  
ATORES  
**Admin** Administrador do sistema com acesso total para cadastro e gestão de permissões.  
**Psicólogo(a)** Profissional responsável pelos atendimentos clínicos com acesso restrito.  
**Recepção** Assistente responsável por agendamentos e recepção de pacientes.  
CASOS DE USO  
*Cadastrar usuário -- Permite registrar novos colaboradores no sistema.  
*Efetuar login -- Permite a autenticação segura do usuário através de e-mail e senha.  
*Gerenciar permissões -- Permite alterar o perfil e níveis de acesso (LGPD/CFP).  

---

**RF02 — Gestão de Pacientes e Responsáveis**  
ATORES  
**Admin** Administrador do sistema com acesso para consulta e atualização cadastral.  
**Psicólogo(a)** Profissional de saúde com acesso ao histórico e cadastro dos pacientes.  
**Recepção** Assistente responsável pelo registro e atualização de dados de pacientes e responsáveis.  
CASOS DE USO  
*Cadastrar paciente e responsável -- Permite registrar os dados do paciente e vinculá-lo ao seu responsável legal.  
*Consultar histórico do paciente -- Permite pesquisar e visualizar a ficha cadastral do paciente e contatos.  
*Atualizar dados do paciente -- Permite alterar informações cadastrais e observações administrativas.  

---

**RF03 — Prontuário Eletrônico e Avaliação Psicológica**  
ATORES  
**Psicólogo(a)** Único usuário com acesso às informações clínicas sigilosas (CFP/LGPD).  
CASOS DE USO  
*Registro de evolução da sessão -- Registro das anotações clínicas e acompanhamento do tratamento.  
*Inserir Avaliação Psicológica -- Registro dos resultados de testes psicológicos/neuropsicológicos e laudos.  
*Anexar documentos ou relatórios -- Permite anexar relatórios escolares, pareceres médicos e termos assinados.  
*Consultar prontuário -- Acesso restrito ao histórico clínico do paciente.  

---

**RF04 — Agendamento de Consultas**  
ATORES  
**Admin** Administrador responsável pela gestão completa da grade de atendimentos da clínica.  
**Recepção** Assistente responsável pelo agendamento, alteração e cancelamento de consultas no dia a dia.  
**Psicólogo(a)** Profissional responsável pela consulta e acompanhamento da sua própria agenda de atendimento.  
CASOS DE USO  
*Agendar consulta -- Seleciona o paciente, profissional, data e horário para marcação.  
*Cancelar ou remarcar consultas -- Permite alterar datas/horários ou efetuar cancelamentos.  
*Visualizar agenda -- Permite consultar a grade de horários e compromissos confirmados.
