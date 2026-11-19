#include "agenda.h"
#include <stdio.h>
#include <string.h>

int missao_criar(Missao *m, int id, int prioridade, const char *nome) {
    if (!m || !nome || !nome[0] || strlen(nome) >= NOME_MAX)
        return 0;
    m->id = id;
    m->prioridade = prioridade;
    strcpy(m->nome, nome);
    return 1;
}

void missao_exibir(const Missao *m) {
    if (!m) return;
    printf("[%d] (P%d) %s\n", m->id, m->prioridade, m->nome);
}