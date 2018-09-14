

int completionTime(struct PCB *process, int n)//n es el tiempo de finalización del proceso anterior, n=0 en la primera llamada
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

/*Muestra el tiempo promedio de los planificadores no apropiativos*/
void showNonPreemptiveAWT(struct PCB *first, int contador)
{
    int priorCompletionTime = 0;//Esta variable guarda el tiempo de finalización de un proceso anterior
    float acumulador = 0;//acumula la suma del tiempo promedio
    struct PCB * actual = NULL;

    actual = first;
    if(actual == NULL)
        printf("Lista Vacia\n");
    else
    {
        while (actual != NULL)
        {
            priorCompletionTime = completionTime(actual, priorCompletionTime);//calculamos el tiempo en que finalizo un proceso
            turnAroundTime(actual);
            waitingTime(actual);
            acumulador = acumulador + (float)actual->waitingTime;
            actual = actual->next;
        }
          printf("\naverageWaitingTime: %.2f\n\n", acumulador/(contador-1));
    }
}

/*
Pasos para realizar el calculo de FCFS:
    1. Calcular completionTime de cada proceso
    2. Calculamos turnAroundTime de cada proceso "tat = completionTime - arrival_time"
    3. Calculamos waitingTime de cada proceso "waitingTime = tat - cpu_burst"
    4. Calculamos el averageWaitingTime
*/
