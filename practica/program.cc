/** @mainpage Práctica de PRO2 (Primavera 2020): Árboles filogenéticos. Documentación

    El programa principal se encuentra en el módulo program.cc. Acorde a la
    datos sugeridos por el enunciado, se han implementado los módulos
    Especie, para representar cada especie con sus respectivos atributos,
    Cjt_Especies, donde se guardan las especies y la relación entre ellas,
    y Cjt_Clusters, donde se desarrolla la agrupación de especies dentro de
    un conjunto de especies.
*/

/** @file program.cc

    @brief Programa principal

    Estamos suponiendo que todos los datos de entrada cumplen el formato decidido
    en el enunciado de la práctica y, por lo tanto, son válidos, por lo que no se
    hace ninguna comprobación sobre estos.

*/
#include "Cjt_Clusters.hh"

int main() {
  int k; // Longitud de una subsecuencia de un gen
  cin >> k;
  Cjt_Especies e(k);
  Cjt_Clusters c;
  string command; // Código de operación
  cin >> command;
  while (command != "fin") {
    string id;
    bool b;
    if (command == "crea_especie") {
      string gen;
      cin >> id >> gen;
      cout << "# " << command << " " << id << " " << gen << endl;
      e.crear_especie(id, gen, b);
      if (not b) cout << "ERROR: La especie " << id << " ya existe." << endl;
    }
    else if (command == "obtener_gen") {
      cin >> id;
      cout << "# " << command << " " << id << endl;
      string s = e.obtener_gen(id);
      if (s == "-1") cout << "ERROR: La especie " << id << " no existe." << endl;
      else cout << s << endl;
    }
    else if (command == "distancia") {
      string id2;
      cin >> id >> id2;
      cout << "# " << command << " " << id << " " << id2 << endl;
      double d = e.consultar_distancia(id, id2);
      if (d == -1) cout << "ERROR: La especie " << id << " no existe." << endl;
      else if (d == -2) cout << "ERROR: La especie " << id2 << " no existe." << endl;
      else if (d == -3) cout << "ERROR: La especie " << id << " y la especie " << id2 << " no existen." << endl;
      else cout << d << endl;
    }
    else if (command == "elimina_especie") {
      cin >> id;
      cout << "# " << command << " " << id << endl;
      e.eliminar_especie(id, b);
      if (not b) cout << "ERROR: La especie " << id << " no existe."  << endl;
    }
    else if (command == "existe_especie") {
      cin >> id;
      cout << "# " << command << " " << id << endl;
      bool b = e.existe_especie(id);
      if (b) cout << "SI" << endl;
      else cout << "NO" << endl;
    }
    else if (command == "lee_cjt_especies") {
      cout << "# " << command << endl;
      e = Cjt_Especies(k);
      e.leer_cjt_especies();
      }
    else if (command == "imprime_cjt_especies") {
      cout << "# " << command << endl;
      e.imprimir_cjt_especies();
    }
    else if (command == "tabla_distancias") {
      cout << "# " << command << endl;
      e.imprimir_distancias_e();
    }
    else if (command == "inicializa_clusters") {
      cout << "# " << command << endl;
      c = Cjt_Clusters(e);
      c.imprimir_distancias_c();
    }
    else if (command == "ejecuta_paso_wpgma") {
      cout << "# " << command << endl;
      c.ejecutar_paso_wpgma(b);
      if (not b) cout << "ERROR: num_clusters <= 1" << endl;
    }
    else if (command == "imprime_cluster") {
      cin >> id;
      cout << "# " << command << " " << id << endl;
      c.imprimir_cluster(id, b);
      if (not b) cout << "ERROR: El cluster " << id << " no existe." << endl;
    }
    else if (command == "imprime_arbol_filogenetico") {
      cout << "# " << command << endl;
      c = Cjt_Clusters(e);
      c.imprimir_arbol_filogenetico(b);
      if (b) cout << "ERROR: El conjunto de clusters es vacio." << endl;
    }
    cout << endl;
    cin >> command;
  }
}
