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

int main() {
    int vida = 100;
    int tesouro = 0;
    int pontuacao = 50;

    int *pvida = &vida;
    int *ptesouro = &tesouro;
    int *ppontuacao = &pontuacao;

    int plataformas[5] = {3, 7, 2, 9, 1};
    int *vetor = plataformas;

    printf("=== ESTADO INICIAL ===\n");
    printf("Vida: %d\n", vida);
    printf("Pontuacao: %d\n", pontuacao);

    // Demonstração das funções anteriores
    aplicar_dano(pvida, 15);
    restaurar_vida(pvida);
    aplicar_pontuacao_dupla(ppontuacao);
    *ptesouro = 1;

    printf("\nApos funcoes: Vida = %d | Pontuacao = %d | Tesouro = %d\n", vida, pontuacao, tesouro);

    /*
     * O deslocamento (vetor + i) respeita o tipo do ponteiro porque o compilador
     * multiplica i pelo tamanho do tipo (sizeof(int)). Assim:
     * vetor + 0 → primeiro elemento
     * vetor + 1 → avança sizeof(int) bytes
     * e assim por diante.
     */

    printf("\n=== PERCORRENDO PLATAFORMAS ===\n");
    printf("Indice | Endereco          | Valor\n");

    int pontuacao_mapa = 0;
    int altura = 0;

    for (int i = 0; i < 5; i++) {
        printf("%d      | %p | %d\n", i, (void *)(vetor + i), *(vetor + i));
        pontuacao_mapa += *(vetor + i);
        altura += *(vetor + i);
    }

    printf("\nPontuacao do mapa: %d\n", pontuacao_mapa);
    printf("Altura total: %d\n", altura);

    return 0;
}