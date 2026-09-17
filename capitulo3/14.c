#include <stdio.h>
#include <stdlib.h>

void imprimir(int *v, int cap) {
    for (int i = 0; i < cap; i++) printf("%d ", v[i]);
    printf("(capacidade: %d)\n", cap);
}

int redimensionar(int **v, int *capAtual, int novaCap) {
    if (novaCap <= 0) {
        printf("Capacidade invalida.\n");
        return 0;
    }

    int capAnterior = *capAtual;
    int *temp = realloc(*v, novaCap * sizeof(int));
    if (temp == NULL) {
        printf("Falha ao realocar. Vetor original preservado.\n");
        return 0;
    }

    for (int i = capAnterior; i < novaCap; i++) temp[i] = 0;

    *v = temp;
    *capAtual = novaCap;
    printf("Capacidade: %d -> %d\n", capAnterior, novaCap);
    return 1;
}

int lerInteiro(const char *prompt) {
    int valor;
    printf("%s", prompt);
    scanf("%d", &valor);
    return valor;
}

int main(void) {
    int cap = lerInteiro("Capacidade inicial do catalogo: ");
    if (cap <= 0) {
        printf("Capacidade inicial invalida.\n");
        return 1;
    }

    int *personagens = calloc(cap, sizeof(int));
    if (!personagens) return 1;

    printf("Inicial: ");
    imprimir(personagens, cap);

    int novaCap = lerInteiro("Nova capacidade (crescer ou reduzir): ");
    redimensionar(&personagens, &cap, novaCap);
    imprimir(personagens, cap);

    novaCap = lerInteiro("Nova capacidade novamente: ");
    redimensionar(&personagens, &cap, novaCap);
    imprimir(personagens, cap);

    free(personagens);
    return 0;
}