#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "usuarios.h"
#include "pacientes.h"
#include "agendamentos.h"
#include "prontuarios.h"
#include "validacoes.h"

/* Descarta entradas longas para nao misturar respostas de campos diferentes.
 * Retorna zero ao encerrar a entrada, sem gravar a operacao incompleta. */
static int lerTexto(const char *rotulo, char *texto, size_t capacidade) {
    for (;;) {
        printf("%s", rotulo);
        fflush(stdout);
        if (fgets(texto, (int)capacidade, stdin) == NULL) return 0;
        char *fim = strchr(texto, '\n');
        if (fim != NULL) *fim = '\0';
        else {
            int c = getchar();
            if (c != '\n' && c != EOF) {
                while ((c = getchar()) != '\n' && c != EOF) {}
                printf("Texto muito longo. Limite: %zu caracteres.\n", capacidade - 1);
                continue;
            }
        }
        size_t n = strlen(texto);
        if (n > 0 && texto[n-1] == '\r') texto[--n] = '\0';
        for (size_t i = 0; i < n; i++)
            if (!isspace((unsigned char)texto[i])) return 1;
        puts("Preencha o campo.");
    }
}

static int lerInteiro(const char *rotulo, int *valor) {
    char linha[64], *fim;
    for (;;) {
        if (!lerTexto(rotulo, linha, sizeof linha)) return 0;
        errno = 0;
        long n = strtol(linha, &fim, 10);
        while (isspace((unsigned char)*fim)) fim++;
        if (fim != linha && *fim == '\0' && errno != ERANGE && n >= 0 && n <= INT_MAX) {
            *valor = (int)n;
            return 1;
        }
        puts("Digite um numero inteiro valido, maior ou igual a zero.");
    }
}

/* CPF invalido repete somente o proprio campo. */
static int lerCpf(const char *rotulo, char *cpf, const char *pessoa,
                  const Usuario *usuario) {
    for (;;) {
        if (!lerTexto(rotulo, cpf, 15)) return 0;
        if (!cpfValido(cpf, 15)) {
            printf("CPF do %s invalido. Use 000.000.000-00 com digitos verificadores validos. Tente novamente.\n", pessoa);
            continue;
        }
        if (usuario != NULL) {
            int r = cpfPacienteDisponivel(usuario, cpf);
            if (r == -1) {
                puts("Erro ao consultar cadastros. Nenhum dado foi gravado.");
                return -1;
            }
            if (r == 0) {
                puts("Paciente ja cadastrado com esse CPF. Informe outro CPF ou consulte o cadastro existente.");
                continue;
            }
        }
        return 1;
    }
}

static int lerData(const char *rotulo, char *data) {
    for (;;) {
        if (!lerTexto(rotulo, data, 11)) return 0;
        if (dataValida(data, 11)) return 1;
        puts("Data invalida. Use DD/MM/AAAA e uma data existente. Tente novamente.");
    }
}

static int lerHorario(const char *rotulo, char *horario) {
    for (;;) {
        if (!lerTexto(rotulo, horario, 6)) return 0;
        if (horarioValido(horario)) return 1;
        puts("Horario invalido. Use HH:MM, de 00:00 a 23:59. Tente novamente.");
    }
}

static void resultado(int r, const char *sucesso) {
    if (r == 1) puts(sucesso);
    else if (r == 0) puts("Operacao nao concluida. Confira o aviso acima ou os dados informados.");
    else puts("Erro de arquivo. Operacao nao confirmada; confira os dados antes de repetir.");
}

static int lerContato(Paciente *p) {
    return lerTexto("Telefone do paciente: ", p->telefone, sizeof p->telefone) &&
           lerTexto("Endereco do paciente: ", p->endereco, sizeof p->endereco) &&
           lerTexto("Telefone do responsavel: ", p->responsavel.telefone, sizeof p->responsavel.telefone) &&
           lerTexto("Endereco do responsavel: ", p->responsavel.endereco, sizeof p->responsavel.endereco);
}

