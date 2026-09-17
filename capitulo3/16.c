#include <stdio.h>
#include <string.h>

#define TAM_NOME 30

typedef struct {
    int id;
    char nome[TAM_NOME];
    int vida;
    int pontuacao;
    int posicao;
} Personagem;

Personagem criarPersonagem(int id, const char *nome, int vida, int pontuacao, int posicao) {
    Personagem p;
    p.id = id;
    strncpy(p.nome, nome, TAM_NOME - 1);
    p.nome[TAM_NOME - 1] = '\0';
    p.vida = vida;
    p.pontuacao = pontuacao;
    p.posicao = posicao;
    return p;
}

void imprimir(Personagem p) {
    printf("ID:%d Nome:%s Vida:%d Pontuacao:%d Posicao:%d\n",
           p.id, p.nome, p.vida, p.pontuacao, p.posicao);
}

void renomear(Personagem *p) {
    char buffer[TAM_NOME];

    printf("Novo nome: ");
    fgets(buffer, sizeof(buffer), stdin);

    size_t tam = strlen(buffer);
    if (tam > 0 && buffer[tam - 1] == '\n') {
        buffer[tam - 1] = '\0';
    }

    strncpy(p->nome, buffer, TAM_NOME - 1);
    p->nome[TAM_NOME - 1] = '\0';
}

int lerInteiro(const char *prompt) {
    int valor;
    printf("%s", prompt);
    scanf("%d", &valor);
    return valor;
}

int main(void) {
    /* Inicializacao designada: exemplo fixo, mostrando a sintaxe. */
    Personagem inicial = { .id = 1, .nome = "Guerreiro", .vida = 100, .pontuacao = 0, .posicao = 0 };

    printf("Inicializacao designada:\n");
    imprimir(inicial);

    printf("\nDados do proximo personagem (criado pela funcao construtora):\n");
    int id = lerInteiro("ID: ");
    char nome[TAM_NOME];
    printf("Nome: ");
    scanf(" %29[^\n]", nome);
    int vida = lerInteiro("Vida: ");
    int pontuacao = lerInteiro("Pontuacao: ");
    int posicao = lerInteiro("Posicao: ");
    getchar();

    Personagem construido = criarPersonagem(id, nome, vida, pontuacao, posicao);

    printf("\nCriado pela funcao construtora:\n");
    imprimir(construido);

    renomear(&construido);

    printf("\nApos renomear:\n");
    imprimir(construido);

    return 0;
}