/** @file Cjt_Especies.hh
    @brief Especificación de la clase Cjt_Especies
*/
#ifndef CJT_ESPECIES_HH
#define CJT_ESPECIES_HH
#include "Especie.hh"

/** @class Cjt_Especies
    @brief Representa la información y las operaciones asociadas a un conjunto
    de especies

    Sus operaciones son las consultoras de gen de una especie del conjunto,
    distancia entre dos especies, existencia de una especie, identificador de una
    especie, las modificadores de crear y eliminar una especie, la de lectura
    de un conjunto de especies y las de escritura del conjunto entero de especies
    y de su tabla de distancias

    Además, hay declaradas operaciones auxiliares como \em private
*/
class Cjt_Especies {

private:

  /** @brief Longitud de una subsecuencia del gen de una especie */
  int k;
  /** @brief Mapa de especies con el identificador de cada especie como key

      Ordenado crecientemente por los identificadores de las especies
  */
  map<string, Especie> especies;
  /** @brief Mapa de submapas donde se guardan las distancias entre dos especies,
      cuyos identificadores son las keys

      Ordenado crecientemente por los identificadores de las especies, sin repetición
      de distancias entre dos mismas especies
  */
  map<string, map<string, double> > distancias_e;

public:

  //Constructoras

  /** @brief Constructora con un atributo 'k'
      \pre k > 0
      \post El resultado es un conjunto de especies con un valor 'k' = k
  */
  Cjt_Especies(int k);

  //Consultoras

  /** @brief Consulta el tamaño del conjunto de especies en el estado en el que se encuentra
      \pre Cierto
      \post El resultado es el número de especies que hay guardadas en el parámetro
      implícito
  */
  int size() const;

  /**  @brief Obtiene el gen de una especie, si dicha especie existe
      \pre Cierto
      \post El resultado es el gen de la especie del parámetro implícito
      cuyo identificador es id; es "-1" si no se ha encontrado dicha especie
  */
  string obtener_gen(const string& id) const;

  /**  @brief El resultado es la distancia entre dos especies, si ambas existen en el conjunto
      \pre Cierto
      \post  Si el parámetro implícito contiene dos especies con los identificadores
      id1 y id2 dados, el resultado es la distancia entre dichas especies.
      Si no se han encontrado alguna de las dos especies: el resultado es -1 si no se
      ha encontrado la especie con id1, -2 si no se ha encontrado la especie con id2,
      -3 si no se ha encontrado ninguna de las dos.
  */
  double consultar_distancia(string& id1, string& id2) const;

  /**  @brief Consulta si una especie existe dentro del conjunto, dado un identificador
      \pre Cierto
      \post El resultado es true si el parámetro implícito contiene una especie con el
      identificador id dado; false contrariamente
  */
  bool existe_especie(const string& id) const;

  /** @brief Consulta el identificador de la iésima especie del conjunto
      \pre 0 < i < número de especies del parámetro implícito
      \post El resultado es el identificador de la iésima especie del parámetro implícito
  */
  string consultar_id_iesimo(int i) const;

  //Modificadoras

  /** @brief Crea una especie con identificador id y gen g y se añade al conjunto
      si no estaba previamente
      \pre Cierto
      \post b indica si se ha encontrado la especie con el identificador id;
      si b = false, se ha añadido la especie al parámetro implícito, b = true contrariamente
  */
  void crear_especie(const string& id, const string& g, bool& b);

  /**  @brief Elimina una especie del conjunto
      \pre Cierto
      \post b indica si el parámetro implícito contiene una especie con el identificador id;
      si b = true, se ha eliminado dicha especie del p.i., b = false contrariamente
  */
  void eliminar_especie(const string& id, bool& b);

  //Lectura

  /**  @brief Lectura de un conjunto de especies
      \pre Hay preparado en el canal estándar de entrada un entero que indicará
      el número de especies inicial del parámetro implícito, y los datos de tal
      número de especies distintas
      \post El parámetro implícito contiene el conjunto de especies leídos del
      canal estándar de entrada
  */
  void leer_cjt_especies();

  //Escritura

  /** @brief Escritura de un conjunto de especies
      \pre Cierto
      \post Se ha imprimido en el canal estándar de salida el conjunto de especies
  */
  void imprimir_cjt_especies() const;

  /** @brief Escritura de la tabla de distancias del conjunto de especies
      \pre Cierto
      \post Se ha escrito en el canal estándar de salida la tabla de distancias del
      parámetro implícito
  */
  void imprimir_distancias_e() const;

private:

  /** @brief Inicializa la tabla de distancias del conjunto de especies en el estado
      en el que se encuentra
      \pre Cierto
      \post Se han calculado las distancias entre todas las combinaciones de dos
      especies del parámetro implícito (sin repetición), y se guardan en el mapa
      de submapas 'distancias_e', ordenado lexicográficamente por los identificadores
  */
  void inicializar_distancias();

  /** @brief Actualiza la tabla de distancias del conjunto de especies cuando se
      añade una nueva especie
      \pre Cierto
      \post Se han calculado las distancias entre la nueva especie e y cada una
      de las especies guardadas en el parámetro implícito. Las distancias se
      añaden respetando el orden lexicográfico del mapa de submapas "distancias_e"
  */
  void actualizar_distancias(const Especie& e);

};
#endif
