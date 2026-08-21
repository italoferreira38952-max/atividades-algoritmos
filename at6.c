#include <stdio.h>

void aplicar_dano(int *vida, int dano) {
    if (!vida) return;
    *vida = *vida - dano;
    if (*vida < 0) *vida = 0;
}

void restaurar_vida(int *vida) {
    if (!vida) return;
    *vida = *vida + 20;
    if (*vida > 100) *vida = 100;
}

void aplicar_pontuacao_dupla(int *pontuacao) {
    if (!pontuacao) return;
    *pontuacao = *pontuacao * 2;
}

void ler_mapa(int *mapa, int tamanho) {
    printf("Digite os %d valores do mapa (0 a 20):\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        int valor;
        do {
            printf("Posicao %d: ", i + 1);
            scanf("%d", &valor);
            if (valor < 0 || valor > 20) {
                printf("Valor invalido! Digite entre 0 e 20.\n");
            }
        } while (valor < 0 || valor > 20);
        *(mapa + i) = valor;
    }
}

void mostrar_mapa(const int *mapa, int tamanho) {
    printf("Mapa: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", *(mapa + i));
    }
    printf("\n");
}

void explorar_mapa(const int *mapa, int tamanho, int *pontuacao) {
    const int *cursor = mapa;
    const int *fim = mapa + tamanho;
    int posicao = 0;
    int pontos_fase = 0;

    printf("\n--- Exploracao ---\n");
    while (cursor < fim) {
        int valor = *cursor;
        pontos_fase += valor;
        *pontuacao += valor;

        printf("Posicao %d | Valor: %d | Pontos fase: %d\n", posicao, valor, pontos_fase);

        /*
         * Comparacao:
         * cursor++          → incremento de ponteiro
         * mapa[posicao]     → acesso por indice
         */
        cursor++;
        posicao++;
    }

    printf("\nResumo: %d plataformas | +%d pontos | Total: %d\n", posicao, pontos_fase, *pontuacao);
}

// ==================== INVENTÁRIO (ATIVIDADE 6) ====================

void mostrar_indice(int *inventario[], int tamanho) {
    printf("\nInventario (usando inventario[i]):\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Slot %d: %d\n", i, *inventario[i]);
    }
}

void mostrar_ponteiro(int *inventario[], int tamanho) {
    printf("\nInventario (usando *(inventario + i)):\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Slot %d: %d\n", i, **(inventario + i));
    }
}

void alterar_item(int *inventario[], int tamanho) {
    int slot, valor;
    printf("Qual slot (0 a %d)? ", tamanho - 1);
    scanf("%d", &slot);

    if (slot < 0 || slot >= tamanho) {
        printf("Slot invalido\n");
        return;
    }

    printf("Novo valor: ");
    scanf("%d", &valor);
    *inventario[slot] = valor;
    printf("Item alterado!\n");
}

int main() {
    int vida = 100;
    int pontuacao = 50;

    int pocao = 10;
    int chave = 1;
    int moeda = 5;

    int *inventario[3];
    inventario[0] = &pocao;
    inventario[1] = &chave;
    inventario[2] = &moeda;

    int mapa[100];
    int tamanho = 0;
    int mapa_ok = 0;

    int opcao;

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Aplicar dano\n");
        printf("2. Restaurar vida\n");
        printf("3. Duplicar pontuacao\n");
        printf("4. Ler mapa\n");
        printf("5. Explorar mapa\n");
        printf("6. Mostrar inventario (indice)\n");
        printf("7. Mostrar inventario (ponteiro)\n");
        printf("8. Alterar item\n");
        printf("9. Ver estado\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int dano;
            printf("Dano: ");
            scanf("%d", &dano);
            aplicar_dano(&vida, dano);
            printf("Vida: %d\n", vida);
        }
        else if (opcao == 2) {
            restaurar_vida(&vida);
            printf("Vida: %d\n", vida);
        }
        else if (opcao == 3) {
            aplicar_pontuacao_dupla(&pontuacao);
            printf("Pontuacao: %d\n", pontuacao);
        }
        else if (opcao == 4) {
            printf("Tamanho do mapa (1-100): ");
            scanf("%d", &tamanho);
            if (tamanho < 1 || tamanho > 100) {
                printf("Tamanho invalido\n");
            } else {
                ler_mapa(mapa, tamanho);
                mostrar_mapa(mapa, tamanho);
                mapa_ok = 1;
            }
        }
        else if (opcao == 5) {
            if (!mapa_ok) {
                printf("Carregue o mapa primeiro (opcao 4)\n");
            } else {
                explorar_mapa(mapa, tamanho, &pontuacao);
            }
        }
        else if (opcao == 6) {
            mostrar_indice(inventario, 3);
        }
        else if (opcao == 7) {
            mostrar_ponteiro(inventario, 3);
        }
        else if (opcao == 8) {
            alterar_item(inventario, 3);
        }
        else if (opcao == 9) {
            printf("\n=== ESTADO ===\n");
            printf("Vida: %d\n", vida);
            printf("Pontuacao: %d\n", pontuacao);
            if (mapa_ok) mostrar_mapa(mapa, tamanho);
            else printf("Mapa: nao carregado\n");
            mostrar_indice(inventario, 3);
        }
        else if (opcao == 0) {
            printf("Saindo...\n");
        }
        else {
            printf("Opcao invalida\n");
        }

    } while (opcao != 0);

    return 0;
}