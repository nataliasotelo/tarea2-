/*
  Módulo de implementación de `cronologia_consistente'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/

#include <stdio.h>

#include "../include/cronologia_consistente.h"

// Función recursivo para encontrar todos los ordenamientos topológicos de un DAG dado
static void findAllTopologicalOrderings(Grafo &G, Lista &orden, bool *discovered, nat n, nat *indegred);

Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2) {
  // bool existe_cr_consistente = false;

  Cronologia cr = new evento[2 * n];

  // Crear estructuras
  nat cant1 = cantidad(tipo1);
  nat cant2 = cantidad(tipo2);
  Grafo G = crear_grafo(n, true);
  for (nat i = 0; i < cant1; i++) agregar_vertice(i, G);
  for (nat i = 0; i < cant2; i++) agregar_vertice(i, G);
  nat indegred[n];
  for (nat i = 0; i < n; i++) indegred[i] = 0;
  ListaDatos rect1 = tipo1;
  while (!es_vacia_lista_datos(rect1)) {
    agregar_arista(id1(primer_dato(rect1)), id2(primer_dato(rect1)), G);
    indegred[id2(primer_dato(rect1))]++;
    rect1 = resto_datos(rect1);
  }

  ListaDatos rect2 = tipo2;
  while (!es_vacia_lista_datos(rect2)){
    agregar_arista(id1(primer_dato(rect2)), id2(primer_dato(rect2)), G);
    agregar_arista(id2(primer_dato(rect2)), id1(primer_dato(rect2)), G);
    rect2 = resto_datos(rect2);
  }

  // suppongamos finalizadas estructuras

  Lista ordenado = crear_lista();
  // bool discovered = bool[n];
  bool discovered[n];
  for (int i = 0; i < (int)n; i++) discovered[i] = false;
  // inicializo discovered
  findAllTopologicalOrderings(G, ordenado, discovered, n, indegred);

  while (!es_vacia_lista(ordenado))


  if (cantidad_elementos(ordenado) == n) { // si existe, retornarla en cr
    // existe_cr_consistente = true;
    imprimir_lista(ordenado);
    return cr;
  }
  else { // si no existe, liberar la memoria asociada a cr y retornar NULL
    delete[] cr;
    return NULL;
  }
}

void findAllTopologicalOrderings(Grafo &G, Lista &orden, bool *discovered, nat n, nat *indegred) {
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

      // recurre
      findAllTopologicalOrderings(G, orden, discovered, n, indegred);
    }
  }
}