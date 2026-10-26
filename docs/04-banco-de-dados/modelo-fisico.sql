
/*
    Projeto: Clínica Ser Possível
    Arquivo: modelo-fisico.sql

    Objetivo:
    Proposta de implementação física do modelo relacional
    do sistema de gerenciamento de pacientes e consultas.

    SGBD de referência: Microsoft SQL Server.

    IMPORTANTE:
    Este script é uma proposta documental. O protótipo atual
    utiliza arquivos locais .dat e não está integrado a este banco.

    A regra de criação automática do vínculo após a primeira
    consulta realizada deve ser implementada e testada na aplicação
    ou por mecanismo específico do banco de dados.
*/

-- =========================================================
-- 1. USUÁRIO
-- =========================================================

CREATE TABLE USUARIO (
    id_usuario INT IDENTITY(1,1) PRIMARY KEY,
    matricula VARCHAR(30) NOT NULL UNIQUE,
    senha_hash VARCHAR(255) NOT NULL,
    perfil VARCHAR(20) NOT NULL,
    ativo BIT NOT NULL DEFAULT 1,

    CONSTRAINT CK_USUARIO_PERFIL
        CHECK (perfil IN ('Administrador', 'Psicologo'))
);
GO

-- =========================================================
-- 2. RESPONSÁVEL
-- =========================================================

CREATE TABLE RESPONSAVEL (
    id_responsavel INT IDENTITY(1,1) PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    cpf VARCHAR(14) NOT NULL UNIQUE,
    telefone VARCHAR(20) NOT NULL,
    email VARCHAR(100) NULL,
    parentesco VARCHAR(50) NOT NULL
);
GO

-- =========================================================
-- 3. PACIENTE
-- Cada paciente deve possuir um responsável cadastrado.
-- =========================================================

CREATE TABLE PACIENTE (
    id_paciente INT IDENTITY(1,1) PRIMARY KEY,
    id_responsavel INT NOT NULL,
    nome VARCHAR(100) NOT NULL,
    cpf VARCHAR(14) NOT NULL UNIQUE,
    data_nascimento DATE NOT NULL,
    telefone VARCHAR(20) NULL,
    email VARCHAR(100) NULL,
    endereco VARCHAR(200) NULL,

    CONSTRAINT FK_PACIENTE_RESPONSAVEL
        FOREIGN KEY (id_responsavel)
        REFERENCES RESPONSAVEL(id_responsavel),

    CONSTRAINT CK_PACIENTE_DATA_NASCIMENTO
        CHECK (data_nascimento <= CAST(GETDATE() AS DATE))
);
GO

-- =========================================================
-- 4. PSICÓLOGO
-- Cada psicólogo está associado a um usuário do sistema.
-- =========================================================

CREATE TABLE PSICOLOGO (
    id_psicologo INT IDENTITY(1,1) PRIMARY KEY,
    id_usuario INT NOT NULL UNIQUE,
    nome VARCHAR(100) NOT NULL,
    registro_profissional VARCHAR(30) NOT NULL UNIQUE,
    telefone VARCHAR(20) NULL,
    email VARCHAR(100) NULL,

    CONSTRAINT FK_PSICOLOGO_USUARIO
        FOREIGN KEY (id_usuario)
        REFERENCES USUARIO(id_usuario)
);
GO

-- =========================================================
-- 5. VÍNCULO ENTRE PACIENTE E PSICÓLOGO
-- Mantém o histórico dos vínculos ao longo do tempo.
-- =========================================================

CREATE TABLE VINCULO_PACIENTE_PSICOLOGO (
    id_vinculo INT IDENTITY(1,1) PRIMARY KEY,
    id_paciente INT NOT NULL,
    id_psicologo INT NOT NULL,
    data_inicio DATE NOT NULL,
    data_fim DATE NULL,
    ativo BIT NOT NULL DEFAULT 1,

    CONSTRAINT FK_VINCULO_PACIENTE
        FOREIGN KEY (id_paciente)
        REFERENCES PACIENTE(id_paciente),

    CONSTRAINT FK_VINCULO_PSICOLOGO
        FOREIGN KEY (id_psicologo)
        REFERENCES PSICOLOGO(id_psicologo),

    CONSTRAINT CK_VINCULO_PERIODO
        CHECK (data_fim IS NULL OR data_fim >= data_inicio),

    CONSTRAINT CK_VINCULO_ATIVO
        CHECK (
            (ativo = 1 AND data_fim IS NULL)
            OR
            (ativo = 0 AND data_fim IS NOT NULL)
        )
);
GO

