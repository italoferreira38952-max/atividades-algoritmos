#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct {
    int id;
    char nome[30];
    int pontuacao;
} Jogador;

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

void intercalar(char *base, char *aux, int inicio, int meio, int fim,
                size_t tam, Comparador cmp, int *comparacoes) {
    int i = inicio;
    int j = meio + 1;
    int k = inicio;

    while (i <= meio && j <= fim) {
        (*comparacoes)++;
        if (cmp(base + i * tam, base + j * tam) <= 0) {
            memcpy(aux + k * tam, base + i * tam, tam);
            i++;
        } else {
            memcpy(aux + k * tam, base + j * tam, tam);
            j++;
        }
        k++;
    }

    while (i <= meio) {
        memcpy(aux + k * tam, base + i * tam, tam);
        i++;
        k++;
    }

    while (j <= fim) {
        memcpy(aux + k * tam, base + j * tam, tam);
        j++;
        k++;
    }

    memcpy(base + inicio * tam, aux + inicio * tam, (fim - inicio + 1) * tam);
}

void merge_sort_rec(char *base, char *aux, int inicio, int fim,
                    size_t tam, Comparador cmp, int *comparacoes) {
    if (inicio >= fim) {
        return;
    }

    int meio = inicio + (fim - inicio) / 2;

    merge_sort_rec(base, aux, inicio, meio, tam, cmp, comparacoes);
    merge_sort_rec(base, aux, meio + 1, fim, tam, cmp, comparacoes);
    intercalar(base, aux, inicio, meio, fim, tam, cmp, comparacoes);
}

int merge_sort(void *base, int n, size_t tam, Comparador cmp, int *comparacoes) {
    *comparacoes = 0;

    if (n <= 1) {
        return 1;
    }

    char *aux = malloc(n * tam);
    if (aux == NULL) {
        printf("Erro de memoria\n");
        return 0;
    }

    merge_sort_rec(base, aux, 0, n - 1, tam, cmp, comparacoes);

    free(aux);
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

void mostrar_numeros(char texto[], int vet[], int n) {
    printf("%s", texto);
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void mostrar_jogadores(Jogador vet[], int n) {
    for (int i = 0; i < n; i++) {
        printf("ID: %d | Nome: %-8s | Pontos: %d\n", vet[i].id, vet[i].nome, vet[i].pontuacao);
    }
}

void mostrar_validacao(int ok) {
    if (ok) {
        printf("Validacao: OK\n");
    } else {
        printf("Validacao: ERRO\n");
    }
}

void merge_numeros() {
    int original[] = {38, 27, 43, 3, 9, 82, 10, 27, 3, 50};
    int n = 10;
    int copia[MAX];
    int comparacoes;

    memcpy(copia, original, sizeof(int) * n);

    mostrar_numeros("Antes:  ", copia, n);
    merge_sort(copia, n, sizeof(int), comparar_int, &comparacoes);
    mostrar_numeros("Depois: ", copia, n);

    printf("Comparacoes: %d\n", comparacoes);
    mostrar_validacao(esta_ordenado(copia, n, sizeof(int), comparar_int) &&
                      mesmos_elementos(original, copia, n, sizeof(int)));
}

void merge_jogadores() {
    Jogador original[] = {
        {101, "Marcos", 850},
        {102, "Ana", 920},
        {103, "Bruno", 740},
        {104, "Ana", 610},
        {105, "Carla", 980},
        {106, "Bruno", 700},
        {107, "Ana", 880},
        {108, "Diego", 530}
    };
    int n = 8;
    Jogador copia[MAX];
    int comparacoes;

    memcpy(copia, original, sizeof(Jogador) * n);

    printf("\n--- Antes ---\n");
    mostrar_jogadores(copia, n);

    merge_sort(copia, n, sizeof(Jogador), comparar_jogador, &comparacoes);

    printf("\n--- Depois (nome, desempate por id) ---\n");
    mostrar_jogadores(copia, n);

    printf("\nComparacoes: %d\n", comparacoes);
    mostrar_validacao(esta_ordenado(copia, n, sizeof(Jogador), comparar_jogador) &&
                      mesmos_elementos(original, copia, n, sizeof(Jogador)));
}

int main() {
    int opcao;

    do {
        printf("\n=== CENTRAL ===\n");
        printf("1 - Atividade 38 (Merge Sort de numeros)\n");
        printf("2 - Atividade 38 (Merge Sort de jogadores)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                merge_numeros();
                break;
            case 2:
                merge_jogadores();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (opcao != 0);

    return 0;
}