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

    if (arquivo == NULL) {
        printf("Historico vazio.\n");
        return;
    }

    while (fscanf(arquivo, "%d %49s %d",
                  &p.id, p.jogador, &p.pontuacao) == 3) {

        printf("ID: %d | Jogador: %s | Pontuacao: %d\n",
               p.id, p.jogador, p.pontuacao);
    }

    fclose(arquivo);
}

void gravarBinario(Partida p) {
    FILE *arquivo = fopen("partidas.bin", "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo binario!\n");
        return;
    }

    if (fwrite(&p, sizeof(Partida), 1, arquivo) != 1) {
        printf("Erro ao gravar a partida!\n");
    }

    fclose(arquivo);
}

void lerBinario() {
    FILE *arquivo = fopen("partidas.bin", "rb");
    Partida p;

    if (arquivo == NULL) {
        printf("Arquivo binario vazio ou inexistente!\n");
        return;
    }

    if (fread(&p, sizeof(Partida), 1, arquivo) == 1) {
        printf("\nPartida recuperada:\n");
        printf("ID: %d\n", p.id);
        printf("Jogador: %s\n", p.jogador);
        printf("Pontuacao: %d\n", p.pontuacao);
    } else {
        printf("Registro incompleto ou arquivo vazio!\n");
    }

    fclose(arquivo);
}

int main() {
    Partida p = {1, "Lucas", 100};

    salvarPartida();
    lerPartidas();

    gravarBinario(p);
    lerBinario();

    return 0;
}