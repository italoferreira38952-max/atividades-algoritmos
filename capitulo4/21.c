#include <stdio.h>

typedef struct {
    int id;
    char jogador[50];
    int pontuacao;
} Partida;

void salvarPartida() {
    FILE *arquivo = fopen("partidas.txt", "w");
    Partida p;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o ID: ");
    scanf("%d", &p.id);

    printf("Digite o jogador: ");
    scanf("%49s", p.jogador);

    printf("Digite a pontuacao: ");
    scanf("%d", &p.pontuacao);

    fprintf(arquivo, "%d %s %d\n",
            p.id, p.jogador, p.pontuacao);

    fclose(arquivo);
}

void lerPartidas() {
    FILE *arquivo = fopen("partidas.txt", "r");
    Partida p;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("\nDados recuperados:\n");

    while (fscanf(arquivo, "%d %49s %d",
                  &p.id, p.jogador, &p.pontuacao) == 3) {
        printf("ID: %d | Jogador: %s | Pontuacao: %d\n",
               p.id, p.jogador, p.pontuacao);
    }

    fclose(arquivo);
}

int main() {
    salvarPartida();
    lerPartidas();

    return 0;
}