#include <stdio.h>

void ler_mapa(int *mapa, int tamanho) {
    printf("Digite os %d valores do mapa:\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        printf("Digite o valor para a posicao %d: ", i + 1);
        scanf("%d", mapa + i);
    }
}
void mostrar_mapa(int *mapa, int tamanho) {
    printf("Valores do mapa:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", *(mapa + i));
    }
    printf("\n");
}
int main() {
    int tamanho;
    int mapa[100];
    printf("Digite o tamanho do mapa (1 a 100): ");
    scanf("%d", &tamanho);
    if (tamanho > 100 || tamanho < 1) {
        printf("Tamanho invalido\n");
        return 1;
    }
    ler_mapa(mapa, tamanho);
    mostrar_mapa(mapa, tamanho);
    return 0;
}