#include <time.h>
#include <stdio.h>
int main(){

int tempo = clock(); //começa a contar o tempo

printf("Aguarde . . .");

while(clock() - tempo < 5000){ //enquanto não se passaram 5segundos

//printf("Mensagem para exibição enquanto repete ciclo");

}

printf("\n\nAguarde 5 segundos para o fechamento do programa");

tempo = clock();

while(clock() - tempo < 5000){ //enquanto não se passaram 5segundos

//printf("Mensagem para exibição enquanto repete ciclo");

}

}
