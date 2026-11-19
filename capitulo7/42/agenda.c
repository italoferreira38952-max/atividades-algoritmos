#include "agenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    Missao dados;
    struct No *prox;
} No;

struct Agenda {
    No *inicio;
};

Agenda *agenda_criar(void) {
    return calloc(1, sizeof(Agenda));
}

void agenda_destruir(Agenda *a) {
    if (!a) return;
    No *p = a->inicio;
    while (p) {
        No *prox = p->prox;
        free(p);
        p = prox;
    }
    free(a);
}

int agenda_inserir_inicio(Agenda *a, const Missao *m) {
    if (!a || !m || !m->nome[0] || !memchr(m->nome, '\0', NOME_MAX))
        return 0;

    No *n = malloc(sizeof *n);
    if (!n) return 0;

    n->dados = *m;
    n->prox = a->inicio;
    a->inicio = n;
    return 1;
}

int agenda_tamanho(const Agenda *a) {
    int t = 0;
    if (!a) return 0;
    for (const No *p = a->inicio; p; p = p->prox) t++;
    return t;
}

void agenda_exibir(const Agenda *a) {
    if (!a || !a->inicio) {
        printf("Lista vazia.\n");
        return;
    }
    for (const No *p = a->inicio; p; p = p->prox)
        printf("[%d] (P%d) %s\n", p->dados.id, p->dados.prioridade, p->dados.nome);
}