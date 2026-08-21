#include <stdio.h>

void ler_mapa(int *m, int t) {
    printf("Digite os %d valores do mapa:\n", t);
    for (int i = 0; i < t; i++) {
        printf("Digite o valor para a posicao %d: ", i + 1);
        scanf("%d", m + i);
    }
}
void mostrar_mapa(int *m, int t) {
    printf("Valores do mapa:\n");
    for (int i = 0; i < t; i++) {
        printf("%d ", *(m + i));
    }
    printf("\n");
}
int main() {
    int t;
    int m[100];
    printf("Digite o tamanho do mapa (1 a 100): ");
    scanf("%d", &t);
    if (t > 100 || t < 1) {
        printf("Tamanho invalido\n");
        return 1;
    }
    ler_mapa(m, t);
    mostrar_mapa(m, t);
    return 0;
}