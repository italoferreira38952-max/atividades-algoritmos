#include <stdio.h>
#include <string.h>

#define TAM_NOME 50
#define TAM_APELIDO 15
#define TAM_SENHA 20
#define TAM_EQUIPE 20
#define TAM_EXIBICAO 40  
#define MAX_JOGADORES 5

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

    char jogadores[MAX_JOGADORES][TAM_EXIBICAO];
    int total = 0;

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

    while (total < MAX_JOGADORES) {
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

    return 0;
}