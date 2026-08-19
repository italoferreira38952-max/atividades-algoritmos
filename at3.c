#include <stdio.h>

int main() {
    int a[5] = {1, 2, 3, 4, 5};  
    int *pa = a;              
    int pontuacao = 0;
    int altura = 0;

    printf("indice | Endereco      | Valor\n");
    for(int i = 0; i < 5; i++) {
        printf("%d      | %p | %d\n", i, (void*)(pa + i), *(pa + i));

        pontuacao += *(pa + i);     
        altura += *(pa + i);            
    }

    printf("\nPontuacao final: %d\n", pontuacao);
    printf("Altura total: %d\n", altura);
    return 0;
}