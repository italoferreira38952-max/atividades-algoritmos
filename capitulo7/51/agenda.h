#ifndef AGENDA_H
#define AGENDA_H

#define NOME_MAX 50
#define MAX_LOTE 100

/* Dados de uma missao. O no da lista fica escondido em agenda.c. */
typedef struct {
    int id;
    int prioridade;
    char nome[NOME_MAX];
} Missao;

typedef struct Agenda Agenda;

/* Codigos de retorno */
enum {
    AG_OCUPADA = -2,        /* carregamento recusado: agenda nao esta vazia */
    AG_ERRO = -1,           /* dado invalido, falha de memoria ou de arquivo */
    AG_NAO_ENCONTRADO = 0,  /* id de referencia inexistente */
    AG_OK = 1,
    AG_SEM_VIZINHO = 2      /* nao ha missao antes/depois da referencia */
};

/* Cria uma agenda vazia. Retorna NULL se faltar memoria. */
Agenda *agenda_criar(void);
/* Libera todos os nos e a agenda. Aceita NULL. */
void agenda_destruir(Agenda *a);
/* Remove todas as missoes, deixando a agenda vazia. */
void agenda_limpar(Agenda *a);
/* Quantidade de missoes (0 se vazia). Nao altera a agenda. */
int agenda_tamanho(const Agenda *a);
/* Imprime as missoes na ordem atual, ou "Lista vazia.". */
void agenda_exibir(const Agenda *a);

/* Insercoes: AG_OK, AG_NAO_ENCONTRADO (so apos/antes) ou AG_ERRO.
   A missao e copiada; nome nao pode ser vazio nem ter NOME_MAX ou mais chars. */
int agenda_inserir_inicio(Agenda *a, const Missao *m);
int agenda_inserir_fim(Agenda *a, const Missao *m);
int agenda_inserir_apos(Agenda *a, int id_ref, const Missao *m);
int agenda_inserir_antes(Agenda *a, int id_ref, const Missao *m);

/* Remocoes: AG_OK (dados removidos copiados em *out, se out != NULL),
   AG_NAO_ENCONTRADO, AG_SEM_VIZINHO ou AG_ERRO (agenda vazia). */
int agenda_remover_inicio(Agenda *a, Missao *out);
int agenda_remover_fim(Agenda *a, Missao *out);
int agenda_remover_id(Agenda *a, int id, Missao *out);
int agenda_remover_apos(Agenda *a, int id_ref, Missao *out);
int agenda_remover_antes(Agenda *a, int id_ref, Missao *out);

/* Troca o nome da missao; o id (chave) nunca muda.
   AG_OK, AG_NAO_ENCONTRADO ou AG_ERRO (nome invalido). */
int agenda_alterar(Agenda *a, int id, const char *novo_nome);

/* Insere o lote no fim, preservando a ordem do vetor. Atomico.
   Retorna n em sucesso ou AG_ERRO (lote nulo, n fora de 1..MAX_LOTE,
   dado invalido ou falta de memoria). */
int agenda_importar(Agenda *a, const Missao *lote, int n);

/* Ordena por prioridade (maior primeiro); empate: menor id primeiro. */
void agenda_ordenar(Agenda *a);

/* Grava "id;prioridade;nome" por linha, na ordem atual.
   AG_OK ou AG_ERRO (nao abriu, falha de escrita ou de fechamento). */
int agenda_salvar(const Agenda *a, const char *caminho);

/* Carrega o arquivo na ordem gravada. Politica: so carrega em agenda vazia.
   Retorna a quantidade carregada (0 se o arquivo nao existe),
   AG_OCUPADA se ja ha missoes, ou AG_ERRO (linha invalida ou erro de leitura;
   nesse caso a agenda continua vazia). */
int agenda_carregar(Agenda *a, const char *caminho);

#endif