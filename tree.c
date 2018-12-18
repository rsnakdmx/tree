#include <stdio.h> //snprintf,printf
#include <stdint.h> //enteros estandar
#include <stdlib.h> //free,calloc,perror
#include <dirent.h> //opendir,readdir,closedir
#include <string.h> //strlen, strcmp

void listarDir(const char*, int64_t, int64_t*, int64_t*); //Prototipo

int32_t main(const int32_t argc, const char *argv[]){
  //Se valida la cantidad de argumentos pasados
  if (argc == 2) {
    int64_t dirs= 0, archs= 0; //Variables donde se cuentan los elementos
    printf("\n\n[%s]\n",argv[1]);
    listarDir(argv[1], 1, &dirs, &archs); //Se pasan por referencia
    printf("\nDirectorios: %jd, Archivos: %jd\n",dirs,archs);
    return EXIT_SUCCESS;

  }else{
    printf("Error al ingresar los parametros\n");
    return EXIT_FAILURE;
  }
}

void listarDir(const char *rutaParcial,int64_t nivel,int64_t *d,int64_t *a){
  char *ruta= (char*)calloc(1024,sizeof(char)); //Memoria para la ruta
  DIR *carpeta; //Flujo
  struct dirent *contenido; //Contenido de la carpeta

  //Se comprueba que hay espacio para la ruta
  if (!ruta) {
    perror("Error: ");
    return;
  }

  //Se comprueba que sean directorios validos
  if (!(carpeta = opendir(rutaParcial))) {
    perror("Error: ");
    return;
  }

  if (!(contenido = readdir(carpeta))) {
    perror("Error: ");
    return;
  }

  do {
    //Se verifica si la entrada es un archivo o un directorio
    if (contenido->d_type == DT_DIR) {
      //Se escribe la ruta siguiente a usarse
      snprintf(ruta,1023,"%s/%s",rutaParcial,contenido->d_name);

      //No se imprimen . ni ..
      if (strcmp(contenido->d_name, ".") == 0 ||
        strcmp(contenido->d_name, "..") == 0)
          continue;

      //Se usa %*s para hacer las sangrias correspondientes al nivel
      //printf("%*s[%s]\n", (int32_t)nivel*4, "", contenido->d_name);
      (*d)++; //Se incrementa el contenido
      listarDir(ruta, nivel+1,d,a); //Se muestra la carpeta siguiente
      //Se sigue enviando las referencias

    } else { //Caso directorio
      printf("%*s- %s/%s\n", (int32_t)nivel*4, "", rutaParcial, contenido->d_name);
      (*a)++;
    }
  } while ((contenido= readdir(carpeta))!= NULL);

  //Se cierra el flujo
  closedir(carpeta);
  free(ruta); //Se libera la memoria
}
