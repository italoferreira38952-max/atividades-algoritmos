//esse codigo so responde sa perguntas da questão 10.
//o codido não esta complementado com os das demais questões.
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    int numero;
} Jogador;

int main() {
    int quantidade;

    printf("Informe a quantidade de jogadores da equipe: ");
    if (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return 1;
    }

    Jogador *equipe = (Jogador*) malloc(quantidade * sizeof(*equipe));

    if (equipe == NULL) {
        printf("Erro: Falha na alocacao de memoria!\n");
        return 1;
    }

    printf("\n--- Preenchimento da Equipe ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Jogador %d - Nome: ", i + 1);
        scanf(" %[^\n]", equipe[i].nome);
        printf("Jogador %d - Numero: ", i + 1);
        scanf("%d", &equipe[i].numero);
    }

    printf("\n--- Equipe Escalada ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Posicao %d: %s (Camisa %d)\n", i + 1, equipe[i].nome, equipe[i].numero);
    }

    free(equipe);
    equipe = NULL;

    return 0;
}