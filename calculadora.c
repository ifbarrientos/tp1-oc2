#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define LONG_MAX 256
const char *patron = "^-?[[:digit:]]{1,10}[[:space:]][+\\*\\/-][[:space:]]-?[[:digit:]]{1,10}$";
const char *patron_continuo = "^[+\\*\\/-][[:space:]]-?[[:digit:]]{1,10}$";

extern int sum_mmx(int a, int b);
//extern int res(int a, int b);
//extern int mul(int a, int b);
//extern int divi(int a, int b);

int nro1, nro2, resultado;
bool continua;
char oper_texto[4], oper_texto_continua[3], oper, str[LONG_MAX];

bool ChequearRegex(const char *input){
    regex_t regex;
    int ret;

    ret = regcomp(&regex, input, REG_EXTENDED);

    if (ret){
        fprintf(stderr, "No se pudo compilar el regex\n");
        return false;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (!ret){
        puts("Ok!");
    } else if (ret == REG_NOMATCH) {
        //Falló el regex
        return false;
    } else {
        char msgbuf[LONG_MAX];
        regerror(ret, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Fallo el matcheo de regex: %s\n", msgbuf);
        return false;
    }
    regfree(&regex);
    return true;
}

int CalcularOperacion(int operando1, char operador, int operando2){
    if (operador == '+'){
        resultado = sum_mmx(operando1, operando2);
    } else if (operador == '-'){
        //resultado = res(operando1, operando2);
    } else if (operador == '*'){
        //resultado = mul(operando1, operando2);
    } else if (operador == '/'){
        if (operando2 == 0){
            fprintf(stderr, "No se puede dividir por cero\n");
            return 0;
        }
        //resultado = divi(operando1, operando2);
    }
        printf("Presione CTRL + C para salir\n");
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
        token = strtok(str, oper_texto_continua);
    } else {
        token = strtok(str, oper_texto);
    }
    
    /* Identifica los otros token */
    int i = 1;
    if (continua) {
        while (token!=NULL){
            nro1 = resultado;
            nro2 = atoi(token);
            token = strtok(NULL, oper_texto_continua);
        }
    } else {
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
    }
    printf("Nro1 = %d, Nro2 = %d, Operador = %c\n", nro1,nro2,oper);
}

void LeerPregunta(){
    if (ChequearRegex(patron)){
        continua = false;
        printf("Operación nueva detectada\n");
    } else if (ChequearRegex(patron_continuo)){
        continua = true;
        printf("Operación continua detectada\n");
    } else {
        printf("Lo siento, mis respuestas son limitadas.\nAseguráte de escribir la operación como '1 + 2' por ejemplo.");
    }
    IdentificarNrosYDelim();
    CalcularOperacion(nro1,oper,nro2);
}

void LeerInput(){
    if (fgets(str, LONG_MAX, stdin) != NULL) { //Hace el input
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n')  //Le saca el \n al final
        str[len-1] = '\0';
    } else {
        fprintf(stderr, "Hubo un error al leer el input\n");
        return;
    }
}

int main (void){ 
    continua = false;
    printf("Por favor, ingrese una operación matemática con espacios entre los numeros y el operando:\n");
    while(1){
        LeerInput();
        LeerPregunta();
    }
    return 0;
}