#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50
#define TAM_MAX 64

#define NUMEROS 1
#define JOGADORES 2

#define INSERTION 1
#define BUBBLE 2
#define MERGE 3
#define QUICK 4

typedef struct {
    int id;
    char nome[30];
    int pontuacao;
} Jogador;

typedef struct {
    int comparacoes;
    int trocas;
    int deslocamentos;
} Metricas;

typedef struct {
    int tipo;
    int n;
    int numeros[MAX];
    Jogador jogadores[MAX];
} Dados;

typedef int (*Comparador)(const void *a, const void *b);

int comparar_int(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

int comparar_jogador(const void *a, const void *b) {
    const Jogador *x = a;
    const Jogador *y = b;

    int r = strcmp(x->nome, y->nome);
    if (r != 0) {
        return r;
    }
    return x->id - y->id;
}

void trocar(char *a, char *b, size_t tam) {
    char temp[TAM_MAX];

    memcpy(temp, a, tam);
    memcpy(a, b, tam);
    memcpy(b, temp, tam);
}

void insertion_sort(void *base, int n, size_t tam, Comparador cmp, Metricas *m) {
    char *v = base;
    char temp[TAM_MAX];

    for (int i = 1; i < n; i++) {
        memcpy(temp, v + i * tam, tam);
        int j = i - 1;

        while (j >= 0) {
            m->comparacoes++;
            if (cmp(v + j * tam, temp) > 0) {
                memcpy(v + (j + 1) * tam, v + j * tam, tam);
                m->deslocamentos++;
                j--;
            } else {
                break;
            }
        }

        memcpy(v + (j + 1) * tam, temp, tam);
    }
}

void bubble_sort(void *base, int n, size_t tam, Comparador cmp, Metricas *m) {
    char *v = base;
    int fim = n - 1;
    int trocou = 1;

    while (trocou && fim > 0) {
        trocou = 0;

        for (int i = 0; i < fim; i++) {
            m->comparacoes++;
            if (cmp(v + i * tam, v + (i + 1) * tam) > 0) {
                trocar(v + i * tam, v + (i + 1) * tam, tam);
                m->trocas++;
                trocou = 1;
            }
        }

        fim--;
    }
}

void intercalar(char *v, char *aux, int inicio, int meio, int fim,
                size_t tam, Comparador cmp, Metricas *m) {
    int i = inicio;
    int j = meio + 1;
    int k = inicio;

    while (i <= meio && j <= fim) {
        m->comparacoes++;
        if (cmp(v + i * tam, v + j * tam) <= 0) {
            memcpy(aux + k * tam, v + i * tam, tam);
            i++;
        } else {
            memcpy(aux + k * tam, v + j * tam, tam);
            j++;
        }
        m->deslocamentos++;
        k++;
    }

    while (i <= meio) {
        memcpy(aux + k * tam, v + i * tam, tam);
        m->deslocamentos++;
        i++;
        k++;
    }

    while (j <= fim) {
        memcpy(aux + k * tam, v + j * tam, tam);
        m->deslocamentos++;
        j++;
        k++;
    }

    memcpy(v + inicio * tam, aux + inicio * tam, (fim - inicio + 1) * tam);
}

void merge_sort_rec(char *v, char *aux, int inicio, int fim,
                    size_t tam, Comparador cmp, Metricas *m) {
    if (inicio >= fim) {
        return;
    }

    int meio = inicio + (fim - inicio) / 2;

    merge_sort_rec(v, aux, inicio, meio, tam, cmp, m);
    merge_sort_rec(v, aux, meio + 1, fim, tam, cmp, m);
    intercalar(v, aux, inicio, meio, fim, tam, cmp, m);
}

int merge_sort(void *base, int n, size_t tam, Comparador cmp, Metricas *m) {
    if (n <= 1) {
        return 1;
    }

    char *aux = malloc(n * tam);
    if (aux == NULL) {
        return 0;
    }

    merge_sort_rec(base, aux, 0, n - 1, tam, cmp, m);

    free(aux);
    return 1;
}

int particionar(char *v, int inicio, int fim, size_t tam, Comparador cmp, Metricas *m) {
    int p = inicio + rand() % (fim - inicio + 1);

    if (p != fim) {
        trocar(v + p * tam, v + fim * tam, tam);
        m->trocas++;
    }

    int i = inicio;

    for (int j = inicio; j < fim; j++) {
        m->comparacoes++;
        if (cmp(v + j * tam, v + fim * tam) < 0) {
            if (i != j) {
                trocar(v + i * tam, v + j * tam, tam);
                m->trocas++;
            }
            i++;
        }
    }

    if (i != fim) {
        trocar(v + i * tam, v + fim * tam, tam);
        m->trocas++;
    }

    return i;
}

void quick_sort_rec(char *v, int inicio, int fim, size_t tam, Comparador cmp, Metricas *m) {
    if (inicio >= fim) {
        return;
    }

    int p = particionar(v, inicio, fim, tam, cmp, m);

    quick_sort_rec(v, inicio, p - 1, tam, cmp, m);
    quick_sort_rec(v, p + 1, fim, tam, cmp, m);
}

int ordenar(void *base, int n, size_t tam, Comparador cmp, int algoritmo, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    m->deslocamentos = 0;

    if (algoritmo == INSERTION) {
        insertion_sort(base, n, tam, cmp, m);
    } else if (algoritmo == BUBBLE) {
        bubble_sort(base, n, tam, cmp, m);
    } else if (algoritmo == MERGE) {
        return merge_sort(base, n, tam, cmp, m);
    } else {
        quick_sort_rec(base, 0, n - 1, tam, cmp, m);
    }

    return 1;
}

int esta_ordenado(void *base, int n, size_t tam, Comparador cmp) {
    char *v = base;

    for (int i = 1; i < n; i++) {
        if (cmp(v + (i - 1) * tam, v + i * tam) > 0) {
            return 0;
        }
    }
    return 1;
}

int mesmos_elementos(void *original, void *ordenado, int n, size_t tam) {
    char *o = original;
    char *s = ordenado;
    int usado[MAX] = {0};

    for (int i = 0; i < n; i++) {
        int achou = 0;
        for (int j = 0; j < n && !achou; j++) {
            if (!usado[j] && memcmp(o + i * tam, s + j * tam, tam) == 0) {
                usado[j] = 1;
                achou = 1;
            }
        }
        if (!achou) {
            return 0;
        }
    }
    return 1;
}

void mostrar_dados(void *base, int n, int tipo) {
    if (tipo == NUMEROS) {
        int *v = base;
        for (int i = 0; i < n; i++) {
            printf("%d ", v[i]);
        }
        printf("\n");
    } else {
        Jogador *v = base;
        for (int i = 0; i < n; i++) {
            printf("ID: %d | Nome: %-8s | Pontos: %d\n", v[i].id, v[i].nome, v[i].pontuacao);
        }
    }
}

char *nome_algoritmo(int algoritmo) {
    if (algoritmo == INSERTION) {
        return "Insertion";
    }
    if (algoritmo == BUBBLE) {
        return "Bubble";
    }
    if (algoritmo == MERGE) {
        return "Merge";
    }
    return "Quick";
}

void executar(Dados *d, int algoritmo, Metricas *m, int *valido, int mostrar) {
    void *original;
    size_t tam;
    Comparador cmp;

    if (d->tipo == NUMEROS) {
        original = d->numeros;
        tam = sizeof(int);
        cmp = comparar_int;
    } else {
        original = d->jogadores;
        tam = sizeof(Jogador);
        cmp = comparar_jogador;
    }

    char *copia = malloc(d->n * tam);
    if (copia == NULL) {
        printf("Erro de memoria\n");
        *valido = 0;
        return;
    }

    memcpy(copia, original, d->n * tam);

    if (mostrar) {
        printf("\n--- Antes ---\n");
        mostrar_dados(copia, d->n, d->tipo);
    }

    int ok = ordenar(copia, d->n, tam, cmp, algoritmo, m);

    if (mostrar) {
        printf("\n--- Depois ---\n");
        mostrar_dados(copia, d->n, d->tipo);
    }

    *valido = ok && esta_ordenado(copia, d->n, tam, cmp) &&
              mesmos_elementos(original, copia, d->n, tam);

    free(copia);
}

int ler_quantidade() {
    int n;

    printf("Quantidade (1 a %d): ", MAX);
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Valor invalido, usando 10\n");
        n = 10;
    }
    return n;
}

