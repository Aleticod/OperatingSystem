#include <stdio.h>
#include <string.h>

int main(void) {
    //Variables
    FILE* archivo = NULL;

    int i;
    int longitud;
    int estado;
    char cadena[] = "cadena que se almacena en una archio";

    //Procesar

    //Abrir archivo para escritura. Si no existe se crea
    archivo = fopen("archivo.txt", "wt");

    if(archivo != NULL) {
        //Calcular la longitud de la cadena de caracteres
        longitud = strlen(cadena);

        //Escribir los caracteres uno por uno en el archivo
        for(i = 0; i < longitud; i++) {
            estado = fputc(cadena[i], archivo);
            if(estado == EOF) {
                puts("Ha ocurrido un error al escribir en el archivo");
            }
        }
        fputc('\n', archivo); //Insertar un salto de linea
    }
    else {
        puts("No se pudo abrir el archivo");
    }
    return 0;
}