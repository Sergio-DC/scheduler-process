#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PCB
{
    int procces_id;
    int arrival_time;
    int cpu_burst;
    int priority;

    int completionTime;//tiempo de finalización
    int turnAroundTime;//tiempo de retorno
    int waitingTime;//tiempo de espera

    struct PCB * next;
};

struct PCB *first = NULL, *last = NULL, *actual = NULL, *new = NULL;
int quantum;
int contador = 0;// Está variable determinará el tamaño de la lista enlazada
int num1,num2,num3,num4;

void readFile();//función que nos permite leer un archivo de texto y tokenizar los datos
void releaseMemory();//función que se utiliza para liberar memoria cuando el hayamos finalizado el programa
void genLinkedList(int, int, int, int);//Genera una lista enlazada
void showLinkedList();//Funcion Debug() muestra la lista enlazada con datos importantes del planificador
void showOrderedList(); //Funcion Debug() que muestra la lista enlazada ordenada
int completionTime(struct PCB *, int);//calcula el tiempo en el que finalizo un proceso después de ejecutarse
void turnAroundTime(struct PCB *);//calcula el tiempo de retorno por cada procese
void waitingTime(struct PCB *);// calcula el tiempo de espera de cada proceso
void sortById();//Ordena la lista enlazada de menor a mayor


int main()
{
    readFile();
    showLinkedList();
    printf("\n\nOrdenados: \n");
    sortById();
    showOrderedList();
    releaseMemory();
    showLinkedList();
    return 0;
}

void readFile()
{
      FILE * archivo;
      int procces_id, arrival_time, cpu_burst, priority;
      char num[20];
      char * token;
      int digit;

      archivo = fopen("input.txt", "r"); //Abrimos el archivo txt que se encuntra en la misma ubicación que scheduler.c

      while (!feof(archivo))
      {
          if(contador == 0)
          {
              fscanf(archivo,"%d", &quantum);
              printf("quantum: %d\n", quantum);
              contador++;
          }
          else
          {
              //leemos los 4 valores del txt y los guardmos
              int x = fscanf(archivo,"%d %d %d %d\n",&procces_id, &arrival_time,&cpu_burst,&priority);
              //Guardamos los datos en un bloque de memoria que formara parte de una Lista enlazada
              genLinkedList(procces_id, arrival_time, cpu_burst, priority);
              contador++;
          }
      }

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

void genLinkedList(int procces_id, int arrival_time, int cpu_burst, int priority)
{
      //1. Reservar Espacio en memoria
      new = (struct PCB *)malloc(sizeof(struct PCB));
      new->procces_id = procces_id;
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

void showLinkedList()
{
  int priorCompletionTime = 0;//Esta variable guarda el tiempo de finalización de un proceso anterior
  float acumulador = 0;//acumula la suma del tiempo promedio

    actual = first;
    if(actual == NULL)
        printf("Lista Vacia\n");
    else
    {
        while (actual != NULL)
        {
            printf("procces_id: %d\n", actual->procces_id);//Mostramos el pid
            printf("arrival_time: %d\n", actual->arrival_time);//Mostramos el tiempo en que llego el proceso
            printf("cpu_burst: %d\n", actual->cpu_burst);//Mostramos la ráfaga de CPU
            printf("priority: %d\n", actual->priority);//// Mostramos la prioridad
            priorCompletionTime = completionTime(actual, priorCompletionTime);//calculamos el tiempo en que finalizo un proceso
            printf("completionTime: %d\n", actual->completionTime);
            turnAroundTime(actual);
            printf("turnAroundTime: %d\n", actual->turnAroundTime);
            waitingTime(actual);
            printf("waitingTime: %d\n\n", actual->waitingTime);
            acumulador = acumulador + (float)actual->waitingTime;
            actual = actual->next;
        }
          printf("averageWaitingTime: %.2f\n\n", acumulador/(contador-1));
    }
}

int completionTime(struct PCB *process, int n)//n es el tiempo de finalización del proceso anterior
{
    process->completionTime = n + process->cpu_burst;

    return  process->completionTime;
}

void turnAroundTime(struct PCB *process)
{
    process->turnAroundTime = process->completionTime - process->arrival_time;
}

void waitingTime(struct PCB *process)
{
    process->waitingTime = process->turnAroundTime - process->cpu_burst;
}

void sortById()//Ordena la lista enlazada en función de cpu_burst
{
  int i, hop=1;
  struct PCB *aux = NULL, *anterior = NULL;


    for(i=0; i<contador-1; i++)
    {
        actual = first;
        while (actual->next != NULL)
        {
            aux = actual->next;
            if(actual->cpu_burst > aux->cpu_burst && hop==1)
            {
                actual->next = aux->next;
                aux->next = actual;
                anterior = aux;
                first = aux;
                hop++;
            }
            else if(actual->cpu_burst > aux-> cpu_burst)
            {
                actual->next = aux->next;
                aux->next = actual;
                anterior->next = aux;
                anterior = aux;
            }
            else
            {
                if(hop == 1)
                {
                    first = actual;
                    anterior = actual;
                    actual = actual->next;
                    hop++;
                }
                else
                {
                    anterior = actual;
                    actual = actual->next;
                }
            }
        }
        hop = 1;
    }

}

void showOrderedList()
{
    actual = first;
    if(actual == NULL)
        printf("Lista Vacia\n");
    else
    {

        printf("\n\n\n");
        while (actual != NULL)
        {
            printf("cpu_burst: %d\n", actual->cpu_burst);//Mostramos la ráfaga de CPU
            actual = actual->next;
        }
    }
}
