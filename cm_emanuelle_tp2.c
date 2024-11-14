#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "log.h"

// declaração da função verificar_vitoria
int verificar_vitoria(int** matriz, int** revelado, int tamanho);

int main() {
    FILE* teste = fopen("teste.txt", "r");
    if (!teste) {
        printf("Erro ao abrir o arquivo teste.txt\n");
        return 1;
    }

    int dificuldade, tamanho, num_minas;
    fscanf(teste, "%d", &dificuldade);
    switch (dificuldade) {
        case 1: tamanho = 10; num_minas = 3; break;
        case 2: tamanho = 20; num_minas = 6; break;
        case 3: tamanho = 30; num_minas = 9; break;
        default: printf("Opção inválida!...\n"); return 1;
    }

    int** campo = criar_matriz(tamanho);
    int** revelado = criar_matriz(tamanho);
    inicializar_matriz(campo, tamanho);
    inicializar_matriz(revelado, tamanho);
    distribuir_minas(campo, tamanho, num_minas);
    calcular_vizinhos(campo, tamanho);

    Log* log = iniciar_log("log.txt");

    int x, y;
    int game_over = 0; // Variável para monitorar o fim do jogo

    while (fscanf(teste, "%d, %d", &x, &y) == 2) {
        x--; y--; // Ajuste para índice da matriz (começando em 0)

        if (campo[x][y] == MINA) {
            printf("Game over!\n");
            registrar_log(log, campo, revelado, tamanho, x, y);
            game_over = 1; // Define o jogo como finalizado
            break;
        }

        revelar_celulas(campo, revelado, tamanho, x, y);
        registrar_log(log, campo, revelado, tamanho, x, y);

        // Verifica se o jogador venceu
        if (verificar_vitoria(campo, revelado, tamanho)) {
            printf("Parabéns, você venceu!\n");
            game_over = 1; // Define o jogo como finalizado
            break;
        }
    }

    // Mensagem final se não houver vitória ou derrota explícita (não esperado no teste normal)
    if (!game_over) {
        printf("Jogo terminado sem condições de vitória ou derrota claras.\n");
    }

    fclose(teste);
    fechar_log(log);
    liberar_matriz(campo, tamanho);
    liberar_matriz(revelado, tamanho);
    return 0;
}

int verificar_vitoria(int** matriz, int** revelado, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (matriz[i][j] != MINA && revelado[i][j] == 0) {
                return 0; // Existem células seguras ainda não reveladas
            }
        }
    }
    return 1; // Todas as células seguras foram reveladas
}
