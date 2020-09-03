[![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://classroom.github.com/online_ide?assignment_repo_id=280727&assignment_repo_type=GroupAssignmentRepo)
# Actividad *3*: *Administración de un SO*  

##### Estudiantes:  
*Carla Pérez Gavilán del Castillo* - *A01023033* - *CSF*  
*Andrés Barragán Salas* - *A01026567* - *CSF*  


##### Profesor:  
*Vicente Cubells Nonell*

## Instrucciones
**Ejercicio 1.**

Realice un programa en C donde simule el comportamiento del algoritmo de planificación por pandilla. El programa debe permitir al usuario entrar por teclado el número total de procesos a planificar, el tiempo de CPU que se requiere para cada uno, la relación que existe entre los procesos (grupos) y el número de CPUs. Los grupos de procesos deben ir planificándose según el criterio que Ud. defina (puede ser Round Robin, FIFO, etc.), garantizando siempre un máximo aprovechamiento de todas las CPUs.

<ins>Nota:</ins> Para simular que un proceso consume tiempo de CPU, puede utilizar la función sleep()

Favor de revisar el Capítulo 8. Multiprocesadores,  Sección 8.1.4. Calendarización de multiprocesadores, del libro [Sistemas Operativos Modernos de Andrew S. Tanenbaum](https://books.google.com.mx/books/about/Sistemas_operativos_modernos.html?hl=es&id=g88A4rxPH3wC&redir_esc=y)
 

**Ejercicio 2.**

Escriba un programa en C que parta de un directorio dado y descienda por el árbol de archivos registrando los tamaños de todos los archivos que encuentre. Cuando termine, deberá imprimir un histograma de los tamaños de archivo, utilizando una anchura de urna especificada como parámetro ( por ejemplo, para un valor de urna de 1024, todos los archivos con tamaño entre 0 y 1023 se colocan en una urna, los de 1024 a 2047 en otra y así sucesivamente).

Debe utilizar llamadas al sistema (system calls). Por favor, verifique las llamadas al sistema para manipulación de archivos y directorios que a aparecen en la última clase.

Ejemplo de visualización del histograma:

    Urna        Número de archivos	    Histograma  
    0-1023      20	                    ********************  
    1024-2047   15	                    **************  
    2048-3071   35	                    *****************************  
    3072-4095   40	                    **************************************  

<ins>Sugerencia:</ins> Para determinar la cantidad de * a imprimir, defina una relación respecto al número máximo de archivos obtenido. Por ejemplo, si el número máximo de archivos obtenido es 1000, entonces divida la cantidad entre 100. De esta manera, para la cantidad máxima imprimirá 10 * y todos los demás estarán acotados por debajo de este máximo.
