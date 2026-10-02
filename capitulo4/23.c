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

    printf("Total de partidas: %d\n", contador);
}

void processarPartidas() {
    FILE *origem = fopen("partidas.txt", "r");
    FILE *destino;
    Partida p;
    int contador = 0;

    if (origem == NULL) {
        printf("Erro ao abrir o arquivo de origem!\n");
        return;
    }

    destino = fopen("relatorio.txt", "w");

    if (destino == NULL) {
        printf("Erro ao criar o arquivo de destino!\n");
        fclose(origem);
        return;
    }

    while (fscanf(origem, "%d %49s %d",
                  &p.id, p.jogador, &p.pontuacao) == 3) {

        p.pontuacao += 10;

        fprintf(destino, "%d %s %d\n",
                p.id, p.jogador, p.pontuacao);

        contador++;
    }

    fclose(origem);
    fclose(destino);

    printf("Registros processados: %d\n", contador);
}

int main() {
    salvarPartida();
    lerPartidas();
    processarPartidas();

    return 0;
}