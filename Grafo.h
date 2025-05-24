#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <cmath>

using namespace std;

struct Punto {
    float X, Y;

    // Calcula la distancia euclidiana entre este punto y otro
    float distanciaA(const Punto& otro) const {
        float dx = X - otro.X;
        float dy = Y - otro.Y;
        return sqrt(dx * dx + dy * dy); // Calcula raíz cuadrada
    }
};

// Alias para simplificar tipos de rutas
typedef vector<unsigned long> TRuta;
typedef vector<TRuta> TCaminos;
typedef vector<float> TDist;

class Grafo {
private:
    vector<Punto> vertices;
    vector< vector<float> > matrizAdyacencia; // Matriz de costos (distancias)

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

