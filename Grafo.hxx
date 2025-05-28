#include "Grafo.h"

Grafo::Grafo() {
}

void Grafo::insertarVertice(Punto p) {
    vertices.push_back(p);
    int n = vertices.size();

    matrizAdyacencia.resize(n);
    for (int i = 0; i < n; i++) {
        matrizAdyacencia[i].resize(n, 0.0);
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

vector< vector<unsigned long> > Grafo::algoritmoPrim(int origen) const {
    int n = vertices.size();

    vector<bool> visitado(n, false);
    vector<int> padre(n, -1);
    vector<float> costo(n, 99999);
    vector< vector<unsigned long> > rutas(n);

    costo[origen] = 0;

    for (int cuenta = 0; cuenta < n - 1; cuenta++) {
        int u = -1;
        float minimo = 99999;

        for (int i = 0; i < n; i++) {
            if (!visitado[i] && costo[i] < minimo) {
                minimo = costo[i];
                u = i;
            }
        }

        if (u == -1) {
            break;
        }

        visitado[u] = true;

        for (int v = 0; v < n; v++) {
            float peso = matrizAdyacencia[u][v];
            if (peso > 0 && !visitado[v] && peso < costo[v]) {
                costo[v] = peso;
                padre[v] = u;
            }
        }
    }

    for (int v = 0; v < n; v++) {
        int actual = v;
        while (actual != -1) {
            rutas[v].insert(rutas[v].begin(), actual);
            actual = padre[actual];
        }
    }

    return rutas;
}

vector< vector<unsigned long> > Grafo::algoritmoDijkstra(int origen) const {
    int n = vertices.size();

    vector<bool> visitado(n, false);
    vector<float> distancia(n, 99999);
    vector<int> padre(n, -1);
    vector< vector<unsigned long> > rutas(n);

    distancia[origen] = 0;

    for (int cuenta = 0; cuenta < n; cuenta++) {
        int u = -1;
        float minimo = 99999;

        for (int i = 0; i < n; i++) {
            if (!visitado[i] && distancia[i] < minimo) {
                minimo = distancia[i];
                u = i;
            }
        }

        if (u == -1) {
            break;
        }

        visitado[u] = true;

        for (int v = 0; v < n; v++) {
            float peso = matrizAdyacencia[u][v];
            if (peso > 0 && !visitado[v] && distancia[u] + peso < distancia[v]) {
                distancia[v] = distancia[u] + peso;
                padre[v] = u;
            }
        }
    }

    for (int v = 0; v < n; v++) {
        int actual = v;
        while (actual != -1) {
            rutas[v].insert(rutas[v].begin(), actual);
            actual = padre[actual];
        }
    }

    return rutas;
}

