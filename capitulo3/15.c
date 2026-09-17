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

void imprimir(Personagem p) {
    printf("ID:%d Nome:%s Vida:%d Pontuacao:%d Posicao:%d\n",
           p.id, p.nome, p.vida, p.pontuacao, p.posicao);
}

void alterarVida(Personagem *p, int delta) {
    p->vida += delta;
    if (p->vida < 0) p->vida = 0;
    if (p->vida > 100) p->vida = 100;
}

void alterarPontuacao(Personagem *p, int delta) {
    p->pontuacao += delta;
    if (p->pontuacao < 0) p->pontuacao = 0;
}

void alterarPosicao(Personagem *p, int delta, int limite) {
    p->posicao += delta;
    if (p->posicao < 0) p->posicao = 0;
    if (p->posicao > limite) p->posicao = limite;
}

int lerInteiro(const char *prompt) {
    int valor;
    printf("%s", prompt);
    scanf("%d", &valor);
    return valor;
}

void lerTexto(char *destino, int tamanho, const char *prompt) {
    printf("%s", prompt);
    scanf(" %29[^\n]", destino);
    (void) tamanho;
}

int main(void) {
    Personagem heroi;

    heroi.id = lerInteiro("ID do personagem: ");
    lerTexto(heroi.nome, TAM_NOME, "Nome do personagem: ");
    heroi.vida = lerInteiro("Vida inicial: ");
    heroi.pontuacao = lerInteiro("Pontuacao inicial: ");
    heroi.posicao = lerInteiro("Posicao inicial: ");

    printf("\nAntes:\n");
    imprimir(heroi);

    int deltaVida = lerInteiro("\nAlterar vida em quanto: ");
    int deltaPontuacao = lerInteiro("Alterar pontuacao em quanto: ");
    int deltaPosicao = lerInteiro("Alterar posicao em quanto: ");

    alterarVida(&heroi, deltaVida);
    alterarPontuacao(&heroi, deltaPontuacao);
    alterarPosicao(&heroi, deltaPosicao, 99);

    printf("\nDepois:\n");
    imprimir(heroi);

    return 0;
}