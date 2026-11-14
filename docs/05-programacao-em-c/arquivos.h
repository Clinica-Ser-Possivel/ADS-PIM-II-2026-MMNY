#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

/* Substitui somente depois de fechar e validar o arquivo temporario.
 * Se a substituicao falhar, o arquivo original permanece no lugar.
 * Uso local, com uma unica instancia do programa por pasta de dados. */
static inline int substituirArquivo(const char *temporario,
                                    const char *destino) {
#ifdef _WIN32
    return MoveFileExA(temporario, destino,
                      MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)
               ? 1 : 0;
#else
    return rename(temporario, destino) == 0;
#endif
}

#endif
