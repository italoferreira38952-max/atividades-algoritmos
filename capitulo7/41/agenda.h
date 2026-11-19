#ifndef AGENDA_H
#define AGENDA_H

#define NOME_MAX 50

typedef struct {
    int id;
    int prioridade;
    char nome[NOME_MAX];
} Missao;

/* Cria uma missao com os dados informados.
   Retorna 1 em sucesso, ou 0 se o nome for nulo, vazio ou grande demais. */
int missao_criar(Missao *m, int id, int prioridade, const char *nome);

/* Imprime uma missao no formato "[id] (Pprioridade) nome". */
void missao_exibir(const Missao *m);

#endif