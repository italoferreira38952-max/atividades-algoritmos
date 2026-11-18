#include "agenda.h"
#include <errno.h>
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

static int valida(const Missao *m) {
    return m && m->nome[0] && memchr(m->nome, '\0', NOME_MAX);
}

static No *novo_no(const Missao *m) {
    if (!valida(m)) return NULL;
    No *n = malloc(sizeof *n);
    if (!n) return NULL;
    n->dados = *m;
    n->prox = NULL;
    return n;
}

static void liberar_cadeia(No *p) {
    while (p) {
        No *prox = p->prox;
        free(p);
        p = prox;
    }
}

static void anexar(Agenda *a, No *ini) {
    No **p = &a->inicio;
    while (*p) p = &(*p)->prox;
    *p = ini;
}

/* Devolve o ponteiro que aponta para o no com o id (ou para NULL). */
static No **elo(Agenda *a, int id) {
    No **p = &a->inicio;
    while (*p && (*p)->dados.id != id) p = &(*p)->prox;
    return p;
}

static int retirar(No **p, Missao *out) {
    No *t = *p;
    if (out) *out = t->dados;
    *p = t->prox;
    free(t);
    return AG_OK;
}

Agenda *agenda_criar(void) {
    return calloc(1, sizeof(Agenda));
}

void agenda_limpar(Agenda *a) {
    if (!a) return;
    liberar_cadeia(a->inicio);
    a->inicio = NULL;
}

void agenda_destruir(Agenda *a) {
    agenda_limpar(a);
    free(a);
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

int agenda_inserir_inicio(Agenda *a, const Missao *m) {
    No *n = a ? novo_no(m) : NULL;
    if (!n) return AG_ERRO;
    n->prox = a->inicio;
    a->inicio = n;
    return AG_OK;
}

int agenda_inserir_fim(Agenda *a, const Missao *m) {
    No *n = a ? novo_no(m) : NULL;
    if (!n) return AG_ERRO;
    anexar(a, n);
    return AG_OK;
}

int agenda_inserir_apos(Agenda *a, int id_ref, const Missao *m) {
    if (!a || !valida(m)) return AG_ERRO;
    No **p = elo(a, id_ref);
    if (!*p) return AG_NAO_ENCONTRADO;
    No *n = novo_no(m);
    if (!n) return AG_ERRO;
    n->prox = (*p)->prox;
    (*p)->prox = n;
    return AG_OK;
}

int agenda_inserir_antes(Agenda *a, int id_ref, const Missao *m) {
    if (!a || !valida(m)) return AG_ERRO;
    No **p = elo(a, id_ref);
    if (!*p) return AG_NAO_ENCONTRADO;
    No *n = novo_no(m);
    if (!n) return AG_ERRO;
    n->prox = *p;
    *p = n;
    return AG_OK;
}

int agenda_remover_inicio(Agenda *a, Missao *out) {
    if (!a || !a->inicio) return AG_ERRO;
    return retirar(&a->inicio, out);
}

int agenda_remover_fim(Agenda *a, Missao *out) {
    if (!a || !a->inicio) return AG_ERRO;
    No **p = &a->inicio;
    while ((*p)->prox) p = &(*p)->prox;
    return retirar(p, out);
}

int agenda_remover_id(Agenda *a, int id, Missao *out) {
    if (!a) return AG_ERRO;
    No **p = elo(a, id);
    return *p ? retirar(p, out) : AG_NAO_ENCONTRADO;
}

int agenda_remover_apos(Agenda *a, int id_ref, Missao *out) {
    if (!a) return AG_ERRO;
    No **p = elo(a, id_ref);
    if (!*p) return AG_NAO_ENCONTRADO;
    if (!(*p)->prox) return AG_SEM_VIZINHO;
    return retirar(&(*p)->prox, out);
}

int agenda_remover_antes(Agenda *a, int id_ref, Missao *out) {
    if (!a) return AG_ERRO;
    if (a->inicio && a->inicio->dados.id == id_ref) return AG_SEM_VIZINHO;
    No **p = &a->inicio;
    while (*p && (*p)->prox && (*p)->prox->dados.id != id_ref)
        p = &(*p)->prox;
    if (!*p || !(*p)->prox) return AG_NAO_ENCONTRADO;
    return retirar(p, out);
}

int agenda_alterar(Agenda *a, int id, const char *novo_nome) {
    if (!a || !novo_nome || !novo_nome[0] || strlen(novo_nome) >= NOME_MAX)
        return AG_ERRO;
    No *n = *elo(a, id);
    if (!n) return AG_NAO_ENCONTRADO;
    strcpy(n->dados.nome, novo_nome);
    return AG_OK;
}

int agenda_importar(Agenda *a, const Missao *lote, int n) {
    if (!a || !lote || n <= 0 || n > MAX_LOTE) return AG_ERRO;
    No *ini = NULL, **fim = &ini;
    for (int i = 0; i < n; i++) {
        No *x = novo_no(&lote[i]);
        if (!x) {
            liberar_cadeia(ini);
            return AG_ERRO;
        }
        *fim = x;
        fim = &x->prox;
    }
    anexar(a, ini);
    return n;
}

/* Ordenacao por troca de dados: o encadeamento nunca muda. */
static int vem_antes(const Missao *x, const Missao *y) {
    if (x->prioridade != y->prioridade) return x->prioridade > y->prioridade;
    return x->id < y->id;
}

void agenda_ordenar(Agenda *a) {
    if (!a) return;
    int trocou;
    do {
        trocou = 0;
        for (No *p = a->inicio; p && p->prox; p = p->prox) {
            if (vem_antes(&p->prox->dados, &p->dados)) {
                Missao t = p->dados;
                p->dados = p->prox->dados;
                p->prox->dados = t;
                trocou = 1;
            }
        }
    } while (trocou);
}

int agenda_salvar(const Agenda *a, const char *caminho) {
    if (!a || !caminho) return AG_ERRO;
    FILE *f = fopen(caminho, "w");
    if (!f) return AG_ERRO;
    int r = AG_OK;
    for (const No *p = a->inicio; p; p = p->prox) {
        if (fprintf(f, "%d;%d;%s\n", p->dados.id, p->dados.prioridade, p->dados.nome) < 0) {
            r = AG_ERRO;
            break;
        }
    }
    if (fclose(f) != 0) r = AG_ERRO;
    return r;
}

int agenda_carregar(Agenda *a, const char *caminho) {
    if (!a || !caminho) return AG_ERRO;
    if (a->inicio) return AG_OCUPADA;

    FILE *f = fopen(caminho, "r");
    if (!f) return errno == ENOENT ? 0 : AG_ERRO;

    No *ini = NULL, **fim = &ini;
    char linha[128];
    int total = 0, erro = 0;

    while (fgets(linha, sizeof linha, f)) {
        linha[strcspn(linha, "\r\n")] = '\0';
        if (!linha[0]) continue;

        Missao m;
        No *x;
        if (sscanf(linha, "%d;%d;%49[^\n]", &m.id, &m.prioridade, m.nome) != 3
            || !(x = novo_no(&m))) {
            erro = 1;
            break;
        }
        *fim = x;
        fim = &x->prox;
        total++;
    }
    if (ferror(f)) erro = 1;
    fclose(f);

    if (erro) {
        liberar_cadeia(ini);
        return AG_ERRO;
    }
    a->inicio = ini;
    return total;
}