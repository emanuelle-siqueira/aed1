#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* cria_fila() {
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    if (fila == NULL) {
        printf("Erro ao alocar memória para a fila.\n");
        exit(1);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void insere_cliente(Fila* fila, int idade) {
    No* novo_no = (No*) malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro ao alocar memória para o nó.\n");
        exit(1);
    }
    novo_no->idade = idade;
    novo_no->proximo = NULL;
    
    if (fila->fim == NULL) {
        fila->inicio = novo_no;
    } else {
        fila->fim->proximo = novo_no;
    }
    fila->fim = novo_no;
}

void remove_cliente(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia, não há clientes para remover.\n");
        return;
    }
    No* temp = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    free(temp);
}

void ordena_fila(Fila* fila) {
    if (fila == NULL || fila->inicio == NULL) return;

    No* atual;
    No* prox;
    int temp;

    for (atual = fila->inicio; atual != NULL; atual = atual->proximo) {
        for (prox = atual->proximo; prox != NULL; prox = prox->proximo) {
            if (atual->idade < prox->idade) {
                temp = atual->idade;
                atual->idade = prox->idade;
                prox->idade = temp;
            }
        }
    }
}

void libera_fila(Fila* fila) {
    while (fila->inicio != NULL) {
        remove_cliente(fila);
    }
    free(fila);
}
