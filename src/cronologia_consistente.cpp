/*
  Módulo de implementación de `cronologia_consistente'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/

#include <stdio.h>

#include "../include/cronologia_consistente.h"

// Función recursivo para encontrar todos los ordenamientos topológicos de un DAG dado
static void findAllTopologicalOrderings(Grafo &G, Lista &orden, bool *discovered, nat n, nat *indegred, bool existe_cr_consistente);

Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2) {


ListaDatos lst1 = crear_lista_datos();
ListaDatos lst2 = crear_lista_datos();

while (!es_vacia_lista_datos(tipo1)) {
    insertar_dato({id1(primer_dato(tipo1)), id2(primer_dato(tipo1))}, lst1);
    tipo1 = resto_datos(tipo1);
}

while (!es_vacia_lista_datos(tipo2)) {
    insertar_dato({id1(primer_dato(tipo2)), id2(primer_dato(tipo2))}, lst2);
    tipo2 = resto_datos(tipo2);
}

Grafo G = crear_grafo(n, true);

nat indegred[n];
 for (nat i = 0; i < n; i++) indegred[i] = 0;

while (!es_vacia_lista_datos(lst1)) {
    
    agregar_vertice(id1(primer_dato(lst1)), G);
    agregar_vertice(id2(primer_dato(lst1)), G);
    agregar_arista(id1(primer_dato(lst1)), id2(primer_dato(lst1)), G);
    indegred[id2(primer_dato(lst1))]++;
    
    lst1 = resto_datos(lst1);
}

while (!es_vacia_lista_datos(lst2)) {
    agregar_vertice(id1(primer_dato(lst2)), G);
    agregar_vertice(id2(primer_dato(lst2)), G);
    agregar_arista(id1(primer_dato(lst2)), id2(primer_dato(lst2)), G);
    agregar_arista(id2(primer_dato(lst2)), id1(primer_dato(lst2)), G);
    lst2 = resto_datos(lst2);
}



imprimir_grafo(G);
return NULL;


  //  bool existe_cr_consistente = false;

  // Cronologia cr = new evento[2 * n];

  // // Crear estructuras
  // nat cant1 = cantidad(tipo1);
  // nat cant2 = cantidad(tipo2);
  // Grafo G = crear_grafo(n, true);
  // for (nat i = 0; i < cant1; i++) agregar_vertice(primer_dato(id1), G);
  // for (nat i = 0; i < cant2; i++) agregar_vertice(i, G);
  // nat indegred[n];
  // for (nat i = 0; i < n; i++) indegred[i] = 0;
  // ListaDatos rect1 = tipo1;
  // while (!es_vacia_lista_datos(rect1)) {
  //   agregar_arista(id1(primer_dato(rect1)), id2(primer_dato(rect1)), G);
  //   indegred[id2(primer_dato(rect1))]++;
  //   rect1 = resto_datos(rect1);
  // }
      
  // ListaDatos rect2 = tipo2;
  // while (!es_vacia_lista_datos(rect2)){
  //   agregar_arista(id1(primer_dato(rect2)), id2(primer_dato(rect2)), G);
  //   agregar_arista(id2(primer_dato(rect2)), id1(primer_dato(rect2)), G);
  //   rect2 = resto_datos(rect2);
  // }

  // // suppongamos finalizadas estructuras

  // Lista ordenado = crear_lista();
  // // bool discovered = bool[n];
  // bool discovered[n];
  // for (int i = 0; i < (int)n; i++) discovered[i] = false;
  // // inicializo discovered
  // findAllTopologicalOrderings(G, ordenado, discovered, n, indegred, existe_cr_consistente);

  // comienzo(ordenado);
  // nat k = 0;
  // int matado[n];
  // for (int i = 0; i < (int)n; i++) matado[i] = 0;
  // while (!es_vacia_lista(ordenado)){
  //   cr[k].id = actual(ordenado);
  //   if (matado[actual(ordenado)] == 0) {
  //   cr[k].tipo = nace;
  //   matado[actual(ordenado)]++;
  //   }
  //   else cr[k].tipo = muere;
  //   k++;
  //   siguiente(ordenado);
  // }

  // destruir_lista_datos(rect1);
  // destruir_lista_datos(rect2);
  // destruir_lista(ordenado);
  // destruir_grafo(G);
  // if (existe_cr_consistente) { // si existe, retornarla en cr
  //   return cr;
  // }
  // else { // si no existe, liberar la memoria asociada a cr y retornar NULL
  //   delete[] cr;
  //   return NULL;
  // }
}

void findAllTopologicalOrderings(Grafo &G, Lista &orden, bool *discovered, nat n, nat *indegred, bool existe_cr_consistente) {
  // hacer para cada vértice
  for (int v = 0; v < (int)n; v++) {
    // proceder solo si el grado de entrada del nodo actual es 0 y
    // el nodo actual aún no se procesa
    if ((in_grado(v, G) == 0) && (discovered[v] == false)) {
      // para cada vértice adyacente `u` de `v`, reduce el grado de entrada de `u` en 1
      while (!es_vacia_lista(adyacentes(v, G))) indegred[v]--;

      // incluir el nodo actual en la ruta y marcarlo como descubierto

      insertar_al_final(v, orden);
      discovered[v] = true;
      existe_cr_consistente = true;

      // recurre
      findAllTopologicalOrderings(G, orden, discovered, n, indegred, existe_cr_consistente);
    }
    else existe_cr_consistente = false;
  }
}