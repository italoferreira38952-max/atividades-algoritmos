#include <stdio.h>

int main() {
    int vida = 100;
    int tesouro = 0;       

    int *pvida = &vida;
    int *ptesouro = &tesouro;

    printf("=== ESTADO INICIAL ===\n");
    printf("Vida: %d (endereco: %p)\n", vida, (void *)pvida);
    printf("Tesouro: %d (endereco: %p)\n", tesouro, (void *)ptesouro);
    int dano;
    printf("\nInforme o dano: ");
    scanf("%d", &dano);

    printf("Aplicando %d de dano...\n", dano);
    *pvida = *pvida - dano;
    printf("Vida apos dano: %d\n", vida);
    printf("\nCurando 20 de vida...\n");
    *pvida = *pvida + 20;
    printf("Vida apos cura: %d\n", vida);

    printf("\nAtivando tesouro...\n");
    *ptesouro = 1;
    printf("Tesouro agora: %d\n", tesouro);

    return 0;
}