static int novoUsuario(const Usuario *u) {
    Usuario n = {0};
    if (!lerInteiro("Matricula: ", &n.matricula) ||
        !lerTexto("Nome: ", n.nome, sizeof n.nome) ||
        !lerTexto("Senha (ate 19 caracteres, sem espacos): ", n.senha, sizeof n.senha)) return 0;
    if (strpbrk(n.senha, " \t\r\n") != NULL) {
        puts("A senha nao pode conter espacos.");
        return 1;
    }
    if (!lerInteiro("Funcao (1 Administrador, 2 Recepcao, 3 Psicologo): ", &n.perfil)) return 0;
    if (n.perfil == 3 && !lerTexto("CRP: ", n.crp, sizeof n.crp)) return 0;
    n.ativo = 1;
    resultado(cadastrarUsuario(u, &n), "Usuario cadastrado com sucesso!");
    return 1;
}

static int novoPaciente(const Usuario *u) {
    Paciente p = {0};
    if (!lerTexto("Nome do paciente: ", p.nome, sizeof p.nome)) return 0;
    int cpf = lerCpf("CPF do paciente (000.000.000-00): ", p.cpf, "paciente", u);
    if (cpf != 1) return cpf == 0 ? 0 : 1;
    if (!lerData("Nascimento (DD/MM/AAAA): ", p.dataNascimento) ||
        !lerTexto("Nome do responsavel: ", p.responsavel.nome, sizeof p.responsavel.nome)) return 0;
    if (!lerCpf("CPF do responsavel (000.000.000-00): ", p.responsavel.cpf,
                "responsavel", NULL)) return 0;
    if (!lerTexto("Parentesco: ", p.responsavel.parentesco, sizeof p.responsavel.parentesco) ||
        !lerContato(&p)) return 0;
    int r = cadastrarPaciente(u, &p);
    resultado(r, "Paciente e responsavel cadastrados com sucesso!");
    if (r == 1) printf("ID do paciente: %d\\n", p.id);
    return 1;
}

static int permitida(const Usuario *u, int op) {
    if (op == 0 || op == 13) return 1;
    if (u->perfil == 1) return op >= 1 && op <= 10;
    if (u->perfil == 2) return op >= 3 && op <= 10;
    if (u->perfil == 3) return op == 5 || op == 10 || op == 11 || op == 12;
    return 0;
}

static void menu(const Usuario *u) {
    const char *perfil = u->perfil == 1 ? "Administrador" : u->perfil == 2 ? "Recepcao" : "Psicologo";
    printf("\n=== Menu %s - %s ===\n", perfil, u->nome);
    if (u->perfil == 1) {
        puts("1 - Cadastrar usuario");
        puts("2 - Inativar usuario");
    }
    if (u->perfil == 1 || u->perfil == 2) {
        puts("3 - Buscar colaborador por matricula");
        puts("4 - Cadastrar paciente e responsavel");
    }
    puts("5 - Consultar paciente e responsavel");
    if (u->perfil == 1 || u->perfil == 2) {
        puts("6 - Atualizar contato e endereco");
        puts("7 - Agendar consulta");
        puts("8 - Remarcar consulta");
        puts("9 - Cancelar consulta");
    }
    puts("10 - Consultar agenda");
    if (u->perfil == 3) {
        puts("11 - Registrar evolucao tecnica");
        puts("12 - Consultar prontuario");
    }
    puts("13 - Trocar usuario");
    puts("0 - Sair");
}

