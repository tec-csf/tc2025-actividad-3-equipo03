/*  Andrés Barragán Salas               A01026567
    Carla Pérez Gavilán del Castillo    A01023033

    Actividad 3: Administración de un SO - Ejercicio 2
*/

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

// Tamaño de los grupos y máximo número de grupos
#define groupSize 1024
#define maxGroupNumber 10

// Estructuras en donde guardar la información obtenida al iterar sobre los directorios
int groupCount = 1;
int fileCount = 0;
int * groups;

/*  Método utilizado para incrementar el tamaño del arreglo dinamicamente a un tamaño dado.
    @param groupNumber: el número de elementos al cual se desea incrementar el arreglo.
*/
void growGroupList(int groupNumber) {
    // Agrandar el numero de elementos en el arreglo dinámicamente
	groups = realloc(groups, sizeof(int) * groupNumber);
    // Asignar 0s a los nuevos elementos
	int * aux = groups + groupCount;
	groupCount = groupNumber;
	int * last = groups + groupNumber;
	for(; aux<last; ++aux) {
		*aux = 0;
	}
}

/*  Metodo utilizado para imprimir la cantidad de asteríscos (*) adecuada al mostrar el histograma de los directorios recorridos.
    @param n: tamaño del grupo que se desea mostrar gráficamente.
*/
void printGraph(int n) {
    // Se obtiene una relación porcentual para imprimir la cantidad correcta de asteríscos
    int size = n * 100 / fileCount;
    // Imprimir los asteríscos
    for (int i=0; i<size; ++i) {
        printf("*");
    }
    printf("\n");
}

/*  Función recursiva que itera sobre todos los subdirectorios posibles dado el nombre de un directoriio inicial. 
    @param directoryPath: nombre o dirección del directorio a partir del cual se comenzará a buscar.
*/
void filesBySizeIn(char * directoryPath) {
	struct stat info;
	struct dirent * directory;
	DIR * directoryStream;

	directoryStream = opendir(directoryPath);

	if (!directoryStream)
		return;
    
    // Iterar sobre todos los elementos presentes en el directorio actual
	while ((directory = readdir(directoryStream)) != NULL) {
        // Obtener la informacion del directorio actual y su direccion completa (path)
		char path[1024];
		snprintf(path, sizeof(path), "%s/%s", directoryPath, directory->d_name);
		stat(path, &info);
        
        // Evitar los directorios "." y ".."
		if (strcmp(directory->d_name, ".") !=0 && strcmp(directory->d_name, "..") !=0) {
            // Llamar recursivamente cuando el elemento actual es un directorio
			if (S_ISDIR(info.st_mode)) {
				filesBySizeIn(path);
			}
            // Obtener la información si se trata de un archivo
			else if (S_ISREG(info.st_mode)) {
                // Obtener el grupo al cual asignar el archivo con su tamaño y determinar si aumentar el número de grupos posibles
				int i = info.st_size/groupSize;
				if (i >= groupCount) {
                    if (groupCount == maxGroupNumber) {
                        i = maxGroupNumber - 1;
                    }
                    else if (i > maxGroupNumber) {
                        growGroupList(maxGroupNumber);
                        i = maxGroupNumber - 1;
                    }
                    else {
                        growGroupList(i + 1);
                    }
				}
				*(groups + i) += 1;
                fileCount++;
			}
		}
	}
    // Cerrar el directorio
	closedir(directoryStream);
}

int main (int argc, char **argv) {
    // Inicializar el arreglo de grupos dinámicamente
	groups = (int *)malloc(sizeof(int) * groupCount);
	*groups = 0;

    // Actualizar la información de los grupos en la carpeta actual
	filesBySizeIn(".");

    // Imprimir la información pertinente para cada uno de los grupos
    printf("%-20s %-20s %-10s\n", "Urna", "Numero Archivos", "Histograma");
	int * aux = groups;
	int * last = groups + groupCount;
    int count = 0;
	for (; aux < last; ++aux) {
        if (*aux > 0) {
            char range[50];
            if (aux == last - 1 && groupCount == maxGroupNumber) {
                snprintf(range, sizeof(range), "%d - %s", count * groupSize, "+++");
            }
            else {
                snprintf(range, sizeof(range), "%d - %d", count * groupSize, (count+1) * groupSize - 1);
            }
		    printf("%-20s %-20d ", range, *aux);
            printGraph(*aux);
        }
        count++;
	}

    // Liberar memoria
	free(groups);

	return 0;
}