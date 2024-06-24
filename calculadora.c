#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define LONG_MAX 256
const char *patron = "^-?[[:digit:]]{1,10}[[:space:]][+\\*\\/-][[:space:]]-?[[:digit:]]{1,10}$";
const char *patron_continuo = "^[+\\*\\/-][[:space:]]-?[[:digit:]]{1,10}$";

extern int sum(int a, int b);
extern int res(int a, int b);
extern int mul(int a, int b);
//extern int divi(int a, int b);

int nro1, nro2, resultado;
bool continua;
char oper, str[LONG_MAX];

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
        //puts("Ok!");
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
        resultado = sum(operando1, operando2);
    } else if (operador == '-'){
        resultado = res(operando1, operando2);
    } else if (operador == '*'){
        resultado = mul(operando1, operando2);
    } else if (operador == '/'){
        if (operando2 == 0){
            fprintf(stderr, "No se puede dividir por cero!\n");
            return 0;
        }
        //resultado = divi(operando1, operando2);
    }
        printf("\nPresione CTRL + C para salir. \nTambién puede realizar otra operación con el resultado (como '+ 1').\nO realizar una nueva operación (como '6 / 2').\n");
        printf("\nEl resultado es: %d\n", resultado);
        continua = true;
        str[0] = '\0';
        return resultado;
    }

void IdentificarNrosYOper(){
    if (continua) {
        nro1 = resultado;
        int cant_items = sscanf(str, "%c %d", &oper, &nro2);
    } else {
        int cant_items = sscanf(str, "%d %c %d", &nro1, &oper, &nro2);
    }
    //printf("Nro1 = %d, Nro2 = %d, Operador = %c\n", nro1,nro2,oper);
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

void LeerPregunta(){
    LeerInput();
    if (ChequearRegex(patron)){
        continua = false;
        //printf("Operación nueva detectada\n");
    } else if (ChequearRegex(patron_continuo) && continua==true){
        continua = true;
        //printf("Operación continua detectada\n");
    } else if (ChequearRegex(patron_continuo) && continua==false) {
        printf("\nAntes de realizar una operación continua haga una operación nueva, como '2 * 2'\n");
        return;
    } else {
        printf("Lo siento, mis respuestas son limitadas.\nAseguráte de escribir la operación como '1 + 2', con un espacio entre el signo y los numeros.\n");
        return;
    }
    IdentificarNrosYOper();
    CalcularOperacion(nro1,oper,nro2);
}

int main (void){ 
    continua = false;
    printf("Ingrese una operación matemática con un espacio entre los numeros y el operador:\n");
    while(1){
        LeerPregunta();
    }
    return 0;
}