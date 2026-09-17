#include <stdio.h>
#include <stdlib.h>
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

Personagem criarPersonagem(int id, const char *nome, int vida,
                           int pontuacao, int posicao) {
    Personagem p;

    p.id = id;

    strncpy(p.nome, nome, TAM_NOME - 1);
    p.nome[TAM_NOME - 1] = '\0';

    if (vida < 0)
        p.vida = 0;
    else if (vida > VIDA_MAX)
        p.vida = VIDA_MAX;
    else
        p.vida = vida;

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

int adicionarPersonagem(Personagem **equipe,
                        int *quantidade,
                        int *capacidade,
                        Personagem p) {

    if (*quantidade >= *capacidade) {
        int novaCapacidade = (*capacidade) * 2;

        Personagem *temp = realloc(
            *equipe,
            novaCapacidade * sizeof(Personagem)
        );

        if (temp == NULL)
            return 0;

        *equipe = temp;
        *capacidade = novaCapacidade;
    }

    (*equipe)[*quantidade] = p;
    (*quantidade)++;

    return 1;
}

void imprimirEquipe(Personagem *equipe, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("[%d] ", i);
        imprimir(equipe[i]);
    }
}

int intercalar(Personagem *A, int nA,
               Personagem *B, int nB,
               Personagem *C,
               long long *comparacoes) {

    int i = 0;
    int j = 0;
    int k = 0;

    *comparacoes = 0;

    while (i < nA && j < nB) {
        (*comparacoes)++;

        if (A[i].pontuacao <= B[j].pontuacao) {
            C[k] = A[i];
            i++;
        } else {
            C[k] = B[j];
            j++;
        }

        k++;
    }

    while (j < nB) {
        C[k] = B[j];
        j++;
        k++;
    }

    while (i < nA) {
        C[k] = A[i];
        i++;
        k++;
    }

    return k;
}

void mergeSort(Personagem *vetor, int inicio, int fim) {

    // dividir
    if (inicio >= fim)
        return;

    int meio = inicio + (fim - inicio) / 2;

    // resolver
    mergeSort(vetor, inicio, meio);
    mergeSort(vetor, meio + 1, fim);

    // combinar
}

int main(void) {

    int id = lerInteiro("ID: ");

    char nome[TAM_NOME];

    printf("Nome: ");
    scanf(" %29[^\n]", nome);

    int vida = lerInteiro("Vida: ");
    int pontuacao = lerInteiro("Pontuacao: ");
    int posicao = lerInteiro("Posicao: ");

    Personagem heroi =
        criarPersonagem(id, nome, vida, pontuacao, posicao);

    printf("\nPersonagem original (main):\n");
    imprimir(heroi);

    printf("\nForca calculada: %d\n",
           calcularForca(heroi));

    printf("Esta vivo: %s\n",
           estaVivo(heroi) ? "sim" : "nao");

    printf("\nChamando funcao que altera apenas a copia:\n");
    demonstrarCopia(heroi);

    printf("\nPersonagem original (main) apos a chamada:\n");
    imprimir(heroi);

    alterarVida(&heroi, -30);
    moverPersonagem(&heroi, 10);
    adicionarPontos(&heroi, 150);

    printf("\nPersonagem apos modificacoes via ponteiro:\n");
    imprimir(heroi);

    int capacidade = 2;
    int quantidade = 0;

    Personagem *equipe =
        malloc(capacidade * sizeof(Personagem));

    if (equipe == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    adicionarPersonagem(
        &equipe,
        &quantidade,
        &capacidade,
        heroi
    );

    Personagem p2 =
        criarPersonagem(2, "Guerreiro", 80, 200, 10);

    Personagem p3 =
        criarPersonagem(3, "Mago", 60, 350, 20);

    Personagem p4 =
        criarPersonagem(4, "Arqueiro", 90, 150, 30);

    adicionarPersonagem(
        &equipe,
        &quantidade,
        &capacidade,
        p2
    );

    adicionarPersonagem(
        &equipe,
        &quantidade,
        &capacidade,
        p3
    );

    adicionarPersonagem(
        &equipe,
        &quantidade,
        &capacidade,
        p4
    );

    printf("\nEquipe:\n");
    imprimirEquipe(equipe, quantidade);

    printf("\nQuantidade: %d\n", quantidade);
    printf("Capacidade: %d\n", capacidade);

    Personagem A[3] = {
        criarPersonagem(1, "A1", 100, 100, 0),
        criarPersonagem(2, "A2", 100, 300, 0),
        criarPersonagem(3, "A3", 100, 500, 0)
    };

    Personagem B[3] = {
        criarPersonagem(4, "B1", 100, 200, 0),
        criarPersonagem(5, "B2", 100, 400, 0),
        criarPersonagem(6, "B3", 100, 600, 0)
    };

    Personagem C[6];

    long long comparacoes;

    int total = intercalar(
        A, 3,
        B, 3,
        C,
        &comparacoes
    );

    printf("\nVetor A:\n");
    imprimirEquipe(A, 3);

    printf("\nVetor B:\n");
    imprimirEquipe(B, 3);

    printf("\nVetor C intercalado:\n");
    imprimirEquipe(C, total);

    printf("\nComparacoes realizadas: %lld\n",
           comparacoes);

    mergeSort(equipe, 0, quantidade - 1);

    free(equipe);

    return 0;
}
