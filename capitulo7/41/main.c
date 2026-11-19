#include <stdio.h>
#include "agenda.h"

int main(void) {
    Missao m;

    if (!missao_criar(&m, 1, 5, "Resgate")) {
        printf("Dados invalidos.\n");
        return 1;
    }
    missao_exibir(&m);

    if (!missao_criar(&m, 2, 3, ""))
        printf("Nome vazio rejeitado.\n");

    return 0;
}