#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int** criar_matriz(int tamanho) {
    int** matriz = (int**) malloc(tamanho * sizeof(int*));
    for (int i = 0; i < tamanho; i++) {
        matriz[i] = (int*) malloc(tamanho * sizeof(int));
    }
    return matriz;
}

void liberar_matriz(int** matriz, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void inicializar_matriz(int** matriz, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            matriz[i][j] = 0;
        }
    }
}

void distribuir_minas(int** matriz, int tamanho, int num_minas) {
    srand(time(NULL));
    int minas_colocadas = 0;
    while (minas_colocadas < num_minas) {
        int x = rand() % tamanho;
        int y = rand() % tamanho;
        if (matriz[x][y] != MINA) {
            matriz[x][y] = MINA;
            minas_colocadas++;
        }
    }
}

void calcular_vizinhos(int** matriz, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (matriz[i][j] == MINA) continue;
            int vizinhas = 0;
            for (int x = i - 1; x <= i + 1; x++) {
                for (int y = j - 1; y <= j + 1; y++) {
                    if (x >= 0 && x < tamanho && y >= 0 && y < tamanho && matriz[x][y] == MINA) {
                        vizinhas++;
                    }
                }
            }
            matriz[i][j] = vizinhas;
        }
    }
}

void revelar_celulas(int** matriz, int** revelado, int tamanho, int x, int y) {
    if (x < 0 || x >= tamanho || y < 0 || y >= tamanho || revelado[x][y] || matriz[x][y] == MINA) return;
    revelado[x][y] = 1;
    if (matriz[x][y] == 0) {
        revelar_celulas(matriz, revelado, tamanho, x - 1, y);
        revelar_celulas(matriz, revelado, tamanho, x + 1, y);
        revelar_celulas(matriz, revelado, tamanho, x, y - 1);
        revelar_celulas(matriz, revelado, tamanho, x, y + 1);
    }
}
