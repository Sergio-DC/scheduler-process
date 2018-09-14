/*Ordena la lista en función de la ráfaga de CPU y tomando en cuenta los tiempos de llegada*/
struct PCB* sort(struct PCB * first)
{
    struct PCB * actual = NULL, *aux = NULL , *aux2 = NULL, *anterior = NULL;
    int tiempo = 0, i;

          actual = first;

          while (actual->next!=NULL)
          {
              aux = actual->next;
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
                          if(aux2->arrival_time == tiempo)
                          {
                              anterior->next = aux2;
                              aux->next = aux2->next;
                              aux2->next = actual;
                              break;
                          }
                          aux2 = aux2->next;
                      }

                          anterior = actual;
                          actual = actual->next;
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

/*Función que complementa el ordenamiento por rafagá de CPU*/
struct PCB * sortByCpuBurst(struct PCB * first, int contador)
{
      int i;
      for (i = 0; i < contador-1; i++)
      {
          first = sort(first);
      }
    return first;
}
