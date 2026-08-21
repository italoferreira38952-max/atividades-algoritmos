#include <stdio.h>

void ler_mapa(int *m, int t) {
    printf("Digite os %d valores do mapa:\n", t);
    for (int i = 0; i < t; i++) {
        printf("Digite o valor para a posicao %d: ", i + 1);
        scanf("%d", m + i);
    }
}
void mostrar_mapa(int *m, int t) {
    for (int i = 0; i < t; i++) {
        printf("%d ", *(m + i));
    }
    printf("\n");
    
}
void explorar_mapa(int *m, int t) {
    int *cursor = m;      // ponteiro auxiliar inicia na 1ª posição
    int *fim = m + t;     // endereço imediatamente após o último elemento
    int pontuacao = 0;
    int posicao = 0;
    printf("\n--- Inicio da Exploracao ---\n");
    while (cursor < fim) {
        int valor_atual = *cursor;
        pontuacao += valor_atual;
        printf("Visitando Posicao Logica %d | Valor da Plataforma: %d | Pontuacao Atual: %d\n", 
               posicao, valor_atual, pontuacao);
               /*
         * COMPARAÇÃO:
         * - Incremento de ponteiro:  cursor++
         *   Move o cursor para a próxima plataforma (próximo endereço de memória).
         *
         * - Acesso por índice:       m[posicao]
         *   Calcula o endereço a partir da base do vetor + deslocamento.
         *
         * Ambos chegam no mesmo resultado, mas o incremento de ponteiro
         * é mais natural e eficiente quando se percorre o mapa sequencialmente.
         */
        cursor++;   // avanço do ponteiro auxiliar
        posicao++;
    }

    printf("\n--- Resumo do Percurso ---\n");
    printf("Total de plataformas exploradas: %d\n", posicao);
    printf("Pontuacao final acumulada: %d\n", pontuacao);
}

int main() {
    int t;
    int m[100];
    printf("Digite o tamanho do mapa (1 a 100): ");
    scanf("%d", &t);
    if (t > 100 || t < 1) {
        printf("Tamanho invalido\n");
        return 1;
    }
    ler_mapa(m, t);
    mostrar_mapa(m, t);
    explorar_mapa(m, t);
    return 0;
}