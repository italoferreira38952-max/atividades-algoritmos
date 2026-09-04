#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TAM_NOME 50
#define TAM_APELIDO 15
#define TAM_SENHA 20
#define TAM_EQUIPE 20
#define TAM_EXIBICAO 40 

#define LINHAS_MAPA_FIXO 4
#define COLUNAS_MAPA_FIXO 5
#define LIVRE -1   

#define MAX_PARTIDAS 100
#define MAX_DIMENSAO_MAPA 100 

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

void limparBufferTeclado(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparBuffer(char *texto) {
    if (strchr(texto, '\n') == NULL) {
        limparBufferTeclado();
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
    limparBufferTeclado();
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

    printf("Maior pontuacao: %d (Partida %d / Indice %d)\n", maior, posicao + 1, posicao);
}

int* criarMatrizLinear(int linhas, int colunas) {
    if (linhas <= 0 || colunas <= 0 || linhas > MAX_DIMENSAO_MAPA || colunas > MAX_DIMENSAO_MAPA) {
        printf("Dimensoes invalidas.\n");
        return NULL;
    }

    if (linhas > INT_MAX / colunas) {
        printf("Erro: Dimensoes resultam em overflow de memoria.\n");
        return NULL;
    }

    int *matriz = (int *) malloc(linhas * colunas * sizeof(*matriz));
    if (matriz == NULL) {
        printf("Erro de alocacao na matriz linear.\n");
        return NULL;
    }

    for (int i = 0; i < linhas * colunas; i++) {
        matriz[i] = LIVRE;
    }

    return matriz;
}

void preencherMatrizLinear(int *matriz, int linhas, int colunas) {
    if (matriz == NULL) return;
    printf("\n--- Preenchendo Matriz Linear (Linha por Linha) ---\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i * colunas + j] = (i * colunas + j) + 1;
        }
    }
}

void exibirMatrizLinear(const int *matriz, int linhas, int colunas) {
    if (matriz == NULL) return;
    printf("\n--- Exibindo Matriz Linear (Bloco Continuo) ---\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%3d ", matriz[i * colunas + j]);
        }
        printf("\n");
    }
}

void liberarMatrizLinear(int **matriz) {
    if (matriz != NULL && *matriz != NULL) {
        free(*matriz);
        *matriz = NULL;
    }
}

int** criarMatrizPonteiros(int linhas, int colunas) {
    if (linhas <= 0 || colunas <= 0 || linhas > MAX_DIMENSAO_MAPA || colunas > MAX_DIMENSAO_MAPA) {
        printf("Dimensoes invalidas.\n");
        return NULL;
    }

    int **matriz = (int **) malloc(linhas * sizeof(*matriz));
    if (matriz == NULL) {
        printf("Erro ao alocar vetor de linhas.\n");
        return NULL;
    }

    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *) malloc(colunas * sizeof(**matriz));
        
        if (matriz[i] == NULL) {
            printf("Erro de alocacao na linha %d. Desfazendo alocacoes anteriores...\n", i);
            for (int k = 0; k < i; k++) {
                free(matriz[k]);
            }
            free(matriz);
            return NULL;
        }

        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = LIVRE;
        }
    }

    return matriz;
}

void preencherMatrizPonteiros(int **matriz, int linhas, int colunas) {
    if (matriz == NULL) return;
    printf("\n--- Preenchendo Matriz de Ponteiros ---\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = (i * colunas + j) + 1;
        }
    }
}

void exibirMatrizPonteiros(int **matriz, int linhas, int colunas) {
    if (matriz == NULL) return;
    printf("\n--- Exibindo Matriz de Ponteiros (Vetor de Ponteiros) ---\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%3d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void liberarMatrizPonteiros(int ***matriz, int linhas) {
    if (matriz != NULL && *matriz != NULL) {
        for (int i = 0; i < linhas; i++) {
            if ((*matriz)[i] != NULL) {
                free((*matriz)[i]);
            }
        }
        free(*matriz);
        *matriz = NULL;
    }
}

void executarCadastroEPosicionamento(void) {
    char nome[TAM_NOME], apelido[TAM_APELIDO], senha[TAM_SENHA], confirmaSenha[TAM_SENHA], equipe[TAM_EQUIPE];
    char (*jogadores)[TAM_EXIBICAO] = NULL;
    int qtdJogadores = 0, total = 0;

    printf("\n=== CADASTRO E POSICIONAMENTO DA EQUIPE ===\n");
    printf("Nome do responsavel: ");
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

    if (strcmp(senha, confirmaSenha) != 0) {
        printf("Erro: Senhas nao conferem. Operacao cancelada.\n");
        return;
    }

    printf("Quantidade de jogadores da equipe: ");
    if (scanf("%d", &qtdJogadores) != 1 || qtdJogadores <= 0) {
        printf("Quantidade invalida.\n");
        limparBufferTeclado();
        return;
    }
    limparBufferTeclado();

    jogadores = malloc(qtdJogadores * sizeof(*jogadores));
    if (jogadores == NULL) {
        printf("Erro na alocacao de jogadores.\n");
        return;
    }

    printf("Nome da equipe: ");
    fgets(equipe, TAM_EQUIPE, stdin);
    limparBuffer(equipe);
    equipe[strcspn(equipe, "\n")] = '\0';

    snprintf(jogadores[total], TAM_EXIBICAO, "%s - %s", apelido, equipe);
    total++;

    while (total < qtdJogadores) {
        char apelidoTmp[TAM_APELIDO], equipeTmp[TAM_EQUIPE];

        printf("\nJogador %d - Apelido: ", total + 1);
        fgets(apelidoTmp, TAM_APELIDO, stdin);
        limparBuffer(apelidoTmp);
        apelidoTmp[strcspn(apelidoTmp, "\n")] = '\0';

        printf("Jogador %d - Equipe: ", total + 1);
        fgets(equipeTmp, TAM_EQUIPE, stdin);
        limparBuffer(equipeTmp);
        equipeTmp[strcspn(equipeTmp, "\n")] = '\0';

        if (strlen(apelidoTmp) + strlen(" - ") + strlen(equipeTmp) < TAM_EXIBICAO) {
            snprintf(jogadores[total], TAM_EXIBICAO, "%s - %s", apelidoTmp, equipeTmp);
            total++;
        } else {
            printf("Nome de exibicao muito longo! Tente novamente.\n");
        }
    }

    printf("\n--- Equipe Cadastrada com Sucesso ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d: %s\n", i, jogadores[i]);
    }

    free(jogadores);
    jogadores = NULL;
}

