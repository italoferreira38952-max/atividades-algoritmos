#include <stdio.h>
int main(){
    int vida=100;
    int dano;
    int tesouro=0;
    int *pvida=&vida;
    int *ptesouro=&tesouro;
    printf("===ESTADO INICIAL===\n");
    printf("vida:%d (endereco:%p)\n", vida, pvida );
    printf("informe o dano: \n");
    scanf("%d", &dano);
    printf("aplicando %d de dano...\n", dano);
    *pvida=*pvida-dano;
    printf("a vida atual e:%d\n", vida);
    printf("==curando 20 de vida==\n");
    *pvida=*pvida+20;
     printf("a vida atual e:%d\n", vida);
    printf("ativando tesouro...\n");
    *ptesouro=1;
    printf("tesouro agora:%d", tesouro);
    return 0;
}