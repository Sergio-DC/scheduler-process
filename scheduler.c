#include <stdlib.h>
#include "pcb.h"//Estructura del "Process Control Block"
#include "avgWaitTimeNon.h"//Average waiting time Non Preemptive
#include "sortNonSJF.h"//funciones de ordenamiento  de procesos por ráfaga de CPU
#include "sortNonPriority.h"//funciones de ordenamiento de procesos por prioridad

struct PCB *first = NULL, *last = NULL, *actual = NULL, *new = NULL;
int quantum;
int size = 0;// Está variable determinará el tamaño de la lista enlazada

void readFile();//función que nos permite leer un archivo de texto y tokenizar los datos
void releaseMemory();//función que se utiliza para liberar memoria cuando el hayamos finalizado el programa
void genLinkedList(int, int, int, int);//Genera una lista enlazada
void showList(); //Funcion Debug() que muestra la lista enlazada ordenada
char * nameFile;
/*Planificadores de procesos, tienen que colocar las funciones en este formato*/
void fcfs();                /*Revisen la implementación de las funciones abajo, a partir de la linea 119*/ 
void sjfNonPreemptive();    /*Traten de hacer sus implementaciones siguiendo ese patrón*/
void nonPriority();
/***************************************************************************************/

int main(int argc,char * argv[])
{
	 nameFile = argv[1];
    fcfs();
    releaseMemory();
    sjfNonPreemptive();
    releaseMemory();
    nonPriority();

    return 0;
}

void readFile()
{
      FILE * archivo;
      int process_id, arrival_time, cpu_burst, priority;

      archivo = fopen(nameFile, "r"); //Abrimos el archivo txt que se encuentra en la misma ubicación que scheduler.c

      while (!feof(archivo))
      {
          if(size == 0)
          {
              fscanf(archivo,"%d", &quantum);
              size++;
          }
          else
          {
              //leemos los 4 valores del txt y los guardmos
              fscanf(archivo,"%d %d %d %d\n",&process_id, &arrival_time,&cpu_burst,&priority);
              //Guardamos los datos en un bloque de memoria que formara parte de una Lista enlazada
              genLinkedList(process_id, arrival_time, cpu_burst, priority);
              size++;
          }
      }
      fseek(archivo,0,SEEK_SET);
        fclose(archivo);
}

void releaseMemory()
{
    struct PCB * aux_free; //aux_free permite liberar la memoria
    actual = first;

    while (actual != NULL)
    {
        aux_free = actual;
        actual = actual->next;
        free(aux_free);//Liberamos memoria
    }
    //Los apuntadores hacemos que apunte NULL
    first = NULL;
    last = NULL;
    actual = NULL;
    aux_free = NULL;
    new = NULL;
}

void genLinkedList(int process_id, int arrival_time, int cpu_burst, int priority)
{
      //1. Reservar Espacio en memoria
      new = (struct PCB *)malloc(sizeof(struct PCB));
      //2. Guardamos los datos en un bloque de memoria
      new->process_id = process_id;
      new->arrival_time = arrival_time;
      new->cpu_burst = cpu_burst;
      new->priority = priority;

      if(first == NULL)//Construimos la cabeza de la lista enlazada
      {
          first = new;
          last = new;
          last->next = NULL;
      }
      else//Construimos la cola de la lista enlazada
      {
          last->next = new;
          new->next = NULL;
          last = new;
      }
}

void showList()//Muestra el número de proceso y la ráfaga de CPU, esta función se utiliza con el fin de corregir errores en los 
{               //algoritmos de planificación
    actual = first;
    if(actual == NULL)
        printf("Lista Vacia\n");
    else
    {
        while (actual != NULL)
        {
            printf("process: %d  cpu_burst: %d\n", actual->process_id,actual->cpu_burst);//Mostramos la ráfaga de CPU
            actual = actual->next;
        }
    }
}

void fcfs()
{
    readFile();
    //showList();Funcion para debug
    showNonPreemptiveAWT(first, size, "FCFS");
    size = 0;//se le da el valor de 0 para que el siguiente planificador que sea llamado pueda leer correctamente del archivo txt
}

void sjfNonPreemptive()
{
    readFile();
    first = sortByCpuBurst(first, size);
    //showList();Funcion para debug
    showNonPreemptiveAWT(first, size, "Non-preemptive SJF");
    size = 0;//se le da el valor de 0 para que el siguiente planificador que sea llamado pueda leer correctamente del archivo txt
}

void nonPriority()
{
    readFile();
    first = sortByPriority(first, size);
    //showList();Funcion para debug
    showNonPreemptiveAWT(first, size, "Non-preemptive priority");
    size = 0;//se le da el valor de 0 para que el siguiente planificador que sea llamado pueda leer correctamente del archivo txt

}
