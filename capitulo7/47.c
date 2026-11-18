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

Missao *remover_fim(Missao *inicio) {
    if (!inicio) {
        printf("Lista vazia. Nada a remover.\n");
        return NULL;
    }
    Missao *ant = NULL, *atual = inicio;
    while (atual->prox != NULL) {
        ant = atual;
        atual = atual->prox;
    }
    printf("Removida: [%d] %s\n", atual->id, atual->nome);
    free(atual);
    if (!ant) return NULL;
    ant->prox = NULL;
    return inicio;
}

Missao *remover_id(Missao *inicio, int id) {
    Missao *ant = NULL, *atual = inicio;
    while (atual != NULL && atual->id != id) {
        ant = atual;
        atual = atual->prox;
    }
    if (!atual) {
        printf("Missao %d nao encontrada. Lista inalterada.\n", id);
        return inicio;
    }
    if (!ant) inicio = atual->prox;
    else ant->prox = atual->prox;
    printf("Removida: [%d] %s\n", atual->id, atual->nome);
    free(atual);
    return inicio;
}

void remover_apos(Missao *inicio, int id_ref) {
    Missao *ref = buscar(inicio, id_ref);
    if (!ref) {
        printf("Missao %d nao encontrada. Lista inalterada.\n", id_ref);
        return;
    }
    if (!ref->prox) {
        printf("Nao ha missao depois de %d.\n", id_ref);
        return;
    }
    Missao *t = ref->prox;
    ref->prox = t->prox;
    printf("Removida: [%d] %s\n", t->id, t->nome);
    free(t);
}

Missao *remover_antes(Missao *inicio, int id_ref) {
    Missao *ant2 = NULL, *ant = NULL, *atual = inicio;
    while (atual != NULL && atual->id != id_ref) {
        ant2 = ant;
        ant = atual;
        atual = atual->prox;
    }
    if (!atual) {
        printf("Missao %d nao encontrada. Lista inalterada.\n", id_ref);
        return inicio;
    }
    if (!ant) {
        printf("Nao ha missao antes de %d.\n", id_ref);
        return inicio;
    }
    if (!ant2) inicio = atual;
    else ant2->prox = atual;
    printf("Removida: [%d] %s\n", ant->id, ant->nome);
    free(ant);
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

    lista = inserir_fim(lista, 1, "Resgate");
    lista = inserir_fim(lista, 2, "Patrulha");
    lista = inserir_fim(lista, 3, "Escolta");
    lista = inserir_fim(lista, 4, "Apoio");
    lista = inserir_fim(lista, 5, "Relatorio");
    printf("Inicial:\n");
    exibir(lista);

    printf("\n-- casos sem remocao --\n");
    remover_apos(lista, 5);
    lista = remover_antes(lista, 1);
    remover_apos(lista, 99);
    lista = remover_antes(lista, 99);
    exibir(lista);

    printf("\n-- remover antes de 2 (altera o inicio) --\n");
    lista = remover_antes(lista, 2);
    exibir(lista);

    printf("\n-- remover apos 2 --\n");
    remover_apos(lista, 2);
    exibir(lista);

    printf("\n-- remover antes de 5 --\n");
    lista = remover_antes(lista, 5);
    exibir(lista);

    printf("\n-- remover apos 2 (ultimo nó) --\n");
    remover_apos(lista, 2);
    exibir(lista);

    printf("\n-- lista com um no --\n");
    lista = remover_antes(lista, 2);
    remover_apos(lista, 2);
    exibir(lista);

    liberar(lista);
    return 0;
}