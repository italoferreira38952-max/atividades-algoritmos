#include <stdio.h>
#include <string.h>

#define TAM_NOME 50
#define TAM_APELIDO 15
#define TAM_SENHA 20

int main(void) {
    char nome[TAM_NOME];
    char apelido[TAM_APELIDO];
    char senha[TAM_SENHA];
    char confirmaSenha[TAM_SENHA];

    printf("Nome: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Apelido: ");
    fgets(apelido, TAM_APELIDO, stdin);
    apelido[strcspn(apelido, "\n")] = '\0';

    printf("Senha: ");
    fgets(senha, TAM_SENHA, stdin);
    senha[strcspn(senha, "\n")] = '\0';

    printf("Confirme a senha: ");
    fgets(confirmaSenha, TAM_SENHA, stdin);
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

    return 0;
}