#include <stdio.h>
#include <string.h>

#define N 10

int inserir(int vet[], int pos, int *comparacoes, int *deslocamentos) {
    int valor = vet[pos];
    int j = pos - 1;

    while (j >= 0) {
        (*comparacoes)++;
        if (vet[j] > valor) {
            vet[j + 1] = vet[j];
            (*deslocamentos)++;
            j--;
        } else {
            break;
        }
    }

    vet[j + 1] = valor;
    return j + 1;
}

void insertion_sort(int vet[], int n, int *comparacoes, int *deslocamentos) {
    *comparacoes = 0;
    *deslocamentos = 0;

    for (int i = 1; i < n; i++) {
        inserir(vet, i, comparacoes, deslocamentos);
    }
}

int esta_ordenado(int vet[], int n) {
    for (int i = 1; i < n; i++) {
        if (vet[i - 1] > vet[i]) {
            return 0;
        }
    }
    return 1;
}

int soma(int vet[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += vet[i];
    }
    return total;
}

void mostrar(char texto[], int vet[], int n) {
    printf("%s", texto);
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

int main() {
    int original[N] = {42, 7, 19, 3, 88, 25, 7, 61, 14, 50};
    int copia[N];
    int comparacoes, deslocamentos;

    int prefixo[6] = {3, 10, 15, 22, 40, 18};
    int c = 0, d = 0;
    int pos = inserir(prefixo, 5, &c, &d);

    printf("Inserindo 18 no prefixo ordenado\n");
    mostrar("Resultado: ", prefixo, 6);
    printf("Posicao: %d\n", pos);
    printf("Comparacoes: %d\n", c);
    printf("Deslocamentos: %d\n\n", d);

    memcpy(copia, original, sizeof(original));

    mostrar("Original: ", original, N);
    insertion_sort(copia, N, &comparacoes, &deslocamentos);
    mostrar("Ordenado: ", copia, N);

    printf("Comparacoes: %d\n", comparacoes);
    printf("Deslocamentos: %d\n", deslocamentos);

    if (esta_ordenado(copia, N) && soma(original, N) == soma(copia, N)) {
        printf("Validacao: OK\n");
    } else {
        printf("Validacao: ERRO\n");
    }

    return 0;
}