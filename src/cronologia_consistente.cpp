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

    //Crear estructuras
    Grafo G = crear_grafo(n, true);
    for (nat i = 0; i<= n; i++){
        agregar_vertice(i, G);
        agregar_vertice(i, G);
    }
    ListaDatos rect1 = tipo1;
    while (!es_vacia_lista_datos(rect1)){
        agregar_vertice(i, G);
        agregar_vertice(i, G);
        agregar_arista(id1(primer_dato(rect1)), id2(primer_dato(rect1)), G);
        rect1 = resto_datos(rect1);
    }

    ListaDatos rect2 = tipo2;
    while (!es_vacia_lista_datos(rect2)){
        agregar_arista(id1(primer_dato(rect2)), id2(primer_dato(rect2)), G);
        agregar_arista(id2(primer_dato(rect2)), id1(primer_dato(rect2)), G);
        rect2 = resto_datos(rect2);
    }



    ListaDatos rect1 = tipo1;
    nat indegred[n];
    for (int i = 0; i < n; i++)
        indegred[i] = 0;
    //crear grafo -> solo con tipo1
    Grafo G = crear_grafo(n, true); 
    while(!es_vacia_lista_datos(rect1)){
        dato actualt1 = primer_dato(rect1);
        if (!existe_vertice(id1(actualt1), G)) agregar_vertice(id1(actualt1), G);
        if (!existe_vertice(id2(actualt1), G)) agregar_vertice(id2(actualt1), G);
        agregar_arista(id1(actualt1), id2(actualt1), G);
        indegred[id2(actualt1)] ++;
        rect1 = resto_datos(rect1);
    }
    //grafo sin ser dirigido para hacer los de tipeo2 -> me sirve para poder comparar todo bien 
    Grafo Gnodir = crear_grafo(n, false);
    ListaDatos rect2 = tipo2;
    while(!es_vacia_lista_datos(rect2)){
        dato actualt2 = primer_dato(rect2);
        if (!existe_vertice(id1(actualt2), Gnodir)) agregar_vertice(id1(actualt2), Gnodir);
        if (!existe_vertice(id2(actualt2), Gnodir)) agregar_vertice(id2(actualt2), Gnodir);
        agregar_arista(id1(actualt2), id2(actualt2), Gnodir);
        rect2 = resto_datos(rect2);
    }
    //Fin estructuras
    
    


    if(existe_cr_consistente) { // si existe, retornarla en cr
        return cr;
    } else {// si no existe, liberar la memoria asociada a cr y retornar NULL   
        delete[] cr;
        return NULL;
    }
}


// Función recursivo para encontrar todos los ordenamientos topológicos de un DAG dado
void findAllTopologicalOrderings(Grafo &G, Lista &orden, bool* &discovered, int n, nat* indegred)
{
    // hacer para cada vértice
    for (int v = 0; v < n; v++) {
        // proceder solo si el grado de entrada del nodo actual es 0 y
        // el nodo actual aún no se procesa
        if (in_grado(v,G) == 0 && !discovered[v]){
            // para cada vértice adyacente `u` de `v`, reduce el grado de entrada de `u` en 1
            while (!es_vacia_lista(adyacentes(v, G))){
                indegred[v]--;
            }

            

            // incluir el nodo actual en la ruta y marcarlo como descubierto

            insertar_al_final(v, orden);
            discovered[v] = true;

            // recurre
            findAllTopologicalOrderings(G, orden, discovered, n, indegred);
        }
    }
}