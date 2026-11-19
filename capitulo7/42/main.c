#include <stdio.h>
#include "agenda.h"

int main(void) {
    Agenda *ag = agenda_criar();
    if (!ag) return 1;

    agenda_exibir(ag);

    Missao a = {1, 5, "Resgate"};
    Missao b = {2, 3, "Patrulha"};
    Missao c = {3, 1, ""};

    agenda_inserir_inicio(ag, &a);
    agenda_inserir_inicio(ag, &b);
    if (!agenda_inserir_inicio(ag, &c))
        printf("Nome vazio rejeitado.\n");

    printf("\nTotal: %d\n", agenda_tamanho(ag));
    agenda_exibir(ag);

    agenda_destruir(ag);
    return 0;
}