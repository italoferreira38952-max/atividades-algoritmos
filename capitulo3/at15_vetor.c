#include <stdio.h>

#define MAX_JOGADORES 3

typedef struct {
    int id;
    char nome[30];
    int vida;
    int pontuacao;
    int posX;
    int posY;
} Personagem;

void ajustarVida(Personagem *p, int delta) {
    p->vida += delta;
    if (p->vida > 100) p->vida = 100;
    if (p->vida < 0)   p->vida = 0;
}

void ajustarPontuacao(Personagem *p, int delta) {
    p->pontuacao += delta;
    if (p->pontuacao < 0) p->pontuacao = 0;
}

void moverPersonagem(Personagem *p, int dx, int dy) {
    p->posX += dx;
    p->posY += dy;
}

void exibirEstado(const Personagem *p, const char *titulo) {
    printf("--- %s ---\n", titulo);
    printf("ID: %d\n", p->id);
    printf("Nome: %s\n", p->nome);
    printf("Vida: %d\n", p->vida);
    printf("Pontuacao: %d\n", p->pontuacao);
    printf("Posicao: (%d, %d)\n\n", p->posX, p->posY);
}

int main(void) {
    Personagem jogadores[MAX_JOGADORES];
    int i;

    printf("=== Criacao dos Personagens ===\n");
    for (i = 0; i < MAX_JOGADORES; i++) {
        printf("\n--- Jogador %d ---\n", i + 1);

        printf("ID: ");
        scanf("%d", &jogadores[i].id);

        printf("Nome: ");
        scanf(" %29[^\n]", jogadores[i].nome);

        printf("Vida inicial (0-100): ");
        scanf("%d", &jogadores[i].vida);
        if (jogadores[i].vida > 100) jogadores[i].vida = 100;
        if (jogadores[i].vida < 0)   jogadores[i].vida = 0;

        printf("Pontuacao inicial: ");
        scanf("%d", &jogadores[i].pontuacao);
        if (jogadores[i].pontuacao < 0) jogadores[i].pontuacao = 0;

        printf("Posicao X: ");
        scanf("%d", &jogadores[i].posX);

        printf("Posicao Y: ");
        scanf("%d", &jogadores[i].posY);
    }

    printf("\n===================================\n");
    printf("ESTADO INICIAL DOS JOGADORES\n");
    printf("===================================\n");
    for (i = 0; i < MAX_JOGADORES; i++) {
        exibirEstado(&jogadores[i], "Estado Inicial");
    }

    printf("===================================\n");
    printf("ALTERACAO DE DADOS DOS JOGADORES\n");
    printf("===================================\n");
    for (i = 0; i < MAX_JOGADORES; i++) {
        int deltaVida, deltaPontuacao, dx, dy;

        printf("\n--- Alteracoes para o Jogador %d (%s) ---\n", i + 1, jogadores[i].nome);

        printf("Quanto de vida ganhar/perder (ex: -30): ");
        scanf("%d", &deltaVida);
        ajustarVida(&jogadores[i], deltaVida);

        printf("Quanto de pontuacao ganhar/perder (ex: 50): ");
        scanf("%d", &deltaPontuacao);
        ajustarPontuacao(&jogadores[i], deltaPontuacao);

        printf("Deslocamento em X: ");
        scanf("%d", &dx);
        printf("Deslocamento em Y: ");
        scanf("%d", &dy);
        moverPersonagem(&jogadores[i], dx, dy);
    }
    printf("\n===================================\n");
    printf("ESTADO APOS ALTERACOES\n");
    printf("===================================\n");
    for (i = 0; i < MAX_JOGADORES; i++) {
        exibirEstado(&jogadores[i], "Estado Final");
    }

    return 0;
}