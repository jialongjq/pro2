/** @file Cjt_Clusters.cc
    @brief Código de la clase Cjt_Clusters
*/
#include "Cjt_Clusters.hh"

Cjt_Clusters::Cjt_Clusters() {}

Cjt_Clusters::Cjt_Clusters(const Cjt_Especies& e) {
  d_min = -1;
  int size = e.size();
  for (int i = 0; i < size; ++i) {
    string id = e.consultar_id_iesimo(i);
    BinTree<pair<string, double> > leaf(make_pair(id, -1));
    clusters.insert(clusters.end(), make_pair(id, leaf));
  }
  map<string, double> aux;
  map<string, BinTree<pair<string, double> > >::iterator it1 = clusters.begin();
  while (it1 != clusters.end()) {
    map<string, double> aux;
    map<string, BinTree<pair<string, double> > >::iterator it2 = it1;
    ++it2;
    while (it2 != clusters.end()) {
      string id1 = it1->first;
      string id2 = it2->first;
      double d = e.consultar_distancia(id1, id2);
      aux.insert(aux.end(), make_pair(id2, d));
      ++it2;
    }
    distancias_c.insert(distancias_c.end(), make_pair(it1->first, aux));
    ++it1;
  }
  distancia_minima();
}

void Cjt_Clusters::distancia_minima() {
  map<string, map<string, double> >::const_iterator it1 = distancias_c.begin();
  while (it1 != distancias_c.end()) {
    map<string, double>::const_iterator it2 = it1->second.begin();
    while (it2 != it1->second.end()) {
      double d = it2->second;
      if (d_min == -1 or d < d_min) {
        save_c1 = it1->first;
        save_c2 = it2->first;
        d_min = d;
      }
      ++it2;
    }
    ++it1;
  }
}

void imprimir_tabla(const map<string, map<string, double> >& m) {
  map<string, map<string, double> >::const_iterator it1 = m.begin();
  while (it1 != m.end()) {
    cout << it1->first << ":";
    map<string, double>::const_iterator it2 = it1->second.begin();
    while (it2 != it1->second.end()) {
      cout << " " << it2->first << " (" << it2->second << ")";
      ++it2;
    }
    cout << endl;
    ++it1;
  }
}

void Cjt_Clusters::algoritmo_wpgma() {
  string s = save_c1 + save_c2;
  //bintrees
  map<string, BinTree<pair<string, double> > >::iterator it_c1 = clusters.find(save_c1);

  map<string, BinTree<pair<string, double> > >::iterator it_c2 = clusters.find(save_c2);
  BinTree<pair<string, double> > tree(make_pair(s, d_min/2), it_c1->second, it_c2->second);
  clusters.erase(it_c2);
  clusters.insert(clusters.erase(it_c1), make_pair(s, tree));

  //distancias
  map<string, map<string, double> >::iterator it1 = distancias_c.begin();
  //Bucle para actualizar la tabla de los clusters previos a save_c1

  while (it1->first < save_c1) {
    map<string, double>::iterator it_c1 = it1->second.find(save_c1);
    map<string, double>::iterator it_c2 = it1->second.find(save_c2);
    double d = (it_c1->second + it_c2->second) / 2;
    it1->second.erase(it_c2);
    //"La inserción es más rápida si se le da una pista; dicha pista es el iterador
    //que apunta al elemento que le procede al elemento insertado"
    it1->second.insert(it1->second.erase(it_c1), make_pair(s, d));
    ++it1;
  }

  //En este momento it1 apunta al clúster save_c1 y su mapa de distancias, por lo que
  //me interesa guardarlo para determinar las distancias actualizadas
  map<string, map<string, double> >::iterator save_it1 = it1;
  map<string, double> aux;
  //it2 apuntará a los clústers cuya distancia tengo que actualizar
  map<string, double>::iterator it2 = save_it1->second.begin();
  map<string, double>::iterator itc2;
  while (it2 != save_it1->second.end()) {
    //A la hora de recalcular distancias, se sigue un cierto patrón:
    //Si el id del cluster que quiero recalcular (llamémosle c3) es menor que save_c2,
    //las distancias que me interesan son la distancia de c3 respecto save_c1 primeramente
    //(se encuentra en el map de save_c1), y la distancia de c3 respecto save_c2
    //(se encuentra en el map de c3 porque c3 < save_c2);
    if (it2->first < save_c2) {
      ++it1;
      double d1 = it2->second;
      map<string, double>::iterator itt = it1->second.find(save_c2);
      double d2 = itt->second;
      it1->second.erase(itt);
      double d = (d1 + d2) / 2;
      aux.insert(aux.end(), make_pair(it2->first, d));
    }
    //Para el caso en el que me encuentre a save_c2 en el map de save_c1, no debo añadir
    //ningún valor al mapa auxiliar aux, porque save_c2 se combina con save_c1
    //lo que sí que me interesa es que it1 apunte a save_c2 y su mapa de distancias, ya que
    //serán necesarias para recalcular las distancias de c3 > save_c2 (para ello necesito
    //consultar el mapa de distancias de save_c2, ya que se encuentran ahí todas las distancias
    //respecto los c3 restantes

    else if (it2->first == save_c2) {
      ++it1;
      itc2 = it1->second.begin();
    }

    else if (it2->first > save_c2) {
      double d1 = it2->second;
      double d2 = itc2->second;
      double d = (d1 + d2) / 2;
      aux.insert(aux.end(), make_pair(it2->first, d));
      ++itc2;
    }
    ++it2;
  }
  distancias_c.insert(distancias_c.erase(save_it1), make_pair(s, aux));
  distancias_c.erase(it1);

  d_min = -1;
  distancia_minima();
}

void Cjt_Clusters::ejecutar_paso_wpgma(bool& b) {
  if (clusters.size() > 1) {
    b = true;
    algoritmo_wpgma();
    imprimir_tabla(distancias_c);
  }
  else b = false;
}

void imprimir_preorden(const BinTree<pair<string, double> >& t) {

  if (not t.empty()) {
    cout << "[";
    double d = t.value().second;
    if (d == -1) cout << t.value().first;
    else cout << "(" << t.value().first << ", " << d << ") ";
    imprimir_preorden(t.left());
    imprimir_preorden(t.right());
    cout << "]";
  }
}

void Cjt_Clusters::imprimir_cluster(string id, bool& b) const {
  map<string, BinTree<pair<string,double> > >::const_iterator it = clusters.find(id);
  if (it == clusters.end()) b = false;
  else {
    b = true;
    imprimir_preorden(it->second);
    cout << endl;
  }
}

void Cjt_Clusters::imprimir_arbol_filogenetico(bool& b) {

  if (clusters.size() == 0) b = true;
  else {
    b = false;
    while (clusters.size() > 1) {
      algoritmo_wpgma();
    }
    imprimir_preorden(clusters.begin()->second);
    cout << endl;
  }
}

void Cjt_Clusters::imprimir_distancias_c() const {
  imprimir_tabla(distancias_c);
}
