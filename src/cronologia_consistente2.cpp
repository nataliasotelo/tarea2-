#include <stdio.h>

#include "../include/cronologia_consistente.h"

Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2)
{
    bool existe_cr_consistente = false; 

    Cronologia cr = new evento[2*n]; 

    ListaDatos reco = tipo1;
    nat indegred[n];
    for (int i = 0; i <= n; i++)
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
    //en el caso de tipo2, no tengo aristas incidentes, pero voy a ir verificando q se cumpla siempre
    //para saber los incidentes   paso en O(m+n)
    nat cont = 0;
    Lista sinIncidentes = crear_lista();
    while (cont <= n){
        if(in_grado(cont, G) == 0) insertar_al_final(cont, sinIncidentes);
        cont++;
    }
    //viene el mientras
    Lista ordenado = crear_lista();
    nat aux = 0;
    while(!es_vacia_lista(sinIncidentes)){
        comienzo(ordenado);
        nat elem = primero(sinIncidentes);
        insertar_al_final(elem, ordenado);
        cont++;
        remover_al_inicio(sinIncidentes);
    }


    if(existe_cr_consistente) { // si existe, retornarla en cr
        return cr;
    } else {// si no existe, liberar la memoria asociada a cr y retornar NULL   
        delete[] cr;
        return NULL;
    }
}