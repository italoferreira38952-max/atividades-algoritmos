#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long acessos;
    long comparacoes;
} Contadores;

/* ---------- Atividade 26: O(1) e O(n) ---------- */

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

/* ---------- Atividade 27: O(n²) ---------- */

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

/* ---------- Atividade 28: busca binária O(log n) ---------- */

// Retorna 1 se o vetor está em ordem crescente (aceita repetidos), 0 caso contrário
int esta_ordenado(const int *v, int n) {
    for (int i = 1; i < n; i++) {
        if (v[i - 1] > v[i]) {
            return 0;
        }
    }
    return 1;
}

// Retorna a posição de alvo, ou -1 se não existir (ou se o vetor for inválido/desordenado).
// Cada passagem do laço conta 1 comparação (v[meio] contra o alvo, decidindo
// entre igual, menor ou maior). Se imprimir != 0, mostra início, meio e fim de cada passagem.
int busca_binaria(const int *v, int n, int alvo, Contadores *c, int imprimir) {
    if (v == NULL || n <= 0 || !esta_ordenado(v, n)) {
        return -1;
    }
    int inicio = 0;
    int fim = n - 1;

    while (inicio <= fim) { // termina quando o intervalo fica vazio
        int meio = inicio + (fim - inicio) / 2; // evita overflow de (inicio + fim) e nunca sai de [inicio, fim]
        c->comparacoes++;
        if (imprimir) {
            printf("  inicio=%d meio=%d fim=%d -> v[%d]=%d\n", inicio, meio, fim, meio, v[meio]);
        }
        if (v[meio] == alvo) {
            return meio;
        } else if (v[meio] < alvo) {
            inicio = meio + 1; // descarta a metade esquerda e o meio
        } else {
            fim = meio - 1; // descarta a metade direita e o meio
        }
    }
    return -1;
}

/* ---------- Atividade 29: busca linear ---------- */

// Retorna a PRIMEIRA posição de alvo, ou -1 se não existir. Funciona em qualquer sequência.
// Mesma interface da busca binária. Cada elemento examinado conta 1 comparação.
int busca_linear(const int *v, int n, int alvo, Contadores *c, int imprimir) {
    if (v == NULL || n <= 0) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        c->comparacoes++;
        if (imprimir) {
            printf("  posicao=%d -> v[%d]=%d\n", i, i, v[i]);
        }
        if (v[i] == alvo) {
            return i; // primeira ocorrência: para ao encontrar
        }
    }
    return -1;
}

// floor(log2(n)) sem usar math.h
int piso_log2(int n) {
    int r = 0;
    while (n > 1) {
        n /= 2;
        r++;
    }
    return r;
}

