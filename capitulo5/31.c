#define __USE_MINGW_ANSI_STDIO 1
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

/* ---------- Atividade 27: O(n^2) ---------- */

// Retorna a quantidade de pares (i < j) com v[i] + v[j] == alvo, ou -1 se a entrada for invalida
int pares_com_soma(const int *v, int n, int alvo, Contadores *c, int imprimir) {
    if (v == NULL || n < 2) {
        return -1;
    }
    int encontrados = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) { // j > i evita repeticao e o par de i consigo mesmo
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

/* ---------- Atividade 28: busca binaria O(log n) ---------- */

// Retorna 1 se o vetor estiver em ordem crescente (aceita repetidos), 0 caso contrario
int esta_ordenado(const int *v, int n) {
    for (int i = 1; i < n; i++) {
        if (v[i - 1] > v[i]) {
            return 0;
        }
    }
    return 1;
}

// Retorna a posicao de alvo, ou -1 se nao existir (ou se o vetor for invalido/desordenado).
// Cada passagem do laco conta 1 comparacao (v[meio] contra o alvo, decidindo
// entre igual, menor ou maior). Se imprimir != 0, mostra inicio, meio e fim de cada passagem.
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

// Retorna a PRIMEIRA posicao de alvo, ou -1 se nao existir. Funciona em qualquer sequencia.
// Mesma interface da busca binaria. Cada elemento examinado conta 1 comparacao.
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
            return i; // primeira ocorrencia: para ao encontrar
        }
    }
    return -1;
}

/* ---------- Atividade 30: recursao ---------- */

typedef struct {
    long chamadas;       // total de chamadas recursivas feitas
    int profundidade_max; // maior nivel de empilhamento atingido (a 1a chamada e o nivel 1)
} Recursao;

// Passo recursivo do fatorial: n! = n * (n-1)!
// Caso-base: n <= 1 devolve 1. Progresso: n diminui 1 por chamada, entao sempre chega ao caso-base.
static long long fatorial_aux(int n, Recursao *r, int nivel, int imprimir) {
    r->chamadas++;
    if (nivel > r->profundidade_max) {
        r->profundidade_max = nivel;
    }
    if (imprimir) {
        printf("%*schamada fatorial(%d) [nivel %d]\n", (nivel - 1) * 2, "", n, nivel);
    }
    long long resultado;
    if (n <= 1) {
        resultado = 1; // caso-base
    } else {
        resultado = n * fatorial_aux(n - 1, r, nivel + 1, imprimir);
    }
    if (imprimir) {
        printf("%*sretorna %lld (fatorial(%d))\n", (nivel - 1) * 2, "", resultado, n);
    }
    return resultado;
}

// Retorna 1 e grava o resultado em *saida; 0 se n < 0 ou n > 20 (20! e o maior que cabe em long long)
int fatorial_recursivo(int n, Recursao *r, long long *saida, int imprimir) {
    if (n < 0 || n > 20) {
        return 0;
    }
    *saida = fatorial_aux(n, r, 1, imprimir);
    return 1;
}

int fatorial_iterativo(int n, long *iteracoes, long long *saida) {
    if (n < 0 || n > 20) {
        return 0;
    }
    long long resultado = 1;
    for (int i = 2; i <= n; i++) {
        (*iteracoes)++;
        resultado *= i;
    }
    *saida = resultado;
    return 1;
}

// Soma os n primeiros elementos de v. Caso-base: n == 0 (nenhum elemento) devolve 0.
// Progresso: cada chamada trata v[n-1] e delega os n-1 restantes. Como n >= 1 fora do
// caso-base, o indice n-1 fica sempre entre 0 e o ultimo elemento do vetor.
static long soma_aux(const int *v, int n, Recursao *r, int nivel, int imprimir) {
    r->chamadas++;
    if (nivel > r->profundidade_max) {
        r->profundidade_max = nivel;
    }
    if (imprimir) {
        printf("%*schamada soma(n=%d) [nivel %d]\n", (nivel - 1) * 2, "", n, nivel);
    }
    long resultado;
    if (n == 0) {
        resultado = 0; // caso-base
    } else {
        resultado = v[n - 1] + soma_aux(v, n - 1, r, nivel + 1, imprimir);
    }
    if (imprimir) {
        printf("%*sretorna %ld (soma de %d elementos)\n", (nivel - 1) * 2, "", resultado, n);
    }
    return resultado;
}

