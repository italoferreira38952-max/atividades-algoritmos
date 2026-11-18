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

Missao *inserir_antes(Missao *inicio, int id_ref, int id, const char *nome, int *ok) {
    *ok = 0;
    Missao *ant = NULL, *atual = inicio;

    while (atual != NULL && atual->id != id_ref) {
        ant = atual;
        atual = atual->prox;
    }
    if (!atual) return inicio;

    Missao *n = criar(id, nome);
    if (!n) { *ok = -1; return inicio; }

    n->prox = atual;
    *ok = 1;
    if (!ant) return n;
    ant->prox = n;
    return inicio;
}

Missao *remover_inicio(Missao *inicio) {
    if (!inicio) {
        printf("Lista vazia. Nada a remover.\n");
        return NULL;
    }
    printf("Removida: [%d] %s\n", inicio->id, inicio->nome);
    Missao *t = inicio;
    inicio = inicio->prox;
    free(t);
    return inicio;
}

void relatar(int r, int id_ref) {
    if (r == 1)
        printf("Inserida com sucesso (ref %d).\n", id_ref);
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
    int ok;

    lista = remover_inicio(lista);

    lista = inserir_fim(lista, 1, "Resgate");
    lista = inserir_antes(lista, 1, 2, "Urgente", &ok);
    relatar(ok, 1);

    lista = inserir_fim(lista, 3, "Escolta");
    lista = inserir_antes(lista, 3, 4, "Apoio", &ok);
    relatar(ok, 3);

    lista = inserir_antes(lista, 99, 5, "Inexistente", &ok);
    relatar(ok, 99);

    printf("\nOrdem atual:\n");
    exibir(lista);

    printf("\n");
    lista = remover_inicio(lista);
    lista = remover_inicio(lista);
    lista = remover_inicio(lista);
    printf("\nApos remocoes:\n");
    exibir(lista);

    lista = remover_inicio(lista);
    lista = remover_inicio(lista);

    liberar(lista);
    return 0;
}