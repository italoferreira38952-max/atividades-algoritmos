#include <stdio.h>

int main() {
    int a[5] = {1, 2, 3, 4, 5};  
    int *vetor = a;              
    int pontuacao = 0;
    int altura = 0;
    // O deslocamento vetor + i respeita o tipo do ponteiro porque o compilador
// leva em conta o tamanho do tipo que o ponteiro está apontando.
// Como o vetor é um ponteiro pra int (int*), ele multiplica o valor de i
// pelo tamanho de um int (que geralmente é 4 bytes).
// Por isso:
// - vetor + 0 aponta pro primeiro elemento
// - vetor + 1 aponta pro segundo (avança 4 bytes)
// - vetor + 2 aponta pro terceiro (avança 8 bytes)
// e assim por diante.
// Dessa forma a aritmética de ponteiros sempre acessa a posição certa
// do vetor, respeitando o tipo do dado.

    printf("indice | Endereco      | Valor\n");
    for(int i = 0; i < 5; i++) {
        printf("%d      | %p | %d\n", i, (void*)(vetor + i), *(vetor + i));

        pontuacao += *(vetor + i);     
            altura += *(vetor + i);            
    }
    printf("\nPontuacao final: %d\n", pontuacao);
    printf("Altura total: %d\n", altura);
    return 0;
}