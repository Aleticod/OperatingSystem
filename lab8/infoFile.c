#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


int main(int argc, char *argv[]) {
    // Variables
    struct stat info;
    struct passwd *pw;
    struct group *gr;

    int ret;
    int i;
    char permisos[] = {'x', 'w', 'r'};

    // Procesar y mostrar resultados

    if (argc < 2) {
        fprintf(stderr, "Uso del programa: %s <archivo> \n", argv[0]);
        return 1;
    }

    ret = stat(argv[1], &info);

    if (ret) {
        perror("stat");
        return 1;
    }

    printf("Informacion del archivo %s \n", argv[1]);

    printf("\tReside en el dispositivo contenedor: %ld, %ld\n", (info.st_dev & 0xff00) >> 8, info.st_dev & 0x00ff);

    printf("\tNro de i-nodo: %ld \n", info.st_ino);

    printf("\tTipo de dispositivo: ");
    //tipo de dispositivo
    switch(info.st_mode & S_IFMT) {
        case S_IFREG:
            printf("Ordinario.\n");
            break;
        case S_IFDIR:
            printf("Directorio.\n");
            break;
        case S_IFCHR:
            printf("Especial de caracter.\n");
            break;
        case S_IFBLK:
            printf("Especial de bloque.\n");
            break;
        case S_IFIFO:
            printf("FIFO.\n");
            break;
    }

    if (info.st_mode & S_ISUID) {
        printf("\t\t\t Cambiar el ID del propietario en ejecucion\n");
    }

    if(info.st_mode & S_ISGID) {
        printf("\t\t\t Cambiar el ID del grupo en ejecucion.\n");
    }
    if(info.st_mode & S_ISVTX ) {
        printf("\t\t\t Sticky bit archivo.\n");
    }

    //Mostrar los permisos
    printf("\tPermisos: O%o ", info.st_mode & 0777);

    for (i = 0; i < 9; i++) {
        if(info.st_mode & (0400 >> i)) {
            printf("%c", permisos[(8 - i) % 3]);
        }
        else {
            printf("-");
        }
    }

    printf("\n\tNumeros de enlaces: %ld\n", info.st_nlink);

    //UID y GID
    printf("\tUser ID: %d; Nombre: ", info.st_uid);

    if((pw = getpwuid(info.st_uid)) == NULL) {
        printf("???\n");
    }
    else {
        printf("%s\n", pw->pw_name);
    }

    printf("\tGroup ID: %d; Nombre: ", info.st_gid);

    if((gr = getgrgid(info.st_gid))  == NULL) {
        printf("???\n");
    }
    else {
        printf("%s\n", gr->gr_name);
    }

    // presentacion de los numeros de dispositiovs

    switch (info.st_mode & S_IFMT) {
        case S_IFCHR:
        case S_IFBLK:
            printf("\tNumero de dispositovs %ld, %ld\n", (info.st_rdev & 0xff00) >> 8, info.st_rdev & 0x00ff);
    }

    // Tamanio del archivo 
    printf("\tTamanio: %ld bytes\n", info.st_size);

    // Tamanio del bloque para E/S

    printf("\tTamanio de bloque para E/S: %ld bytes\n", info.st_blksize);

    // Numero de bloques asignados
    printf("\tNro de bloques asignados: %ld\n", info.st_blocks);

    // Registro de tiempo
    printf("\tFecha de ultimo acceso: %s", asctime(localtime(&info.st_atime)));

    printf("\tFecha de ultima modificacion: %s", asctime(localtime(&info.st_mtime)));

    printf("\tFecha de ultimo cambio de estado: %s", asctime(localtime(&info.st_ctime)));

    return 0;

}