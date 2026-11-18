#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOTE 100

typedef struct Missao {
    int id;
    int prioridade;
    char nome[50];
    struct Missao *prox;
} Missao;

typedef struct {
    int id;
    int prioridade;
    const char *nome;
} Item;

Missao *criar(int id, const char *nome) {
    Missao *n = malloc(sizeof(Missao));
    if (!n) return NULL;
    n->id = id;
    n->prioridade = 0;
    strcpy(n->nome, nome);
    n->prox = NULL;
    return n;
}

Missao *inserir_inicio(Missao *inicio, int id, const char *nome) {
    Missao *n = criar(id, nome);
    if (!n) return inicio;
    n->prox = inicio;
    return n;
}

Missao *inserir_fim(Missao *inicio, int id, const char *nome) {
    Missao *n = criar(id, nome);
    if (!n) return inicio;

    if (inicio == NULL)
        return n;

    Missao *aux = inicio;
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = n;
    return inicio;
}

Missao *buscar(Missao *inicio, int id) {
    for (Missao *aux = inicio; aux != NULL; aux = aux->prox)
        if (aux->id == id)
            return aux;
    return NULL;
}

int inserir_apos(Missao *inicio, int id_ref, int id, const char *nome) {
    Missao *ref = buscar(inicio, id_ref);
    if (!ref) return 0;

    Missao *n = criar(id, nome);
    if (!n) return -1;

    n->prox = ref->prox;
    ref->prox = n;
    return 1;
}

Missao *inserir_antes(Missao *inicio, int id_ref, int id, const char *nome, int *ok) {
    *ok = 0;
    Missao *ant = NULL, *atual = inicio;

    while (atual != NULL && atual->id != id_ref) {
        ant = atual;
        atual = atual->prox;
    }
    if (!atual) return inicio;

    Missao *n = criar(id, nome);
    if (!n) { *ok = -1; return inicio; }

    n->prox = atual;
    *ok = 1;
    if (!ant) return n;
    ant->prox = n;
    return inicio;
}

Missao *remover_inicio(Missao *inicio) {
    if (!inicio) {
        printf("Lista vazia. Nada a remover.\n");
        return NULL;
    }
    printf("Removida: [%d] %s\n", inicio->id, inicio->nome);
    Missao *t = inicio;
    inicio = inicio->prox;
    free(t);
    return inicio;
}

Missao *remover_fim(Missao *inicio) {
    if (!inicio) {
        printf("Lista vazia. Nada a remover.\n");
        return NULL;
    }
    Missao *ant = NULL, *atual = inicio;
    while (atual->prox != NULL) {
        ant = atual;
        atual = atual->prox;
    }
    printf("Removida: [%d] %s\n", atual->id, atual->nome);
    free(atual);
    if (!ant) return NULL;
    ant->prox = NULL;
    return inicio;
}

Missao *remover_id(Missao *inicio, int id) {
    Missao *ant = NULL, *atual = inicio;
    while (atual != NULL && atual->id != id) {
        ant = atual;
        atual = atual->prox;
    }
    if (!atual) {
        printf("Missao %d nao encontrada. Lista inalterada.\n", id);
        return inicio;
    }
    if (!ant) inicio = atual->prox;
    else ant->prox = atual->prox;
    printf("Removida: [%d] %s\n", atual->id, atual->nome);
    free(atual);
    return inicio;
}

void remover_apos(Missao *inicio, int id_ref) {
    Missao *ref = buscar(inicio, id_ref);
    if (!ref) {
        printf("Missao %d nao encontrada. Lista inalterada.\n", id_ref);
        return;
    }
    if (!ref->prox) {
        printf("Nao ha missao depois de %d.\n", id_ref);
        return;
    }
    Missao *t = ref->prox;
    ref->prox = t->prox;
    printf("Removida: [%d] %s\n", t->id, t->nome);
    free(t);
}

Missao *remover_antes(Missao *inicio, int id_ref) {
    Missao *ant2 = NULL, *ant = NULL, *atual = inicio;
    while (atual != NULL && atual->id != id_ref) {
        ant2 = ant;
        ant = atual;
        atual = atual->prox;
    }
    if (!atual) {
        printf("Missao %d nao encontrada. Lista inalterada.\n", id_ref);
        return inicio;
    }
    if (!ant) {
        printf("Nao ha missao antes de %d.\n", id_ref);
        return inicio;
    }
    if (!ant2) inicio = atual;
    else ant2->prox = atual;
    printf("Removida: [%d] %s\n", ant->id, ant->nome);
    free(ant);
    return inicio;
}

