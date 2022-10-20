/*
  Módulo de implementación de `cronologia_consistente'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/

#include <stdio.h>

#include "../include/cronologia_consistente.h"

Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2)
{
    bool existe_cr_consistente = false; 

    Cronologia cr = new evento[2*n]; 

    ListaDatos reco = tipo1;
    nat indegred[n];
    for (int i = 0; i < n; i++)
        indegred[i] = 0;
    //crear grafo -> solo con tipo1
    Grafo G = crear_grafo(n, true); 
    while(!es_vacia_lista_datos(reco)){
        dato actualt1 = primer_dato(reco);
        if (!existe_vertice(id1(actualt1), G)) agregar_vertice(id1(actualt1), G);
        if (!existe_vertice(id2(actualt1), G)) agregar_vertice(id2(actualt1), G);
        agregar_arista(id1(actualt1), id2(actualt1), G);
        indegred[id2(actualt1)] ++;
        reco = resto_datos(reco);
    }
    //grafo sin ser dirigido para hacer los de tipeo2 -> me sirve para poder comparar todo bien 
    Grafo Gnodir = crear_grafo(n, false);
    ListaDatos Tipeo2 = tipo2;
    while(!es_vacia_lista_datos(Tipeo2)){
        dato actualt2 = primer_dato(Tipeo2);
        if (!existe_vertice(id1(actualt2), G)) agregar_vertice(id1(actualt2), G);
        if (!existe_vertice(id2(actualt2), G)) agregar_vertice(id2(actualt2), G);
        agregar_arista(id1(actualt2), id2(actualt2), Gnodir);
        Tipeo2 = resto_datos(Tipeo2);
    }
    //en el caso de tipo2, no tengo aristas incidentes, pero voy a ir verificando q se cumpla siempre

    //aca veo los incidentes
    Lista sinIncidentes = crear_lista();
    for (nat j = 0; j < n; j++){
        if(indegred[j] == 0) insertar_al_final(j, sinIncidentes);
    }

    //ahora voy a crear la lista de ordenado, para ir acercandonos a la solucion final 
    Lista ordenado = crear_lista();
    nat cont = 0;
    comienzo(ordenado);
    comienzo(sinIncidentes);
    siguiente(sinIncidentes);
    while (!es_vacia_lista(sinIncidentes)){
        Lista eliminarAristas = incidentes(actual(sinIncidentes), G);
        comienzo(eliminarAristas);
        siguiente(eliminarAristas);
        Lista aEvaluar = crear_lista();
        while(existe_actual(eliminarAristas)){
            if(indegred[actual(eliminarAristas)] == 1) {
                insertar_al_inicio(actual(eliminarAristas), sinIncidentes);
                insertar_al_inicio(actual(eliminarAristas), aEvaluar);
            }

            else 
                indegred[actual(eliminarAristas)] --;
            siguiente(eliminarAristas);   //esta bien asi??????????
        } 

        //ahora hay q meterlo en la lista llamada ordenado para meterlos en orden
        Lista tieneAdyacente = adyacentes(actual(sinIncidentes), Gnodir);
        if ( es_vacia_lista(tieneAdyacente))
            insertar_al_inicio(actual(sinIncidentes), ordenado);  //mete el nacimiento !!
        else {
            //supongamos que el vertice si tiene adyacentes entonces en este caso lo que tengo q hacer es poner que tengo que ir poniendo a quienes esta vinculado, y si ese vertice esta vinculado a alguien mas tambien tengo que poner el vertice ese (ejemplo en tipo 2, 1 vunculado con 2 y dos con 3, despues en tipo 1 esta 1 y 4 => el orden seria 1 nace. 2 nace. 3 nace. 1 muere. 4 nace. 4 muere). creo que eso es todo ejej hasta la proximaa
            

            //no es vacia tieneadyacentes entonces
            while  (!es_vacia_lista(tieneAdyacente)){
                if (existe_vertice(actual(tieneAdyacente), G)){
                    //si existe es pq apunta a alguien o es apuntado,, tengo q buscarla
                    if ((out_grado(actual(tieneAdyacente), G) == 0) && (in_grado(actual(tieneAdyacente), G) == 0) || ((out_grado(actual(tieneAdyacente), G) == 0))) {
                        insertar_al_final(actual(tieneAdyacente), ordenado);
                        //muerto[(actual(tieneAdyacente)]  = false;
                        //cada vez q meto a uno lo pongo como vivo asi despues lo mat0
                    }
                    else {
                        //tiene aristas incidentes
                        //verifico si ese es apuntado por alguien 
                        Lista unosTrolos = incidentes(actual(tieneAdyacente), G);
                        while (!es_vacia_lista(unosTrolos)){
                            //si es igual a cero sigo, sino comparo con aEvaluar
                            if (in_grado(actual(unosTrolos)) > 0)
                                if pertenece_a_lista()
                        }
                        
                    }
                }

            }

            }
            destruir_lista(aEvaluar);
        }
        //tengo que cambiar al siguiente elemento de sinIncidentes

    }



    // Estructura de datos para almacenar un borde de graph
struct Edge {
    int src, dest;
};
 
// Una clase para representar un objeto graph
class Graph
{
public:
 
    // un vector de vectores para representar una lista de adyacencia
    vector<vector<int>> adjList;
 
    // construye otro vector para almacenar el grado de entrada de los vértices
    vector<int> indegree;
 
    // Constructor de graph
    Graph(vector<Edge> const &edges, int n)
    {
        // resize the adjacency list to `n` elements of type `vector<int>`
        adjList.resize(n);
 
        // cambiar el tamaño del vector de grado para `n` vértices
        indegree.resize(n);
 
        // agrega bordes al grafo dirigido
        for (auto &edge: edges)
        {
            adjList[edge.src].push_back(edge.dest);
 
            // incrementa el grado del vértice de destino en 1
            indegree[edge.dest]++;
        }
    }
};
 
// Función de utilidad para imprimir el contenido de una lista dada
void printPath(list<int> list)        // sin referencia, sin constante
{
    while (!list.empty())
    {
        cout << list.front() << ' ';
        list.pop_front();
    }
    cout << endl;
}
 
// Función recursivo para encontrar todos los ordenamientos topológicos de un DAG dado
void findAllTopologicalOrderings(Graph &graph, auto &path, auto &discovered, int n)
{
    // hacer para cada vértice
    for (int v = 0; v < n; v++)
    {
        // proceder solo si el grado de entrada del nodo actual es 0 y
        // el nodo actual aún no se procesa
        if (graph.indegree[v] == 0 && !discovered[v])
        (in_grado(v, graph))
        {
            // para cada vértice adyacente `u` de `v`, reduce el grado de entrada de `u` en 1
            for (int u: graph.adjList[v]) {
                graph.indegree[u]--;
            }
 
            // incluir el nodo actual en la ruta y marcarlo como descubierto
            path.push_back(v);
            discovered[v] = true;
 
            // recurre
            findAllTopologicalOrderings(graph, path, discovered, n);
 
            // retroceder: restablecer la información de grado para el nodo actual
            for (int u: graph.adjList[v]) {
                graph.indegree[u]++;
            }
 
            // retroceder: eliminar el nodo actual de la ruta y
            // marcarlo como no descubierto
            path.pop_back();
            discovered[v] = false;
        }
    }
 
    // imprime el orden topológico si todos los vértices están incluidos en la ruta
    if (path.size() == n) {
        printPath(path);
    }
}
 
// Imprime todos los ordenamientos topológicos de un DAG dado
void printAllTopologicalOrders(Graph &graph)
{
    // obtener el número total de nodos en el graph
    int n = graph.adjList.size();
 
    // crea una array auxiliar para realizar un seguimiento de si se descubre un vértice
    vector<bool> discovered(n);
 
    // lista para almacenar el orden topológico
    list<int> path;
 
    // encontrar todos los ordenamientos topológicos e imprimirlos
    findAllTopologicalOrderings(graph, path, discovered, n);
}
    

    
    
    // nat cont = 0;
    // // Lista sinIncidentes = crear_lista();
    // while (cont <= n){
    //     if(in_grado(cont, G) == 0) insertar_al_final(cont, sinIncidentes);
    //     cont++;
    // }
    // //viene el mientras
    // Lista ordenado = crear_lista();
    // nat aux = 0;
    // while(!es_vacia_lista(sinIncidentes)){
    //     comienzo(ordenado);
    //     nat elem = primero(sinIncidentes);
    //     insertar_al_final(elem, ordenado);
    //     aux++;
    //     remover_al_inicio(sinIncidentes);
    // }


    if(existe_cr_consistente) { // si existe, retornarla en cr
        return cr;
    } else {// si no existe, liberar la memoria asociada a cr y retornar NULL   
        delete[] cr;
        return NULL;
    }
}