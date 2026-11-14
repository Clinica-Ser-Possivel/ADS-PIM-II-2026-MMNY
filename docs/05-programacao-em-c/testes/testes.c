#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <windows.h>
#include "usuarios.h"
#include "pacientes.h"
#include "agendamentos.h"
#include "prontuarios.h"

static int verificacoes;
#define CHECAR(condicao) do { \
    verificacoes++; \
    if (!(condicao)) { \
        fprintf(stderr, "FALHOU linha %d: %s\n", __LINE__, #condicao); \
        exit(1); \
    } \
} while (0)

static Usuario admin, recepcao, psi, outro;
static Paciente modeloPaciente(void) {
    Paciente p = {0};
    strcpy(p.nome, "Paciente Ficticio");
    strcpy(p.cpf, "529.982.247-25");
    strcpy(p.dataNascimento, "10/05/2015");
    strcpy(p.telefone, "1100000000");
    strcpy(p.endereco, "Endereco Ficticio A");
    strcpy(p.responsavel.nome, "Responsavel Ficticio");
    strcpy(p.responsavel.cpf, "111.444.777-35");
    strcpy(p.responsavel.parentesco, "Mae");
    strcpy(p.responsavel.telefone, "1100000001");
    strcpy(p.responsavel.endereco, "Endereco Ficticio B");
    return p;
}

static Usuario colaborador(int matricula, int perfil, const char *nome) {
    Usuario u = {0};
    u.matricula = matricula;
    u.perfil = perfil;
    u.ativo = 1;
    strcpy(u.nome, nome);
    strcpy(u.senha, "teste");
    if (perfil == 3) strcpy(u.crp, "00/000000");
    return u;
}

static void preparar(void) {
    CHECAR(inicializarUsuarios() == 1);
    CHECAR(efetuarLogin(1001, "1234", &admin) == 1);
    recepcao = colaborador(2001, 2, "Recepcao Ficticia");
    psi = colaborador(3001, 3, "Psicologo Ficticio");
    outro = colaborador(3002, 3, "Outro Psicologo");
    CHECAR(cadastrarUsuario(&admin, &recepcao) == 1);
    CHECAR(cadastrarUsuario(&admin, &psi) == 1);
    CHECAR(cadastrarUsuario(&admin, &outro) == 1);
}

static Agendamento consulta(int idPaciente, const char *horario) {
    Agendamento a = {0};
    a.idPaciente = idPaciente;
    a.matriculaPsicologo = psi.matricula;
    strcpy(a.data, "20/11/2026");
    strcpy(a.horario, horario);
    return a;
}

static long tamanho(const char *nome) {
    FILE *f = fopen(nome, "rb");
    CHECAR(f != NULL);
    CHECAR(fseek(f, 0, SEEK_END) == 0);
    long n = ftell(f);
    CHECAR(fclose(f) == 0);
    return n;
}