int alterar(Missao *inicio, int id, const char *novo_nome) {
    if (!novo_nome || novo_nome[0] == '\0' || strlen(novo_nome) >= sizeof(inicio->nome)) {
        printf("Nome invalido. Nada alterado.\n");
        return -1;
    }
    Missao *m = buscar(inicio, id);
    if (!m) {
        printf("Missao %d nao encontrada. Lista inalterada.\n", id);
        return 0;
    }
    printf("Alterada: [%d] %s -> %s\n", m->id, m->nome, novo_nome);
    strcpy(m->nome, novo_nome);
    return 1;
}

void limpar(Missao **inicio) {
    Missao *atual = *inicio;
    while (atual) {
        Missao *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    *inicio = NULL;
}

int contar(const Missao *inicio) {
    int total = 0;
    for (const Missao *aux = inicio; aux != NULL; aux = aux->prox)
        total++;
    return total;
}

int importar(Missao **inicio, const Item *lote, int n) {
    if (!lote || n <= 0 || n > MAX_LOTE) return 0;

    Missao *ini = NULL, *fim = NULL;
    for (int i = 0; i < n; i++) {
        Missao *novo = criar(lote[i].id, lote[i].nome);
        if (!novo) {
            limpar(&ini);
            return -1;
        }
        novo->prioridade = lote[i].prioridade;
        if (!ini) ini = novo;
        else fim->prox = novo;
        fim = novo;
    }

    if (!*inicio) {
        *inicio = ini;
    } else {
        Missao *aux = *inicio;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = ini;
    }
    return n;
}

/* Decisao: troca de dados (id, prioridade, nome) e nao de nos.
   E mais simples e seguro: o encadeamento nunca muda, entao o inicio
   permanece valido. Custo: copiar o registro a cada troca.
   Criterio: maior prioridade primeiro; empate -> menor id. */
static int antes(const Missao *a, const Missao *b) {
    if (a->prioridade != b->prioridade)
        return a->prioridade > b->prioridade;
    return a->id < b->id;
}

void ordenar(Missao *inicio) {
    int trocou;
    do {
        trocou = 0;
        for (Missao *p = inicio; p && p->prox; p = p->prox) {
            if (antes(p->prox, p)) {
                int id = p->id, pr = p->prioridade;
                char nome[50];
                strcpy(nome, p->nome);

                p->id = p->prox->id;
                p->prioridade = p->prox->prioridade;
                strcpy(p->nome, p->prox->nome);

                p->prox->id = id;
                p->prox->prioridade = pr;
                strcpy(p->prox->nome, nome);
                trocou = 1;
            }
        }
    } while (trocou);
}

/* Formato: id;prioridade;nome (uma missao por linha, sem ponteiros).
   Retorna 1 ok, 0 falha de escrita/fechamento, -1 nao abriu o arquivo. */
int salvar(const Missao *inicio, const char *caminho) {
    FILE *f = fopen(caminho, "w");
    if (!f) return -1;

    int ok = 1;
    for (const Missao *aux = inicio; aux != NULL; aux = aux->prox) {
        if (fprintf(f, "%d;%d;%s\n", aux->id, aux->prioridade, aux->nome) < 0) {
            ok = 0;
            break;
        }
    }
    if (fclose(f) != 0) ok = 0;
    return ok;
}

void exibir(Missao *inicio) {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    for (Missao *aux = inicio; aux != NULL; aux = aux->prox)
        printf("[%d] (P%d) %s\n", aux->id, aux->prioridade, aux->nome);
}

int main(void) {
    Missao *lista = NULL;

    Item lote[] = {
        {1, 2, "Resgate"},
        {2, 5, "Patrulha"},
        {3, 2, "Escolta"},
        {4, 5, "Apoio"},
        {5, 1, "Relatorio"}
    };
    importar(&lista, lote, 5);

    printf("Antes (%d):\n", contar(lista));
    exibir(lista);

    ordenar(lista);
    printf("\nDepois (%d):\n", contar(lista));
    exibir(lista);

    int r = salvar(lista, "missoes.txt");
    if (r == 1) printf("\nSalvo em missoes.txt\n");
    else if (r == 0) printf("\nErro ao gravar o arquivo.\n");
    else printf("\nNao foi possivel abrir o arquivo.\n");

    limpar(&lista);
    return 0;
}