#ifndef MATRIZ_H
#define MATRIZ_H

// Define constante para minas
#define MINA -1

// Funções para manipulação da matriz
int** criar_matriz(int tamanho); // Cria uma matriz dinamicamente
void liberar_matriz(int** matriz, int tamanho); // Libera memória alocada
void inicializar_matriz(int** matriz, int tamanho); // Inicializa matriz com zeros
void distribuir_minas(int** matriz, int tamanho, int num_minas); // Distribui minas aleatoriamente
void calcular_vizinhos(int** matriz, int tamanho); // Calcula o número de minas vizinhas
void revelar_celulas(int** matriz, int** revelado, int tamanho, int x, int y); // Função de flood fill para revelar células com valor zero

#endif // MATRIZ_H
