#include <stdio.h>
#include <stdlib.h>

int comparacoes = 0, trocas = 0;

void mostrar(const char *rotulo, int v[], int n) {
    printf("%s", rotulo);
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
}

void trocar(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
    trocas++;
}

/* Regra: pivo = ultimo elemento. Menores a esquerda, maiores ou iguais a direita. */

/* Particao com memoria auxiliar. Devolve a posicao final do pivo. */
int particaoAux(int v[], int n) {
    int pivo = v[n - 1];
    int *aux = malloc(n * sizeof(int));
    int esq = 0, dir = n - 1;

    for (int i = 0; i < n - 1; i++) {
        comparacoes++;
        if (v[i] < pivo) aux[esq++] = v[i];
        else             aux[dir--] = v[i];
    }
    aux[esq] = pivo;

    for (int i = 0; i < n; i++) v[i] = aux[i];
    free(aux);
    return esq;
}

/* Particao in-place em v[left..right]. Devolve a posicao final do pivo. */
int particao(int v[], int left, int right) {
    int pivo = v[right];
    int j = left;
    for (int i = left; i < right; i++) {
        comparacoes++;
        if (v[i] < pivo) {
            if (i != j) trocar(&v[i], &v[j]);
            j++;
        }
    }
    if (j != right) trocar(&v[j], &v[right]);
    return j;
}

void quickSort(int v[], int left, int right) {
    if (left < right) {
        int index = particao(v, left, right);
        if (index - 1 > left)  quickSort(v, left, index - 1);   /* so subintervalos com 2+ elementos */
        if (index + 1 < right) quickSort(v, index + 1, right);
    }
}

int main() {
    int original[8] = {5, 3, 9, 3, 10, 4, 5, 6};   /* tem valores repetidos */
    int v[8], n = 8, op, p;

    do {
        printf("\n1 - Particao auxiliar\n2 - Particao in-place\n3 - Quick Sort\n0 - Sair\nOpcao: ");
        if (scanf("%d", &op) != 1) break;
        if (op < 1 || op > 3) continue;

        for (int i = 0; i < n; i++) v[i] = original[i];
        comparacoes = 0;
        trocas = 0;
        mostrar("antes : ", v, n);

        if (op == 1) {
            p = particaoAux(v, n);
            printf("pivo na posicao %d\n", p);
        } else if (op == 2) {
            p = particao(v, 0, n - 1);
            printf("pivo na posicao %d\n", p);
        } else {
            quickSort(v, 0, n - 1);
        }

        mostrar("depois: ", v, n);
        printf("comparacoes = %d | trocas = %d\n", comparacoes, trocas);
    } while (op != 0);
    return 0;
}