void gerar_numeros(Dados *d) {
    d->tipo = NUMEROS;
    d->n = ler_quantidade();

    for (int i = 0; i < d->n; i++) {
        d->numeros[i] = rand() % 100;
    }
}

void carregar_numeros(Dados *d) {
    int exemplo[10] = {38, 27, 43, 3, 9, 82, 10, 27, 3, 50};

    d->tipo = NUMEROS;
    d->n = 10;
    memcpy(d->numeros, exemplo, sizeof(exemplo));
}

void gerar_jogadores(Dados *d) {
    char *nomes[] = {"Ana", "Bruno", "Carla", "Diego", "Elisa", "Fabio", "Gabi", "Marcos"};

    d->tipo = JOGADORES;
    d->n = ler_quantidade();

    for (int i = 0; i < d->n; i++) {
        d->jogadores[i].id = 100 + i;
        strcpy(d->jogadores[i].nome, nomes[rand() % 8]);
        d->jogadores[i].pontuacao = rand() % 1000;
    }
}

void carregar_jogadores(Dados *d) {
    Jogador exemplo[8] = {
        {101, "Marcos", 850},
        {102, "Ana", 920},
        {103, "Bruno", 740},
        {104, "Ana", 610},
        {105, "Carla", 980},
        {106, "Bruno", 700},
        {107, "Ana", 880},
        {108, "Diego", 530}
    };

    d->tipo = JOGADORES;
    d->n = 8;
    memcpy(d->jogadores, exemplo, sizeof(exemplo));
}

