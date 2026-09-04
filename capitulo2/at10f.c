#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 50
#define TAM_APELIDO 15
#define TAM_SENHA 20
#define TAM_EQUIPE 20
#define TAM_EXIBICAO 40 

#define LINHAS 4
#define COLUNAS 5
#define LIVRE -1   

void inicializarMapa(int mapa[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            mapa[i][j] = LIVRE;
        }
    }
}

int coordenadaValida(int linha, int coluna) {
    return (linha >= 0 && linha < LINHAS && coluna >= 0 && coluna < COLUNAS);
}

int posicionarJogador(int mapa[LINHAS][COLUNAS], int linha, int coluna, int idJogador) {
    if (!coordenadaValida(linha, coluna)) {
        printf("Coordenada invalida.\n");
        return 0;
    }
    if (mapa[linha][coluna] != LIVRE) {
        printf("Celula ja ocupada.\n");
        return 0;
    }
    mapa[linha][coluna] = idJogador;
    return 1;
}

int removerPosicao(int mapa[LINHAS][COLUNAS], int linha, int coluna) {
    if (!coordenadaValida(linha, coluna)) {
        printf("Coordenada invalida.\n");
        return 0;
    }
    if (mapa[linha][coluna] == LIVRE) {
        printf("Celula ja esta livre.\n");
        return 0;
    }
    mapa[linha][coluna] = LIVRE;
    return 1;
}

int localizarJogador(int mapa[LINHAS][COLUNAS], int idJogador, int *linha, int *coluna) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (mapa[i][j] == idJogador) {
                *linha = i;
                *coluna = j;
                return 1;
            }
        }
    }
    return 0;
}

int reposicionarJogador(int mapa[LINHAS][COLUNAS], int idJogador, int novaLinha, int novaColuna) {
    int linhaAtual, colunaAtual;

    if (!localizarJogador(mapa, idJogador, &linhaAtual, &colunaAtual)) {
        printf("Jogador ainda nao esta no mapa.\n");
        return 0;
    }
    if (!coordenadaValida(novaLinha, novaColuna)) {
        printf("Coordenada invalida.\n");
        return 0;
    }
    if (mapa[novaLinha][novaColuna] != LIVRE) {
        printf("Celula de destino ja ocupada.\n");
        return 0;
    }

    mapa[linhaAtual][colunaAtual] = LIVRE;
    mapa[novaLinha][novaColuna] = idJogador;
    return 1;
}

void exibirMapa(int mapa[LINHAS][COLUNAS]) {
    printf("\n--- Mapa da equipe ---\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (mapa[i][j] == LIVRE) {
                printf(" .  ");
            } else {
                printf("%2d  ", mapa[i][j]);
            }
        }
        printf("\n");
    }
}

