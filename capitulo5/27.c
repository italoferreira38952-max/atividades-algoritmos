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

// Retorna a quantidade de pares (i < j) com v[i] + v[j] == alvo, ou -1 se a entrada for inválida
int pares_com_soma(const int *v, int n, int alvo, Contadores *c, int imprimir) {
    if (v == NULL || n < 2) {
        return -1;
    }
    int encontrados = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) { // j > i evita repetição e o par de i consigo mesmo
            c->comparacoes++;
            if (v[i] + v[j] == alvo) {
                encontrados++;
                if (imprimir) {
                    printf("  (v[%d]=%d, v[%d]=%d)\n", i, v[i], j, v[j]);
                }
            }
        }
    }
    return encontrados;
}

int main(void) {
    int tamanhos[] = {10, 100, 1000, 10000};
    int qtd = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("%-8s | %-8s | %-11s | %-12s | %-8s\n",
           "n", "O(1)", "Maior O(n)", "Pares O(n²)", "Pares");
    printf("---------+----------+-------------+--------------+---------\n");

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
        Contadores c_pares = {0, 0};
        int valor = 0, maior = 0;

        acesso_direto(v, n, n / 2, &c_acesso, &valor);
        maior_valor(v, n, &c_busca, &maior);
        int pares = pares_com_soma(v, n, 1000, &c_pares, 0);

        printf("%-8d | %-8ld | %-11ld | %-12ld | %-8d\n",
               n, c_acesso.acessos, c_busca.comparacoes, c_pares.comparacoes, pares);
        free(v);
    }

    int demo[] = {1, 4, 6, 3, 5, 7, 2};
    Contadores c = {0, 0};
    printf("\nPares com soma 8 em {1, 4, 6, 3, 5, 7, 2}:\n");
    int total = pares_com_soma(demo, 7, 8, &c, 1);
    printf("Total: %d pares, %ld comparações (7*6/2 = 21)\n", total, c.comparacoes);

    printf("\nConclusão: o acesso direto é O(1) e a busca do maior é O(n).\n"
           "Os pares fazem n(n-1)/2 comparações: 10x mais dados, cerca de 100x mais trabalho -> O(n²).\n");
    return 0;
}