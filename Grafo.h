#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <cmath>

using namespace std;

struct Punto {
    float X, Y;
    float distanciaA(const Punto& b) const {
        float x = X - b.X;
        float y = Y - b.Y;
        return std::sqrt((x * x) + (y * y));
    }
};

typedef vector<unsigned long> TRuta;
typedef vector<TRuta> TCaminos;

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

    TCaminos algoritmoPrim(int origen) const;
    TCaminos algoritmoDijkstra(int origen) const;
};

#endif



