#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LONG 256

int nro1, nro2;
char str[MAX_LONG];

char* setDelim(){
    printf("Ingrese una operación: \n");
    fgets(str, MAX_LONG, stdin);
    printf("%s",str);
    if (strstr(str, " + ") != NULL)
        printf("Detectado!");
}

//TODO
void leerPreguntas(){
    char delim[4];

    //fgets(str, MAX_LONG, stdin);
    //delim = setDelim();
    strcpy(delim, setDelim());

    /* Consigue el primer token */
    char* token = strtok(str, delim);
    
    /* Identifica los otros token */
    int i = 1;
    while( token != NULL ) {
        printf("%s\n",token);
        switch (i){
            case 1:
            nro1 = atoi(token);
            break;
            case 2:
            nro2 = atoi(token);
            break;
        }
        i++;
        token = strtok(NULL, delim);
    }
    printf("Nro1 = %d, Nro2 = %d, Operador =%s\n", nro1,nro2,delim);
}

//TODO
int calcularOperacion(int operando1, char operador, int operando2){

}

//TODO
int main(){
    leerPreguntas();
    return(0);
}