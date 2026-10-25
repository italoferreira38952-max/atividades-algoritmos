#include <stdio.h>

#define MAX 20

void intercalar(int a[], int na, int b[], int nb, int saida[], int *comparacoes) {
    int i = 0;
    int j = 0;
    int k = 0;

    *comparacoes = 0;

    while (i < na && j < nb) {
        (*comparacoes)++;
        if (a[i] <= b[j]) {
            saida[k] = a[i];
            i++;
        } else {
            saida[k] = b[j];
            j++;
        }
        k++;
    }

    while (i < na) {
        saida[k] = a[i];
        i++;
        k++;
    }

    while (j < nb) {
        saida[k] = b[j];
        j++;
        k++;
    }
}

void dividir(int vet[], int inicio, int fim, int nivel) {
    for (int i = 0; i < nivel; i++) {
        printf("   ");
    }

    printf("[%d..%d] -> ", inicio, fim);
    for (int i = inicio; i <= fim; i++) {
        printf("%d ", vet[i]);
    }

    /* RESOLVER: intervalo com um elemento ja esta ordenado (caso-base) */
    if (inicio >= fim) {
        printf("(caso-base)\n");
        return;
    }
    printf("\n");

    int meio = inicio + (fim - inicio) / 2;

    /* DIVIDIR: separa o intervalo em duas metades */
    dividir(vet, inicio, meio, nivel + 1);
    dividir(vet, meio + 1, fim, nivel + 1);

    /* COMBINAR: na proxima atividade, intercalar as duas metades aqui */
}

int esta_ordenado(int vet[], int n) {
    for (int i = 1; i < n; i++) {
        if (vet[i - 1] > vet[i]) {
            return 0;
        }
    }
    return 1;
}

int soma(int vet[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += vet[i];
    }
    return total;
}

void mostrar(char texto[], int vet[], int n) {
    printf("%s", texto);
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void testar_intercalacao(int a[], int na, int b[], int nb) {
    int saida[MAX];
    int comparacoes;

    intercalar(a, na, b, nb, saida, &comparacoes);

    mostrar("Vetor A: ", a, na);
    mostrar("Vetor B: ", b, nb);
    mostrar("Saida:   ", saida, na + nb);
    printf("Comparacoes: %d\n", comparacoes);

    if (esta_ordenado(saida, na + nb) && soma(a, na) + soma(b, nb) == soma(saida, na + nb)) {
        printf("Validacao: OK\n");
    } else {
        printf("Validacao: ERRO\n");
    }
}

void atividade_37() {
    int a1[] = {1, 4, 7, 10, 12};
    int b1[] = {2, 3, 8, 9, 15, 20, 21};

    int a2[] = {1, 2, 3};
    int b2[] = {10, 11, 12, 13};

    int vet[] = {38, 27, 43, 3, 9, 82, 10};
    int n = 7;

    printf("\n--- Intercalacao 1 ---\n");
    testar_intercalacao(a1, 5, b1, 7);

    printf("\n--- Intercalacao 2 (A termina primeiro) ---\n");
    testar_intercalacao(a2, 3, b2, 4);

    printf("\n--- Divisao recursiva ---\n");
    dividir(vet, 0, n - 1, 0);
}

int main() {
    int opcao;

    do {
        printf("\n=== CENTRAL ===\n");
        printf("1 - Atividade 37 (Intercalacao e divisao)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atividade_37();
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