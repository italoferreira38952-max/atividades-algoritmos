#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 30
#define VIDA_MAX 100

typedef struct {
    int x;
    int y;
} Posicao;

typedef enum {
    GUERREIRO,
    MAGO,
    ARQUEIRO
} Classe;

typedef struct {
    int id;
    char nome[TAM_NOME];
    int vida;
    int pontuacao;
    Posicao posicao;
    Classe classe;
} Personagem;

typedef struct {
    Personagem *personagens;
    int quantidade;
    int capacidade;
} Equipe;

Personagem criarPersonagem(int id, const char *nome, int vida,
                           int pontuacao, int x, int y,
                           Classe classe) {
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

    p.posicao.x = x;
    p.posicao.y = y;

    p.classe = classe;

    return p;
}

const char *classeParaTexto(Classe classe) {
    switch (classe) {
        case GUERREIRO:
            return "Guerreiro";
        case MAGO:
            return "Mago";
        case ARQUEIRO:
            return "Arqueiro";
        default:
            return "Desconhecida";
    }
}

void imprimir(Personagem p) {
    printf("ID:%d Nome:%s Vida:%d Pontuacao:%d Posicao:(%d,%d) Classe:%s\n",
           p.id,
           p.nome,
           p.vida,
           p.pontuacao,
           p.posicao.x,
           p.posicao.y,
           classeParaTexto(p.classe));
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
    if (p == NULL)
        return 0;

    int novaVida = p->vida + deltaVida;

    if (novaVida < 0)
        p->vida = 0;
    else if (novaVida > VIDA_MAX)
        p->vida = VIDA_MAX;
    else
        p->vida = novaVida;

    return 1;
}

int moverPersonagem(Personagem *p, int passosX, int passosY) {
    if (p == NULL)
        return 0;

    p->posicao.x += passosX;
    p->posicao.y += passosY;

    return 1;
}

int adicionarPontos(Personagem *p, int pontos) {
    if (p == NULL)
        return 0;

    if (p->pontuacao + pontos < 0)
        p->pontuacao = 0;
    else
        p->pontuacao += pontos;

    return 1;
}

int lerInteiro(const char *prompt) {
    int valor;

    printf("%s", prompt);
    scanf("%d", &valor);

    return valor;
}

int adicionarPersonagem(Equipe *equipe, Personagem p) {
    if (equipe == NULL)
        return 0;

    if (equipe->quantidade >= equipe->capacidade) {
        int novaCapacidade = equipe->capacidade * 2;

        Personagem *temp = realloc(
            equipe->personagens,
            novaCapacidade * sizeof(Personagem)
        );

        if (temp == NULL)
            return 0;

        equipe->personagens = temp;
        equipe->capacidade = novaCapacidade;
    }

    equipe->personagens[equipe->quantidade] = p;
    equipe->quantidade++;

    return 1;
}

Personagem *buscarPersonagem(Equipe *equipe, int id) {
    if (equipe == NULL)
        return NULL;

    for (int i = 0; i < equipe->quantidade; i++) {
        if (equipe->personagens[i].id == id)
            return &equipe->personagens[i];
    }

    return NULL;
}

void listarEquipe(Equipe *equipe) {
    if (equipe == NULL)
        return;

    if (equipe->quantidade == 0) {
        printf("\nEquipe vazia.\n");
        return;
    }

    for (int i = 0; i < equipe->quantidade; i++) {
        printf("[%d] ", i);
        imprimir(equipe->personagens[i]);
    }
}

void cadastrarPersonagem(Equipe *equipe) {
    int id;
    char nome[TAM_NOME];
    int vida;
    int pontuacao;
    int x;
    int y;
    int classe;

    printf("\nID: ");
    scanf("%d", &id);

    if (buscarPersonagem(equipe, id) != NULL) {
        printf("ID ja cadastrado.\n");
        return;
    }

    printf("Nome: ");
    scanf(" %29[^\n]", nome);

    printf("Vida: ");
    scanf("%d", &vida);

    printf("Pontuacao: ");
    scanf("%d", &pontuacao);

    printf("Posicao X: ");
    scanf("%d", &x);

    printf("Posicao Y: ");
    scanf("%d", &y);

    printf("Classe:\n");
    printf("0 - Guerreiro\n");
    printf("1 - Mago\n");
    printf("2 - Arqueiro\n");
    scanf("%d", &classe);

    if (classe < GUERREIRO || classe > ARQUEIRO) {
        printf("Classe invalida.\n");
        return;
    }

    Personagem p = criarPersonagem(
        id,
        nome,
        vida,
        pontuacao,
        x,
        y,
        (Classe)classe
    );

    if (adicionarPersonagem(equipe, p))
        printf("Personagem cadastrado.\n");
    else
        printf("Erro ao cadastrar personagem.\n");
}

void buscarEImprimir(Equipe *equipe) {
    int id;

    printf("\nID do personagem: ");
    scanf("%d", &id);

    Personagem *p = buscarPersonagem(equipe, id);

    if (p == NULL)
        printf("Personagem nao encontrado.\n");
    else
        imprimir(*p);
}

void alterarPersonagem(Equipe *equipe) {
    int id;

    printf("\nID do personagem: ");
    scanf("%d", &id);

    Personagem *p = buscarPersonagem(equipe, id);

    if (p == NULL) {
        printf("Personagem nao encontrado.\n");
        return;
    }

    int opcao;

    printf("\n1 - Alterar vida\n");
    printf("2 - Adicionar/remover pontos\n");
    printf("3 - Mover personagem\n");
    printf("4 - Alterar classe\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        int valor = lerInteiro("Alteracao de vida: ");
        alterarVida(p, valor);
    }
    else if (opcao == 2) {
        int valor = lerInteiro("Alteracao de pontuacao: ");
        adicionarPontos(p, valor);
    }
    else if (opcao == 3) {
        int x = lerInteiro("Passos em X: ");
        int y = lerInteiro("Passos em Y: ");
        moverPersonagem(p, x, y);
    }
    else if (opcao == 4) {
        int classe = lerInteiro("Nova classe (0-Guerreiro, 1-Mago, 2-Arqueiro): ");

        if (classe >= GUERREIRO && classe <= ARQUEIRO)
            p->classe = (Classe)classe;
        else
            printf("Classe invalida.\n");
    }
    else {
        printf("Opcao invalida.\n");
        return;
    }

    printf("Personagem alterado.\n");
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

void inicializarEquipe(Equipe *equipe) {
    equipe->capacidade = 2;
    equipe->quantidade = 0;

    equipe->personagens =
        malloc(equipe->capacidade * sizeof(Personagem));
}

void liberarEquipe(Equipe *equipe) {
    free(equipe->personagens);
    equipe->personagens = NULL;
    equipe->quantidade = 0;
    equipe->capacidade = 0;
}

int main(void) {

    Equipe equipe;

    inicializarEquipe(&equipe);

    if (equipe.personagens == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    int opcao;

    do {
        printf("\n========== CATALOGO ==========\n");
        printf("1 - Cadastrar personagem\n");
        printf("2 - Buscar personagem\n");
        printf("3 - Alterar personagem\n");
        printf("4 - Listar equipe\n");
        printf("5 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                cadastrarPersonagem(&equipe);
                break;

            case 2:
                buscarEImprimir(&equipe);
                break;

            case 3:
                alterarPersonagem(&equipe);
                break;

            case 4:
                listarEquipe(&equipe);
                break;

            case 5:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 5);

    liberarEquipe(&equipe);

    return 0;
}