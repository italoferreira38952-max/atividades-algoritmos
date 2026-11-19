#ifndef AGENDA_H
#define AGENDA_H

#define NOME_MAX 50

typedef struct {
    int id;
    int prioridade;
    char nome[NOME_MAX];
} Missao;

/* Tipo opaco: a representacao dos nos fica em agenda.c. */
typedef struct Agenda Agenda;

/* Cria uma agenda vazia. Retorna NULL se faltar memoria. */
Agenda *agenda_criar(void);

/* Libera todos os nos e a agenda. Aceita NULL. */
void agenda_destruir(Agenda *a);

/* Insere uma copia da missao no inicio.
   Retorna 1 em sucesso, ou 0 se a agenda/missao/nome for invalido ou faltar memoria. */
int agenda_inserir_inicio(Agenda *a, const Missao *m);

/* Quantidade de missoes (0 se vazia). */
int agenda_tamanho(const Agenda *a);

/* Imprime as missoes na ordem atual, ou "Lista vazia.". */
void agenda_exibir(const Agenda *a);

#endif