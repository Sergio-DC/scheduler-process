#include "pcb.h"
#include <stdlib.h>

void hola()
{

}

struct PCB* sort(struct PCB * first)
{
    struct PCB * actual = NULL, *aux = NULL , *aux2 = NULL, *anterior = NULL;
    int tiempo = 0;

    actual = first;

    while (actual->next!=NULL)
    {
        aux = actual->next;
        printf("aux: %d\n",aux->cpu_burst);
        printf("actual: %d\n", actual->cpu_burst);
        system("pause");
        if(tiempo == 0)
        {
            tiempo = tiempo + actual->cpu_burst;
            first = actual;
            anterior = actual;
            actual = actual->next;
        }
        else
        {
            if(actual->cpu_burst > aux->cpu_burst && tiempo >= aux->arrival_time)
            {
                actual->next = aux->next;
                aux->next = actual;
                anterior->next = aux;

                actual = aux;//swap


                tiempo = tiempo + actual->cpu_burst;

                anterior = actual;
                actual = actual->next;


            }
            else if(tiempo >= aux->arrival_time)
            {
                aux2 = aux;
                aux2 = aux2->next;

                while (aux2 != NULL)
                {
                    printf("aux2: %d\n", aux2->cpu_burst);
                    system("pause");
                    if(aux2->arrival_time == tiempo)
                    {
                        anterior->next = aux2;
                        aux->next = aux2->next;
                        aux2->next = actual;
                        printf("Entre al if\n");
                        system("pause");
                        break;
                    }
                    aux2 = aux2->next;
                }//POR AQUI ESTA EL PROBLEMA

                    anterior = actual;
                    actual = actual->next;
                    printf("sali\n");
                    system("pause");
            }
            else
            {
                tiempo = tiempo + actual->cpu_burst;
                anterior = actual;
                actual = actual->next;
            }
        }
    }

    return first;
}
