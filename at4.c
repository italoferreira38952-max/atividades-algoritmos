#include <stdio.h>

void aplicar_dano(int *vida, int dano) {
    if (!vida) return;
    *vida = *vida - dano;
}

void restaurar_vida(int *vida) {
    if (!vida) return;
    *vida = *vida + 20;
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
    printf("Mapa atual: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", *(mapa + i));
    }
    printf("\n");
}

int main() {
    int vida = 100;
    int tesouro = 0;
    int pontuacao = 50;
    int mapa[100];
    int tamanho;

    int *pvida = &vida;
    int *ptesouro = &tesouro;
    int *ppontuacao = &pontuacao;

    printf("=== ESTADO INICIAL ===\n");
    printf("Vida: %d | Pontuacao: %d | Tesouro: %d\n", vida, pontuacao, tesouro);

    // Funções das atividades anteriores
    aplicar_dano(pvida, 10);
    restaurar_vida(pvida);
    aplicar_pontuacao_dupla(ppontuacao);
    *ptesouro = 1;

    printf("Apos funcoes: Vida = %d | Pontuacao = %d | Tesouro = %d\n\n", vida, pontuacao, tesouro);

    printf("Digite o tamanho do mapa (1 a 100): ");
    scanf("%d", &tamanho);

    if (tamanho < 1 || tamanho > 100) {
        printf("Tamanho invalido\n");
        return 1;
    }

    ler_mapa(mapa, tamanho);
    mostrar_mapa(mapa, tamanho);

    return 0;
}