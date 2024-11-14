#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>

typedef struct {
    FILE* arquivo;
} Log;

Log* iniciar_log(const char* nome_arquivo); // Inicia log com cabeçalho
void registrar_log(Log* log, int** matriz, int** revelado, int tamanho, int x, int y); // Registra o estado do jogo no log
void fechar_log(Log* log); // Fecha o log

#endif // LOG_H
