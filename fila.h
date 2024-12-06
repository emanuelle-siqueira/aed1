#ifndef FILA_H
#define FILA_H

typedef struct No {
    int idade;
    struct No* proximo;
} No;

typedef struct Fila {
    No* inicio;
    No* fim;
} Fila;

// Funções de gerenciamento da fila
Fila* cria_fila();
void insere_cliente(Fila* fila, int idade);
void remove_cliente(Fila* fila);
void ordena_fila(Fila* fila);
void libera_fila(Fila* fila);

#endif
