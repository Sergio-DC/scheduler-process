#include <stdlib.h>
#include "pcb.h"
#include "awtNon.h"//Average waiting time Non Preemptive
#include "sjf_non.h"

struct PCB *first = NULL, *last = NULL, *actual = NULL, *new = NULL;
int quantum;
int size = 0;// Está variable determinará el tamaño de la lista enlazada

void readFile();//función que nos permite leer un archivo de texto y tokenizar los datos
void releaseMemory();//función que se utiliza para liberar memoria cuando el hayamos finalizado el programa
void genLinkedList(int, int, int, int);//Genera una lista enlazada
void showList(); //Funcion Debug() que muestra la lista enlazada ordenada
void fcfs();
void sjfNonPreemptive();

int main()
{
    
    fcfs();
    releaseMemory();
    sjfNonPreemptive();
    releaseMemory();

    return 0;
}

void readFile()
{
      FILE * archivo;
      int process_id, arrival_time, cpu_burst, priority;

      archivo = fopen("input.txt", "r"); //Abrimos el archivo txt que se encuntra en la misma ubicación que scheduler.c

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
    struct PCB * aux_free; //VARIABLE AUXILIAR QUE PERMITIRA LIBERAR LA MEMORIA USADA EN LA LISTA ENLAZADA
    actual = first;

    while (actual != NULL)
    {
        aux_free = actual;
        actual = actual->next;
        free(aux_free);
    }

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
      new->process_id = process_id;
      new->arrival_time = arrival_time;
      new->cpu_burst = cpu_burst;
      new->priority = priority;

      if(first == NULL)
      {
          first = new;
          last = new;
          last->next = NULL;
      }
      else
      {
          last->next = new;
          new->next = NULL;
          last = new;
      }
}

void showList()
{
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
    showNonPreemptiveAWT(first, size);
    size = 0;//se resetea para que se pueda volvel a leer del archivo
}

void sjfNonPreemptive()
{
    readFile();
    first = sortByCpuBurst(first, size);
    showNonPreemptiveAWT(first, size);
    size = 0;
}
