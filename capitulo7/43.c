#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Missao {
    int id;
    char nome[50];
    struct Missao *prox;
} Missao;

Missao *criar(int id, const char *nome) {
    Missao *n = malloc(sizeof(Missao));
    if (!n) return NULL;
    n->id = id;
    strcpy(n->nome, nome);
    n->prox = NULL;
    return n;
}

Missao *inserir_inicio(Missao *inicio, int id, const char *nome) {
    Missao *n = criar(id, nome);
    if (!n) return inicio;
    n->prox = inicio;
    return n;
}

Missao *inserir_fim(Missao *inicio, int id, const char *nome) {
    Missao *n = criar(id, nome);
    if (!n) return inicio;

    if (inicio == NULL)
        return n;

    Missao *aux = inicio;
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = n;
    return inicio;
}

void exibir(Missao *inicio) {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    for (Missao *aux = inicio; aux != NULL; aux = aux->prox)
        printf("[%d] %s\n", aux->id, aux->nome);
}

void liberar(Missao *inicio) {
    while (inicio) {
        Missao *t = inicio;
        inicio = inicio->prox;
        free(t);
    }
}

int main(void) {
    Missao *lista = NULL;

    exibir(lista);

    lista = inserir_fim(lista, 1, "Resgate");
    lista = inserir_inicio(lista, 2, "Patrulha");
    lista = inserir_fim(lista, 3, "Escolta");
    lista = inserir_inicio(lista, 4, "Emergencia");
    lista = inserir_fim(lista, 5, "Relatorio");

    printf("\nOrdem atual:\n");
    exibir(lista);

    liberar(lista);
    return 0;
}
