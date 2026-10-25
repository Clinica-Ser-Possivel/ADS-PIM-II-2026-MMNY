-- Clínica Ser Possível — modelo físico de referência
-- SGBD de referência: Microsoft SQL Server
-- IMPORTANTE: script documental. O protótipo deste semestre usa arquivos .dat em C
-- e não possui integração com SQL Server.
-- Executar em uma base de testes vazia; o script cria as tabelas.

CREATE TABLE USUARIO (
    id_usuario INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_USUARIO PRIMARY KEY,
    matricula VARCHAR(50) NOT NULL,
    senha_hash VARCHAR(255) NOT NULL,
    perfil VARCHAR(20) NOT NULL,
    ativo BIT NOT NULL CONSTRAINT DF_USUARIO_ATIVO DEFAULT (1),
    CONSTRAINT UQ_USUARIO_MATRICULA UNIQUE (matricula),
    CONSTRAINT CK_USUARIO_PERFIL CHECK (perfil IN ('ADMIN', 'RECEPCAO', 'PSICOLOGO'))
);

CREATE TABLE RESPONSAVEL (
    id_responsavel INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_RESPONSAVEL PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    cpf VARCHAR(14) NULL,
    telefone VARCHAR(20) NULL,
    email VARCHAR(100) NULL,
    parentesco VARCHAR(50) NULL
);
-- CPF é opcional. Índice filtrado permite vários registros sem CPF (NULL).
CREATE UNIQUE INDEX UX_RESPONSAVEL_CPF_INFORMADO
    ON RESPONSAVEL(cpf) WHERE cpf IS NOT NULL;

CREATE TABLE PACIENTE (
    id_paciente INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_PACIENTE PRIMARY KEY,
    id_responsavel INT NOT NULL,
    nome VARCHAR(100) NOT NULL,
    cpf VARCHAR(14) NULL,
    data_nascimento DATE NOT NULL,
    telefone VARCHAR(20) NULL,
    email VARCHAR(100) NULL,
    endereco VARCHAR(200) NULL,
    CONSTRAINT FK_PACIENTE_RESPONSAVEL FOREIGN KEY (id_responsavel)
        REFERENCES RESPONSAVEL(id_responsavel)
);
CREATE UNIQUE INDEX UX_PACIENTE_CPF_INFORMADO
    ON PACIENTE(cpf) WHERE cpf IS NOT NULL;

CREATE TABLE PSICOLOGO (
    id_psicologo INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_PSICOLOGO PRIMARY KEY,
    id_usuario INT NOT NULL,
    nome VARCHAR(100) NOT NULL,
    registro_profissional VARCHAR(30) NOT NULL,
    telefone VARCHAR(20) NULL,
    email VARCHAR(100) NULL,
    CONSTRAINT UQ_PSICOLOGO_USUARIO UNIQUE (id_usuario),
    CONSTRAINT UQ_PSICOLOGO_REGISTRO UNIQUE (registro_profissional),
    CONSTRAINT FK_PSICOLOGO_USUARIO FOREIGN KEY (id_usuario)
        REFERENCES USUARIO(id_usuario)
);

CREATE TABLE VINCULO_PACIENTE_PSICOLOGO (
    id_vinculo INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_VINCULO_PACIENTE_PSICOLOGO PRIMARY KEY,
    id_paciente INT NOT NULL,
    id_psicologo INT NOT NULL,
    data_inicio DATE NOT NULL,
    data_fim DATE NULL,
    ativo BIT NOT NULL CONSTRAINT DF_VINCULO_ATIVO DEFAULT (1),
    CONSTRAINT FK_VINCULO_PACIENTE FOREIGN KEY (id_paciente)
        REFERENCES PACIENTE(id_paciente),
    CONSTRAINT FK_VINCULO_PSICOLOGO FOREIGN KEY (id_psicologo)
        REFERENCES PSICOLOGO(id_psicologo),
    CONSTRAINT CK_VINCULO_DATAS CHECK (data_fim IS NULL OR data_fim >= data_inicio)
);
-- Evita dois vínculos ativos para o mesmo par paciente/psicólogo.
CREATE UNIQUE INDEX UX_VINCULO_ATIVO_PACIENTE_PSICOLOGO
    ON VINCULO_PACIENTE_PSICOLOGO(id_paciente, id_psicologo)
    WHERE ativo = 1;

CREATE TABLE CONSULTA (
    id_consulta INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_CONSULTA PRIMARY KEY,
    id_paciente INT NOT NULL,
    id_psicologo INT NOT NULL,
    data_consulta DATE NOT NULL,
    horario TIME(0) NOT NULL,
    status VARCHAR(20) NOT NULL CONSTRAINT DF_CONSULTA_STATUS DEFAULT ('AGENDADA'),
    CONSTRAINT FK_CONSULTA_PACIENTE FOREIGN KEY (id_paciente)
        REFERENCES PACIENTE(id_paciente),
    CONSTRAINT FK_CONSULTA_PSICOLOGO FOREIGN KEY (id_psicologo)
        REFERENCES PSICOLOGO(id_psicologo),
    CONSTRAINT CK_CONSULTA_STATUS CHECK (status IN ('AGENDADA', 'REALIZADA', 'CANCELADA'))
);
-- A regra de conflito cobre o mesmo dia e horário exatos, não intervalos sobrepostos.
-- Consultas canceladas não bloqueiam o horário.
CREATE UNIQUE INDEX UX_CONSULTA_PSICOLOGO_HORARIO_ATIVO
    ON CONSULTA(id_psicologo, data_consulta, horario)
    WHERE status <> 'CANCELADA';
CREATE UNIQUE INDEX UX_CONSULTA_PACIENTE_HORARIO_ATIVO
    ON CONSULTA(id_paciente, data_consulta, horario)
    WHERE status <> 'CANCELADA';

CREATE TABLE PRONTUARIO (
    id_prontuario INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_PRONTUARIO PRIMARY KEY,
    id_paciente INT NOT NULL,
    data_criacao DATE NOT NULL CONSTRAINT DF_PRONTUARIO_DATA DEFAULT (CONVERT(DATE, GETDATE())),
    CONSTRAINT UQ_PRONTUARIO_PACIENTE UNIQUE (id_paciente),
    CONSTRAINT FK_PRONTUARIO_PACIENTE FOREIGN KEY (id_paciente)
        REFERENCES PACIENTE(id_paciente)
);

CREATE TABLE EVOLUCAO (
    id_evolucao INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_EVOLUCAO PRIMARY KEY,
    id_prontuario INT NOT NULL,
    id_psicologo INT NOT NULL,
    data_atendimento DATE NOT NULL,
    data_registro DATETIME2(0) NOT NULL CONSTRAINT DF_EVOLUCAO_DATA_REGISTRO DEFAULT (SYSDATETIME()),
    descricao VARCHAR(1000) NOT NULL,
    CONSTRAINT FK_EVOLUCAO_PRONTUARIO FOREIGN KEY (id_prontuario)
        REFERENCES PRONTUARIO(id_prontuario),
    CONSTRAINT FK_EVOLUCAO_PSICOLOGO FOREIGN KEY (id_psicologo)
        REFERENCES PSICOLOGO(id_psicologo)
);

-- Observação de regra de acesso:
-- A aplicação deve validar VINCULO_PACIENTE_PSICOLOGO.ativo = 1 antes de
-- permitir consultar o prontuário ou registrar evolução. As FKs deste script
-- garantem integridade referencial, mas não implementam sozinhas a autorização clínica.
-- O perfil ADMIN não deve receber acesso ao conteúdo clínico apenas por ser administrador.
-- Fim do script.
