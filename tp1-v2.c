#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MINA -1

// prototipos para criar e liberação a matriz
int** criar_matriz(int tamanho);
void liberar_matriz(int** matriz, int tamanho);
void inicializar_matriz(int** matriz, int tamanho);
void distribuir_minas(int** matriz, int tamanho, int num_minas);
void calcular_vizinhos(int** matriz, int tamanho);

// funções do utilizadas jogo
void imprimir_matriz(int** matriz, int** revelado, int tamanho, int revelar);
int jogar(int** matriz, int** revelado, int tamanho);
int verificar_vitoria(int** matriz, int** revelado, int tamanho);

int main() {
    int dificuldade, tamanho, num_minas;
    
    // escolha da dificuldade
    printf("Escolha a dificuldade (1 = Fácil, 2 = Médio, 3 = Difícil): ");
    scanf("%d", &dificuldade);
    
    switch (dificuldade) {
        case 1: tamanho = 10; num_minas = 3; break;
        case 2: tamanho = 20; num_minas = 6; break;
        case 3: tamanho = 30; num_minas = 9; break;
        default: printf("Opção inválida!\n"); return 1;
    }

    // criação do campo minado
    int** campo = criar_matriz(tamanho);
    int** revelado = criar_matriz(tamanho); // matriz que controla as células reveladas (0 = não mostrado, 1 = mostrado)
    inicializar_matriz(campo, tamanho);
    inicializar_matriz(revelado, tamanho); // inicia como todas as células não reveladas
    distribuir_minas(campo, tamanho, num_minas);
    calcular_vizinhos(campo, tamanho);
    
    // jogo
    imprimir_matriz(campo, revelado, tamanho, 0); // inicialmente não revela minas
    if (jogar(campo, revelado, tamanho)) {
        printf("Parabéns, você é fera!\n");
        imprimir_matriz(campo, revelado, tamanho, 1); // exibi o campo completo após a vitória
    } else {
        printf("Game over!\n");
        imprimir_matriz(campo, revelado, tamanho, 1); // mostra todas as minas após a derrota
    }

    liberar_matriz(campo, tamanho);
    liberar_matriz(revelado, tamanho);
    return 0;
}

// criação da matriz dinamicamente
int** criar_matriz(int tamanho) {
    int** matriz = (int**) malloc(tamanho * sizeof(int*));
    for (int i = 0; i < tamanho; i++) {
        matriz[i] = (int*) malloc(tamanho * sizeof(int));
    }
    return matriz;
}

// função para liberação a memória alocada da matriz
void liberar_matriz(int** matriz, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// inicialização a matriz com zeros
void inicializar_matriz(int** matriz, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            matriz[i][j] = 0;
        }
    }
}

// função usada para distribuição de minas aleatoriamente
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

// calculo das minas vizinhas para cada célula
void calcular_vizinhos(int** matriz, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (matriz[i][j] == MINA) continue;
            int vizinhas = 0;
            for (int x = i-1; x <= i+1; x++) {
                for (int y = j-1; y <= j+1; y++) {
                    if (x >= 0 && x < tamanho && y >= 0 && y < tamanho && matriz[x][y] == MINA) {
                        vizinhas++;
                    }
                }
            }
            matriz[i][j] = vizinhas;
        }
    }
}

// impessão da matriz, com opção de revelar ou não as minas
void imprimir_matriz(int** matriz, int** revelado, int tamanho, int revelar) {
    printf("\nCampo Minado:\n");
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (revelar || revelado[i][j]) {
                if (matriz[i][j] == MINA) {
                    printf("* ");
                } else {
                    printf("%d ", matriz[i][j]);
                }
            } else {
                printf("x ");
            }
        }
        printf("\n");
    }
}

// função principal do jogo
int jogar(int** matriz, int** revelado, int tamanho) {
    int x, y;
    while (1) {
        printf("Digite as coordenadas (linha, coluna): ");
        
        // validando a entrada
        if (scanf("%d %d", &x, &y) != 2) {
            printf("Entrada inválida! Tente novamente.\n");
            // limpando o buffer de entrada
            while(getchar() != '\n'); 
            continue; // return ao início do loop
        }

        // Verifica se as coordenadas estão dentro do limite
        if (x < 0 || x >= tamanho || y < 0 || y >= tamanho) {
            printf("Coordenada inválida! Tente novamente.\n");
            continue;
        }

        // Verifica se o jogador acertou uma mina
        if (matriz[x][y] == MINA) {
            return 0; // game over :(
        }

        revelado[x][y] = 1; // exibindo a célula escolhida
        imprimir_matriz(matriz, revelado, tamanho, 0); // atualizando a impressão da matriz

        // verificando se o jogador venceu
        if (verificar_vitoria(matriz, revelado, tamanho)) {
            return 1; // vitória 
        }
    }
}

// verifica se todas as células sem minas foram exibidas
int verificar_vitoria(int** matriz, int** revelado, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (matriz[i][j] != MINA && revelado[i][j] == 0) {
                return 0; //  não possui células não exibidas
            }
        }
    }
    return 1; // todas as células seguras foram mostradas
}
