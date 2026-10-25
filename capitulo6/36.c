#include <stdio.h>
#include <string.h>

#define N 8

#define POR_ID 1
#define POR_VIDA 2

#define CRESCENTE 1
#define DECRESCENTE 2

typedef struct {
    int id;
    char nome[30];
    int vida;
    int pontuacao;
} Jogador;

int comparar_jogadores(Jogador a, Jogador b, int campo, int direcao) {
    int resultado;

    if (campo == POR_ID) {
        resultado = a.id - b.id;
    } else {
        resultado = a.vida - b.vida;
    }

    if (direcao == DECRESCENTE) {
        resultado = -resultado;
    }

    return resultado;
}

void bubble_sort_jogadores(Jogador vet[], int n, int campo, int direcao,
                           int *comparacoes, int *trocas, int *passagens) {
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
            if (comparar_jogadores(vet[i], vet[i + 1], campo, direcao) > 0) {
                Jogador temp = vet[i];
                vet[i] = vet[i + 1];
                vet[i + 1] = temp;
                (*trocas)++;
                trocou = 1;
            }
        }

        fim--;
    }
}

int esta_ordenado(Jogador vet[], int n, int campo, int direcao) {
    for (int i = 1; i < n; i++) {
        if (comparar_jogadores(vet[i - 1], vet[i], campo, direcao) > 0) {
            return 0;
        }
    }
    return 1;
}

void mostrar_jogadores(Jogador vet[], int n) {
    for (int i = 0; i < n; i++) {
        printf("ID: %d | Nome: %-8s | Vida: %3d | Pontos: %d\n",
               vet[i].id, vet[i].nome, vet[i].vida, vet[i].pontuacao);
    }
}

char *nome_campo(int campo) {
    if (campo == POR_ID) {
        return "Identificador";
    }
    return "Vida";
}

char *nome_direcao(int direcao) {
    if (direcao == CRESCENTE) {
        return "Crescente";
    }
    return "Decrescente";
}

void ordenar_e_mostrar(int campo, int direcao) {
    Jogador original[N] = {
        {104, "Ana", 60, 610},
        {101, "Marcos", 85, 850},
        {107, "Bruno", 40, 700},
        {103, "Carla", 100, 980},
        {102, "Diego", 60, 530},
        {106, "Elisa", 75, 920},
        {108, "Fabio", 20, 440},
        {105, "Gabi", 85, 880}
    };
    Jogador copia[N];
    int comparacoes, trocas, passagens;

    memcpy(copia, original, sizeof(original));

    printf("\nOrdenando por: %s (%s)\n", nome_campo(campo), nome_direcao(direcao));

    printf("\n--- Antes ---\n");
    mostrar_jogadores(copia, N);

    bubble_sort_jogadores(copia, N, campo, direcao, &comparacoes, &trocas, &passagens);

    printf("\n--- Depois ---\n");
    mostrar_jogadores(copia, N);

    printf("\nComparacoes: %d\n", comparacoes);
    printf("Trocas: %d\n", trocas);
    printf("Passagens: %d\n", passagens);

    if (esta_ordenado(copia, N, campo, direcao)) {
        printf("Validacao: OK\n");
    } else {
        printf("Validacao: ERRO\n");
    }
}

void atividade_36() {
    int campo = POR_ID;
    int direcao = CRESCENTE;
    int opcao;

    do {
        printf("\n=== ATIVIDADE 36 ===\n");
        printf("Campo atual: %s\n", nome_campo(campo));
        printf("Direcao atual: %s\n", nome_direcao(direcao));
        printf("1 - Escolher campo\n");
        printf("2 - Escolher direcao\n");
        printf("3 - Ordenar\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("1 - Identificador | 2 - Vida: ");
            scanf("%d", &campo);
        } else if (opcao == 2) {
            printf("1 - Crescente | 2 - Decrescente: ");
            scanf("%d", &direcao);
        } else if (opcao == 3) {
            ordenar_e_mostrar(campo, direcao);
        }
    } while (opcao != 0);
}

int main() {
    int opcao;

    do {
        printf("\n=== CENTRAL ===\n");
        printf("1 - Atividade 36 (Bubble Sort de jogadores)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atividade_36();
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