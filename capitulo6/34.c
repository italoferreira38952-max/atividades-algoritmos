#include <stdio.h>
#include <string.h>

#define N 8

typedef struct {
    int id;
    char nome[30];
    int pontuacao;
} Jogador;

int comparar(Jogador a, Jogador b) {
    int r = strcmp(a.nome, b.nome);
    if (r != 0) {
        return r;
    }
    return a.id - b.id;
}

void insertion_sort_jogadores(Jogador vet[], int n) {
    for (int i = 1; i < n; i++) {
        Jogador temp = vet[i];
        int j = i - 1;

        while (j >= 0 && comparar(vet[j], temp) > 0) {
            vet[j + 1] = vet[j];
            j--;
        }

        vet[j + 1] = temp;
    }
}

void mostrar_jogadores(Jogador vet[], int n) {
    for (int i = 0; i < n; i++) {
        printf("ID: %d | Nome: %-10s | Pontos: %d\n", vet[i].id, vet[i].nome, vet[i].pontuacao);
    }
}

int validar(Jogador original[], Jogador ordenado[], int n) {
    for (int i = 1; i < n; i++) {
        if (comparar(ordenado[i - 1], ordenado[i]) > 0) {
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        int achou = 0;
        for (int j = 0; j < n; j++) {
            if (original[j].id == ordenado[i].id) {
                if (strcmp(original[j].nome, ordenado[i].nome) == 0 &&
                    original[j].pontuacao == ordenado[i].pontuacao) {
                    achou = 1;
                }
            }
        }
        if (!achou) {
            return 0;
        }
    }

    return 1;
}

void atividade_34() {
    Jogador original[N] = {
        {101, "Marcos", 850},
        {102, "Ana", 920},
        {103, "Bruno", 740},
        {104, "Ana", 610},
        {105, "Carla", 980},
        {106, "Bruno", 700},
        {107, "Ana", 880},
        {108, "Diego", 530}
    };
    Jogador copia[N];

    memcpy(copia, original, sizeof(original));

    printf("\n--- Antes da ordenacao ---\n");
    mostrar_jogadores(copia, N);

    insertion_sort_jogadores(copia, N);

    printf("\n--- Depois da ordenacao ---\n");
    mostrar_jogadores(copia, N);

    if (validar(original, copia, N)) {
        printf("\nValidacao: OK\n");
    } else {
        printf("\nValidacao: ERRO\n");
    }
}

int main() {
    int opcao;

    do {
        printf("\n=== CENTRAL ===\n");
        printf("1 - Atividade 34 (Insertion Sort de jogadores)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atividade_34();
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