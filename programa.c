#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

#define LONG_MAX 256

extern int suma(int a, int b);
extern int resta(int a, int b);

int nro1, nro2;
char oper_texto[4];
char oper;
char str[LONG_MAX];
int resultado;

//TODO
int calcularOperacion(int operando1, char operador, int operando2){
    if (operador == '+'){
        resultado = suma(operando1, operando2);
        printf("El resultado es: %d\n", resultado);
        return resultado;
        }
    if (operador == '-'){
        resultado = resta(operando1, operando2);
        printf("El resultado es: %d\n", resultado);
        return resultado;
        }
        return 0;
    }

void identificarNrosYDelim(){

    if (strstr(str, " + ") != NULL) {
        printf("Suma detectada!\n");
        strcpy(oper_texto, " + ");
        oper = '+';
    } else if (strstr(str, " - ") != NULL){
        printf("Resta detectada!\n");
        strcpy(oper_texto, " - ");
        oper = '-';
    } else if (strstr(str, " * ") != NULL) {
        printf("Multiplicación detectada!\n");
        strcpy(oper_texto, " * ");
        oper = '*';
    } else if (strstr(str, " / ") != NULL) {
        if (nro2 == 0){
            fprintf(stderr, "No se puede dividir por cero.\n");
            return;
        }
        printf("División detectada!\n");
        strcpy(oper_texto, " / ");
        oper = '/';
    } else {
        fprintf(stderr,"No se detecto una operación valida.\n");
    }

    /* Consigue el primer token */
    char* token = strtok(str, oper_texto);
    
    /* Identifica los otros token */
    int i = 1;
    while( token != NULL ) {
        switch (i){
            case 1:
            nro1 = atoi(token);
            break;
            case 2:
            nro2 = atoi(token);
            break;
        }
        i++;
        token = strtok(NULL, oper_texto);
    }
    printf("Nro1 = %d, Nro2 = %d, Operador =%c\n", nro1,nro2,oper);
}

void leer_pregunta(){
    printf("Por favor, ingrese una operación matemática con espacios entre los numeros y el operando:\n");
    regex_t regex;
    int ret;
    const char *patron = "-?[[:digit:]]{1,10}[[:space:]][\\+\\*\\/\\-][[:space:]]-?[[:digit:]]{1,10}";
    ret = regcomp(&regex, patron, REG_EXTENDED);
    char msgbuf[LONG_MAX];
    char *p;

    fgets(str, LONG_MAX, stdin); //Hace el input

    if (ret){
        fprintf(stderr, "No se pudo compilar el regex\n");
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (!ret){
        puts("Ok!");
    } else if (ret == REG_NOMATCH) {
        puts("Lo siento, mis respuestas son limitadas.\nAseguráte de escribir la operación como '1 + 2' por ejemplo.");
        return;
    } else {
        regerror(ret, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Fallo el matcheo de regex: %s\n", msgbuf);
    }

    regfree(&regex);

    identificarNrosYDelim();
    //printf("oper: %d", oper);
    calcularOperacion(nro1,oper,nro2);
}

int main (void){
    leer_pregunta();
    return 0;
}
