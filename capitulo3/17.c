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

    /* Custo da copia: cada chamada por valor duplica todos os campos
       da struct (id, vetor de nome, vida, pontuacao, posicao) na pilha.
       Para structs pequenas isso e barato e seguro, pois garante que a
       funcao nao modifique o original. Para structs grandes ou chamadas
       muito frequentes, esse custo de copia pode pesar, e nesses casos
       passar um ponteiro (const Personagem *) seria mais eficiente,
       desde que a intencao continue sendo apenas ler os dados. */

    return 0;
}