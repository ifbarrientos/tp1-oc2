#include <stdio.h>

void leer_pregunta(){
    char input[30];
    printf("Por favor, ingrese una operación matemática con espacios entre los numeros y el operando:\n");
    scanf("%99s", input);
    printf("%s\n",input);
}

int main (void){
    leer_pregunta();
    return 0;
}