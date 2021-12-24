/** @file Especie.cc
    @brief Código de la clase Especie
*/
#include "Especie.hh"

void Especie::calcular_kmer(int k) {
  int size = this->gen.size() - k + 1;
  for (int i = 0; i < size; ++i) {
    string aux = "";
    for (int j = i; j < i + k; ++j) {
      aux += this->gen[j];
    }
    pair<map<string, int>::iterator, bool> p;
    p = this->kmer.insert(make_pair(aux, 1));
    if (not p.second) p.first->second += 1;
  }
}

double Especie::calcular_distancia(const Especie& e) const {
  map<string, int>::const_iterator it1 = this->kmer.begin();
  map<string, int>::const_iterator it2 = e.kmer.begin();
  double n_interseccion = 0;
  double n_union = 0;
  while (it1 != this->kmer.end() and it2 != e.kmer.end()) {
    if (it1->first > it2->first) {
      n_union += it2->second;
      ++it2;
    }
    else if (it1->first < it2->first) {
      n_union += it1->second;
      ++it1;
    }
    else if (it1->first == it2->first){
      n_union += max(it1->second, it2->second);
      n_interseccion += min(it1->second, it2->second);
      ++it1;
      ++it2;
    }
  }
  while (it1 != this->kmer.end()) {
    n_union += it1->second;
    ++it1;
  }
  while (it2 != e.kmer.end()) {
    n_union += it2->second;
    ++it2;
  }
  double distancia = ((1 - (n_interseccion/n_union)) * 100);
  return distancia;
}

Especie::Especie() {
  id = "";
  gen = "";
}

Especie::Especie(const string& id, const string& gen, int k) {
  this->id = id;
  this->gen = gen;
  calcular_kmer(k);
}

string Especie::consultar_id() const {
  return this->id;
}

string Especie::consultar_gen() const {
  return this->gen;
}

void Especie::leer_especie(int k) {
  cin >> id >> gen;
  calcular_kmer(k);
}

void Especie::imprimir_especie() const {
  cout << id << " " << gen << endl;
}
