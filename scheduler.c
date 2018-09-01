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

void readFile();//función que nos permite leer un archivo de texto y tokenizar los datos
void releaseMemory();//función que se utiliza para liberar memoria cuando el hayamos finalizado el programa
void genLinkedList(int, int, int, int);//Genera una lista enlazada
void showLinkedList();// muestra la lista enlazada con datos importantes del planificador
int completionTime(struct PCB *, int);//calcula el tiempo en el que finalizo un proceso después de ejecutarse
void turnAroundTime(struct PCB *);//calcula el tiempo de retorno por cada procese
void waitingTime(struct PCB *);// calcula el tiempo de espera de cada proceso
void sortById();
void showOrderedList(); //Funcion de prueba

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

      archivo = fopen("input2.txt", "r");


      while (fgets(num,20, archivo))
      {

            if(contador == 0)
            {
                printf("quantum: %s\n", num);
                quantum = (int)num - 48;
                contador++;
            }
            else
            {
                printf("original: %s\n", num);

                token = strtok(num," ");
                digit = (int)*token - 48;
                procces_id = digit;

                token = strtok(NULL," ");
                digit = (int) *token - 48;
                arrival_time = digit;

                token = strtok(NULL," ");
                digit = (int) *token - 48;
                cpu_burst = digit;

                token = strtok(NULL," ");
                digit = (int) *token - 48;
                priority = digit;

                printf("contador: %d\n\n", contador++);
                //Creamos una lista ENLAZADA
                genLinkedList(procces_id, arrival_time, cpu_burst, priority);
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

void sortById()//Deberia ser para burstTime y priority
{
  int i, hop=1;
  struct PCB *aux = NULL, *anterior = NULL;


    for(i=0; i<contador-1; i++)
    {
        printf("Entre exterior\n");
        actual = first;
        while (actual->next != NULL)
        {   printf("Entre\n");
            aux = actual->next;
            if(actual->cpu_burst > aux->cpu_burst && hop==1)
            {
                actual->next = aux->next;
                aux->next = actual;
                anterior = aux;
                first = aux;
                hop++;
                printf("Entre if 1\n");
            }
            else if(actual->cpu_burst > aux-> cpu_burst)
            {
                actual->next = aux->next;
                aux->next = actual;
                anterior->next = aux;
                anterior = aux;
                printf("Entre if 2\n");
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
                    printf("Entre if 3\n");
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
