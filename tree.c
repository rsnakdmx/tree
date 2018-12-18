#include <stdio.h> //snprintf,printf
#include <stdint.h> //enteros estandar
#include <stdlib.h> //free,calloc,perror
#include <dirent.h> //opendir,readdir,closedir
#include <string.h> //strlen, strcmp

void listarDir(const char*); //Prototipo

int32_t main(const int32_t argc, const char *argv[])
{
    if (argc == 2)//Se valida la cantidad de argumentos pasados
    {
        listarDir(argv[1]); //Se pasan por referencia
        return EXIT_SUCCESS;
    }

    else
    {
        printf("Error al ingresar los parametros\n");
        return EXIT_FAILURE;
    }
}

void listarDir(const char *rutaParcial)
{
    char *ruta= (char*)calloc(2048, sizeof(char)); //Memoria para la ruta
    FILE *salida = NULL;
    DIR *carpeta; //Flujo
    struct dirent *contenido; //Contenido de la carpeta

    if (!ruta) //Se comprueba que hay espacio para la ruta
    {
        perror("Error: ");
        return;
    }

    if (!(carpeta = opendir(rutaParcial))) //Se comprueba que sean directorios validos
    {
        perror("Error: ");
        return;
    }

    if (!(contenido = readdir(carpeta))) 
    {
        perror("Error: ");
        return;
    }

    salida = fopen("salida.txt", "w");

    do 
    {
        if (contenido->d_type == DT_DIR) //Se verifica si la entrada es un archivo o un directorio
        {
            if (!(strcmp(contenido->d_name, ".") == 0 || strcmp(contenido->d_name, "..") == 0))
            {
                snprintf(ruta, 2047, "%s/%s/", rutaParcial, contenido->d_name); //Se escribe la ruta siguiente a usarse
                listarDir(ruta); //Se muestra la carpeta siguiente
            }
        }

        else //Caso archivo
        {
            fprintf(salida, "%s%s%s%s%s%s%s\n", "<li data-jstree=\'{\"icon\":\"fas fa-file-pdf\"}\'>", "<a href=\"", 
                    rutaParcial, contenido->d_name, "\"><strong>", contenido->d_name, "</strong></a></li>"); 
        }
    } while (contenido = readdir(carpeta));

    fclose(salida);
    closedir(carpeta); //Se cierra el flujo
    free(ruta); //Se libera la memoria
}
