/*  Andrés Barragán Salas               A01026567
    Carla Pérez Gavilán del Castillo    A01023033

    Actividad 3: Administración de un SO - Ejercicio 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define quantum 4

typedef struct Processes
    {
        int id;
        int time; 
        struct Processes * next;
    } Process;

typedef struct Gangs
    {
        int num;
        int id;
        Process * first;
        struct Gangs * next; 
    } Gang;




Gang * createGang(int id, int num, Process * queue);
Process * createProcess(int time, int id);
void execute_process(Process * p);
void enqueue_gang(Gang * toAdd);
void enqueue_process(Process * toAdd, Process * first_process);
Process * dequeue_process(Process * first_process);
Gang * dequeue_gang();

Gang * first;
int count;

int main(int argc, const char * argv[])
    {
        //Initialize Variables
        count = 0;
        int process_counter = 0;
        int num_procesos = 0;
        int tiempo_proceso = 0;
        int proceso_gang = 0;
        int num_cpu = 0;
        int num_gang = 0;
        int i = 0;

        //Get all inputs from user 
        printf("Ingrese el número total de procesos a planificar: ");
        scanf("%d", &num_procesos);

        printf("Ingrese el número de procesadores: ");
        scanf("%d", &num_cpu);

        printf("Ingrese el número de pandillas (gangs): ");
        scanf("%d", &num_gang);

        //Gang Creation 
        for(;i<num_gang; i++){

            printf("Ingrese el número de procesos para el gang %d \n", i);
            scanf("%d", &proceso_gang);
            Process * first = NULL;

            for(int j=0; j<proceso_gang; j++){
                printf("Ingrese el tiempo del proceso %d: \n", j);
                scanf("%d", &tiempo_proceso);
                Process * temp = createProcess(tiempo_proceso, j);
                enqueue_process(temp, first);
                process_counter++;
            }

            Gang * new_gang = createGang(i, proceso_gang, first);
            enqueue_gang(new_gang);
            printf("Gang creada \n");
        }
        

        //Gang Execution
        Gang * in_execution;
        
        
        while( num_gang > 0)
        {

            //Get first gang in queue
            in_execution = dequeue_gang();
            int num_process_gang = in_execution->num;
            printf(" EJECUTANDO GANG %d \n", in_execution->id);

            //Each CPU should execute a single process the quantum assigned time. 
            for(i=0; i<num_cpu; i++)
            {
                if(num_process_gang != 0)
                {
                    Process * temp = dequeue_process(in_execution->first);
                    printf(" EJECUTANDO PROCESO %d DE TIEMPO %d \n", temp->id, temp->time);
                    execute_process(temp, quantum);

                    if(temp->time > 0)
                    {
                    enqueue_process(temp, in_execution->first);
                    printf(" Formando de nuevo: NO TERMINO PROCESO %d FALTA TIEMPO %d \n", temp->id, temp->time);

                    }else
                    {
                        free(temp);
                    }
                    num_process_gang--;
                }
                  
            }
            
            if(in_execution->first != NULL)
            {
                enqueue_gang(in_execution);
            }else
            {
                free(in_execution);
                num_gang--;
            }
        }
        
    }

    Gang * createGang(int id, int num, Process * queue)
    {
        Gang * new = (Gang *)malloc(sizeof(Gang));
        new->first = queue;
        new->num = num;
        new->id = id;

        return new;
    }

    Process * createProcess(int time, int id)
    {
        Process * new = (Process *)malloc(sizeof(Process));
        new->time = time;
        new->id = id;
        return new;
    }

    void execute_process(Process * p)
    {
    p->time -= quantum;
    }

    void enqueue_gang(Gang * toAdd)
    {
        if(first==NULL)
        {
            first=toAdd;
        }else
        {
            Gang * temp = first;
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            temp->next=toAdd;
        }
        count++;
    }

void enqueue_process(Process * toAdd, Process * first_process){
	if(first_process==NULL)
    {
		first_process=toAdd;
	}else
    {
		Process * temp = first_process;
		while(temp->next!=NULL)
        {
			temp=temp->next;
		}
		temp->next=toAdd;
	}
}

Process * dequeue_process(Process * first_process)
{
	Process *toReturn = first_process;
	first_process = first_process->next;
	toReturn->next=NULL;
	return toReturn;
}

Gang * dequeue_gang()
{
	Gang *toReturn = first;
	first = first->next;
	count--;
	toReturn->next=NULL;
	return toReturn;
}