static void normal(void) {
    preparar();
    Usuario u;
    CHECAR(efetuarLogin(1001, "errada", &u) == 0);
    CHECAR(cadastrarUsuario(&admin, &recepcao) == 0);
    CHECAR(cadastrarUsuario(&recepcao, &outro) == 0);
    CHECAR(inativarUsuario(&admin, 1001) == 0);
    CHECAR(buscarUsuarioPorMatricula(&recepcao, psi.matricula, &u) == 1);
    CHECAR(u.senha[0] == '\0');
    CHECAR(buscarUsuarioPorMatricula(&psi, outro.matricula, &u) == 0);
    Paciente p = modeloPaciente(), lido;
    CHECAR(cadastrarPaciente(&psi, &p) == 0);
    CHECAR(cadastrarPaciente(&recepcao, &p) == 1);
    CHECAR(p.id == 1 && p.matriculaPsicologo == 0);
    CHECAR(cadastrarPaciente(&admin, &p) == 0);
    Paciente invalido = p;
    strcpy(invalido.cpf, "000.000.000-00");
    CHECAR(cadastrarPaciente(&admin, &invalido) == 0);
    CHECAR(consultarPacientes(&recepcao, "responsavel ficticio") == 1);
    CHECAR(consultarPacientes(&recepcao, "111.444.777-35") == 1);
    CHECAR(consultarPacientes(&psi, "Ficticio") == 0);
    Agendamento a = consulta(p.id, "09:00");
    CHECAR(agendarConsulta(&psi, &a) == 0);
    Agendamento ruim = a;
    strcpy(ruim.data, "31/02/2026");
    CHECAR(agendarConsulta(&recepcao, &ruim) == 0);
    ruim = a; strcpy(ruim.horario, "24:00");
    CHECAR(agendarConsulta(&recepcao, &ruim) == 0);
    ruim = a; ruim.matriculaPsicologo = 2001;
    CHECAR(agendarConsulta(&recepcao, &ruim) == 0);
    CHECAR(agendarConsulta(&recepcao, &a) == 1);
    CHECAR(a.id == 1 && a.situacao == 1);
    CHECAR(buscarPacientePorId(&admin, p.id, &lido) == 1);
    CHECAR(lido.matriculaPsicologo == psi.matricula);
    CHECAR(vincularPsicologo(&admin, p.id, outro.matricula) == 0);
    CHECAR(buscarPacientePorId(&outro, p.id, &lido) == 0);
    CHECAR(consultarPacientes(&psi, "Responsavel") == 1);

    /* Mesmo um cadastro completo adulterado so pode alterar contato. */
    Paciente contato = p;
    strcpy(contato.nome, "NAO DEVE SUBSTITUIR");
    strcpy(contato.responsavel.nome, "NAO DEVE SUBSTITUIR");
    contato.matriculaPsicologo = outro.matricula;
    strcpy(contato.telefone, "1199999999");
    strcpy(contato.endereco, "Endereco Novo");
    CHECAR(atualizarContatoPaciente(&recepcao, &contato) == 1);
    CHECAR(buscarPacientePorId(&admin, p.id, &lido) == 1);
    CHECAR(strcmp(lido.nome, p.nome) == 0);
    CHECAR(strcmp(lido.responsavel.nome, p.responsavel.nome) == 0);
    CHECAR(lido.matriculaPsicologo == psi.matricula);
    CHECAR(strcmp(lido.telefone, "1199999999") == 0);
    CHECAR(strcmp(lido.endereco, "Endereco Novo") == 0);
    /* Tambem aceita apenas ID + os quatro campos previstos no contrato. */
    Paciente parcial = {0};
    parcial.id = p.id;
    strcpy(parcial.telefone, "1188888888");
    strcpy(parcial.endereco, "Endereco Final");
    strcpy(parcial.responsavel.telefone, "1177777777");
    strcpy(parcial.responsavel.endereco, "Endereco Responsavel Final");
    CHECAR(atualizarContatoPaciente(&psi, &parcial) == 0);
    CHECAR(atualizarContatoPaciente(&recepcao, &parcial) == 1);
    CHECAR(buscarPacientePorId(&admin, p.id, &lido) == 1);
    CHECAR(strcmp(lido.cpf, p.cpf) == 0);
    CHECAR(strcmp(lido.dataNascimento, p.dataNascimento) == 0);
    CHECAR(strcmp(lido.responsavel.cpf, p.responsavel.cpf) == 0);
    CHECAR(strcmp(lido.responsavel.parentesco, p.responsavel.parentesco) == 0);
    CHECAR(lido.matriculaPsicologo == psi.matricula);

    Agendamento b = consulta(p.id, "09:00");
    CHECAR(agendarConsulta(&admin, &b) == 0);
    strcpy(b.horario, "10:00");
    b.matriculaPsicologo = outro.matricula;
    CHECAR(agendarConsulta(&admin, &b) == 1);
    CHECAR(b.matriculaPsicologo == psi.matricula);
    CHECAR(remarcarConsulta(&admin, a.id, a.data, a.horario) == 1);
    CHECAR(remarcarConsulta(&admin, a.id, a.data, "10:00") == 0);
    CHECAR(remarcarConsulta(&recepcao, a.id, a.data, "11:00") == 1);
    CHECAR(remarcarConsulta(&psi, b.id, b.data, "12:00") == 0);
    CHECAR(cancelarConsulta(&recepcao, b.id) == 1);
    CHECAR(cancelarConsulta(&admin, b.id) == 0);
    CHECAR(remarcarConsulta(&admin, b.id, b.data, "12:00") == 0);
    CHECAR(cancelarConsulta(&psi, a.id) == 0);
    Agendamento c = consulta(p.id, "10:00");
    CHECAR(agendarConsulta(&admin, &c) == 1);
    CHECAR(consultarAgenda(&psi, a.data, psi.matricula) == 1);
    CHECAR(consultarAgenda(&psi, a.data, outro.matricula) == 0);

    Evolucao e = {0};
    e.idPaciente = p.id;
    e.matriculaPsicologo = outro.matricula;
    strcpy(e.data, "20/11/2026");
    strcpy(e.descricao, "EVOLUCAO_POSTERIOR");
    CHECAR(registrarEvolucao(&admin, &e) == 0);
    CHECAR(registrarEvolucao(&recepcao, &e) == 0);
    CHECAR(registrarEvolucao(&outro, &e) == 0);
    CHECAR(registrarEvolucao(&psi, &e) == 1);
    CHECAR(e.matriculaPsicologo == psi.matricula && e.id == 1);
    strcpy(e.data, "19/11/2026");
    strcpy(e.descricao, "EVOLUCAO_ANTERIOR");
    CHECAR(registrarEvolucao(&psi, &e) == 1);
    CHECAR(e.id == 2);
    CHECAR(consultarProntuario(&admin, p.id) == 0);
    CHECAR(consultarProntuario(&recepcao, p.id) == 0);
    CHECAR(consultarProntuario(&outro, p.id) == 0);
    CHECAR(consultarProntuario(&psi, p.id) == 1);
    Usuario inativo = psi; inativo.ativo = 0;
    CHECAR(registrarEvolucao(&inativo, &e) == 0);
    CHECAR(inativarUsuario(&admin, recepcao.matricula) == 1);
    CHECAR(efetuarLogin(recepcao.matricula, "teste", &u) == 0);
    CHECAR(tamanho("agendamentos.dat") == 3 * (long)sizeof(Agendamento));
}

