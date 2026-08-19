#include <stdio.h>

void aplicar_dano(int *vida, int dano) {
    if (!vida) return;
    printf("endereco em aplicar_dano: %p\n", (void *)vida);
    *vida = *vida - dano;
}

void restaurar_vida(int *vida) {
    if (!vida) return;
    printf("endereco em restaurar_vida: %p\n", (void *)vida);
    *vida = *vida + 20;
}

void aplicar_pontuacao_dupla(int *pontuacao) {
    if (!pontuacao) return;
    printf("endereco em aplicar_pontuacao_dupla: %p\n", (void *)pontuacao);
    *pontuacao = *pontuacao * 2;
}

int main() {
    int vida = 100;
    int dano;
    int pontuacao = 50;

    int *pvida = &vida;
    int *ppontuacao = &pontuacao;
    printf("=== ESTADO INICIAL ===\n");
    printf("vida: %d (endereco: %p)\n", vida, (void *)pvida);
    printf("pontuacao: %d (endereco: %p)\n", pontuacao, (void *)ppontuacao);
    printf("\ninforme o dano:\n");
    scanf("%d", &dano);
    printf("\naplicando %d de dano...\n", dano);
    aplicar_dano(pvida, dano);
    printf("vida atual na main: %d\n", vida);
    printf("\ncurando 20 de vida...\n");
    restaurar_vida(pvida);
    printf("vida atual na main: %d\n", vida);
    printf("\nduplicando pontuacao...\n");
    aplicar_pontuacao_dupla(ppontuacao);
    printf("pontuacao atual na main: %d\n", pontuacao);

    return 0;
}