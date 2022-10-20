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

  // Determinar si existe o no una cronología consistente con los datos, 
  // en caso de existir, construirla en cr 

  //   Para cada persona Pi, definimos los nodos bi y di, representando estos con fechas de nacimiento
  // y muerte respectivamente. La aristas corresponderán a un evento que precede a otro.
  // Comencemos entonces, incluimos la arista (bi, di) para cada i. Cuando nos dicen eso:
  // – para cada i y j tal que la persona Pi muere antes que la persona Pj haya nacido,
  // incluimos una arista (di, bj). 
  // Cuando nos dicen eso:
  // – para cada i y j, la esperanza de vida de Pi y Pj se superponen al menos parcialmente,
  // incluimos las aristas (bi, dj ) y (bj , di). 
  //Esto completa la construcción de G.

  Grafo G = crear_grafo(n, true);   //podria generar_grafo
  //preguntar si es orden topologico, si es hacer todo, sino f 
  while ((!es_vacia_lista_datos(tipo1))|| (!es_vacia_lista_datos(tipo2))){
    if (!es_vacia_lista_datos(tipo1)){
      dato actualt = primer_dato(tipo1);
      agregar_vertice(id1(actualt), G);
      agregar_vertice(id2(actualt), G);
      agregar_arista(id1(actualt), id2(actualt), G);  //agrego solo en el sentido del que muere antes
    remover_dato(actualt, tipo1);  
    }
    if (!es_vacia_lista_datos(tipo2)){
      dato recien = primer_dato(tipo2);
      agregar_vertice(id1(recien), G);
      agregar_vertice(id2(recien), G);
      agregar_arista(id1(recien), id2(recien), G);
      agregar_arista(id2(recien), id1(recien), G);
    remover_dato(recien, tipo2);
    }             
  }

  nat cont = 0;
  //recorro los elementos del grafo para saber cuales no tienen incidencia
  Lista sinIncidentes = crear_lista();
  while (cont <= n){
    if (in_grado(cont, G) == 0) insertar_al_final(cont, sinIncidentes);
    cont++;
  }

  //adyacentes lo que hace es dar lista de los elementos que salen del vertice
  //incidentes da la lista de los que entran 
  //para eliminar un elemento del grafo tengo que hacer que si v apunta a u y w a v,
  //w apunta a u (para eliminar el v)

  Lista ordenado = crear_lista();
  nat cont = 0;
  while (!es_vacia_lista(sinIncidentes)){
    comienzo(ordenado);
    comienzo(sinIncidentes);  //??
    nat elem = primero(sinIncidentes);
    insertar_al_final(elem, ordenado);
    cont++;
    remover_al_inicio(sinIncidentes);
    //FALTA eliminar a elem de G
    //los que queden en la lista de incidentes tengo que agregarlos a sinIncidentes

        //elimino a v de G
    Lista eliminarAristas = adyacentes(elem, G);
    comienzo(eliminarAristas);
    while(!es_vacia_lista(eliminarAristas)){
      //como es el unico que apunta, no tengo que verificar para atras
      if (in_grado(actual(eliminarAristas), G) == 1){
        // lo agrego a sinInicidentes
        insertar_al_final(actual(eliminarAristas), sinIncidentes);
      }
      else {
        //borra 1 vertice de la cantidad de entrantes
        Lista incidentesV = incidentes(actual(eliminarAristas), G);
        

      }
      siguiente(eliminarAristas);
      remover_al_inicio(eliminarAristas);
    } 
  }
  if (cont == n)
    imprimir_lista(ordenado);
  else {
    
  }


  if(existe_cr_consistente) { // si existe, retornarla en cr
    return cr;
  } else {// si no existe, liberar la memoria asociada a cr y retornar NULL   
    delete[] cr;
    return NULL;
  }

} 





// -Sea S el conjunto de nodos sin aristas incidentes de G=(v,E)              
// -Sea orden una lista vacia
// -Mientras S <> {vacio} hacer:
// 	-tomo v E S y lo agrego a orden
// 	-elimino a v de G y de S
// 	-Agrego a S los nodos que quedaron sin aristas incidentes -> producto de eliminar a v de G
// Finmientras
// -Si largo de orden == n
// 	-Imprimo orden
// Sino 
// 	-Sea visitado[u] = false     para todo u E G
// 	-Sea iter un vértice en G y camino = iter
// 	 -Mientras visitado[iter] == false hacer
// 		-visitado[iter] = true
// 		-Sea v en G el origen de una arista incidente a iter
// 		-Agregar v al inicio del camino
// 		-asignar iter = v
// 	Finmientras
// 	-Imprimo el ciclo : imprimir el camino hasta encontrar nuevamente el primero
// Finsi