int main(void) {
    int opcao = 0;

    int *historicoPartidas = NULL;
    int numPartidas = 0;

    int *matrizLinear = NULL;
    int **matrizPonteiros = NULL;
    int linMatriz = 0, colMatriz = 0;

    do {
        printf("   SISTEMA DE DIAGNOSTICO E CADASTRO    \n");
        printf("1. Realizar Cadastro da Equipe\n");
        printf("2. Gerenciar Historico de Partidas\n");
        printf("3. Testar Matriz em Bloco Continuo (Linear)\n");
        printf("4. Testar Matriz por Vetor de Ponteiros\n");
        printf("5. Executar Diagnostico de Tipos (void*)\n");
        printf("0. Sair do Sistema\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida.\n");
            limparBufferTeclado();
            continue;
        }
        limparBufferTeclado();

        switch (opcao) {
            case 1:
                executarCadastroEPosicionamento();
                break;

            case 2:
                if (historicoPartidas != NULL) {
                    free(historicoPartidas);
                    historicoPartidas = NULL;
                }
                printf("\nQuantidade de partidas a registrar: ");
                if (scanf("%d", &numPartidas) == 1) {
                    limparBufferTeclado();
                    historicoPartidas = criarHistorico(numPartidas);
                    if (historicoPartidas != NULL) {
                        preencherHistorico(historicoPartidas, numPartidas);
                        exibirHistorico(historicoPartidas, numPartidas);
                        printf("Media de Pontuacao: %.2f\n", calcularMediaHistorico(historicoPartidas, numPartidas));
                        exibirMaiorResultado(historicoPartidas, numPartidas);
                    }
                } else {
                    limparBufferTeclado();
                }
                break;

            case 3:
                liberarMatrizLinear(&matrizLinear);
                printf("\nInforme as linhas e colunas (ex: 4 5): ");
                if (scanf("%d %d", &linMatriz, &colMatriz) == 2) {
                    limparBufferTeclado();
                    matrizLinear = criarMatrizLinear(linMatriz, colMatriz);
                    if (matrizLinear != NULL) {
                        preencherMatrizLinear(matrizLinear, linMatriz, colMatriz);
                        exibirMatrizLinear(matrizLinear, linMatriz, colMatriz);
                    }
                } else {
                    limparBufferTeclado();
                }
                break;

            case 4:
                liberarMatrizPonteiros(&matrizPonteiros, linMatriz);
                printf("\nInforme as linhas e colunas (ex: 4 5): ");
                if (scanf("%d %d", &linMatriz, &colMatriz) == 2) {
                    limparBufferTeclado();
                    matrizPonteiros = criarMatrizPonteiros(linMatriz, colMatriz);
                    if (matrizPonteiros != NULL) {
                        preencherMatrizPonteiros(matrizPonteiros, linMatriz, colMatriz);
                        exibirMatrizPonteiros(matrizPonteiros, linMatriz, colMatriz);
                    }
                } else {
                    limparBufferTeclado();
                }
                break;

            case 5: {
                printf("\n--- Teste da Funcao Generica ---\n");
                int exemploInt = 42;
                float exemploFloat = 98.6f;
                char exemploStr[] = "Equipe Alpha";

                exibirValorGenerico(&exemploInt, TIPO_INT);
                exibirValorGenerico(&exemploFloat, TIPO_FLOAT);
                exibirValorGenerico(exemploStr, TIPO_STRING);
                break;
            }

            case 0:
                printf("\nEncerrando e liberando todos os recursos...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }

    } while (opcao != 0);

    if (historicoPartidas != NULL) {
        free(historicoPartidas);
        historicoPartidas = NULL;
    }
    liberarMatrizLinear(&matrizLinear);
    liberarMatrizPonteiros(&matrizPonteiros, linMatriz);

    printf("[Sistema]: Todos os recursos foram liberados com sucesso.\n");
    return 0;
}