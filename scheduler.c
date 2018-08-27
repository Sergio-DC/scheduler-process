#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct PCB
{
    int procces_id;
    int arrival_time;
    int cpu_burst;
    int priority;

    int completionTime;//tiempo de finalización
    int turnAroundTime;//tiempo de retorno

    struct PCB * next;
};

struct PCB *first = NULL, *last = NULL, *actual = NULL, *new = NULL;
int quantum;

void readFile();
void releaseMemory();
void genLinkedList(int, int, int, int);
void showLinkedList();

int main()
{
    readFile();
    showLinkedList();
    releaseMemory();
    showLinkedList();
    return 0;
}

void readFile()
{
      FILE * archivo;
      int procces_id, arrival_time, cpu_burst, priority;
      char num[20];
      int quantum_flag = 0;
      char * token;
      int digit;
      int contador = 0;

      archivo = fopen("input.txt", "r");


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
  int n = 0;
    actual = first;
    if(actual == NULL)
        printf("Lista Vacia\n");
    else
    {
        while (actual != NULL)
        {
            printf("procces_id: %d\n", actual->procces_id);
            printf("arrival_time: %d\n", actual->arrival_time);
            printf("cpu_burst: %d\n", actual->cpu_burst);
            printf("priority: %d\n", actual->priority);
            n = completionTime(actual, n);
            printf("completionTime: %d\n", actual->completionTime);
            turnAroundTime(actual);
            printf("turnAroundTime: %d\n\n", actual->turnAroundTime);
            actual = actual->next;
        }
    }
}

//Tiempo de finalización =
int completionTime(struct PCB *process, int n)//n es el tiempo de finalización del proceso anterior
{
    process->completionTime = n + process->cpu_burst;

    return  process->completionTime;
}

void turnAroundTime(struct PCB *process)
{
    process->turnAroundTime = process->completionTime - process->arrival_time;
}
