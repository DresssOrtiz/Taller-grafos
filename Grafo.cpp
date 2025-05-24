#include "Grafo.h"

Grafo::Grafo() {
}

void Grafo::insertarVertice(Punto p) {
    vertices.push_back(p);
    int n = vertices.size();

    // Redimensionar la matriz de adyacencia para incluir el nuevo vértice
    matrizAdyacencia.resize(n);
    for (int i = 0; i < n; i++) {
        matrizAdyacencia[i].resize(n, 0.0); // 0 indica que no hay conexión entre nodos
    }
}

void Grafo::insertarArista(int origen, int destino, float costo) {
    if (origen >= 0 && destino >= 0 &&
        origen < vertices.size() && destino < vertices.size()) {
        matrizAdyacencia[origen][destino] = costo;
        matrizAdyacencia[destino][origen] = costo; // Grafo no dirigido
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

TCaminos Grafo::algoritmoPrim(int origen) const {
    int n = vertices.size();

    vector<bool> visitado(n, false);       // Marca los nodos que ya están en el MST
    vector<int> padre(n, -1);              // Guarda el nodo desde el cual se alcanzó cada vértice
    vector<float> costo(n, 99999);         // Costo mínimo para alcanzar cada nodo (inicializado en "infinito")
    TCaminos rutas(n);                     // Lista de rutas resultado, una por cada nodo

    costo[origen] = 0; // El nodo inicial tiene costo 0 para iniciar el MST

    for (int cuenta = 0; cuenta < n - 1; cuenta++) {
        int u = -1;
        float minimo = 99999;

        // Buscar el nodo no visitado con menor costo para agregar al MST
        for (int i = 0; i < n; i++) {
            if (!visitado[i] && costo[i] < minimo) {
                minimo = costo[i];
                u = i;
            }
        }

        if (u == -1) {
            break; // El grafo no está completamente conectado
        }

        visitado[u] = true;

        // Verificar si desde el nodo u se puede mejorar el costo a otros nodos
        for (int v = 0; v < n; v++) {
            float peso = matrizAdyacencia[u][v];
            if (peso > 0 && !visitado[v] && peso < costo[v]) {
                costo[v] = peso;
                padre[v] = u;
            }
        }
    }

    // Reconstrucción de rutas desde el origen hasta cada nodo
    for (int v = 0; v < n; v++) {
        int actual = v;
        while (actual != -1) {
            rutas[v].insert(rutas[v].begin(), actual);
            actual = padre[actual];
        }
    }

    return rutas;
}

TCaminos Grafo::algoritmoDijkstra(int origen) const {
    int n = vertices.size();

    vector<bool> visitado(n, false);       // Marca los nodos ya procesados
    vector<float> distancia(n, 99999);     // Distancia mínima desde el origen a cada nodo
    vector<int> padre(n, -1);              // Guarda el nodo anterior en el camino más corto
    TCaminos rutas(n);                     // Lista de rutas resultado

    distancia[origen] = 0; // La distancia desde el origen hasta sí mismo es cero

    for (int cuenta = 0; cuenta < n; cuenta++) {
        int u = -1;
        float minimo = 99999;

        // Seleccionar el nodo no visitado con menor distancia conocida
        for (int i = 0; i < n; i++) {
            if (!visitado[i] && distancia[i] < minimo) {
                minimo = distancia[i];
                u = i;
            }
        }

        if (u == -1) {
            break; // No hay más nodos alcanzables
        }

        visitado[u] = true;

        // Intentar mejorar la distancia a los vecinos de u
        for (int v = 0; v < n; v++) {
            float peso = matrizAdyacencia[u][v];
            if (peso > 0 && !visitado[v] && distancia[u] + peso < distancia[v]) {
                distancia[v] = distancia[u] + peso;
                padre[v] = u;
            }
        }
    }

    // Reconstrucción de rutas desde el origen hasta cada nodo
    for (int v = 0; v < n; v++) {
        int actual = v;
        while (actual != -1) {
            rutas[v].insert(rutas[v].begin(), actual);
            actual = padre[actual];
        }
    }

    return rutas;
}

