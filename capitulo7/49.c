#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOTE 100

typedef struct Missao {
    int id;
    char nome[50];
    struct Missao *prox;
} Missao;

typedef struct {
    int id;
    const char *nome;
} Item;

Missao *criar(int id, const char *nome) {
    Missao *n = malloc(sizeof(Missao));
    if (!n) return NULL;
    n->id = id;
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

/* Ordem preservada: o lote entra no fim, na mesma ordem do vetor.
   Atomico: se qualquer alocacao falhar, a lista original fica intacta. */
int importar(Missao **inicio, const Item *lote, int n) {
    if (!lote || n <= 0 || n > MAX_LOTE) return 0;

    Missao *ini = NULL, *fim = NULL;
    for (int i = 0; i < n; i++) {
        Missao *novo = criar(lote[i].id, lote[i].nome);
        if (!novo) {
            limpar(&ini);
            return -1;
        }
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

void exibir(Missao *inicio) {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    for (Missao *aux = inicio; aux != NULL; aux = aux->prox)
        printf("[%d] %s\n", aux->id, aux->nome);
}

int main(void) {
    Missao *lista = NULL;

    printf("Tamanho: %d\n", contar(lista));

    lista = inserir_fim(lista, 1, "Resgate");
    lista = inserir_fim(lista, 2, "Patrulha");

    Item lote[] = {
        {10, "Reconhecimento"},
        {11, "Escolta"},
        {12, "Relatorio"}
    };

    printf("\nAntes: %d\n", contar(lista));
    int r = importar(&lista, lote, 3);
    if (r > 0) printf("Importadas: %d\n", r);
    else if (r == 0) printf("Lote invalido.\n");
    else printf("Erro de memoria. Lista inalterada.\n");
    printf("Depois: %d\n", contar(lista));
    exibir(lista);

    printf("\n");
    if (importar(&lista, lote, 0) == 0) printf("Lote vazio rejeitado.\n");
    if (importar(&lista, lote, MAX_LOTE + 1) == 0) printf("Lote grande demais rejeitado.\n");
    if (importar(&lista, NULL, 3) == 0) printf("Lote nulo rejeitado.\n");
    printf("Tamanho: %d\n", contar(lista));

    limpar(&lista);
    return 0;
}