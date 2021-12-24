/** @file Cjt_Clusters.hh
    @brief Especificación de la clase Cjt_Clusters
*/
#ifndef CJT_CLUSTERS_HH
#define CJT_CLUSTERS_HH

#include "Cjt_Especies.hh"
#ifndef NO_DIAGRAM
#include "BinTree.hh"
#endif

/** @class Cjt_Clusters
    @brief Representa la información y las operaciones de un conjunto de clústers

    Sus operaciones son la modificadora de ejecución de un paso del algoritmo WPGMA,
    y las de escritura de un clúster dado un identificador, del árbol filogenético
    del conjunto de clústers y de la tabla de distancias entre los clústers del conjunto

    Hay declaradas varias operaciones auxiliares como \em private
*/
class Cjt_Clusters {

private:

  /** @brief Mapa de submapas donde se guardan las distancias entre dos especies,
      cuyos identificadores son las keys

      Ordenado crecientemente por los identificadores de las especies, sin repetición
      de distancias entre dos mismas especies
  */
  map<string, map<string, double> > distancias_c;
  /** @brief Mapa de árboles binarios donde se guardan los clústers, donde la key de cada
      árbol es el identificador de su nodo.

      Ordenado crecientemente por dichos identificadores
  */
  map<string, BinTree<pair<string,double> > > clusters;
  /** @brief Parámetro auxiliar que indica el identificador de uno de los dos clústers de distancia mínima,
      dicho identificador es el menor
  */
  string save_c1;
  /** @brief Parámetro auxiliar que indica el identificador de uno de los dos clústers de distancia mínima,
      dicho identificador es el mayor
  */
  string save_c2;
  /** @brief Parámetro auxiliar que indica la distancia mínima entre el clúster save_c1 y save_c2 */
  double d_min;

public:

  //Constructoras

  /** @brief Constructora por defecto
      \pre Cierto
      \post Se ha creado un conjunto de clusters vacío
  */
  Cjt_Clusters();

  /** @brief Constructora a partir de un conjunto de especies
      \pre Cierto
      \post Se ha creado un conjunto de clusters a partir de un conjunto de especies e.
      Se le asigna al parámetro implícito los clústers y sus distancias obtenidas a partir
      de e.
  */
  Cjt_Clusters(const Cjt_Especies& e);

  //Modificadoras

  /** @brief Ejecuta un paso del algoritmo WPGMA
      \pre Cierto
      \post b indica si el número de clústers del parámetro implícito es mayor que 1;
      si b = true, se ha ejecutado un paso del algoritmo WPGMA; b = false contrariamente
  */
  void ejecutar_paso_wpgma(bool& b);

  //Escritura

  /** @brief Escritura de un clúster del conjunto, dado un identificador
      \pre El parámetro implícito está inicializado
      \post b indica si el parámetro implícito contiene un clúster con el identificador id dado;
      si b = true, se escribe dicho clúster por el canal estándar de salida;
      b = false contrariamente
  */
  void imprimir_cluster(string id, bool& b) const;

  /**  @brief Escritura del árbol filogenético del conjunto de especies con el que se ha
      inicializado el conjunto de clústers
      \pre Cierto
      \post b indica si el conjunto de clústers está vacío. Si b = false, se escribe
      el árbol filogenético (en preorden) del conjunto actual de clusters. El parámetro implícito
      pasa a tener el conjunto final de clústers, resultado de aplicar el algoritmo
      WPGMA de manera completa
  */
  void imprimir_arbol_filogenetico(bool& b);

  /** @brief Escritura de la tabla de distancias entre clústers
      \pre Cierto
      \post Se ha escrito en el canal estándar de salida la tabla de distancias del
      parámetro implícito
  */
  void imprimir_distancias_c() const;

private:

  /** @brief Calcula la distancia mínima entre los clústers del conjunto
      \pre Cierto
      \post Se atribuyen a 'save_c1' y 'save_c2' (tal que save_c1 < save_c2)
      los identificadores de los clusters cuya distancia es la mínima.
      'd_min' es dicha distancia.
  */
  void distancia_minima();

  /** @brief Ejecuta un paso del algoritmo WPGMA
      \pre Cierto
      \post Los clústers con identificador 'save_c1' y 'save_c2' se combinan y
      como consecuencia se actualiza toda la tabla de distancias 'distancias_c',
      recalculando nuevas distancias entre el nuevo clúster y los demás.
      También se actualiza el mapa de árboles binarios 'clusters', donde los árboles
      binarios con nodos 'save_c1' y 'save_c2' pasan a formar parte del subárbol
      izquierdo y derecho, respectivamente. Se recalculan también 'save_c1', 'save_c2'
      y 'd_min', con tal de poder volver a ejecutar el algoritmo sin problemas.
  */
  void algoritmo_wpgma();

};
#endif
