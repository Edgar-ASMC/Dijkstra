#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using namespace std;

const int INF = numeric_limits<int>::max();

// Clase Grafo
class Grafo {
public:
    int numNodos;
    vector<vector<pair<int, int>>> listaAdyacencia;

    Grafo(int n) : numNodos(n), listaAdyacencia(n) {}

    void agregarArista(int origen, int destino, int peso) {
        listaAdyacencia[origen].push_back({destino, peso});
    }

    const vector<vector<pair<int, int>>>& obtenerGrafo() const {
        return listaAdyacencia;
    }
};

// Función de Dijkstra
vector<int> dijkstra(int n, int origen, const vector<vector<pair<int, int>>>& grafo, vector<int>& predecesor) {
    vector<int> distancias(n, INF);
    distancias[origen] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, origen});

    predecesor.assign(n, -1);

    while (!pq.empty()) {
        int distancia_actual = pq.top().first;
        int nodo_actual = pq.top().second;
        pq.pop();

        if (distancia_actual > distancias[nodo_actual]) continue;

        for (const auto& vecino : grafo[nodo_actual]) {
            int nodo_vecino = vecino.first;
            int peso_arista = vecino.second;

            int nueva_distancia = distancia_actual + peso_arista;

            if (nueva_distancia < distancias[nodo_vecino]) {
                distancias[nodo_vecino] = nueva_distancia;
                pq.push({nueva_distancia, nodo_vecino});
                predecesor[nodo_vecino] = nodo_actual;
            }
        }
    }

    return distancias;
}

// Función para reconstruir el camino desde el nodo de origen hasta el nodo destino
int reconstruirCamino(int destino, const vector<int>& predecesor) {
    stack<int> camino;
    int nodo = destino;

    // Contador de pasos en el camino específico
    int pasos = 0;

    while (nodo != -1) {
        camino.push(nodo);
        nodo = predecesor[nodo];
        pasos++;
    }

    cout << "Camino: ";
    while (!camino.empty()) {
        cout << camino.top();
        camino.pop();
        if (!camino.empty()) cout << " -> ";
    }
    cout << endl;

    return pasos - 1;
}

int main() {
    int n = 17; // Número de nodos
    Grafo grafo(n);

    // Añadir aristas al grafo
    grafo.agregarArista(0, 1, 477);
    grafo.agregarArista(1, 0, 477);
    grafo.agregarArista(1, 2, 135);
    grafo.agregarArista(2, 3, 1870);
    grafo.agregarArista(2, 5, 133);
    grafo.agregarArista(3, 4, 366);
    grafo.agregarArista(4, 5, 1540);
    grafo.agregarArista(5, 6, 263);
    grafo.agregarArista(6, 7, 385);
    grafo.agregarArista(6, 15, 1280);
    grafo.agregarArista(7, 6, 385);
    grafo.agregarArista(7, 8, 1410);
    grafo.agregarArista(7, 10, 1080);
    grafo.agregarArista(8, 7, 1410);
    grafo.agregarArista(8, 9, 184);
    grafo.agregarArista(9, 8, 184);
    grafo.agregarArista(9, 10, 1100);
    grafo.agregarArista(10, 9, 1100);
    grafo.agregarArista(10, 7, 1080);
    grafo.agregarArista(10, 11, 449);
    grafo.agregarArista(11, 10, 449);
    grafo.agregarArista(11, 13, 1260);
    grafo.agregarArista(11, 12, 139);
    grafo.agregarArista(12, 11, 139);
    grafo.agregarArista(13, 11, 1260);
    grafo.agregarArista(13, 14, 1420);
    grafo.agregarArista(14, 13, 1420);
    grafo.agregarArista(14, 15, 263);
    grafo.agregarArista(15, 16, 304);
    grafo.agregarArista(16, 1, 1360);

    int origen;
    cout << "Selecciona el nodo de origen: ";
    cin >> origen;

    vector<int> predecesor;
    vector<int> distancias = dijkstra(n, origen, grafo.obtenerGrafo(), predecesor);

    int nodof = 0;

    cout << "Selecciona el nodo de destino: ";
    cin >> nodof;
    if (distancias[nodof] == INF) {
        cout << "El nodo " << nodof << " es inalcanzable desde el nodo de origen " << origen << "." << endl;
    } else {
        cout << "La distancia entre el nodo de origen " << origen << " y el nodo " << nodof << " es de: " << endl << distancias[nodof] << " m" << endl;

        int pasos = reconstruirCamino(nodof, predecesor);
        cout << "Numero total de pasos en el camino final: " << pasos << endl;
    }

    return 0;
}
