"""Testes locais com dados sinteticos, sempre em pastas temporarias isoladas."""
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile

BASE = Path(__file__).resolve().parents[1]
GCC = os.environ.get("CLINICA_GCC") or shutil.which("gcc")
if not GCC:
    candidato = Path(r"C:\Program Files\CodeBlocks\MinGW\bin\gcc.exe")
    if candidato.exists():
        GCC = str(candidato)
if not GCC:
    raise SystemExit("GCC nao encontrado. Defina CLINICA_GCC com o caminho do compilador.")
FONTES = ["usuarios.c", "pacientes.c", "agendamentos.c", "prontuarios.c"]

def executar(args, pasta, entrada=None):
    r = subprocess.run([str(a) for a in args], cwd=pasta, input=entrada,
                       text=True, encoding="utf-8", errors="replace",
                       stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=30)
    if r.returncode:
        raise AssertionError(f"Falha ({r.returncode}): {args}\n{r.stdout}\n{r.stderr}")
    return r.stdout

with tempfile.TemporaryDirectory(prefix="clinica-testes-", dir=BASE / "testes") as temporaria:
    raiz = Path(temporaria)
    assert raiz.resolve().parent == (BASE / "testes").resolve()
    teste = raiz / "testes.exe"
    app = raiz / "clinica.exe"
    flags = ["-std=c11", "-Wall", "-Wextra", "-Wpedantic", "-Werror", "-I", str(BASE)]
    fontes = [BASE / f for f in FONTES]
    executar([GCC, *flags, BASE / "testes/testes.c", *fontes, "-o", teste], BASE)
    executar([GCC, *flags, BASE / "main.c", *fontes, "-o", app], BASE)
    print("Compilacao: passou sem avisos.")
    banco = raiz / "normal"
    banco.mkdir()
    for modo in ["normal", "persistencia"]:
        saida = executar([teste, modo], banco)
        assert "Responsavel Ficticio" in saida or modo == "persistencia"
        assert saida.index("EVOLUCAO_ANTERIOR") < saida.index("EVOLUCAO_POSTERIOR")
        print(re.search(r"PASSOU:.*", saida).group(0))
    falhas = raiz / "falhas"
    falhas.mkdir()
    print(re.search(r"PASSOU:.*", executar([teste, "falhas"], falhas)).group(0))

    cli = raiz / "menus"
    cli.mkdir()
    linhas = [
        "abc", "1001", "errada", "1001", "1234",
        "1", "3001", "Psicologo Ficticio", "teste", "3", "00/000000",
        "1", "2001", "Recepcao Ficticia", "teste", "2",
        "4", "Paciente Ficticio", "529.982.247-25", "10/05/2015",
        "Responsavel Ficticio", "111.444.777-35", "Mae",
        "1100000000", "Endereco A", "1100000001", "Endereco B",
        "6", "1", "1199999999", "Endereco Novo", "1188888888", "Endereco Novo B",
        "5", "Responsavel",
        "7", "1", "3001", "20/11/2026", "09:00",
        "8", "1", "20/11/2026", "10:00",
        "7", "1", "20/11/2026", "11:00",
        "9", "2", "10", "20/11/2026", "3001",
        "13", "3001", "teste", "4",
        "11", "1", "20/11/2026", "Registro ficticio pelo menu",
        "12", "1", "10", "20/11/2026",
        "13", "2001", "teste", "1", "5", "Responsavel",
        "13", "1001", "1234", "11", "2", "2001",
        "13", "2001", "teste", "0",
    ]
    saida = executar([app], cli, "\n".join(linhas) + "\n")
    for mensagem in [
        "Digite um numero inteiro valido",
        "Matricula ou senha incorreta",
        "Usuario cadastrado com sucesso!",
        "Paciente e responsavel cadastrados com sucesso!",
        "Contato atualizado com sucesso!",
        "Agendamento confirmado!",
        "Consulta remarcada com sucesso!",
        "Consulta cancelada com sucesso!",
        "Evolucao registrada com sucesso!",
        "Registro ficticio pelo menu",
        "Usuario inativado com sucesso!",
    ]:
        assert mensagem in saida, mensagem
    assert saida.count("Opcao indisponivel para este perfil.") == 3
    assert saida.count("Matricula ou senha incorreta") == 2
    # Reabrir o executavel verifica persistencia e acesso pelo prontuario.
    saida = executar([app], cli, "3001\nteste\n12\n1\n0\n")
    assert "Registro ficticio pelo menu" in saida
    # Campo maior que a capacidade nao deve consumir a resposta seguinte.
    saida = executar([app], cli, "1001\n" + "x" * 30 + "\n1234\n0\n")
    assert "Texto muito longo" in saida and "Login realizado com sucesso!" in saida
    # EOF durante cadastro nao grava dados parciais e nao entra em repeticao.
    antes = (cli / "usuarios.dat").read_bytes()
    executar([app], cli, "1001\n1234\n1\n9999\n")
    assert (cli / "usuarios.dat").read_bytes() == antes
    print("Menus: cadastro, contatos, busca, agenda, evolucao, prontuario, troca de perfil e bloqueios passaram.")
    print("Entradas invalidas, texto longo, EOF e reabertura do programa passaram.")
    cadastro = raiz / "correcao-campos"
    cadastro.mkdir()
    linhas = [
        "1001", "1234", "4", "Nome Preservado",
        "123.258.154-25", "529.982.247-25",
        "31/02/2026", "12/01/2023",
        "Responsavel Preservado", "123.256.958-35", "111.444.777-35",
        "Mae", "1100000000", "Endereco A", "1100000001", "Endereco B", "0",
    ]
    saida = executar([app], cadastro, "\n".join(linhas) + "\n")
    assert "CPF do paciente invalido." in saida
    assert "CPF do responsavel invalido." in saida
    assert "Data invalida." in saida
    assert saida.count("Nome do paciente: ") == 1
    assert saida.count("Nome do responsavel: ") == 1
    assert saida.count("CPF do paciente (000.000.000-00): ") == 2
    assert saida.count("CPF do responsavel (000.000.000-00): ") == 2
    assert saida.count("Nascimento (DD/MM/AAAA): ") == 2
    assert "Paciente e responsavel cadastrados com sucesso!" in saida
    saida = executar([app], cadastro, "1001\n1234\n5\nNome Preservado\n0\n")
    assert "Nome Preservado" in saida and "Responsavel Preservado" in saida
    # CPF duplicado: apenas esse campo e pedido novamente.
    linhas = [
        "1001", "1234", "4", "Segundo Paciente",
        "529.982.247-25", "111.444.777-35", "12/01/2023",
        "Outro Responsavel", "529.982.247-25", "Pai",
        "1100000000", "Endereco A", "1100000001", "Endereco B", "0",
    ]
    saida = executar([app], cadastro, "\n".join(linhas) + "\n")
    assert "Paciente ja cadastrado com esse CPF." in saida
    assert saida.count("Nome do paciente: ") == 1
    assert "ID do paciente: 2" in saida
    # Encerrar a entrada durante a correcao nao grava o cadastro.
    antes = (cadastro / "pacientes.dat").read_bytes()
    executar([app], cadastro, "1001\n1234\n4\nIncompleto\n123.123.123-12\n")
    assert (cadastro / "pacientes.dat").read_bytes() == antes
    linhas = [
        "1001", "1234",
        "1", "3001", "Psicologo Ativo", "teste", "3", "00/000000",
        "1", "3002", "Psicologo Inativo", "teste", "3", "00/000001",
        "1", "2001", "Recepcao", "teste", "2",
        "2", "3002",
        "7", "1", "9999", "20/11/2026", "09:00",
        "7", "1", "2001", "20/11/2026", "09:00",
        "7", "1", "3002", "20/11/2026", "09:00",
        "7", "1", "3001", "31/02/2026", "20/11/2026", "25:00", "09:00",
        "7", "1", "20/11/2026", "09:00", "0",
    ]
    saida = executar([app], cadastro, "\n".join(linhas) + "\n")
    for mensagem in [
        "Psicologo nao encontrado.",
        "nao tem perfil de Psicologo.",
        "Psicologo inativo.",
        "Horario ocupado.",
        "Data invalida.",
        "Horario invalido.",
        "Agendamento confirmado!",
    ]:
        assert mensagem in saida, mensagem
    assert saida.count("Agendamento confirmado!") == 1
    print("Novos avisos: CPF invalido/duplicado, data, horario e psicologo passaram.")
    print("Correcao somente do campo, preservacao de nomes e EOF sem gravacao passaram.")
print("Todos os testes passaram. Dados temporarios descartados.")