void executar_um(Dados *d) {
    int algoritmo;
    int valido;
    Metricas m;

    printf("1 - Insertion | 2 - Bubble | 3 - Merge | 4 - Quick: ");
    scanf("%d", &algoritmo);

    if (algoritmo < 1 || algoritmo > 4) {
        printf("Algoritmo invalido\n");
        return;
    }

    executar(d, algoritmo, &m, &valido, 1);

    printf("\nAlgoritmo: %s\n", nome_algoritmo(algoritmo));
    printf("Comparacoes: %d\n", m.comparacoes);
    printf("Trocas: %d\n", m.trocas);
    printf("Deslocamentos: %d\n", m.deslocamentos);

    if (valido) {
        printf("Validacao: OK\n");
    } else {
        printf("Validacao: ERRO\n");
    }
}

void relatorio(Dados *d) {
    Metricas m;
    int valido;

    printf("\n=== RELATORIO (mesma entrada original, %d elementos) ===\n", d->n);
    printf("%-10s %12s %8s %14s   %s\n", "Algoritmo", "Comparacoes", "Trocas", "Deslocamentos", "Validacao");

    for (int a = 1; a <= 4; a++) {
        executar(d, a, &m, &valido, 0);
        printf("%-10s %12d %8d %14d   %s\n", nome_algoritmo(a),
               m.comparacoes, m.trocas, m.deslocamentos, valido ? "OK" : "ERRO");
    }
}

int main() {
    Dados dados;
    int opcao;

    dados.tipo = 0;
    dados.n = 0;

    srand(time(NULL));

    do {
        printf("\n=== CENTRAL ===\n");
        if (dados.tipo == 0) {
            printf("Dados atuais: nenhum\n");
        } else if (dados.tipo == NUMEROS) {
            printf("Dados atuais: %d numeros\n", dados.n);
        } else {
            printf("Dados atuais: %d jogadores\n", dados.n);
        }
        printf("1 - Gerar numeros aleatorios\n");
        printf("2 - Carregar numeros de exemplo\n");
        printf("3 - Gerar jogadores aleatorios\n");
        printf("4 - Carregar jogadores de exemplo\n");
        printf("5 - Executar uma ordenacao\n");
        printf("6 - Relatorio comparativo\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            gerar_numeros(&dados);
        } else if (opcao == 2) {
            carregar_numeros(&dados);
        } else if (opcao == 3) {
            gerar_jogadores(&dados);
        } else if (opcao == 4) {
            carregar_jogadores(&dados);
        } else if (opcao == 5 || opcao == 6) {
            if (dados.tipo == 0) {
                printf("Gere ou carregue dados primeiro\n");
            } else if (opcao == 5) {
                executar_um(&dados);
            } else {
                relatorio(&dados);
            }
        } else if (opcao != 0) {
            printf("Opcao invalida\n");
        }
    } while (opcao != 0);

    return 0;
}