// Nombre       : directorio.c
// Proposito    : Gestiona directorio desde un archivo
// Autor        : Alex H. Pfoccori Quispe
// FCreacion    : 30/08/2022
// FMod         : --
// Compilacion  : gcc directorio.c -o directorio.exe -Wall
// Ejecucion    : ./directorio.exe archivo.csv

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Menu
void mostrarMenu() {
	puts("");
	puts("********* SISTEMA DE GESTION DE LIBROS **********");
	puts("*                                               *");
	puts("*    1. Almacenar nuevo registro                *");
	puts("*    2. Mostrar directorio                      *");
	puts("*    3. Buscar por Nombres                      *");
	puts("*    4. Buscar por Apellidos                    *");
	puts("*    5. Salir                                   *");
	puts("*                                               *");
	puts("*************************************************");
	puts("");
}

int main () {

    //Variables
    FILE * ptr;
    char registro[50];
    char *ret = NULL;
    char nombre[20];
    char apellido[20];
    int longitud;
	int opcion;
    int count = 0;
	char aux[2];

	do {
		// Indicar que hacer al programa
		mostrarMenu();

		// Leer opcion
		printf("\nIngrese una opcion (1-5): ");
		scanf("%[^\n]%*c", aux);
		opcion = atoi(aux);  // Castear el tipo de dato char a numerico

		// Evalucion de opciones
		switch(opcion) {
			case 1:
				char prDato[50];
                char sdDato[21];
                char trDato[10];
                // Leer datos de consola
                printf("Ingrese nombre(s) (tam max 20 letras): ");
                scanf("%[^\n]%*c", prDato);
                fflush(stdin);
                printf("Ingrese apellido(s) (tam max 20 letras): ");
                scanf("%[^\n]%*c", sdDato);
                fflush(stdin);
                printf("Ingrese el telefono (tam max 9 numeros): ");
                scanf("%[^\n]%*c", trDato);

                // Concatenando
                strcat(prDato, ",");
                strcat(prDato, sdDato);
                strcat(prDato, ",");
                strcat(prDato, trDato);
                strcat(prDato, "\n");

                // Apertura del archivo
                ptr = fopen("mi-directorio.csv", "a+");

                if(ptr == NULL) {
                    fprintf(stderr, "El archivo no se creo correctamente");
                    return 1;
                }
                // Anadiendo registro al mi-directorio
                longitud = strlen(prDato);
                for(int i = 0; i < longitud; i++) {
                    fputc(prDato[i], ptr);
                }
                // Cierre del archivo
                fclose(ptr);

				break;

			case 2:
                // Apertura
                ptr = fopen("mi-directorio.csv", "r");
                if(!ptr) {
                    printf("No se ha podido abrir, no existe el archivo\n");
                    return 1;
                }
                // Impresion
                printf("\nNombres, Apellidos, Telefono\n");
                do {
                    if(fgets(registro, 50, ptr)) {
                        printf("%s", registro);
                    }
                } while(!feof(ptr));
                // Cierre
                fclose(ptr);
				break;

                
			case 3:

                // Leer datos de consola
                printf("Ingrese el nombre (tam max 20 letras): ");
                scanf("%[^\n]%*c", nombre);

                // Apertura
                ptr = fopen("mi-directorio.csv", "r");
                if(!ptr) {
                    printf("No se ha podido abrir");
                    return 1;
                }

                //Busqueda
                count = 0;
                 printf("\nNombres, Apellidos, Telefono\n");
                do {
                    if(fgets(registro, 50, ptr)) {
                        
                        ret = strstr(registro, nombre);
                        if(ret != NULL) {
                            printf("%s", registro);
                            count++;
                            break;
                        }
                    }
                } while(!feof(ptr));
                if(count == 0) {
                    printf("No se ha encontrado\n");
                }
                //Cierre
                fclose(ptr);

				break;
			case 4:

                // Leer datos de consola
                printf("Ingrese el apellido (tam max 20 letras): ");
                scanf("%[^\n]%*c", apellido);

                // Apertura
                ptr = fopen("mi-directorio.csv", "r");
                if(!ptr) {
                    printf("No se ha podido abrir");
                    return 1;
                }

                //Busqueda
                count = 0;
                 printf("\nNombres, Apellidos, Telefono\n");
                do {
                    if(fgets(registro, 50, ptr)) {
                        
                        ret = strstr(registro, apellido);
                        if(ret != NULL) {
                            printf("%s", registro);
                            count++;
                            break;
                        }
                    }
                } while(!feof(ptr));
                if(count == 0) {
                    printf("No se ha encontrado\n");
                }
                //Cierre
                fclose(ptr);

				break;
			case 5:
				break;
			default:
				puts("La opcion no es correcta");
				break;
		}
	} while(opcion != 5);
    return 0;
}

