/*Ordena la lista en función de la prioridad y tomando en cuenta los tiempos de llegada*/
/*El algoritmo esta basado en el algoritmo "bubble sort"*/
struct PCB* subSortPriority(struct PCB * first)
{
    struct PCB * actual = NULL, *aux = NULL , *aux2 = NULL, *anterior = NULL;
    int tiempo = 0;//se encarga de acumular el tiempo que tardan en ejecutarde las ráfagas de CPU

          actual = first;

          while (actual->next!=NULL)
          {
              aux = actual->next;
              if(tiempo == 0)//En el tiempo 0 ,el tiempo=0 es sumado con la ráfaga de cpu del primer proceso
              {
                  tiempo = tiempo + actual->cpu_burst;
                  first = actual;
                  anterior = actual;
                  actual = actual->next;
              }
              else
              {
                  /*Está condición se asegura de ordenar procesos por prioridad alta
                  (prioridad alta: números menores, prioridad baja=números altos) y que su tiempo de llegada
                  esté dentro del tiempo, ya que si se ejecuta uno que este fuera de tiempo, el cálculo sera incorrecto*/
                  /*Compara 2 procesos adyacentes p1,p2, en caso de cumplirse la condición intercambian lugares quedando p2,p1*/
                  if(actual->priority > aux->priority && tiempo >= aux->arrival_time)
                  {
                      actual->next = aux->next;
                      aux->next = actual;
                      anterior->next = aux;

                      actual = aux;//swap


                      tiempo = tiempo + actual->cpu_burst;

                      anterior = actual;
                      actual = actual->next;


                  }
                  /*En caso de que los procesos adyacentes no cumplan la condición anterior, se busca delante de estos procesos C Y D, en caso
                  de encontrar un proceso con una prioridad alta F y que este dentro del tiempo se mueve a una posición antes del proceso C*/
                  /*Representación Gráfica, antes: A-B-C-D-E-'F', después: A-B-'F'-C-D-E
                    Se requieren varias iteraciones para que el algoritmo los ordene correctamente, el algoritmo tiene un orden de O(n^2)
                    */
                  else if(tiempo >= aux->arrival_time)
                  {
                      aux2 = aux;
                      aux2 = aux2->next;

                      while (aux2 != NULL)
                      {
                          if(aux2->arrival_time == tiempo && (aux2->priority <= actual->priority))
                          {
                              anterior->next = aux2;
                              aux->next = aux2->next;

                              aux2->next = actual;
                              break;
                          }
                          aux = aux2;
                          aux2 = aux2->next;
                      }
                          tiempo = tiempo + actual->cpu_burst;

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

/*Función que complementa el ordenamiento por prioridad*/
struct PCB * sortByPriority(struct PCB * first, int contador)
{
      int i;
      for (i = 0; i < contador-1; i++)
      {
          first = subSortPriority(first);
      }
    return first;
}
