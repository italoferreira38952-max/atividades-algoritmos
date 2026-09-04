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

#define MAX_PARTIDAS 100 

typedef enum {
    TIPO_INT,
    TIPO_STRING,
    TIPO_FLOAT
} TipoDado;


void exibirValorGenerico(const void *ptr, TipoDado tipo) {
    if (ptr == NULL) {
        printf("[Diagnostico]: Ponteiro nulo.\n");
        return;
    }

    printf("[Diagnostico] Valor: ");
    switch (tipo) {
        case TIPO_INT: {
            const int *valorInt = (const int *)ptr;
            printf("%d\n", *valorInt);
            break;
        }
        case TIPO_STRING: {
            const char *valorString = (const char *)ptr;
            printf("%s\n", valorString);
            break;
        }
        case TIPO_FLOAT: {
            const float *valorFloat = (const float *)ptr;
            printf("%.2f\n", *valorFloat);
            break;
        }
        default:
            printf("Tipo nao suportado.\n");
            break;
    }
}




int* criarHistorico(int tamanho) {
   
    if (tamanho <= 0 || tamanho > MAX_PARTIDAS) {
        printf("Tamanho invalido! Informe um valor entre 1 e %d.\n", MAX_PARTIDAS);
        return NULL;
    }

    int *historico = (int *) malloc(tamanho * sizeof(*historico));
    if (historico == NULL) {
        printf("Erro ao alocar memoria para o historico!\n");
        return NULL; 
    }

    return historico;
}


void preencherHistorico(int *historico, int tamanho) {
    if (historico == NULL) return;

    printf("\n--- Preenchimento do Historico de Partidas ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Pontuacao da partida %d: ", i + 1);
        scanf("%d", &historico[i]);
    }
    getchar();
}


void exibirHistorico(const int *historico, int tamanho) {
    if (historico == NULL) return;

    printf("\n--- Historico de Pontuacoes ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Partida %d: %d pts\n", i + 1, historico[i]);
    }
}


float calcularMediaHistorico(const int *historico, int tamanho) {
    if (historico == NULL || tamanho <= 0) return 0.0f;

    long soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += historico[i];
    }

    return (float)soma / tamanho;
}


void exibirMaiorResultado(const int *historico, int tamanho) {
    if (historico == NULL || tamanho <= 0) return;

    int maior = historico[0];
    int posicao = 0;

    for (int i = 1; i < tamanho; i++) {
        if (historico[i] > maior) {
            maior = historico[i];
            posicao = i;
        }
    }

    printf("\nMaior pontuacao: %d (Partida %d / Indice %d)\n", maior, posicao + 1, posicao);
}



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

void liberarMemoria(char (**jogadores)[TAM_EXIBICAO]) {
    if (jogadores != NULL && *jogadores != NULL) {
        free(*jogadores);
        *jogadores = NULL;
        printf("\n[Sistema]: Memoria de jogadores liberada.\n");
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
        printf("Quantidade invalida! Encerrando cadastro sem alocar memoria.\n");
        return 1;
    }
    getchar(); 

    jogadores = malloc(qtdJogadores * sizeof(*jogadores));

    if (jogadores == NULL) {
        printf("Erro: Falha na alocacao de memoria! Operacao encerrada.\n");
        return 1;
    }

    printf("\nNome da equipe: ");
    fgets(equipe, TAM_EQUIPE, stdin);
    limparBuffer(equipe);
    equipe[strcspn(equipe, "\n")] = '\0';

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

    int numPartidas = 0;
    int *historicoPartidas = NULL;

    printf("\nInforme a quantidade de partidas disputadas: ");
    if (scanf("%d", &numPartidas) == 1) {
        getchar(); 
        historicoPartidas = criarHistorico(numPartidas);

        if (historicoPartidas != NULL) {
            preencherHistorico(historicoPartidas, numPartidas);
            exibirHistorico(historicoPartidas, numPartidas);

            float media = calcularMediaHistorico(historicoPartidas, numPartidas);
            printf("\nMedia de pontuacao: %.2f\n", media);

            exibirMaiorResultado(historicoPartidas, numPartidas);
        } else {
            printf("Nao foi possivel registrar o historico de partidas.\n");
        }
    }

    printf("\n--- Diagnostico do Cadastro ---\n");
    exibirValorGenerico(&qtdJogadores, TIPO_INT);               
    exibirValorGenerico(jogadores[0], TIPO_STRING);             
    
    float taxaOcupacao = ((float)total / (LINHAS * COLUNAS)) * 100.0f;
    exibirValorGenerico(&taxaOcupacao, TIPO_FLOAT);             

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

    
    liberarMemoria(&jogadores);

    if (historicoPartidas != NULL) {
        free(historicoPartidas);
        historicoPartidas = NULL;
        printf("[Sistema]: Memoria do historico liberada.\n");
    }

    return 0;
}