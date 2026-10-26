#ifndef TIPOS_H
#define TIPOS_H

/*
 * USUARIO
 * Colaborador que acessa o sistema.
 * Arquivo: usuarios.dat
 *
 * Foi mantido os campos existentes para preservar
 * a leitura dos usuarios que ja foram cadastrados.
 */
typedef struct {
    int matricula;
    char nome[100];
    char senha[20];

    /* 1: administrador, 2: recepcionista, 3: psicologo */
    int perfil;

    /* Obrigatorio somente para psicologos. */
    char crp[20];

    /* 1: ativo, 0: inativo */
    int ativo;
} Usuario;


/*
 * RESPONSAVEL
 * Dados do responsavel legal.
 * Sera armazenado dentro do cadastro do paciente.
 */
typedef struct {
    char nome[100];

    /* Formato: 000.000.000-00 */
    char cpf[15];

    char telefone[20];
    char parentesco[30];
    char endereco[150];
} Responsavel;


/*
 * PACIENTE
 * Dados cadastrais do paciente e do seu responsavel.
 * Arquivo: pacientes.dat
 */
typedef struct {
    /* Identificador unico do paciente. */
    int id;

    char nome[100];
    char cpf[15];

    /* Formato: DD/MM/AAAA */
    char dataNascimento[11];

    char telefone[20];
    char endereco[150];

    /* Agrupa os dados do responsavel legal. */
    Responsavel responsavel;

    /*
     * Comeca com 0: paciente ainda sem psicologo.
     * Recebe a matricula no primeiro agendamento confirmado.
     * Os atendimentos seguintes utilizam esse mesmo vinculo.
     */
    int matriculaPsicologo;
} Paciente;


/*
 * AGENDAMENTO
 * Dados de uma consulta.
 * Arquivo: agendamentos.dat
 */
typedef struct {
    /* Identificador unico do agendamento. */
    int id;

    /* Identificador de um paciente existente. */
    int idPaciente;

    /*
     * Psicologo escolhido no primeiro agendamento.
     * Nos seguintes, vem do vinculo salvo no paciente.
     */
    int matriculaPsicologo;

    /* Formato: DD/MM/AAAA */
    char data[11];

    /* Formato de 24 horas: HH:MM */
    char horario[6];

    /* 1: agendado, 2: cancelado */
    int situacao;
} Agendamento;


/*
 * EVOLUCAO
 * Registro tecnico de um atendimento.
 * O historico dessas evolucoes forma o prontuario.
 * Arquivo: evolucoes.dat
 */
typedef struct {
    /* Identificador unico da evolucao. */
    int id;

    /* Paciente ao qual o registro pertence. */
    int idPaciente;

    /*
     * Matricula do psicologo conectado.
     * Ele deve ser o profissional vinculado ao paciente.
     */
    int matriculaPsicologo;

    /* Data do atendimento: DD/MM/AAAA */
    char data[11];

    /* Texto da evolucao, com ate 1999 caracteres. */
    char descricao[2000];
} Evolucao;

#endif