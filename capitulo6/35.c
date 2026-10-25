#include <stdio.h>
#include <string.h>

#define N 8

void bubble_sort(int vet[], int n, int *comparacoes, int *trocas, int *passagens) {
    *comparacoes = 0;
    *trocas = 0;
    *passagens = 0;

    int fim = n - 1;
    int trocou = 1;

    while (trocou && fim > 0) {
        trocou = 0;
        (*passagens)++;

        for (int i = 0; i < fim; i++) {
            (*comparacoes)++;
            if (vet[i] > vet[i + 1]) {
                int temp = vet[i];
                vet[i] = vet[i + 1];
                vet[i + 1] = temp;
                (*trocas)++;
                trocou = 1;
            }
        }

        fim--;
    }
}

int esta_ordenado(int vet[], int n) {
    for (int i = 1; i < n; i++) {
        if (vet[i - 1] > vet[i]) {
            return 0;
        }
    }
    return 1;
}

void mostrar(char texto[], int vet[], int n) {
    printf("%s", texto);
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void testar(char nome[], int original[], int n) {
    int copia[N];
    int comparacoes, trocas, passagens;

    memcpy(copia, original, sizeof(int) * n);

    printf("\n--- %s ---\n", nome);
    mostrar("Antes:  ", copia, n);
    bubble_sort(copia, n, &comparacoes, &trocas, &passagens);
    mostrar("Depois: ", copia, n);

    printf("Comparacoes: %d\n", comparacoes);
    printf("Trocas: %d\n", trocas);
    printf("Passagens: %d\n", passagens);

    if (esta_ordenado(copia, n)) {
        printf("Validacao: OK\n");
    } else {
        printf("Validacao: ERRO\n");
    }
}

void atividade_35() {
    int ordenado[N] = {1, 2, 3, 4, 5, 6, 7, 8};
    int inverso[N] = {8, 7, 6, 5, 4, 3, 2, 1};
    int aleatorio[N] = {5, 2, 8, 1, 7, 3, 6, 4};

    testar("Vetor ordenado", ordenado, N);
    testar("Vetor inverso", inverso, N);
    testar("Vetor aleatorio", aleatorio, N);
}

int main() {
    int opcao;

    do {
        printf("\n=== CENTRAL ===\n");
        printf("1 - Atividade 35 (Bubble Sort)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atividade_35();
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