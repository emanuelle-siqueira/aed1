#include <stdio.h>
#include "fila.h"

// Função para ler o arquivo e preencher a fila
void le_arquivo(const char* nome_arquivo, Fila* fila) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }
    int idade;
    while (fscanf(arquivo, "%d", &idade) != EOF) {
        insere_cliente(fila, idade);
    }
    fclose(arquivo);
}

int main() {
    Fila* fila = cria_fila();
    
    // Lê as idades dos clientes do arquivo "clientes.txt"
    le_arquivo("clientes.txt", fila);
    
    // Ordena os clientes com base na idade
    ordena_fila(fila);

    // Exibe a fila após a ordenação
    printf("Atendimento dos clientes (idade):\n");
    No* atual = fila->inicio;
    while (atual != NULL) {
        printf("%d\n", atual->idade);
        atual = atual->proximo;
    }

    // Libera a memória alocada
    libera_fila(fila);
    
    return 0;
}