int main(void) {
    int tamanhos[] = {10, 100, 1000, 10000};
    int qtd = sizeof(tamanhos) / sizeof(tamanhos[0]);

    /* ===== Atividades 26 e 27 ===== */
    printf("=== Atividades 26 e 27 ===\n");
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

    /* ===== Atividade 28: busca binária ===== */
    printf("\n=== Atividade 28: busca binária ===\n");

    // Vetor pequeno e ordenado para enxergar cada passagem
    int ord[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};
    int n_ord = sizeof(ord) / sizeof(ord[0]);
    printf("Vetor ordenado? %s\n", esta_ordenado(ord, n_ord) ? "sim" : "não");

    int alvos[] = {23, 2, 91, 50}; // meio, primeiro, último, ausente
    for (int k = 0; k < 4; k++) {
        Contadores cb = {0, 0};
        printf("\nBuscando %d:\n", alvos[k]);
        int pos = busca_binaria(ord, n_ord, alvos[k], &cb, 1);
        if (pos >= 0) {
            printf("  Encontrado na posição %d com %ld comparações\n", pos, cb.comparacoes);
        } else {
            printf("  Não encontrado (-1) com %ld comparações\n", cb.comparacoes);
        }
    }

    // Vetor desordenado deve ser rejeitado
    Contadores cd = {0, 0};
    int desordenado[] = {5, 1, 4, 2, 3};
    printf("\nVetor desordenado {5, 1, 4, 2, 3}: busca por 4 devolve %d (rejeitado)\n",
           busca_binaria(desordenado, 5, 4, &cd, 0));

    // Crescimento do custo com n: pior caso (valor ausente maior que todos)
    printf("\n%-8s | %-12s | %-14s | %-12s\n",
           "n", "Linear (n)", "Binária", "floor(log2 n)+1");
    printf("---------+--------------+----------------+----------------\n");
    for (int t = 0; t < qtd; t++) {
        int n = tamanhos[t];
        int *v = malloc(n * sizeof(int));
        if (v == NULL) {
            fprintf(stderr, "Falha de alocação\n");
            return 1;
        }
        for (int i = 0; i < n; i++) {
            v[i] = i * 3; // ordenado e com "buracos" para testar ausentes
        }

        Contadores c_pres = {0, 0};
        Contadores c_aus = {0, 0};
        int presente = busca_binaria(v, n, v[n / 3], &c_pres, 0);
        int ausente = busca_binaria(v, n, v[n - 1] + 1, &c_aus, 0);

        printf("%-8d | %-12d | %-14ld | %-12d  (presente: pos %d com %ld; ausente: %d)\n",
               n, n, c_aus.comparacoes, piso_log2(n) + 1, presente, c_pres.comparacoes, ausente);
        free(v);
    }

    /* ===== Atividade 29: linear x binária ===== */
    printf("\n=== Atividade 29: busca linear x busca binária ===\n");

    // Mesmos valores, mesmo vetor ordenado, contadores lado a lado
    printf("\nVetor ordenado de %d elementos (mesmos alvos nas duas buscas):\n", n_ord);
    printf("%-6s | %-8s | %-18s | %-18s\n", "Alvo", "Caso", "Linear (pos/comp)", "Binaria (pos/comp)");
    printf("-------+----------+--------------------+-------------------\n");
    int alvos29[] = {2, 23, 91, 50};
    const char *casos[] = {"primeiro", "meio", "ultimo", "ausente"};
    for (int k = 0; k < 4; k++) {
        Contadores cl = {0, 0};
        Contadores cb = {0, 0};
        int pl = busca_linear(ord, n_ord, alvos29[k], &cl, 0);
        int pb = busca_binaria(ord, n_ord, alvos29[k], &cb, 0);
        printf("%-6d | %-8s | %5d / %-11ld | %5d / %-11ld\n",
               alvos29[k], casos[k], pl, cl.comparacoes, pb, cb.comparacoes);
    }

    // Custo observado conforme n cresce (vetor ordenado, início/meio/fim/ausente)
    printf("\nComparações (início/meio/fim/ausente) conforme n cresce:\n");
    printf("%-8s | %-29s | %-24s\n", "n", "Linear", "Binaria");
    printf("---------+-------------------------------+-------------------------\n");
    for (int t = 0; t < qtd; t++) {
        int n = tamanhos[t];
        int *v = malloc(n * sizeof(int));
        if (v == NULL) {
            fprintf(stderr, "Falha de alocação\n");
            return 1;
        }
        for (int i = 0; i < n; i++) {
            v[i] = i * 3;
        }
        int alvos_n[4] = {v[0], v[n / 2], v[n - 1], v[n - 1] + 1};
        long lin[4], bin[4];
        for (int k = 0; k < 4; k++) {
            Contadores cl = {0, 0};
            Contadores cb = {0, 0};
            busca_linear(v, n, alvos_n[k], &cl, 0);
            busca_binaria(v, n, alvos_n[k], &cb, 0);
            lin[k] = cl.comparacoes;
            bin[k] = cb.comparacoes;
        }
        printf("%-8d | %-6ld/%-6ld/%-6ld/%-6ld | %-3ld/%-3ld/%-3ld/%-3ld\n", n,
               lin[0], lin[1], lin[2], lin[3], bin[0], bin[1], bin[2], bin[3]);
        free(v);
    }

    // Vetor SEM ordenação e com repetidos: só a linear pode ser aplicada
    int sem_ordem[] = {42, 7, 19, 7, 88, 25, 61, 10};
    int n_sem = sizeof(sem_ordem) / sizeof(sem_ordem[0]);
    printf("\nVetor sem ordenação {42, 7, 19, 7, 88, 25, 61, 10}:\n");
    int ordenado = esta_ordenado(sem_ordem, n_sem);
    printf("Vetor ordenado? %s -> busca binária %s\n", ordenado ? "sim" : "não",
           ordenado ? "permitida" : "NÃO aplicável (resultado não seria confiável)");
    int alvos_sem[] = {7, 61, 99};
    for (int k = 0; k < 3; k++) {
        Contadores cl = {0, 0};
        int pl = busca_linear(sem_ordem, n_sem, alvos_sem[k], &cl, 0);
        if (pl >= 0) {
            printf("  Linear: %d na posição %d com %ld comparações%s\n", alvos_sem[k], pl, cl.comparacoes,
                   alvos_sem[k] == 7 ? " (primeira ocorrência; há outro 7 na posição 3)" : "");
        } else {
            printf("  Linear: %d ausente (-1) com %ld comparações\n", alvos_sem[k], cl.comparacoes);
        }
    }

    printf("\nPré-condições:\n"
           "  Linear:  nenhuma sobre a ordem; só precisa de vetor válido (não nulo, n > 0). Custo O(n).\n"
           "  Binária: vetor ordenado (ordenar custa mais, ~O(n log n), ou o vetor já deve chegar ordenado)\n"
           "           e acesso direto por índice. Custo O(log n) por busca.\n"
           "Se há poucas buscas e os dados não estão ordenados, a linear costuma compensar;\n"
           "se há muitas buscas sobre dados ordenados, a binária ganha cada vez mais.\n");

    printf("\nConclusão: o acesso direto é O(1) e a busca do maior é O(n).\n"
           "Os pares fazem n(n-1)/2 comparações: 10x mais dados, cerca de 100x mais trabalho -> O(n²).\n"
           "Na busca binária cada comparação descarta metade do intervalo: n -> n/2 -> n/4 -> ... -> 1.\n"
           "São no máximo floor(log2 n)+1 passagens, então 10x mais dados custam só ~3 comparações a mais -> O(log n).\n");
    return 0;
}