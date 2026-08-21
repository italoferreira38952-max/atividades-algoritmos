#include <stdio.h>

void aplicar_dano(int *vida, int dano) {
    if (!vida) return;
    printf("Endereco em aplicar_dano: %p\n", (void *)vida);
    *vida = *vida - dano;
}

void restaurar_vida(int *vida) {
    if (!vida) return;
    printf("Endereco em restaurar_vida: %p\n", (void *)vida);
    *vida = *vida + 20;
}

void aplicar_pontuacao_dupla(int *pontuacao) {
    if (!pontuacao) return;
    printf("Endereco em aplicar_pontuacao_dupla: %p\n", (void *)pontuacao);
    *pontuacao = *pontuacao * 2;
}

int main() {
    int vida = 100;
    int tesouro = 0;
    int pontuacao = 50;

    int *pvida = &vida;
    int *ptesouro = &tesouro;
    int *ppontuacao = &pontuacao;

    printf("=== ESTADO INICIAL ===\n");
    printf("Vida: %d (endereco: %p)\n", vida, (void *)pvida);
    printf("Tesouro: %d (endereco: %p)\n", tesouro, (void *)ptesouro);
    printf("Pontuacao: %d (endereco: %p)\n", pontuacao, (void *)ppontuacao);

    int dano;
    printf("\nInforme o dano: ");
    scanf("%d", &dano);

    printf("\nAplicando %d de dano...\n", dano);
    aplicar_dano(pvida, dano);
    printf("Vida atual na main: %d\n", vida);

    printf("\nCurando 20 de vida...\n");
    restaurar_vida(pvida);
    printf("Vida atual na main: %d\n", vida);

    printf("\nDuplicando pontuacao...\n");
    aplicar_pontuacao_dupla(ppontuacao);
    printf("Pontuacao atual na main: %d\n", pontuacao);

    *ptesouro = 1;
    printf("\nTesouro ativado: %d\n", tesouro);
    return 0;
}