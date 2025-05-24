#include "Grafo.h"

Grafo::Grafo() {
}

void Grafo::insertarVertice(Punto p) {
    vertices.push_back(p);
    int n = vertices.size();

    matrizAdyacencia.resize(n);
    for (int i = 0; i < n; i++) {
        matrizAdyacencia[i].resize(n, 0.0); // 0 indica que no hay conexión
    }
}

void Grafo::insertarArista(int origen, int destino, float costo) {
    if (origen >= 0 && destino >= 0 &&
        origen < vertices.size() && destino < vertices.size()) {
        matrizAdyacencia[origen][destino] = costo;
        matrizAdyacencia[destino][origen] = costo;
    }
}

Punto Grafo::obtenerVertice(int indice) const {
    return vertices[indice];
}

float Grafo::obtenerCosto(int origen, int destino) const {
    if (origen >= 0 && destino >= 0 &&
        origen < vertices.size() && destino < vertices.size()) {
        return matrizAdyacencia[origen][destino];
    }
    return 0;
}

int Grafo::numeroVertices() const {
    return vertices.size();
}

