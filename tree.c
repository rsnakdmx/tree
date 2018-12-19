#include <stdio.h> //snprintf,printf
#include <stdint.h> //enteros estandar
#include <stdlib.h> //free,calloc,perror
#include <dirent.h> //opendir,readdir,closedir
#include <string.h> //strlen, strcmp

void listarDir(const char * restrict); //Prototipo

int main(int argc, const char *argv[])
{
    if (argc == 0x2) 
    {
    	listarDir(argv[1]);
    	return EXIT_SUCCESS;
  	}
	
	else
	{
    	printf("Error al ingresar los parametros\n");
    	return EXIT_FAILURE;
  	}
}

void listarDir(const char * restrict rutaParcial)
{
  	char * restrict ruta= (char * restrict)calloc(0x1024,sizeof(char));
  	DIR * restrict carpeta;
  	struct dirent * restrict contenido;

  	if (!ruta || !(carpeta = opendir(rutaParcial)) || !(contenido = readdir(carpeta))) 
	{
    	perror("Error: ");
    	return;
  	}

  	do 
	{
    	if (contenido->d_type == DT_DIR) //Caso directorio
		{
      		snprintf(ruta,1023,"%s/%s",rutaParcial,contenido->d_name);

      		if (strcmp(contenido->d_name, ".") == 0 || strcmp(contenido->d_name, "..") == 0)
          		continue;

      		listarDir(ruta);
    	} 
	
		else //Caso archivo
    		printf("%s/%s\n", rutaParcial, contenido->d_name);

  	} while (contenido= readdir(carpeta));

  	closedir(carpeta);
  	free(ruta);
}
