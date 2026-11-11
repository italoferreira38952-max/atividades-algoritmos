#include <stdio.h>
#include <stdlib.h>

struct No {
    int dado;
    struct No* prox;
};

struct Pilha {
    struct No* topo;
};

void adiciona(struct Pilha* pilha, int dado) {
    struct No* novo = (struct No*) malloc(sizeof(struct No));
    novo->dado = dado;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

int remover(struct Pilha* pilha, int* dado) {
    if (pilha->topo == NULL) return 0;
    struct No* temp = pilha->topo;
    *dado = temp->dado;
    pilha->topo = temp->prox;
    free(temp);
    return 1;
}

void mostrar(struct Pilha* pilha) {
    for (struct No* pi = pilha->topo; pi != NULL; pi = pi->prox) {
        printf("%d ", pi->dado);
    }
    printf("\n");
}

int main() {
    struct Pilha pilha = { NULL };
    int val;

    adiciona(&pilha, 10);
    adiciona(&pilha, 20);
    mostrar(&pilha);

    if (remover(&pilha, &val)) printf("Removido: %d\n", val);
    mostrar(&pilha);

    remover(&pilha, &val);
    if (!remover(&pilha, &val)) printf("Pilha vazia!\n");

    return 0;
}