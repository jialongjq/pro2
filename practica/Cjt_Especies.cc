/** @file Cjt_Especies.cc
    @brief Código de la clase Cjt_Especies
*/

#include "Cjt_Especies.hh"

void Cjt_Especies::inicializar_distancias() {
  map<string, Especie>::iterator it1 = especies.begin();
  while (it1 != especies.end()) {
    map<string, Especie>::iterator it2 = it1;
    ++it2;
    map<string, double> aux;
    while (it2 != especies.end()) {
      double distancia = it1->second.calcular_distancia(it2->second);
      aux.insert(aux.end(), make_pair(it2->first, distancia));
      ++it2;
    }
    distancias_e.insert(distancias_e.end(), make_pair(it1->first, aux));
    ++it1;
  }
}

void Cjt_Especies::actualizar_distancias(const Especie& e) {
  map<string, Especie>::iterator it = especies.begin();
  map<string, map<string, double> >::iterator it_add = distancias_e.begin();
  map<string, double> aux;
  string id2 = e.consultar_id();
  while (it != especies.end()) {
    string id1 = it->first;
    double d = it->second.calcular_distancia(e);
    if (id1 < id2) {
      distancias_e[id1][id2] = d;
      ++it_add;
    }
    else if (id1 > id2) {
      aux.insert(aux.end(), make_pair(id1, d));
    }
    ++it;
  }
  distancias_e.insert(it_add, make_pair(id2, aux));
}

Cjt_Especies::Cjt_Especies(int k) {
  this->k = k;
}

int Cjt_Especies::size() const {
  return especies.size();
}

string Cjt_Especies::obtener_gen(const string& id) const {
  map<string, Especie>::const_iterator it = especies.find(id);
  if (it == especies.end()) return "-1";
  return it->second.consultar_gen();
}

void swap(string& a, string& b) {
  string aux = a;
  a = b;
  b = aux;
}

double Cjt_Especies::consultar_distancia(string& id1, string& id2) const {
  bool swapped = false;
  if (id1 > id2) {
    swap(id1, id2);
    swapped = true;
  }
  map<string, map<string, double> >::const_iterator it1 = distancias_e.find(id1);
  map<string, double>::const_iterator it2;
  if (it1 != distancias_e.end()) {
    it2 = it1->second.find(id2);
    if (it2 != it1->second.end()) return it2->second;
    return -2;
  }
  else {
    it1 = distancias_e.find(id2);
    if (it1 == distancias_e.end()) {
      if (swapped) swap(id1, id2);
      return -3;
    }
    return -1;
  }
}

bool Cjt_Especies::existe_especie(const string& id) const {
  map<string, Especie>::const_iterator it = especies.find(id);
  if (it == especies.end()) return false;
  return true;
}

string Cjt_Especies::consultar_id_iesimo(int i) const {
  map<string, Especie>::const_iterator it = especies.begin();
  for (int x = 0; x < i; ++x) {
    ++it;
  }
  return it->first;
}

void Cjt_Especies::crear_especie(const string& id, const string& g, bool& b) {
  map<string, Especie>::iterator it = especies.find(id);
  if (it != especies.end()) b = false;
  else {
    b = true;
    Especie aux(id, g, k);
    especies.insert(make_pair(id, aux));
    actualizar_distancias(aux);
  }
}

void Cjt_Especies::eliminar_especie(const string& id, bool& b) {
  map<string, Especie>::iterator it = especies.find(id);
  if (it == especies.end()) b = false;
  else {
    b = true;
    especies.erase(it);
    map<string, map<string, double> >::iterator it2 = distancias_e.begin();
    while (it2 != distancias_e.end()) {
      if (it2->first == id) it2 = distancias_e.erase(it2);
      else {
        it2->second.erase(id);
        ++it2;
      }
    }
  }
}

void Cjt_Especies::leer_cjt_especies() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    Especie aux;
    aux.leer_especie(k);
    especies[aux.consultar_id()] = aux;
  }
  inicializar_distancias();
}

void Cjt_Especies::imprimir_cjt_especies() const {
  map<string, Especie>::const_iterator it = especies.begin();
  while (it != especies.end()) {
    it->second.imprimir_especie();
    ++it;
  }
}

void Cjt_Especies::imprimir_distancias_e() const {
  map<string, map<string, double> >::const_iterator it1 = distancias_e.begin();
  while (it1 != distancias_e.end()) {
    cout << it1->first << ":";
    map<string, double>::const_iterator it2 = it1->second.begin();
    while (it2 != it1->second.end()) {
      cout << " " << it2->first << " (" << it2->second << ")";
      ++it2;
    }
    ++it1;
    cout << endl;
  }
}