/* Retorna 1 para voltar ao login e 0 para encerrar. */
static int executarMenu(const Usuario *u) {
    for (;;) {
        int op, id, r;
        char texto[150], data[11], horario[6];
        menu(u);
        if (!lerInteiro("Escolha: ", &op) || op == 0) return 0;
        if (!permitida(u, op)) {
            puts("Opcao indisponivel para este perfil.");
            continue;
        }
        if (op == 13) return 1;
        switch (op) {
        case 1:
            if (!novoUsuario(u)) return 0;
            break;
        case 2:
            if (!lerInteiro("Matricula a inativar: ", &id)) return 0;
            resultado(inativarUsuario(u, id), "Usuario inativado com sucesso!");
            break;
        case 3: {
            Usuario encontrado;
            if (!lerInteiro("Matricula do colaborador: ", &id)) return 0;
            r = buscarUsuarioPorMatricula(u, id, &encontrado);
            resultado(r, "Colaborador encontrado.");
            if (r == 1) printf("Matricula: %d\nNome: %s\nPerfil: %d\nAtivo: %d\nCRP: %s\n",
                encontrado.matricula, encontrado.nome, encontrado.perfil, encontrado.ativo, encontrado.crp);
            break;
        }
        case 4:
            if (!novoPaciente(u)) return 0;
            break;
        case 5:
            if (!lerTexto("Nome ou CPF do paciente ou responsavel: ", texto, sizeof texto)) return 0;
            resultado(consultarPacientes(u, texto), "Consulta concluida.");
            break;
        case 6: {
            Paciente contato = {0}, existente;
            if (!lerInteiro("ID do paciente: ", &contato.id)) return 0;
            r = buscarPacientePorId(u, contato.id, &existente);
            if (r != 1) { if (r == 0) puts("Paciente nao encontrado ou sem permissao de acesso."); resultado(r, ""); break; }
            printf("Paciente: %s\n", existente.nome);
            if (!lerContato(&contato)) return 0;
            resultado(atualizarContatoPaciente(u, &contato), "Contato atualizado com sucesso!");
            break;
        }
        case 7: {
            Agendamento a = {0};
            Paciente paciente;
            if (!lerInteiro("ID do paciente: ", &a.idPaciente)) return 0;
            r = buscarPacientePorId(u, a.idPaciente, &paciente);
            if (r != 1) { if (r == 0) puts("Paciente nao encontrado ou sem permissao de acesso."); resultado(r, ""); break; }
            a.matriculaPsicologo = paciente.matriculaPsicologo;
            if (a.matriculaPsicologo == 0) {
                if (!lerInteiro("Matricula do psicologo: ", &a.matriculaPsicologo)) return 0;
            } else printf("Psicologo vinculado: %d\n", a.matriculaPsicologo);
            if (!lerData("Data (DD/MM/AAAA): ", a.data) ||
                !lerHorario("Horario (HH:MM): ", a.horario)) return 0;
            r = agendarConsulta(u, &a);
            resultado(r, "Agendamento confirmado!");
            if (r == 1) printf("ID do agendamento: %d\n", a.id);
            break;
        }
        case 8:
            if (!lerInteiro("ID do agendamento: ", &id) ||
                !lerData("Nova data (DD/MM/AAAA): ", data) ||
                !lerHorario("Novo horario (HH:MM): ", horario)) return 0;
            resultado(remarcarConsulta(u, id, data, horario), "Consulta remarcada com sucesso!");
            break;
        case 9:
            if (!lerInteiro("ID do agendamento: ", &id)) return 0;
            resultado(cancelarConsulta(u, id), "Consulta cancelada com sucesso!");
            break;
        case 10:
            if (!lerData("Data (DD/MM/AAAA): ", data)) return 0;
            id = u->matricula;
            if (u->perfil != 3 && !lerInteiro("Matricula do psicologo: ", &id)) return 0;
            resultado(consultarAgenda(u, data, id), "Consulta da agenda concluida.");
            break;
        case 11: {
            Evolucao e = {0};
            if (!lerInteiro("ID do paciente: ", &e.idPaciente) ||
                !lerData("Data (DD/MM/AAAA): ", e.data) ||
                !lerTexto("Descricao da evolucao (uma linha, ate 1999 caracteres): ",
                          e.descricao, sizeof e.descricao)) return 0;
            r = registrarEvolucao(u, &e);
            resultado(r, "Evolucao registrada com sucesso!");
            if (r == 1) printf("ID da evolucao: %d\n", e.id);
            break;
        }
        case 12:
            if (!lerInteiro("ID do paciente: ", &id)) return 0;
            resultado(consultarProntuario(u, id), "Consulta do prontuario concluida.");
            break;
        }
    }
}

int main(void) {
    if (inicializarUsuarios() != 1) {
        puts("Erro ao preparar o arquivo de usuarios.");
        return 1;
    }
    for (;;) {
        int matricula;
        char senha[20];
        Usuario logado;
        puts("\n=== Clinica Ser Possivel - Login ===");
        if (!lerInteiro("Matricula (0 para sair): ", &matricula) || matricula == 0) break;
        if (!lerTexto("Senha: ", senha, sizeof senha)) break;
        int r = efetuarLogin(matricula, senha, &logado);
        memset(senha, 0, sizeof senha);
        if (r == -1) { puts("Erro ao ler o arquivo de usuarios."); return 1; }
        if (r != 1) {
            puts("Matricula ou senha incorreta, ou usuario inativo.");
            continue;
        }
        memset(logado.senha, 0, sizeof logado.senha);
        puts("Login realizado com sucesso!");
        if (!executarMenu(&logado)) break;
    }
    puts("Encerrando o sistema.");
    return 0;
}