void limparBuffer(char *texto) {
    if (strchr(texto, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int main(void) {
    char nome[TAM_NOME];
    char apelido[TAM_APELIDO];
    char senha[TAM_SENHA];
    char confirmaSenha[TAM_SENHA];
    char equipe[TAM_EQUIPE];

    char (*jogadores)[TAM_EXIBICAO] = NULL;
    int qtdJogadores = 0;
    int total = 0;

    int mapa[LINHAS][COLUNAS];
    inicializarMapa(mapa);

    printf("Nome: ");
    fgets(nome, TAM_NOME, stdin);
    limparBuffer(nome);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Apelido: ");
    fgets(apelido, TAM_APELIDO, stdin);
    limparBuffer(apelido);
    apelido[strcspn(apelido, "\n")] = '\0';

    printf("Senha: ");
    fgets(senha, TAM_SENHA, stdin);
    limparBuffer(senha);
    senha[strcspn(senha, "\n")] = '\0';

    printf("Confirme a senha: ");
    fgets(confirmaSenha, TAM_SENHA, stdin);
    limparBuffer(confirmaSenha);
    confirmaSenha[strcspn(confirmaSenha, "\n")] = '\0';

    printf("\n--- Resultado ---\n");

    if (strlen(apelido) < 3 || strlen(apelido) > TAM_APELIDO - 1) {
        printf("Apelido invalido. Corrija o apelido.\n");
    } else {
        printf("Apelido valido.\n");
    }

    if (strcmp(senha, confirmaSenha) != 0) {
        printf("Senhas nao conferem. Corrija a senha.\n");
    } else {
        printf("Senha confirmada.\n");
    }

    printf("\nInforme a quantidade de jogadores da equipe: ");
    if (scanf("%d", &qtdJogadores) != 1 || qtdJogadores <= 0) {
        printf("Quantidade invalida! Operacao encerrada.\n");
        return 1;
    }
    getchar();

    jogadores = malloc(qtdJogadores * sizeof(*jogadores));

    if (jogadores == NULL) {
        printf("Erro: Falha ao alocar memoria para os jogadores! Operacao encerrada.\n");
        return 1; 
    }

    printf("\nNome da equipe: ");
    fgets(equipe, TAM_EQUIPE, stdin);
    limparBuffer(equipe);
    equipe[strcspn(equipe, "\n")] = '\0';

    // Cadastro do primeiro jogador
    if (strlen(apelido) + strlen(" - ") + strlen(equipe) < TAM_EXIBICAO) {
        strcpy(jogadores[total], apelido);     
        strcat(jogadores[total], " - ");       
        strcat(jogadores[total], equipe);      
        printf("Nome de exibicao: %s\n", jogadores[total]);
        total++;
    } else {
        printf("Nome de exibicao nao coube no espaco reservado.\n");
    }

    while (total < qtdJogadores) {
        char apelidoTmp[TAM_APELIDO];
        char equipeTmp[TAM_EQUIPE];

        printf("\nJogador %d\n", total + 1);
        printf("Apelido: ");
        fgets(apelidoTmp, TAM_APELIDO, stdin);
        limparBuffer(apelidoTmp);
        apelidoTmp[strcspn(apelidoTmp, "\n")] = '\0';

        printf("Equipe: ");
        fgets(equipeTmp, TAM_EQUIPE, stdin);
        limparBuffer(equipeTmp);
        equipeTmp[strcspn(equipeTmp, "\n")] = '\0';

        if (strlen(apelidoTmp) + strlen(" - ") + strlen(equipeTmp) < TAM_EXIBICAO) {
            strcpy(jogadores[total], apelidoTmp);
            strcat(jogadores[total], " - ");
            strcat(jogadores[total], equipeTmp);
            total++;
        } else {
            printf("Nome de exibicao nao coube no espaco reservado. Tente novamente.\n");
        }
    }

    printf("\n--- Lista de participantes ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d: %s\n", i, jogadores[i]);
    }

    char busca[TAM_EXIBICAO];
    printf("\nDigite o nome de exibicao para buscar: ");
    fgets(busca, TAM_EXIBICAO, stdin);
    limparBuffer(busca);
    busca[strcspn(busca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(jogadores[i], busca) == 0) {
            printf("Encontrado na posicao %d: %s\n", i, jogadores[i]);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Nome nao encontrado na lista.\n");
    }

    printf("\n--- Posicionar jogadores no mapa (%dx%d) ---\n", LINHAS, COLUNAS);
    for (int i = 0; i < total; i++) {
        int linha, coluna;
        int ok = 0;

        while (!ok) {
            printf("Linha e coluna para \"%s\" (0-%d 0-%d): ",
                   jogadores[i], LINHAS - 1, COLUNAS - 1);
            scanf("%d %d", &linha, &coluna);
            getchar(); 

            ok = posicionarJogador(mapa, linha, coluna, i);
        }
    }

    exibirMapa(mapa);

    int idReposicionar, novaLinha, novaColuna;
    printf("\nIndice do jogador a reposicionar (0-%d): ", total - 1);
    scanf("%d", &idReposicionar);
    getchar();

    printf("Nova linha e coluna: ");
    scanf("%d %d", &novaLinha, &novaColuna);
    getchar();

    if (reposicionarJogador(mapa, idReposicionar, novaLinha, novaColuna)) {
        printf("Jogador reposicionado com sucesso.\n");
    }

    exibirMapa(mapa);

    free(jogadores);
    jogadores = NULL;

    return 0;
}