/*  Andrés Barragán Salas               A01026567
    Carla Pérez Gavilán del Castillo    A01023033

    Actividad 3: Administración de un SO - Ejercicio 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define quantum 4

/* Structure Definiton */
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
        Process * firstProcess;
        struct Gangs * next; 
    } Gang;



/* Declaration of Functions */

Gang * createGang(int id, int num, Process * firstProcess);

Process * createProcess(int time, int id);

void executeProcess(Process * p);

void enqueueGang(Gang * toAdd);

void enqueueProcess(Process * toAdd, Gang * g);

Process * dequeueProcess(Gang * g);

Gang * dequeueGang();

void printProcess(Process * firstProcess);

/* Declaration of begining of Gang queue and counter */
Gang * first;

int main(int argc, const char * argv[])
    {
        /* Variable Initializing */
        int processCounter = 0;
        int numProcesos = 0;
        int tiempoProceso = 0;
        int procesoGang = 0;
        int numCpu = 0;
        int numGang = 0;
        int i = 0;

        /* Generate Random Numbers */
        srand((int) time(NULL));

        /* Get user input */
        printf("Ingrese el número de procesos: \n ");
        scanf("%d", &numProcesos);

        printf("Ingrese el número de procesadores: \n");
        scanf("%d", &numCpu);

        printf("Ingrese el número de pandillas (gangs): \n");
        scanf("%d", &numGang);

        /* Gang creation */
        for(;i<numGang; i++)
        {

            printf("Ingrese el número de procesos para el gang %d \n", i);
            scanf("%d", &procesoGang);

            if(processCounter+procesoGang > numProcesos){
                printf("No puede designar esta cantidad a este gang ya que solo quedan %d procesos, ingresa una cantidad menor \n", numProcesos-processCounter+1);
                scanf("%d", &procesoGang);
            }

            Process * firstProcess = NULL;
            Gang * newGang = createGang(i, procesoGang, firstProcess);

            for(int j=0; j<procesoGang; j++)
            {
                tiempoProceso =(rand() %  10) + 1;
                Process * temp = createProcess(tiempoProceso, processCounter);
                enqueueProcess(temp, newGang);
                processCounter++;
            }

            enqueueGang(newGang);
            printf("--> Gang creada \n");
            printProcess(newGang->firstProcess);
        }

        /* Validating all process are asigned to a gang*/
        if(numProcesos>processCounter+1)
        {
            printf("ERROR: %d procesos no tienen gang, vuelva a intentarlo\n", numProcesos-(processCounter+1));
            return 0;
        }
        

        /* Gang Execution  */
        Gang * in_execution;

        while( numGang > 0)
        {

             /* Get first queue in gang */
            in_execution = dequeueGang();
            int num_process_gang = in_execution->num;

            printf(" --> Ejecución de pandilla número %d \n", in_execution->id);

            /* Get first queue in gang */
            for(i=0; i<numCpu; i++)
            {
                if(num_process_gang != 0)
                {
                    Process * temp = dequeueProcess(in_execution);
                    printf(" CPU %d: \t Ejecutando proceso  %d de tiempo %d  \n", i, temp->id, temp->time);
                    executeProcess(temp);
                    if(temp->time > 0)
                    {

                    enqueueProcess(temp, in_execution);
                    printf(" Formando de nuevo: No terminó de ejecutarse el proceso  %d en el quantum, tiempo que faltó; %d segundos \n\n", temp->id, temp->time);
                    }else{
                        in_execution->num--;
                        free(temp);
                    }
                    num_process_gang--;
                }
                  
            }
            
            if(in_execution->firstProcess != NULL)
            {
                enqueueGang(in_execution);
                printf("Gang no terminada! \n");
            }else
            {
                free(in_execution);
                numGang--;
            }
            printf("\n");
        }
        
    }

/*
 * Function: createGang
 * --------------------
 *  
 *  id (int): gang id
 *  num (int): number of process in gang
 *  queue (Proceess *): process queue to be executed
 * 
 *  returns: created gang
 */

    Gang * createGang(int id, int num, Process * firstProcess)
    {
        Gang * new = (Gang *)malloc(sizeof(Gang));
        new->firstProcess = firstProcess;
        new->num = num;
        new->id = id;
        new->next = NULL;

        return new;
    }

/*
 * Function: createProcess
 * --------------------
 *  
 *  id (int): gang id
 *  time (int): time it takes to execute process
 *  returns (Process *): created proces
 */

    Process * createProcess(int time, int id)
    {
        Process * new = (Process *)malloc(sizeof(Process));
        new->time = time;
        new->id = id;
        new->next = NULL;
        return new;
    }

/*
 * Function: executeProcess
 * --------------------
 *  p (Process *): process to be executed
 */

    void executeProcess(Process * p)
    {
    p->time -= quantum;
    sleep(quantum);
    }

/*
 * Function: enqueueGang
 * --------------------
 *  
 *  toAdd (Gang *):  Gang to be added to queue
 */

    void enqueueGang(Gang * toAdd)
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
    }

/*
 * Function: enqueueProcess
 * --------------------
 *  
 *  g (Gang *): Gang to add process 
 *  toAdd (Process *): process to be added to queue
 */

void enqueueProcess(Process * toAdd, Gang * g){
	if(g->firstProcess == NULL)
    {
		g->firstProcess = toAdd;
	}else
    {
		Process * temp = g->firstProcess;
		while(temp->next != NULL)
        {
			temp = temp->next;
		}
		temp->next = toAdd;
	}
}

/*
 * Function: dequeueProcess
 * --------------------
 *  
 *  g (Gang *): Gang to add process 
 *  returns (Process *): process that has been dequeued
 */

Process * dequeueProcess(Gang * g)
{
	Process *toReturn = g->firstProcess;
	g->firstProcess = g->firstProcess->next;
	toReturn->next = NULL;
	return toReturn;
}

/*
 * Function: dequeueGang
 * --------------------
 *  
 *  returns (Gang *): Gang that was just dequeued
 */

Gang * dequeueGang()
{
	Gang *toReturn = first;
    first=first->next;
	toReturn->next=NULL;
	return toReturn;
}

void printProcess(Process * firstProcess)
{
    Process *temp = firstProcess;
    printf(" PRINTING PROCESS QUEUE \n");
	while(temp!=NULL){
			printf("process id:%d, time:%d \n",temp->id, temp->time);
			temp=temp->next;
	}
	printf("\n");
}