#include <stdio.h>
#include <string.h>

typedef struct { int id; char nome[32]; int pontos; } Jogador;

long comp = 0, trocas = 0;

int indice_menor(int v[], int n, int ini) {
    int m = ini;
    for (int i = ini + 1; i < n; i++) { comp++; if (v[i] < v[m]) m = i; }
    return m;
}

void selection_int(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int m = indice_menor(v, n, i);
        if (m != i) { int t = v[i]; v[i] = v[m]; v[m] = t; trocas++; }
    }
}

/* <0 se a vem antes de b: mais pontos, depois nome, depois id */
int cmp(Jogador a, Jogador b) {
    if (a.pontos != b.pontos) return b.pontos - a.pontos;
    int r = strcmp(a.nome, b.nome);
    return r ? r : a.id - b.id;
}

void selection_jog(Jogador v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++) { comp++; if (cmp(v[j], v[m]) < 0) m = j; }
        if (m != i) { Jogador t = v[i]; v[i] = v[m]; v[m] = t; trocas++; }
    }
}

int main(void) {
    const int orig[] = {42, 7, 19, 88, 3, 56, 19, 71};
    const Jogador jorig[] = {{1,"Carlos",50},{2,"Ana",70},{3,"Bruno",70},
                             {4,"Diana",50},{5,"Ana",70},{6,"Eduardo",30}};
    int n = 8, nj = 6, v[8];
    Jogador j[6];

    memcpy(v, orig, sizeof v);
    memcpy(j, jorig, sizeof j);

    selection_int(v, n);
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\ncomparacoes: %ld | trocas: %ld\n\n", comp, trocas);

    comp = trocas = 0;
    selection_jog(j, nj);
    for (int i = 0; i < nj; i++) printf("%d %-8s %d\n", j[i].id, j[i].nome, j[i].pontos);
    printf("comparacoes: %ld | trocas: %ld\n", comp, trocas);

    printf("\noriginal intacto: ");
    for (int i = 0; i < n; i++) printf("%d ", orig[i]);
    printf("\n");
    return 0;
}