// Retorna 1 e grava a soma em *saida; 0 se o vetor for nulo ou n < 0
int soma_recursiva(const int *v, int n, Recursao *r, long *saida, int imprimir) {
    if (v == NULL || n < 0) {
        return 0;
    }
    *saida = soma_aux(v, n, r, 1, imprimir);
    return 1;
}

int soma_iterativa(const int *v, int n, long *iteracoes, long *saida) {
    if (v == NULL || n < 0) {
        return 0;
    }
    long soma = 0;
    for (int i = 0; i < n; i++) {
        (*iteracoes)++;
        soma += v[i];
    }
    *saida = soma;
    return 1;
}

/* ---------- Atividade 31: recursao ramificada x recursao que escolhe uma metade ---------- */

#define LIMITE_FIB 35 // fib(35) ja passa de 29 milhoes de chamadas; acima disso a demonstracao ficaria lenta

// Fibonacci ingenuo: cada chamada gera DUAS chamadas menores (n-1 e n-2).
// Casos-base: n == 0 devolve 0 e n == 1 devolve 1. Sao necessarios dois, porque o passo
// recursivo recua 1 e 2 posicoes: so com n == 1, fib(2) chamaria fib(0), que chamaria fib(-1)... sem fim.
static long long fib_aux(int n, Recursao *r, int nivel, int imprimir) {
    r->chamadas++;
    if (nivel > r->profundidade_max) {
        r->profundidade_max = nivel;
    }
    if (imprimir) {
        printf("%*sfib(%d)\n", (nivel - 1) * 2, "", n);
    }
    if (n == 0) {
        return 0; // caso-base 1
    }
    if (n == 1) {
        return 1; // caso-base 2
    }
    return fib_aux(n - 1, r, nivel + 1, imprimir) + fib_aux(n - 2, r, nivel + 1, imprimir);
}

// Retorna 1 e grava o resultado em *saida; 0 se n < 0 ou n > LIMITE_FIB
int fibonacci_recursivo(int n, Recursao *r, long long *saida, int imprimir) {
    if (n < 0 || n > LIMITE_FIB) {
        return 0;
    }
    *saida = fib_aux(n, r, 1, imprimir);
    return 1;
}

int fibonacci_iterativo(int n, long *iteracoes, long long *saida) {
    if (n < 0 || n > LIMITE_FIB) {
        return 0;
    }
    long long anterior = 0, atual = 1;
    if (n == 0) {
        *saida = 0;
        return 1;
    }
    for (int i = 2; i <= n; i++) {
        (*iteracoes)++;
        long long proximo = anterior + atual;
        anterior = atual;
        atual = proximo;
    }
    *saida = atual;
    return 1;
}

// Busca binaria recursiva em v[inicio..fim]. Cada chamada escolhe UMA metade.
// Casos-base: intervalo vazio (inicio > fim) devolve -1; v[meio] == alvo devolve meio.
// Progresso: o intervalo encolhe pela metade, entao o caso "vazio" sempre e alcancado.
static int busca_bin_rec_aux(const int *v, int inicio, int fim, int alvo,
                             Recursao *r, int nivel, int imprimir) {
    r->chamadas++;
    if (nivel > r->profundidade_max) {
        r->profundidade_max = nivel;
    }
    if (inicio > fim) {
        if (imprimir) {
            printf("%*sinicio=%d fim=%d -> intervalo vazio (caso-base), devolve -1\n",
                   (nivel - 1) * 2, "", inicio, fim);
        }
        return -1; // caso-base 1
    }
    int meio = inicio + (fim - inicio) / 2;
    if (imprimir) {
        printf("%*sinicio=%d meio=%d fim=%d -> v[%d]=%d\n",
               (nivel - 1) * 2, "", inicio, meio, fim, meio, v[meio]);
    }
    if (v[meio] == alvo) {
        return meio; // caso-base 2
    }
    if (v[meio] < alvo) {
        return busca_bin_rec_aux(v, meio + 1, fim, alvo, r, nivel + 1, imprimir);
    }
    return busca_bin_rec_aux(v, inicio, meio - 1, alvo, r, nivel + 1, imprimir);
}

