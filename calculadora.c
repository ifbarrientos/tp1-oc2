#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define LONG_MAX 256
const char *patron = "^-?[[:digit:]]{1,10}[[:space:]][+\\*\\/-][[:space:]]-?[[:digit:]]{1,10}$";
const char *patron_continuo = "^[+\\*\\/-][[:space:]]-?[[:digit:]]{1,10}$";

//extern uint64_t sum(uint64_t a, uint64_t b);
//extern uint64_t res(uint64_t a, uint64_t b);
//extern uint64_t mul(uint64_t a, uint64_t b);
//extern uint64_t div(uint64_t a, uint64_t b);
//extern uint64_t sum64(uint64_t a, uint64_t b);
extern int sum(int a, int b);

//uint64_t nro1, nro2, resultado;
int nro1, nro2, resultado;
bool continua = false;
char oper_texto[4], oper_texto_continua[3], oper, str[LONG_MAX];


//uint64_t CalcularOperacion(uint64_t operando1, char operador, uint64_t operando2){
int CalcularOperacion(int operando1, char operador, int operando2){
    if (operador == '+'){
        //resultado = sum64(operando1, operando2);
        resultado = sum(operando1, operando2);
    } else if (operador == '-'){
        //resultado = res(operando1, operando2);
    } else if (operador == '*'){
        //resultado = mul(operando1, operando2);
    } else if (operador == '/'){
        if (operando2 == 0){
            fprintf(stderr, "No se puede dividir por cero\n");
            return 0;
        }
        //resultado = div(operando1, operando2);
    }
        printf("Presione CTRL + C para salir\n");
        //printf("El resultado es:%llu\n", resultado);
        printf("El resultado es:%d\n", resultado);
        continua = true;
        return resultado;
    }

void IdentificarNrosYDelim(){
    if (strstr(str, "+") != NULL) {
        printf("Suma detectada!\n");
        strcpy(oper_texto, " + ");
        strcpy(oper_texto_continua, "+ ");
        oper = '+';
    } else if (strstr(str, "-") != NULL){
        printf("Resta detectada!\n");
        strcpy(oper_texto, " - ");
        strcpy(oper_texto_continua, "- ");
        oper = '-';
    } else if (strstr(str, "*") != NULL) {
        printf("Multiplicación detectada!\n");
        strcpy(oper_texto, " * ");
        strcpy(oper_texto_continua, "* ");
        oper = '*';
    } else if (strstr(str, "/") != NULL) {
        printf("División detectada!\n");
        strcpy(oper_texto, " / ");
        strcpy(oper_texto_continua, "/ ");
        oper = '/';
    } else {
        fprintf(stderr,"No se detecto una operación valida.\n");
    }

    /* Consigue el primer token */
    char* token;
    if (continua){
        token = strtok(str, oper_texto_continua)
    } else {
        token = strtok(str, oper_texto);
    }
    
    /* Identifica los otros token */
    int i = 1;
    while( token != NULL ) {
        switch (i){
            case 1:
            if (continua) nro1 = resultado;
            else nro1 = atoi(token);
            break;
            case 2:
            nro2 = atoi(token);
            break;
        }
        i++;
        if (continua) token = strtok(NULL, oper_texto_continua);
        else token = strtok(NULL, oper_texto);
    }
    //printf("Nro1 = %llu, Nro2 = %llu, Operador = %c\n", nro1,nro2,oper);
    printf("Nro1 = %d, Nro2 = %d, Operador = %c\n", nro1,nro2,oper);
}

void LeerPregunta(){
    printf("Por favor, ingrese una operación matemática con espacios entre los numeros y el operando:\n");
    regex_t regex;
    int ret;

    if (continua)
        ret = regcomp(&regex, patron_continuo, REG_EXTENDED);
    else ret = regcomp(&regex, patron, REG_EXTENDED);    

    if (fgets(str, LONG_MAX, stdin) != NULL) { //Hace el input
        size_t len = strlen(str);
        if (len > 0 && str[len-1] == '\n')
            str[len-1] = '\0';
    } else {
        fprintf(stderr, "Hubo un error al leer el input\n");
        return;
    }

    if (ret){
        fprintf(stderr, "No se pudo compilar el regex\n");
        return;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (!ret){
        puts("Ok!");
    } else if (ret == REG_NOMATCH) {
        puts("Lo siento, mis respuestas son limitadas.\nAseguráte de escribir la operación como '1 + 2' por ejemplo.");
        return;
    } else {
        char msgbuf[LONG_MAX];
        regerror(ret, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Fallo el matcheo de regex: %s\n", msgbuf);
        return;
    }

    regfree(&regex);
    IdentificarNrosYDelim();
    CalcularOperacion(nro1,oper,nro2);
}

int main (void){ 
    while(1){
        LeerPregunta();
    }
    return 0;
}
  
