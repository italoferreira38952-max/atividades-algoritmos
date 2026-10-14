#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long acessos;
    long comparacoes;
} Contadores;

int acesso_direto(const int *v, int n, int indice, Contadores *c, int *saida) {
    if (v == NULL || indice < 0 || indice >= n) {
        return 0;
    }
    *saida = v[indice];
    c->acessos++; // sempre 1, independente de n
    return 1;
}

int maior_valor(const int *v, int n, Contadores *c, int *maior) {
    if (v == NULL || n <= 0) {
        return 0;
    }
    *maior = v[0];
    c->acessos++;
    for (int i = 1; i < n; i++) {
        c->acessos++;
        c->comparacoes++;
        if (v[i] > *maior) {
            *maior = v[i];
        }
    }
    return 1;
}

int main(void) {
    int tamanhos[] = {10, 100, 1000, 10000};
    int qtd = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("%-8s | %-22s | %-32s\n", "n", "Acesso direto", "Busca do maior");
    printf("%-8s | %-10s %-11s | %-10s %-11s %-8s\n",
           "", "acessos", "comparações", "acessos", "comparações", "maior");
    printf("---------+------------------------+---------------------------------\n");

    for (int t = 0; t < qtd; t++) {
        int n = tamanhos[t];
        int *v = malloc(n * sizeof(int));
        if (v == NULL) {
            fprintf(stderr, "Falha de alocação\n");
            return 1;
        }
        for (int i = 0; i < n; i++) {
            v[i] = (i * 37) % 1009;
        }

        Contadores c_acesso = {0, 0}; // contadores independentes
        Contadores c_busca = {0, 0};
        int valor = 0, maior = 0;

        acesso_direto(v, n, n / 2, &c_acesso, &valor);
        maior_valor(v, n, &c_busca, &maior);

        printf("%-8d | %-10ld %-11ld | %-10ld %-11ld %-8d\n",
               n, c_acesso.acessos, c_acesso.comparacoes,
               c_busca.acessos, c_busca.comparacoes, maior);
        free(v);
    }

    int v[3] = {1, 2, 3}, x;
    Contadores c = {0, 0};
    printf("\nÍndice 5 em vetor de 3: %s\n",
           acesso_direto(v, 3, 5, &c, &x) ? "aceito" : "rejeitado");
    printf("Índice -1 em vetor de 3: %s\n",
           acesso_direto(v, 3, -1, &c, &x) ? "aceito" : "rejeitado");

    printf("\nConclusão: o acesso direto fica em 1 acesso para qualquer n -> O(1).\n"
           "A busca do maior faz n acessos e n-1 comparações, crescendo junto com n -> O(n).\n");
    return 0;
}