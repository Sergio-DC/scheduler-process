
/*Calcula el tiempo en que finalizo un proceso*/
int completionTime(struct PCB *process, int n)//n es el tiempo de finalización del proceso anterior, n=0 en la primera llamada
{
    process->completionTime = n + process->cpu_burst;

    return  process->completionTime;
}
/*Calcula el tiempo de retorno*/
void turnAroundTime(struct PCB *process)
{
    process->turnAroundTime = process->completionTime - process->arrival_time;
}
/*Calcula el tiempo de espera promedio por proceso*/
void waitingTime(struct PCB *process)
{
    process->waitingTime = process->turnAroundTime - process->cpu_burst;
}

/*Muestra el tiempo promedio de los planificadores no apropiativos*/
void showNonPreemptiveAWT(struct PCB *first, int noOfProcesses, char * schedulerName)
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
            acumulador = acumulador + (float)actual->waitingTime;//Calcula la suma de de las ráfagas de CPU de todos los procesos
            actual = actual->next;
        }
          //Mensaje de salida
          printf("%s: for %d processes\n",schedulerName, noOfProcesses - 1);
          printf("Average Wait Time: %.4f\n\n", acumulador/(noOfProcesses-1));
    }
}

/*
Pasos para realizar el calculo de FCFS:
    1. Calcular completionTime de cada proceso
    2. Calculamos turnAroundTime de cada proceso "tat = completionTime - arrival_time"
    3. Calculamos waitingTime de cada proceso "waitingTime = tat - cpu_burst"
    4. Calculamos el averageWaitingTime
*/
