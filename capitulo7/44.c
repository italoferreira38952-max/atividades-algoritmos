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

Missao *buscar(Missao *inicio, int id) {
    for (Missao *aux = inicio; aux != NULL; aux = aux->prox)
        if (aux->id == id)
            return aux;
    return NULL;
}

int inserir_apos(Missao *inicio, int id_ref, int id, const char *nome) {
    Missao *ref = buscar(inicio, id_ref);
    if (!ref) return 0;

    Missao *n = criar(id, nome);
    if (!n) return -1;

    n->prox = ref->prox;
    ref->prox = n;
    return 1;
}

void relatar(int r, int id_ref) {
    if (r == 1)
        printf("Inserida apos a missao %d.\n", id_ref);
    else if (r == 0)
        printf("Missao %d nao encontrada. Lista inalterada.\n", id_ref);
    else
        printf("Erro de memoria.\n");
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

    int r = inserir_apos(lista, 2, 10, "Reconhecimento");
    relatar(r, 2);

    r = inserir_apos(lista, 3, 11, "Retorno");
    relatar(r, 3);

    r = inserir_apos(lista, 99, 12, "Inexistente");
    relatar(r, 99);

    printf("\nOrdem atual:\n");
    exibir(lista);

    liberar(lista);
    return 0;
}