-- Impede mais de um vínculo ativo para o mesmo par
-- paciente-psicólogo.
CREATE UNIQUE INDEX UX_VINCULO_ATIVO_PACIENTE_PSICOLOGO
ON VINCULO_PACIENTE_PSICOLOGO (id_paciente, id_psicologo)
WHERE ativo = 1;
GO

-- =========================================================
-- 6. CONSULTA
-- O horário de início e o horário de término são armazenados
-- separadamente para permitir validar a duração da consulta.
-- =========================================================

CREATE TABLE CONSULTA (
    id_consulta INT IDENTITY(1,1) PRIMARY KEY,
    id_paciente INT NOT NULL,
    id_psicologo INT NOT NULL,
    data_consulta DATE NOT NULL,
    horario_inicio TIME(0) NOT NULL,
    horario_fim TIME(0) NOT NULL,
    status VARCHAR(20) NOT NULL,

    CONSTRAINT FK_CONSULTA_PACIENTE
        FOREIGN KEY (id_paciente)
        REFERENCES PACIENTE(id_paciente),

    CONSTRAINT FK_CONSULTA_PSICOLOGO
        FOREIGN KEY (id_psicologo)
        REFERENCES PSICOLOGO(id_psicologo),

    CONSTRAINT CK_CONSULTA_HORARIO
        CHECK (horario_fim > horario_inicio),

    CONSTRAINT CK_CONSULTA_STATUS
        CHECK (
            status IN ('Agendada', 'Realizada', 'Cancelada', 'Falta')
        )
);
GO

-- =========================================================
-- 7. PRONTUÁRIO
-- Cada paciente pode possuir, no máximo, um prontuário.
-- =========================================================

CREATE TABLE PRONTUARIO (
    id_prontuario INT IDENTITY(1,1) PRIMARY KEY,
    id_paciente INT NOT NULL UNIQUE,
    data_criacao DATE NOT NULL DEFAULT CAST(GETDATE() AS DATE),

    CONSTRAINT FK_PRONTUARIO_PACIENTE
        FOREIGN KEY (id_paciente)
        REFERENCES PACIENTE(id_paciente)
);
GO

-- =========================================================
-- 8. EVOLUÇÃO DO PRONTUÁRIO
-- Cada evolução pertence a um prontuário e registra
-- o psicólogo responsável pelo lançamento.
-- =========================================================

CREATE TABLE EVOLUCAO (
    id_evolucao INT IDENTITY(1,1) PRIMARY KEY,
    id_prontuario INT NOT NULL,
    id_psicologo INT NOT NULL,
    data_atendimento DATE NOT NULL,
    data_registro DATETIME2(0) NOT NULL DEFAULT SYSDATETIME(),
    descricao VARCHAR(MAX) NOT NULL,

    CONSTRAINT FK_EVOLUCAO_PRONTUARIO
        FOREIGN KEY (id_prontuario)
        REFERENCES PRONTUARIO(id_prontuario),

    CONSTRAINT FK_EVOLUCAO_PSICOLOGO
        FOREIGN KEY (id_psicologo)
        REFERENCES PSICOLOGO(id_psicologo),

    CONSTRAINT CK_EVOLUCAO_DATA_REGISTRO
        CHECK (data_registro >= CAST(data_atendimento AS DATETIME2))
);
GO

/*
    REGRAS DE NEGÓCIO QUE PRECISAM SER IMPLEMENTADAS
    E TESTADAS SE O BANCO FOR ADOTADO:

    1. Todo paciente deve ter um responsável cadastrado.
       A obrigatoriedade é garantida por id_responsavel NOT NULL
       e pela chave estrangeira.

    2. A primeira consulta com status 'Realizada' deve estabelecer
       o vínculo entre paciente e psicólogo, caso ainda não exista.
       Esta regra não é executada automaticamente por este script.

    3. A aplicação deve validar conflitos de horários para impedir
       consultas sobrepostas para o mesmo psicólogo e, conforme
       a regra definida pelo projeto, para o mesmo paciente.

    4. O acesso a prontuários e evoluções deve ser controlado
       pela aplicação. As tabelas, isoladamente, não implementam
       autorização por perfil.

    5. O campo senha_hash representa a estrutura prevista para
       armazenar um hash de senha. A aplicação deve gerar e validar
       o hash com algoritmo apropriado; não deve armazenar senhas
       em texto puro.

    6. O uso deste modelo não comprova integração com SQL Server,
       testes de segurança, conformidade legal ou prontidão para
       utilização com dados clínicos reais.
*/
