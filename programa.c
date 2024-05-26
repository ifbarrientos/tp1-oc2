#include <stdio.h>
#include <regex.h>
#include <string.h>

#define LONG_MAX 256

int leer_pregunta(){
    char input[LONG_MAX];
    printf("Por favor, ingrese una operación matemática con espacios entre los numeros y el operando:\n");
    regex_t regex;
    int ret;
    const char *patron = "[[:digit:]]{1,10}[[:space:]][\\+\\*\\/\\-][[:space:]][[:digit:]]{1,10}";
    ret = regcomp(&regex, patron, REG_EXTENDED);
    char msgbuf[LONG_MAX];
    char *p;

    fgets(input, LONG_MAX, stdin); //Hace el input

    //Esta sección elimina el \n del fgets
    //if ((p = strchr(input, '\n')) != NULL)
    //  *p = '\0';

    if (ret){
        fprintf(stderr, "No se pudo compilar el regex\n");
        return 1;
    }

    ret = regexec(&regex, input, 0, NULL, 0);
    if (!ret){
        puts("Hay match!");
    } else if (ret == REG_NOMATCH) {
        puts("No hay match...");
    } else {
        regerror(ret, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Fallo el matcheo de regex: %s\n", msgbuf);
        return 1;
    }

    //printf("%s\n",input);

    regfree(&regex);
}

int main (void){
    leer_pregunta();
    return 0;
}
