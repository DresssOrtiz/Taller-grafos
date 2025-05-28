#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

// TODO # 0: Incluir el archivo cabecera del grafo
#include "Grafo.h"
#include "Grafo.hxx"

// -------------------------------------------------------------------------
typedef std::vector<unsigned long> TRuta;
typedef std::vector<TRuta> TCaminos;
typedef std::vector<float> TDist;

// -------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0] << " archivo_entrada" << std::endl;
    return 1;
  }

  // TODO # 1: Definir el tipo para un grafo con Puntos como vertices y costos reales
  typedef Grafo TGrafo;

  // TODO # 2: Declarar el grafo
  TGrafo g;

  // Cargar el archivo en un buffer
  std::ifstream in_mesh_stream(argv[1], std::ifstream::binary);
  if (!in_mesh_stream) {
    std::cerr << "Error leyendo \"" << argv[1] << "\"" << std::endl;
    return 1;
  }
  in_mesh_stream.seekg(0, in_mesh_stream.end);
  unsigned long in_mesh_file_length = in_mesh_stream.tellg();
  in_mesh_stream.seekg(0, in_mesh_stream.beg);
  char* in_mesh_file_buffer = new char[in_mesh_file_length];
  in_mesh_stream.read(in_mesh_file_buffer, in_mesh_file_length);
  in_mesh_stream.close();
  std::istringstream in_mesh(in_mesh_file_buffer);

  // Leer los vertices desde el buffer
  long nPoints;
  in_mesh >> nPoints;
  for (long pId = 0; pId < nPoints; pId++) {
    Punto pnt;
    in_mesh >> pnt.X >> pnt.Y;

    // TODO # 3: Insertar el Punto en el grafo
    g.insertarVertice(pnt);
  }

  // Leer las aristas desde el buffer
  long nEdges;
  in_mesh >> nEdges;
  for (long eId = 0; eId < nEdges; eId++) {
    long start, end;
    in_mesh >> start >> end;

    // TODO # 4: Calcular el costo de la arista, insertarla en el grafo como no dirigida
    float cost = g.obtenerVertice(start).distanciaA(g.obtenerVertice(end));
    g.insertarArista(start, end, cost);
    g.insertarArista(end, start, cost);
  }
  delete[] in_mesh_file_buffer;

  std::cout << "Porteria: " << g.obtenerVertice(0).X << "," << g.obtenerVertice(0).Y << std::endl;

  // TODO # 5: Calcular distancias lineales (distancia Euclidiana)
  unsigned long s_id = 0;
  float dist_s_e = 0.0;
  TDist distLineales;
  for (unsigned int j = 1; j < g.numeroVertices(); ++j) {
    dist_s_e = g.obtenerVertice(s_id).distanciaA(g.obtenerVertice(j));
    distLineales.push_back(dist_s_e);
  }

  // TODO # 6: Encontrar las rutas de costo minimo usando los algoritmos requeridos
  TCaminos caminosPrim = g.algoritmoPrim(0);
  TCaminos caminosDijkstra = g.algoritmoDijkstra(0);

  // TODO # 7: Imprimir el informe de Prim
  TRuta ruta;
  float cosTotal;
  for (unsigned int j = 1; j < g.numeroVertices(); ++j) {
    std::cout << "Casa " << j << ":" << g.obtenerVertice(j).X << "," << g.obtenerVertice(j).Y << std::endl;
    std::cout << "Distancia lineal a porteria: " << distLineales[j - 1] << std::endl;

    std::cout << "Camino segun algoritmo de Prim: ";
    ruta = caminosPrim[j - 1];
    for (unsigned int i = 0; i < ruta.size(); ++i)
      std::cout << ruta[i] << (i < ruta.size() - 1 ? " - " : "");
    std::cout << std::endl;

    std::cout << "Distancia total recorrida con algoritmo de Prim: ";
    cosTotal = 0.0;
    for (unsigned int i = 0; i < ruta.size() - 1; ++i)
      cosTotal += g.obtenerCosto(ruta[i], ruta[i + 1]);
    std::cout << cosTotal << std::endl;
  }

  // TODO # 8: Imprimir el informe de Dijkstra
  for (unsigned int j = 1; j < g.numeroVertices(); ++j) {
    std::cout << "Casa " << j << ":" << g.obtenerVertice(j).X << "," << g.obtenerVertice(j).Y << std::endl;
    std::cout << "Distancia lineal a porteria: " << distLineales[j - 1] << std::endl;

    std::cout << "Camino segun algoritmo de Dijkstra: ";
    ruta = caminosDijkstra[j - 1];
    for (unsigned int i = 0; i < ruta.size(); ++i)
      std::cout << ruta[i] << (i < ruta.size() - 1 ? " - " : "");
    std::cout << std::endl;

    std::cout << "Distancia total recorrida con algoritmo de Dijkstra: ";
    cosTotal = 0.0;
    for (unsigned int i = 0; i < ruta.size() - 1; ++i)
      cosTotal += g.obtenerCosto(ruta[i], ruta[i + 1]);
    std::cout << cosTotal << std::endl;
  }

  return 0;
}

// eof - taller_5_grafos.cxx
