#include <stdio.h>
#include <stdlib.h>
#include "agenda.h"

#define ARQ "missoes.txt"

static int ler_int(const char *msg) {
    int v, r;
    printf("%s", msg);
    while ((r = scanf("%d", &v)) != 1) {
        if (r == EOF) exit(0);
        scanf("%*[^\n]");
        printf("Invalido. %s", msg);
    }
    return v;
}

static Missao ler_missao(void) {
    Missao m = {0};
    m.id = ler_int("Id: ");
    m.prioridade = ler_int("Prioridade: ");
    printf("Nome: ");
    if (scanf(" %49[^\n]", m.nome) != 1) m.nome[0] = '\0';
    return m;
}

static void relatar(int r, const Missao *rem) {
    switch (r) {
    case AG_OK:
        if (rem) printf("Removida: [%d] (P%d) %s\n", rem->id, rem->prioridade, rem->nome);
        else printf("OK.\n");
        break;
    case AG_NAO_ENCONTRADO: printf("Missao de referencia nao encontrada. Lista inalterada.\n"); break;
    case AG_SEM_VIZINHO:    printf("Nao ha missao nessa posicao.\n"); break;
    default:                printf("Operacao invalida ou lista vazia.\n");
    }
}

int main(void) {
    Agenda *ag = agenda_criar();
    if (!ag) return 1;

    int r = agenda_carregar(ag, ARQ);
    if (r > 0) printf("%d missao(oes) carregada(s).\n", r);
    else if (r == 0) printf("Nenhuma agenda salva. Lista vazia.\n");
    else printf("Arquivo invalido. Lista vazia.\n");

    int op;
    do {
        printf("\n1 ins.inicio  2 ins.fim  3 ins.apos  4 ins.antes\n"
               "5 rem.inicio  6 rem.fim  7 rem.id    8 rem.apos  9 rem.antes\n"
               "10 alterar  11 ordenar  12 exibir  13 importar lote demo\n"
               "14 salvar  15 carregar  0 sair\n");
        op = ler_int("> ");

        Missao m, rem;
        int ref;
        switch (op) {
        case 1: m = ler_missao(); relatar(agenda_inserir_inicio(ag, &m), NULL); break;
        case 2: m = ler_missao(); relatar(agenda_inserir_fim(ag, &m), NULL); break;
        case 3: ref = ler_int("Id de referencia: "); m = ler_missao();
                relatar(agenda_inserir_apos(ag, ref, &m), NULL); break;
        case 4: ref = ler_int("Id de referencia: "); m = ler_missao();
                relatar(agenda_inserir_antes(ag, ref, &m), NULL); break;
        case 5: relatar(agenda_remover_inicio(ag, &rem), &rem); break;
        case 6: relatar(agenda_remover_fim(ag, &rem), &rem); break;
        case 7: ref = ler_int("Id: "); relatar(agenda_remover_id(ag, ref, &rem), &rem); break;
        case 8: ref = ler_int("Id de referencia: ");
                relatar(agenda_remover_apos(ag, ref, &rem), &rem); break;
        case 9: ref = ler_int("Id de referencia: ");
                relatar(agenda_remover_antes(ag, ref, &rem), &rem); break;
        case 10: {
            char nome[NOME_MAX + 20] = "";
            ref = ler_int("Id: ");
            printf("Novo nome: ");
            scanf(" %69[^\n]", nome);
            relatar(agenda_alterar(ag, ref, nome), NULL);
            break;
        }
        case 11: agenda_ordenar(ag); printf("Ordenada.\n"); break;
        case 12: printf("Total: %d\n", agenda_tamanho(ag)); agenda_exibir(ag); break;
        case 13: {
            Missao lote[] = {{10, 3, "Reconhecimento"}, {11, 5, "Escolta"}, {12, 1, "Relatorio"}};
            printf("Antes: %d\n", agenda_tamanho(ag));
            r = agenda_importar(ag, lote, 3);
            if (r > 0) printf("Importadas: %d\n", r); else relatar(r, NULL);
            printf("Depois: %d\n", agenda_tamanho(ag));
            break;
        }
        case 14: printf(agenda_salvar(ag, ARQ) == AG_OK ? "Salvo.\n" : "Erro ao salvar.\n"); break;
        case 15:
            r = agenda_carregar(ag, ARQ);
            if (r == AG_OCUPADA) printf("Recusado: a agenda ja tem missoes.\n");
            else if (r < 0) printf("Arquivo invalido.\n");
            else printf("%d missao(oes) carregada(s).\n", r);
            break;
        }
    } while (op != 0);

    agenda_destruir(ag);
    return 0;
}