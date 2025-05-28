#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <cmath>

using namespace std;

struct Punto;

class Grafo {
private:
    vector<Punto> vertices;
    vector< vector<float> > matrizAdyacencia;

public:
    Grafo();

    void insertarVertice(Punto p);
    void insertarArista(int origen, int destino, float costo);

    Punto obtenerVertice(int indice) const;
    float obtenerCosto(int origen, int destino) const;
    int numeroVertices() const;

    vector< vector<unsigned long> > algoritmoPrim(int origen) const;
    vector< vector<unsigned long> > algoritmoDijkstra(int origen) const;
};

#endif
