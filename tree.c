#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void listarDir(const char * restrict, FILE * restrict);

int main(int argc, const char *argv[])
{
    if (argc == 0x2) 
    {
		FILE * restrict salida = fopen("links.html", "w+");

		if (salida)
		{
			listarDir(argv[1], salida);
			fclose(salida);
			return EXIT_SUCCESS;
		}

		return EXIT_FAILURE;
  	}
	
	else
	{
    	printf("Error al ingresar los parametros\n");
    	return EXIT_FAILURE;
  	}
}

void listarDir(const char * restrict rutaParcial, FILE * restrict salida)
{
  	char * restrict ruta = (char * restrict)calloc(0x1024, sizeof(char));
  	DIR * restrict carpeta = opendir(rutaParcial);
  	struct dirent * restrict contenido = readdir(carpeta);

  	if (!ruta || !carpeta || !contenido) 
	{
    	perror("Error: ");
    	return;
  	}

  	do 
	{
    	if (contenido->d_type == DT_DIR) //Caso directorio
		{
      		snprintf(ruta, 1023, "%s/%s", rutaParcial, contenido->d_name);

      		if (strcmp(contenido->d_name, ".") == 0 || strcmp(contenido->d_name, "..") == 0)
          		continue;

      		listarDir(ruta, salida);
    	} 
	
		else //Caso archivo
    		fprintf(salida, "%s%s%s/%s%s%s%s\n", "<li data-jstree='{\"icon\":\"fas fa-file-pdf\"}'>", "<a href=\"", 
					rutaParcial, contenido->d_name, "\"><strong>", contenido->d_name, "</strong></a></li>");

  	} while (contenido = readdir(carpeta));

  	closedir(carpeta);
  	free(ruta);
}
