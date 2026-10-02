#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char jogador[50];
    int pontuacao;
} Partida;

void cadastrar(Partida *partidas, int *quantidade) {
    printf("Digite o ID: ");
    scanf("%d", &partidas[*quantidade].id);

    printf("Digite o jogador: ");
    scanf("%49s", partidas[*quantidade].jogador);

    printf("Digite a pontuacao: ");
    scanf("%d", &partidas[*quantidade].pontuacao);

    (*quantidade)++;
}

void listar(Partida *partidas, int quantidade) {
    if (quantidade == 0) {
        printf("Nenhuma partida cadastrada.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("ID: %d | Jogador: %s | Pontuacao: %d\n",
               partidas[i].id,
               partidas[i].jogador,
               partidas[i].pontuacao);
    }
}

void salvar(Partida *partidas, int quantidade) {
    FILE *arquivo = fopen("temporada.bin", "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    if (fwrite(&quantidade, sizeof(int), 1, arquivo) != 1) {
        printf("Erro ao salvar a quantidade!\n");
        fclose(arquivo);
        return;
    }

    if (quantidade > 0 &&
        fwrite(partidas, sizeof(Partida), quantidade, arquivo) != quantidade) {

        printf("Erro ao salvar as partidas!\n");
        fclose(arquivo);
        return;
    }

    fclose(arquivo);
    printf("Temporada salva com sucesso!\n");
}

void carregar(Partida **partidas, int *quantidade) {
    FILE *arquivo = fopen("temporada.bin", "rb");
    int novaQuantidade;
    Partida *novo;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    if (fread(&novaQuantidade, sizeof(int), 1, arquivo) != 1 ||
        novaQuantidade < 0) {

        printf("Arquivo invalido!\n");
        fclose(arquivo);
        return;
    }

    novo = malloc(novaQuantidade * sizeof(Partida));

    if (novaQuantidade > 0 && novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        fclose(arquivo);
        return;
    }

    if (novaQuantidade > 0 &&
        fread(novo, sizeof(Partida), novaQuantidade, arquivo) != novaQuantidade) {

        printf("Erro ao carregar as partidas!\n");
        free(novo);
        fclose(arquivo);
        return;
    }

    free(*partidas);

    *partidas = novo;
    *quantidade = novaQuantidade;

    fclose(arquivo);

    printf("Temporada carregada com sucesso!\n");
}

int main() {
    Partida *partidas = malloc(10 * sizeof(Partida));
    int quantidade = 0;
    int opcao;

    if (partidas == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    do {
        printf("\n1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Salvar\n");
        printf("4 - Carregar\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (quantidade < 10)
                    cadastrar(partidas, &quantidade);
                else
                    printf("Limite de partidas atingido.\n");
                break;

            case 2:
                listar(partidas, quantidade);
                break;

            case 3:
                salvar(partidas, quantidade);
                break;

            case 4:
                carregar(&partidas, &quantidade);
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    free(partidas);

    return 0;
}