static void persistencia(void) {
    Usuario u;
    Paciente p;
    CHECAR(inicializarUsuarios() == 1);
    CHECAR(efetuarLogin(1001, "1234", &admin) == 1);
    CHECAR(efetuarLogin(3001, "teste", &psi) == 1);
    CHECAR(efetuarLogin(2001, "teste", &u) == 0);
    CHECAR(buscarPacientePorId(&psi, 1, &p) == 1);
    CHECAR(p.matriculaPsicologo == 3001);
    CHECAR(strcmp(p.telefone, "1188888888") == 0);
    CHECAR(strcmp(p.responsavel.telefone, "1177777777") == 0);
    CHECAR(consultarProntuario(&psi, 1) == 1);
    CHECAR(consultarAgenda(&psi, "20/11/2026", 3001) == 1);
    CHECAR(tamanho("evolucoes.dat") == 2 * (long)sizeof(Evolucao));
}

static void falhas(void) {
    preparar();
    Paciente p = modeloPaciente(), lido;
    CHECAR(cadastrarPaciente(&admin, &p) == 1);
    /* Falha de vinculo apos gravacao deve desfazer a consulta. */
    CHECAR(_mkdir("pacientes.tmp") == 0);
    Agendamento a = consulta(p.id, "09:00");
    CHECAR(agendarConsulta(&admin, &a) == -1);
    CHECAR(tamanho("agendamentos.dat") == 0);
    CHECAR(buscarPacientePorId(&admin, p.id, &lido) == 1);
    CHECAR(lido.matriculaPsicologo == 0);
    CHECAR(_rmdir("pacientes.tmp") == 0);
    CHECAR(agendarConsulta(&admin, &a) == 1);
    /* Windows: arquivo aberto sem compartilhamento de exclusao. */
    HANDLE trava = CreateFileA("pacientes.dat", GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    CHECAR(trava != INVALID_HANDLE_VALUE);
    strcpy(p.telefone, "1199999999");
    CHECAR(atualizarContatoPaciente(&admin, &p) == -1);
    CHECAR(CloseHandle(trava) != 0);
    CHECAR(buscarPacientePorId(&admin, p.id, &lido) == 1);
    CHECAR(strcmp(lido.telefone, "1100000000") == 0);
    CHECAR(lido.matriculaPsicologo == psi.matricula);
    CHECAR(atualizarContatoPaciente(&admin, &p) == 1);
    trava = CreateFileA("agendamentos.dat", GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    CHECAR(trava != INVALID_HANDLE_VALUE);
    CHECAR(cancelarConsulta(&admin, a.id) == -1);
    CHECAR(CloseHandle(trava) != 0);
    CHECAR(cancelarConsulta(&admin, a.id) == 1);

    /* Um registro truncado deve impedir a regravacao do arquivo. */
    FILE *f = fopen("pacientes.dat", "ab");
    CHECAR(f != NULL);
    CHECAR(fputc('X', f) != EOF);
    CHECAR(fclose(f) == 0);
    long antes = tamanho("pacientes.dat");
    CHECAR(atualizarContatoPaciente(&admin, &p) == -1);
    CHECAR(tamanho("pacientes.dat") == antes);
    f = fopen("agendamentos.dat", "ab");
    CHECAR(f != NULL);
    CHECAR(fputc('X', f) != EOF);
    CHECAR(fclose(f) == 0);
    CHECAR(consultarAgenda(&admin, "20/11/2026", psi.matricula) == -1);
}

int main(int argc, char **argv) {
    if (argc != 2) return 2;
    if (strcmp(argv[1], "normal") == 0) normal();
    else if (strcmp(argv[1], "persistencia") == 0) persistencia();
    else if (strcmp(argv[1], "falhas") == 0) falhas();
    else return 2;
    printf("PASSOU: %d verificacoes (%s).\n", verificacoes, argv[1]);
    return 0;
}
