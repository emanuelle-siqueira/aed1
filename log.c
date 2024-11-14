#include "log.h"
#include <stdlib.h>

Log* iniciar_log(const char* nome_arquivo) {
    Log* log = (Log*)malloc(sizeof(Log));
    log->arquivo = fopen(nome_arquivo, "a");
    if (!log->arquivo) {
        printf("Erro ao abrir o arquivo de log.\n");
        exit(1);
    }
    time_t agora = time(NULL);
    fprintf(log->arquivo, "Jogo iniciado em: %s\n", ctime(&agora));
    return log;
}

void registrar_log(Log* log, int** matriz, int** revelado, int tamanho, int x, int y) {
    fprintf(log->arquivo, "Coordenada escolhida: (%d, %d)\n", x, y);
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (revelado[i][j]) {
                fprintf(log->arquivo, "%d ", matriz[i][j]);
            } else {
                fprintf(log->arquivo, "x ");
            }
        }
        fprintf(log->arquivo, "\n");
    }
    fprintf(log->arquivo, "\n");
}

void fechar_log(Log* log) {
    fclose(log->arquivo);
    free(log);
}
