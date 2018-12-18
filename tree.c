#include <stdio.h> //snprintf,printf
#include <stdint.h> //enteros estandar
#include <stdlib.h> //free,calloc,perror
#include <dirent.h> //opendir,readdir,closedir
#include <string.h> //strlen, strcmp

void listarDir(const char*, int64_t, int64_t*, int64_t*); //Prototipo

int32_t main(const int32_t argc, const char *argv[])
{
    if (argc == 2)//Se valida la cantidad de argumentos pasados
    {
        int64_t dirs= 0, archs= 0; //Variables donde se cuentan los elementos
        printf("\n\n[%s]\n",argv[1]);
        listarDir(argv[1], 1, &dirs, &archs); //Se pasan por referencia
        printf("\nDirectorios: %jd, Archivos: %jd\n",dirs,archs);
        return EXIT_SUCCESS;
    }

    else
    {
        printf("Error al ingresar los parametros\n");
        return EXIT_FAILURE;
    }
}

void listarDir(const char *rutaParcial,int64_t nivel,int64_t *d,int64_t *a)
{
    char *ruta= (char*)calloc(1024,sizeof(char)); //Memoria para la ruta
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

    do 
    {
        if (contenido->d_type == DT_DIR) //Se verifica si la entrada es un archivo o un directorio
        {
            snprintf(ruta,1023,"%s/%s",rutaParcial,contenido->d_name); //Se escribe la ruta siguiente a usarse

            if (strcmp(contenido->d_name, ".") == 0 || strcmp(contenido->d_name, "..") == 0) //No se imprimen . ni ..
                continue;

            printf("%*s[%s]\n", (int32_t)nivel*4, "", contenido->d_name); //Se usa %*s para hacer las sangrias del nivel
            (*d)++; //Se incrementa el contenido
            listarDir(ruta, nivel+1,d,a); //Se muestra la carpeta siguiente
        }

        else 
        {
            printf("%*s- %s\n", (int32_t)nivel*4, "", contenido->d_name); //Caso archivo
            (*a)++;
        }
    } while ((contenido= readdir(carpeta))!= NULL);

    closedir(carpeta); //Se cierra el flujo
    free(ruta); //Se libera la memoria
}
