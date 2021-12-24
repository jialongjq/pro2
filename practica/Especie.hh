/** @file Especie.hh
    @brief Especificación de la clase Especie
*/
#ifndef ESPECIE_HH
#define ESPECIE_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#endif
using namespace std;

/** @class Especie
    @brief Representa la información y las operaciones asociadas a una especie

    Sus operaciones son las consultoras de identificador y gen de una especie,
    además de una operación que permite calcular la distancia entre dos especies,
    y las de lectura y escritura

    Hay declarada una operación auxiliar como \em private
*/
class Especie {

private:

  /** @brief Identificador de la especie */
  string id;
  /** @brief Gen de la especie */
  string gen;
  /** @brief Kmer de la especie */
  map<string, int> kmer;

public:

  //Constructoras

  /** @brief Constructora por defecto
      \pre Cierto
      \post El resultado es una especie sin atributos
  */
  Especie();

  /** @brief Constructora con atributos de una especie
      \pre Cierto
      \post El resultado es una especie con atributos 'id' = id, 'gen' = gen,
      y su 'kmer' obtenido a partir de gen y k
  */
  Especie(const string& id, const string& gen, int k);

  //Consultoras

  /** @brief Consulta el identificador de una especie
      \pre Cierto
      \post El resultado es el atributo id del parámetro implícito
  */
  string consultar_id() const;

  /** @brief Consulta el gen de una especie
      \pre Cierto
      \post El resultado es el atributo gen del parámetro implícito
  */
  string consultar_gen() const;

  /** @brief Calcula la distancia entre dos especies
      \pre Cierto
      \post El resultado es la distancia calculada a partir de los kmers del parámetro
      implícito y la especie e
  */
  double calcular_distancia(const Especie& e) const;

  //Lectura y escritura

  /** @brief Lectura de una especie
      \pre Hay preparado en el canal estándar de entrada dos strings, k > 0
      \post El parámetro implícito pasa a tener los atributos leídos del canal
      estándar de entrada
  */
  void leer_especie(int k);

  /** @brief Escritura de una especie
      \pre Cierto
      \post Se ha escrito en el canal estándar de salida los atributos id
      y gen del parámetro implícito
  */
  void imprimir_especie() const;

private:

  /** @brief Calcula el kmer de una especie
      \pre k > 0
      \post Se le asigna al parámetro implícito un kmer calculado a partir de su 'gen'
      y k
  */
  void calcular_kmer(int k);

};
#endif
