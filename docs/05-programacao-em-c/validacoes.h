#ifndef VALIDACOES_H
#define VALIDACOES_H
#include <stddef.h>
#include <string.h>

/* Valida CPF no formato 000.000.000-00. */
static inline int cpfValido(const char *cpf, size_t tamanho) {
    int digitos[11];
    int i, soma, resto;
    int d1, d2;

    if (cpf == NULL || tamanho < 15 ||
        memchr(cpf, '\0', tamanho) == NULL)
        return 0;

    if (strlen(cpf) != 14 ||
        cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-')
        return 0;

    for (i = 0; i < 14; i++) {
        if (i == 3 || i == 7 || i == 11)
            continue;

        if (cpf[i] < '0' || cpf[i] > '9')
            return 0;
    }

    digitos[0] = cpf[0] - '0';
    digitos[1] = cpf[1] - '0';
    digitos[2] = cpf[2] - '0';
    digitos[3] = cpf[4] - '0';
    digitos[4] = cpf[5] - '0';
    digitos[5] = cpf[6] - '0';
    digitos[6] = cpf[8] - '0';
    digitos[7] = cpf[9] - '0';
    digitos[8] = cpf[10] - '0';
    digitos[9] = cpf[12] - '0';
    digitos[10] = cpf[13] - '0';

    for (i = 1; i < 11; i++) {
        if (digitos[i] != digitos[0])
            break;
    }

    if (i == 11)
        return 0;

    soma = 0;

    for (i = 0; i < 9; i++)
        soma += digitos[i] * (10 - i);

    resto = soma % 11;
    d1 = (resto < 2) ? 0 : 11 - resto;

    if (digitos[9] != d1)
        return 0;

    soma = 0;

    for (i = 0; i < 10; i++)
        soma += digitos[i] * (11 - i);

    resto = soma % 11;
    d2 = (resto < 2) ? 0 : 11 - resto;

    return digitos[10] == d2;
}

/* Verifica se o ano e bissexto. */
static inline int anoBissexto(int ano) {
    return (ano % 400 == 0) ||
           (ano % 4 == 0 && ano % 100 != 0);
}

/* Valida data no formato DD/MM/AAAA. */
static inline int dataValida(const char *data, size_t tamanho) {
    int dia, mes, ano;
    int diasNoMes;
    int i;

    if (data == NULL || tamanho < 11 ||
        memchr(data, '\0', tamanho) == NULL)
        return 0;

    if (strlen(data) != 10 ||
        data[2] != '/' || data[5] != '/')
        return 0;

    for (i = 0; i < 10; i++) {
        if (i == 2 || i == 5)
            continue;

        if (data[i] < '0' || data[i] > '9')
            return 0;
    }

    dia = (data[0] - '0') * 10 + data[1] - '0';
    mes = (data[3] - '0') * 10 + data[4] - '0';
    ano = (data[6] - '0') * 1000 +
          (data[7] - '0') * 100 +
          (data[8] - '0') * 10 +
          (data[9] - '0');

    if (ano < 1900 || mes < 1 || mes > 12 || dia < 1)
        return 0;

    diasNoMes = 31;

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasNoMes = 30;
    } else if (mes == 2) {
        diasNoMes = anoBissexto(ano) ? 29 : 28;
    }

    return dia <= diasNoMes;
}

/* Valida um horario no formato HH:MM. */
static inline int horarioValido(const char *horario) {
    int hora, minuto;
    int i;

    if (horario == NULL || memchr(horario, '\0', 6) == NULL)
        return 0;

    if (strlen(horario) != 5 || horario[2] != ':')
        return 0;

    for (i = 0; i < 5; i++) {
        if (i != 2 &&
            (horario[i] < '0' || horario[i] > '9'))
            return 0;
    }

    hora = (horario[0] - '0') * 10 + horario[1] - '0';
    minuto = (horario[3] - '0') * 10 + horario[4] - '0';

    return hora >= 0 && hora <= 23 &&
           minuto >= 0 && minuto <= 59;
}

#endif
