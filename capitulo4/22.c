#include <stdio.h>

typedef struct {
    int id;
    char jogador[50];
    int pontuacao;
} Partida;

void salvarPartida() {
    FILE *arquivo = fopen("partidas.txt", "a");
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
    int contador = 0;

    if (arquivo == NULL) {
        printf("Historico vazio.\n");
        return;
    }

    while (fscanf(arquivo, "%d %49s %d",
                  &p.id, p.jogador, &p.pontuacao) == 3) {

        printf("ID: %d | Jogador: %s | Pontuacao: %d\n",
               p.id, p.jogador, p.pontuacao);

        contador++;
    }

    fclose(arquivo);

    if (contador == 0)
        printf("Historico vazio.\n");
    else
        printf("Total de partidas: %d\n", contador);
}

int main() {
    salvarPartida();
    lerPartidas();

    return 0;
}