// Retorna a posicao de alvo ou -1 (ausente ou vetor invalido/desordenado)
int busca_binaria_recursiva(const int *v, int n, int alvo, Recursao *r, int imprimir) {
    if (v == NULL || n <= 0 || !esta_ordenado(v, n)) {
        return -1;
    }
    return busca_bin_rec_aux(v, 0, n - 1, alvo, r, 1, imprimir);
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

/* ---------- Dados compartilhados pelos experimentos ---------- */

static const int tamanhos[] = {10, 100, 1000, 10000};
static const int qtd = sizeof(tamanhos) / sizeof(tamanhos[0]);
static const int ord[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};
static const int n_ord = sizeof(ord) / sizeof(ord[0]);

void experimento_26_27(void) {
    /* ===== Atividades 26 e 27 ===== */
    printf("=== Atividades 26 e 27 ===\n");
    printf("%-8s | %-8s | %-11s | %-12s | %-8s\n",
           "n", "O(1)", "Maior O(n)", "Pares O(n^2)", "Pares");
    printf("---------+----------+-------------+--------------+---------\n");

    for (int t = 0; t < qtd; t++) {
        int n = tamanhos[t];
        int *v = malloc(n * sizeof(int));
        if (v == NULL) {
            fprintf(stderr, "Falha de alocacao\n");
            return;
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
    printf("Total: %d pares, %ld comparacoes (7*6/2 = 21)\n", total, c.comparacoes);
}

void experimento_28(void) {
    /* ===== Atividade 28: busca binaria ===== */
    printf("\n=== Atividade 28: busca binaria ===\n");

    // Vetor pequeno e ordenado para enxergar cada passagem
    printf("Vetor ordenado? %s\n", esta_ordenado(ord, n_ord) ? "sim" : "nao");

    int alvos[] = {23, 2, 91, 50}; // meio, primeiro, ultimo, ausente
    for (int k = 0; k < 4; k++) {
        Contadores cb = {0, 0};
        printf("\nBuscando %d:\n", alvos[k]);
        int pos = busca_binaria(ord, n_ord, alvos[k], &cb, 1);
        if (pos >= 0) {
            printf("  Encontrado na posicao %d com %ld comparacoes\n", pos, cb.comparacoes);
        } else {
            printf("  Nao encontrado (-1) com %ld comparacoes\n", cb.comparacoes);
        }
    }

    // Vetor desordenado deve ser rejeitado
    Contadores cd = {0, 0};
    int desordenado[] = {5, 1, 4, 2, 3};
    printf("\nVetor desordenado {5, 1, 4, 2, 3}: busca por 4 devolve %d (rejeitado)\n",
           busca_binaria(desordenado, 5, 4, &cd, 0));

    // Crescimento do custo com n: pior caso (valor ausente maior que todos)
    printf("\n%-8s | %-12s | %-14s | %-12s\n",
           "n", "Linear (n)", "Binaria", "floor(log2 n)+1");
    printf("---------+--------------+----------------+----------------\n");
    for (int t = 0; t < qtd; t++) {
        int n = tamanhos[t];
        int *v = malloc(n * sizeof(int));
        if (v == NULL) {
            fprintf(stderr, "Falha de alocacao\n");
            return;
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
}

void experimento_29(void) {
    /* ===== Atividade 29: linear x binaria ===== */
    printf("\n=== Atividade 29: busca linear x busca binaria ===\n");

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

    // Custo observado conforme n cresce (vetor ordenado, inicio/meio/fim/ausente)
    printf("\nComparacoes (inicio/meio/fim/ausente) conforme n cresce:\n");
    printf("%-8s | %-29s | %-24s\n", "n", "Linear", "Binaria");
    printf("---------+-------------------------------+-------------------------\n");
    for (int t = 0; t < qtd; t++) {
        int n = tamanhos[t];
        int *v = malloc(n * sizeof(int));
        if (v == NULL) {
            fprintf(stderr, "Falha de alocacao\n");
            return;
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

    // Vetor SEM ordenacao e com repetidos: so a linear pode ser aplicada
    int sem_ordem[] = {42, 7, 19, 7, 88, 25, 61, 10};
    int n_sem = sizeof(sem_ordem) / sizeof(sem_ordem[0]);
    printf("\nVetor sem ordenacao {42, 7, 19, 7, 88, 25, 61, 10}:\n");
    int ordenado = esta_ordenado(sem_ordem, n_sem);
    printf("Vetor ordenado? %s -> busca binaria %s\n", ordenado ? "sim" : "nao",
           ordenado ? "permitida" : "NAO aplicavel (resultado nao seria confiavel)");
    int alvos_sem[] = {7, 61, 99};
    for (int k = 0; k < 3; k++) {
        Contadores cl = {0, 0};
        int pl = busca_linear(sem_ordem, n_sem, alvos_sem[k], &cl, 0);
        if (pl >= 0) {
            printf("  Linear: %d na posicao %d com %ld comparacoes%s\n", alvos_sem[k], pl, cl.comparacoes,
                   alvos_sem[k] == 7 ? " (primeira ocorrencia; ha outro 7 na posicao 3)" : "");
        } else {
            printf("  Linear: %d ausente (-1) com %ld comparacoes\n", alvos_sem[k], cl.comparacoes);
        }
    }

    printf("\nPre-condicoes:\n"
           "  Linear:  nenhuma sobre a ordem; so precisa de vetor valido (nao nulo, n > 0). Custo O(n).\n"
           "  Binaria: vetor ordenado (ordenar custa mais, ~O(n log n), ou o vetor ja deve chegar ordenado)\n"
           "           e acesso direto por indice. Custo O(log n) por busca.\n"
           "Se ha poucas buscas e os dados nao estao ordenados, a linear costuma compensar;\n"
           "se ha muitas buscas sobre dados ordenados, a binaria ganha cada vez mais.\n");
}

void experimento_30(void) {
    /* ===== Atividade 30: recursao ===== */
    printf("\n=== Atividade 30: recursao x iteracao ===\n");

    // Rastro: a descida (chamadas) e a volta (retornos) do fatorial
    printf("\nRastro de fatorial(4):\n");
    Recursao r_demo = {0, 0};
    long long f_demo = 0;
    fatorial_recursivo(4, &r_demo, &f_demo, 1);
    printf("Resultado: %lld | chamadas: %ld | profundidade maxima: %d\n",
           f_demo, r_demo.chamadas, r_demo.profundidade_max);

    // Rastro da soma sobre um vetor pequeno
    int pequeno[] = {3, 8, 1, 4};
    printf("\nRastro da soma de {3, 8, 1, 4}:\n");
    Recursao r_soma = {0, 0};
    long s_demo = 0;
    soma_recursiva(pequeno, 4, &r_soma, &s_demo, 1);
    printf("Resultado: %ld | chamadas: %ld | profundidade maxima: %d\n",
           s_demo, r_soma.chamadas, r_soma.profundidade_max);

    // Fatorial: recursivo x iterativo (inclui bordas 0 e 1)
    printf("\nFatorial: recursivo x iterativo\n");
    printf("%-4s | %-20s | %-20s | %-6s | %-9s | %-12s | %-10s\n",
           "n", "Recursivo", "Iterativo", "Igual?", "Chamadas", "Profundidade", "Iteracoes");
    printf("-----+----------------------+----------------------+--------+-----------+--------------+-----------\n");
    int ns_fat[] = {0, 1, 5, 10, 20};
    for (int k = 0; k < 5; k++) {
        Recursao rr = {0, 0};
        long iter = 0;
        long long fr = 0, fi = 0;
        fatorial_recursivo(ns_fat[k], &rr, &fr, 0);
        fatorial_iterativo(ns_fat[k], &iter, &fi);
        printf("%-4d | %-20lld | %-20lld | %-6s | %-9ld | %-12d | %-10ld\n",
               ns_fat[k], fr, fi, fr == fi ? "sim" : "NAO", rr.chamadas, rr.profundidade_max, iter);
    }
    long long invalido = 0;
    Recursao r_inv = {0, 0};
    printf("fatorial(-3): %s\n", fatorial_recursivo(-3, &r_inv, &invalido, 0) ? "calculou" : "rejeitado (entrada negativa)");

    // Soma de vetor: recursiva x iterativa
    printf("\nSoma do vetor: recursiva x iterativa\n");
    printf("%-8s | %-12s | %-12s | %-6s | %-9s | %-12s | %-10s\n",
           "n", "Recursiva", "Iterativa", "Igual?", "Chamadas", "Profundidade", "Iteracoes");
    printf("---------+--------------+--------------+--------+-----------+--------------+-----------\n");
    int ns_soma[] = {0, 10, 100, 1000, 10000};
    for (int k = 0; k < 5; k++) {
        int n = ns_soma[k];
        int *v = malloc((n > 0 ? n : 1) * sizeof(int));
        if (v == NULL) {
            fprintf(stderr, "Falha de alocacao\n");
            return;
        }
        for (int i = 0; i < n; i++) {
            v[i] = (i * 37) % 1009;
        }
        Recursao rr = {0, 0};
        long iter = 0, sr = 0, si = 0;
        soma_recursiva(v, n, &rr, &sr, 0);
        soma_iterativa(v, n, &iter, &si);
        printf("%-8d | %-12ld | %-12ld | %-6s | %-9ld | %-12d | %-10ld\n",
               n, sr, si, sr == si ? "sim" : "NAO", rr.chamadas, rr.profundidade_max, iter);
        free(v);
    }
    Recursao r_nulo = {0, 0};
    long s_nulo = 0;
    printf("soma com vetor nulo: %s\n", soma_recursiva(NULL, 5, &r_nulo, &s_nulo, 0) ? "calculou" : "rejeitada");

    printf("\nRecursao: toda chamada precisa de caso-base alcancavel e de um argumento menor.\n"
           "Aqui cada chamada reduz o problema em 1, entao a soma faz n+1 chamadas (n elementos + o caso-base)\n"
           "e chega a profundidade n+1; o fatorial de n>=1 faz n chamadas e chega a profundidade n.\n"
           "O resultado fica igual ao da versao iterativa e o custo tambem fica O(n), mas a recursiva gasta\n"
           "memoria de pilha proporcional a profundidade (O(n)), enquanto a iterativa usa O(1) de memoria extra.\n"
           "Por isso, para n muito grande (centenas de milhares de elementos), a recursao linear pode estourar a pilha.\n");
}

void experimento_31(void) {
    printf("\n=== Atividade 31: recursao ramificada x busca binaria recursiva ===\n");

    // Rastro da arvore de chamadas do Fibonacci
    printf("\nArvore de chamadas de fib(4):\n");
    Recursao r_arv = {0, 0};
    long long f_arv = 0;
    fibonacci_recursivo(4, &r_arv, &f_arv, 1);
    printf("Resultado: %lld | chamadas: %ld | profundidade maxima: %d\n",
           f_arv, r_arv.chamadas, r_arv.profundidade_max);

    // Fibonacci: crescimento das chamadas
    printf("\nFibonacci ingenuo (entrada limitada a 0..%d):\n", LIMITE_FIB);
    printf("%-4s | %-10s | %-12s | %-16s | %-12s | %-10s\n",
           "n", "Resultado", "Chamadas", "2*fib(n+1)-1", "Profundidade", "Iterativo");
    printf("-----+------------+--------------+------------------+--------------+-----------\n");
    int ns_fib[] = {0, 1, 5, 10, 20, 30};
    for (int k = 0; k < 6; k++) {
        int n = ns_fib[k];
        Recursao rr = {0, 0};
        long iter = 0, iter_aux = 0;
        long long fr = 0, fi = 0, fprox = 0;
        fibonacci_recursivo(n, &rr, &fr, 0);
        fibonacci_iterativo(n, &iter, &fi);
        fibonacci_iterativo(n + 1, &iter_aux, &fprox);
        printf("%-4d | %-10lld | %-12ld | %-16lld | %-12d | %-3ld iter %s\n",
               n, fr, rr.chamadas, 2 * fprox - 1, rr.profundidade_max, iter, fr == fi ? "(igual)" : "(DIFERENTE)");
    }
    Recursao r_lim = {0, 0};
    long long f_lim = 0;
    printf("fib(%d): %s\n", LIMITE_FIB + 5,
           fibonacci_recursivo(LIMITE_FIB + 5, &r_lim, &f_lim, 0) ? "calculou" : "rejeitado (acima do limite)");
    printf("fib(-1): %s\n",
           fibonacci_recursivo(-1, &r_lim, &f_lim, 0) ? "calculou" : "rejeitado (entrada negativa)");

    // Busca binaria recursiva: rastro com inicio/fim
    printf("\nBusca binaria recursiva no vetor ordenado de %d elementos:\n", n_ord);
    int alvos31[] = {23, 2, 50};
    for (int k = 0; k < 3; k++) {
        Recursao rb = {0, 0};
        printf("\nBuscando %d:\n", alvos31[k]);
        int pos = busca_binaria_recursiva(ord, n_ord, alvos31[k], &rb, 1);
        printf("Resultado: %d | chamadas: %ld | profundidade maxima: %d\n",
               pos, rb.chamadas, rb.profundidade_max);
    }

    // Comparacao de custo
    printf("\nBinaria recursiva x iterativa (valor ausente, pior caso):\n");
    printf("%-8s | %-10s | %-12s | %-18s | %-8s\n",
           "n", "Chamadas", "Profundidade", "Comparacoes (iter)", "Mesma pos?");
    printf("---------+------------+--------------+--------------------+----------\n");
    for (int t = 0; t < qtd; t++) {
        int n = tamanhos[t];
        int *v = malloc(n * sizeof(int));
        if (v == NULL) {
            fprintf(stderr, "Falha de alocacao\n");
            return;
        }
        for (int i = 0; i < n; i++) {
            v[i] = i * 3;
        }
        Recursao rb = {0, 0};
        Contadores ci = {0, 0};
        int alvo = v[n - 1] + 1;
        int pr = busca_binaria_recursiva(v, n, alvo, &rb, 0);
        int pi = busca_binaria(v, n, alvo, &ci, 0);
        printf("%-8d | %-10ld | %-12d | %-18ld | %-8s\n",
               n, rb.chamadas, rb.profundidade_max, ci.comparacoes, pr == pi ? "sim" : "NAO");
        free(v);
    }

    printf("\nComparando os custos:\n"
           "  Fibonacci ingenuo: cada chamada gera 2 subproblemas que se sobrepoem, entao as chamadas\n"
           "  crescem exponencialmente (~1,6x por unidade de n): fib(30) faz mais de 2,6 milhoes de chamadas.\n"
           "  Busca binaria recursiva: cada chamada escolhe 1 metade, entao as chamadas crescem com log2(n):\n"
           "  para n = 10000 sao so 15 chamadas no pior caso.\n"
           "  Casos-base: no Fibonacci (n == 0 e n == 1) param os dois ramos do recuo de 1 e 2; na busca binaria\n"
           "  (intervalo vazio e valor encontrado) garantem o fim da busca com resultado -1 ou posicao.\n"
           "  A profundidade da pilha e pequena nos dois casos (n no Fibonacci, ~log2 n na busca);\n"
           "  o problema do Fibonacci e o numero de chamadas, nao a pilha.\n");
}

void conclusao_geral(void) {
    printf("\nConclusao: o acesso direto e O(1) e a busca do maior e O(n).\n"
           "Os pares fazem n(n-1)/2 comparacoes: 10x mais dados, cerca de 100x mais trabalho -> O(n^2).\n"
           "Na busca binaria cada comparacao descarta metade do intervalo: n -> n/2 -> n/4 -> ... -> 1.\n"
           "Sao no maximo floor(log2 n)+1 passagens, entao 10x mais dados custam so ~3 comparacoes a mais -> O(log n).\n"
           "Recursao linear (fatorial, soma): n chamadas, custo O(n) com pilha O(n).\n"
           "Recursao ramificada (Fibonacci ingenuo): chamadas exponenciais. Recursao que escolhe uma metade\n"
           "(busca binaria): chamadas O(log n).\n");
}

static void mostrar_menu(void) {
    printf("\n===== Laboratorio de complexidade =====\n"
           " 1) Atividades 26 e 27: O(1), O(n) e O(n^2)\n"
           " 2) Atividade 28: busca binaria iterativa\n"
           " 3) Atividade 29: busca linear x busca binaria\n"
           " 4) Atividade 30: recursao simples x iteracao\n"
           " 5) Atividade 31: Fibonacci ingenuo x busca binaria recursiva\n"
           " 6) Executar todos os experimentos\n"
           " 0) Sair\n"
           "Escolha: ");
}

int main(void) {
    char linha[64];
    int opcao = -1;

    while (opcao != 0) {
        mostrar_menu();
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            printf("\n");
            break; // fim da entrada (Ctrl+D)
        }
        char *fim_num = NULL;
        long lido = strtol(linha, &fim_num, 10);
        if (fim_num == linha) {
            printf("Entrada invalida: digite um numero de 0 a 6.\n");
            continue;
        }
        opcao = (int)lido;

        switch (opcao) {
            case 1: experimento_26_27(); break;
            case 2: experimento_28(); break;
            case 3: experimento_29(); break;
            case 4: experimento_30(); break;
            case 5: experimento_31(); break;
            case 6:
                experimento_26_27();
                experimento_28();
                experimento_29();
                experimento_30();
                experimento_31();
                conclusao_geral();
                break;
            case 0: printf("Ate logo!\n"); break;
            default: printf("Opcao invalida: digite um numero de 0 a 6.\n");
        }
    }
    return 0;
}