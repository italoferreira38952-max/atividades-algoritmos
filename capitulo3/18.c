#include <stdio.h>
#include <string.h>

#define TAM_NOME 30
#define VIDA_MAX 100

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
    
    if (vida < 0) p.vida = 0;
    else if (vida > VIDA_MAX) p.vida = VIDA_MAX;
    else p.vida = vida;

    p.pontuacao = pontuacao < 0 ? 0 : pontuacao;
    p.posicao = posicao;
    return p;
}

void imprimir(Personagem p) {
    printf("ID:%d Nome:%s Vida:%d Pontuacao:%d Posicao:%d\n",
           p.id, p.nome, p.vida, p.pontuacao, p.posicao);
}

int calcularForca(Personagem p) {
    return p.vida + p.pontuacao;
}

int estaVivo(Personagem p) {
    return p.vida > 0;
}

void demonstrarCopia(Personagem p) {
    p.vida = 0;
    p.pontuacao = 9999;
    strncpy(p.nome, "Copia Alterada", TAM_NOME - 1);
    p.nome[TAM_NOME - 1] = '\0';

    printf("Dentro da funcao (copia local alterada):\n");
    imprimir(p);
}

int alterarVida(Personagem *p, int deltaVida) {
    if (p == NULL) return 0;

    int novaVida = p->vida + deltaVida;

    if (novaVida < 0) {
        p->vida = 0;
    } else if (novaVida > VIDA_MAX) {
        p->vida = VIDA_MAX;
    } else {
        p->vida = novaVida;
    }
    return 1;
}

int moverPersonagem(Personagem *p, int passos) {
    if (p == NULL) return 0;

    (*p).posicao += passos;

    return 1;
}

int adicionarPontos(Personagem *p, int pontos) {
    if (p == NULL) return 0;

    if (p->pontuacao + pontos < 0) {
        p->pontuacao = 0;
    } else {
        p->pontuacao += pontos;
    }
    return 1;
}

int lerInteiro(const char *prompt) {
    int valor;
    printf("%s", prompt);
    scanf("%d", &valor);
    return valor;
}

int main(void) {
    int id = lerInteiro("ID: ");
    char nome[TAM_NOME];
    printf("Nome: ");
    scanf(" %29[^\n]", nome);
    int vida = lerInteiro("Vida: ");
    int pontuacao = lerInteiro("Pontuacao: ");
    int posicao = lerInteiro("Posicao: ");

    Personagem heroi = criarPersonagem(id, nome, vida, pontuacao, posicao);

    printf("\nPersonagem original (main):\n");
    imprimir(heroi);

    printf("\nForca calculada: %d\n", calcularForca(heroi));
    printf("Esta vivo: %s\n", estaVivo(heroi) ? "sim" : "nao");

    printf("\nChamando funcao que altera apenas a copia:\n");
    demonstrarCopia(heroi);

    printf("\nPersonagem original (main) apos a chamada:\n");
    imprimir(heroi);

    alterarVida(&heroi, -30);
    moverPersonagem(&heroi, 10);
    adicionarPontos(&heroi, 150);

    printf("\nPersonagem apos modificacoes via ponteiro:\n");
    imprimir(heroi);

    /* Custo da copia: cada chamada por valor duplica todos os campos
       da struct (id, vetor de nome, vida, pontuacao, posicao) na pilha.
       Para structs pequenas isso e barato e seguro, pois garante que a
       funcao nao modifique o original. Para structs grandes ou chamadas
       muito frequentes, esse custo de copia pode pesar, e nesses casos
       passar um ponteiro (const Personagem *) seria mais eficiente,
       desde que a intencao continue sendo apenas ler os dados. */

    return 0;
}