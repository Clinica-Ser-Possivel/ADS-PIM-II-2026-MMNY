# DER — Clínica Ser Possível

O diagrama representa a proposta documental de banco de dados. O protótipo deste semestre utiliza arquivos `.dat` em C e não se conecta ao SQL Server.

```mermaid
erDiagram
    USUARIO {
        INT id_usuario PK
        VARCHAR matricula UK
        VARCHAR senha_hash
        VARCHAR perfil
        BIT ativo
    }

    PACIENTE {
        INT id_paciente PK
        INT id_responsavel FK
        VARCHAR nome
        VARCHAR cpf UK
        DATE data_nascimento
        VARCHAR telefone
        VARCHAR email
        VARCHAR endereco
    }

    RESPONSAVEL {
        INT id_responsavel PK
        VARCHAR nome
        VARCHAR cpf UK
        VARCHAR telefone
        VARCHAR email
        VARCHAR parentesco
    }

    PSICOLOGO {
        INT id_psicologo PK
        INT id_usuario FK, UK
        VARCHAR nome
        VARCHAR registro_profissional UK
        VARCHAR telefone
        VARCHAR email
    }

    VINCULO_PACIENTE_PSICOLOGO {
        INT id_vinculo PK
        INT id_paciente FK
        INT id_psicologo FK
        DATE data_inicio
        DATE data_fim
        BIT ativo
    }

    CONSULTA {
        INT id_consulta PK
        INT id_paciente FK
        INT id_psicologo FK
        DATE data_consulta
        TIME horario
        VARCHAR status
    }

    PRONTUARIO {
        INT id_prontuario PK
        INT id_paciente FK, UK
        DATE data_criacao
    }

    EVOLUCAO {
        INT id_evolucao PK
        INT id_prontuario FK
        INT id_psicologo FK
        DATE data_atendimento
        DATETIME2 data_registro
        VARCHAR descricao
    }

    RESPONSAVEL ||--o{ PACIENTE : responsavel_legal
    USUARIO ||--o| PSICOLOGO : conta_de_acesso
    PACIENTE ||--o{ CONSULTA : possui
    PSICOLOGO ||--o{ CONSULTA : atende
    PACIENTE ||--o| PRONTUARIO : possui
    PRONTUARIO ||--o{ EVOLUCAO : contem
    PSICOLOGO ||--o{ EVOLUCAO : registra
    PACIENTE ||--o{ VINCULO_PACIENTE_PSICOLOGO : possui_vinculo
    PSICOLOGO ||--o{ VINCULO_PACIENTE_PSICOLOGO : possui_vinculo
```

## Legenda

- **PK:** chave primária.
- **FK:** chave estrangeira.
- **UK:** valor único.
- `RESPONSAVEL ||--o{ PACIENTE`: cada paciente referencia um responsável legal principal; um responsável pode estar associado a mais de um paciente.
- `PACIENTE ||--o| PRONTUARIO`: um paciente pode ter zero ou um prontuário; quando criado, o prontuário pertence a um único paciente.
- `VINCULO_PACIENTE_PSICOLOGO` resolve a relação muitos-para-muitos entre pacientes e psicólogos e registra se o vínculo está ativo.
- As restrições de unicidade para impedir horários duplicados e os detalhes de nulidade são definidos no script SQL.
