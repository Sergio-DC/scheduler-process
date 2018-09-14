#include <stdio.h>
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