#ifndef AGENDA_H
#define AGENDA_H

#define NOME_MAX 50
#define MAX_LOTE 100

typedef struct {
    int id;
    int prioridade;
    char nome[NOME_MAX];
} Missao;

typedef struct Agenda Agenda;

enum {
    AG_OCUPADA = -2,
    AG_ERRO = -1,
    AG_NAO_ENCONTRADO = 0,
    AG_OK = 1,
    AG_SEM_VIZINHO = 2
};

/* Cria e retorna uma agenda vazia, ou NULL em falha de memoria. */
Agenda *agenda_criar(void);

/* Libera todos os nos e a agenda. Aceita NULL. */
void agenda_destruir(Agenda *a);

/* Remove todas as missoes da agenda. */
void agenda_limpar(Agenda *a);

/* Retorna a quantidade de missoes na agenda. */
int agenda_tamanho(const Agenda *a);

/* Imprime as missoes na ordem atual ou "Lista vazia.". */
void agenda_exibir(const Agenda *a);

/* Insere uma copia da missao no inicio. Retorna AG_OK ou AG_ERRO. */
int agenda_inserir_inicio(Agenda *a, const Missao *m);

/* Insere uma copia da missao no fim. Retorna AG_OK ou AG_ERRO. */
int agenda_inserir_fim(Agenda *a, const Missao *m);

/* Insere apos id_ref. Retorna AG_OK, AG_NAO_ENCONTRADO ou AG_ERRO. */
int agenda_inserir_apos(Agenda *a, int id_ref, const Missao *m);

/* Insere antes de id_ref. Retorna AG_OK, AG_NAO_ENCONTRADO ou AG_ERRO. */
int agenda_inserir_antes(Agenda *a, int id_ref, const Missao *m);

/* Remove a primeira missao e copia para *out (se != NULL). Retorna AG_OK ou AG_ERRO. */
int agenda_remover_inicio(Agenda *a, Missao *out);

/* Remove a ultima missao e copia para *out (se != NULL). Retorna AG_OK ou AG_ERRO. */
int agenda_remover_fim(Agenda *a, Missao *out);

/* Remove a missao com o id informado. Retorna AG_OK, AG_NAO_ENCONTRADO ou AG_ERRO. */
int agenda_remover_id(Agenda *a, int id, Missao *out);

/* Remove a missao apos id_ref. Retorna AG_OK, AG_NAO_ENCONTRADO, AG_SEM_VIZINHO ou AG_ERRO. */
int agenda_remover_apos(Agenda *a, int id_ref, Missao *out);

/* Remove a missao antes de id_ref. Retorna AG_OK, AG_NAO_ENCONTRADO, AG_SEM_VIZINHO ou AG_ERRO. */
int agenda_remover_antes(Agenda *a, int id_ref, Missao *out);

/* Altera o nome da missao pelo id. Retorna AG_OK, AG_NAO_ENCONTRADO ou AG_ERRO. */
int agenda_alterar(Agenda *a, int id, const char *novo_nome);

/* Importa n missoes no fim de forma atomica. Retorna n ou AG_ERRO. */
int agenda_importar(Agenda *a, const Missao *lote, int n);

/* Ordena por maior prioridade e, em empate, menor id. */
void agenda_ordenar(Agenda *a);

/* Salva no formato "id;prioridade;nome". Retorna AG_OK ou AG_ERRO. */
int agenda_salvar(const Agenda *a, const char *caminho);

/* Carrega missoes apenas em agenda vazia. Retorna quantidade carregada, AG_OCUPADA ou AG_ERRO. */
int agenda_carregar(Agenda *a, const char *caminho);

#endif