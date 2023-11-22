#include <iostream>
#include <limits>
#include <vector>
using namespace std;

const int FILAS = 6;
const int COLUMNAS = 7;
const int JUGADOR_MAX = 1;
const int JUGADOR_MIN = 2;

struct Nodo{

int tablero[FILAS][COLUMNAS];
int columna;
int valor;
vector<Nodo*>hijos;
};


int minimax(Nodo* nodo, int profundidad,bool esMaximo, int alpha, int beta){
if(profundidad==0 || esTerminal(nodo->tablero)){
    return evaluarTablero(nodo->tablero);
}

if(esMaximo){
int maxEv=INT_MIN;
for(Nodo* hijo : nodo->hijos){
    int evaluar = minimax(hijo,profundidad-1,false,alpha,beta);
    maxEv = max(maxEv,evaluar);
    alpha = max(alpha,maxEv);
    if(beta<=alpha){
        break;
    }
}
return maxEv;
}else{
int minEv=INT_MAX;
for(Nodo* hijo : nodo->hijos){
    int evaluar = minimax(hijo,profundidad-1,true,alpha,beta);
    minEv = min(minEv,evaluar);
    beta = min(beta,minEv);
    if(beta<=alpha){
        break;
    }   
}
return minEv;
}

}
Nodo* construirArbol(int tablero[FILAS][COLUMNAS], int profundidad, int jugador, int columna) {
    Nodo* nodo = new Nodo();
    memcpy(nodo->tablero, tablero, sizeof(tablero));
    nodo->columna = columna;
    nodo->valor = 0;

    if (profundidad > 0 && !esTerminal(tablero)) {
        for (int i = 0; i < COLUMNAS; ++i) {
            if (movimientoValido(tablero, i)) {
                int nuevoTablero[FILAS][COLUMNAS];
                memcpy(nuevoTablero, tablero, sizeof(tablero));
                realizarMovimiento(nuevoTablero, i, jugador);

                Nodo* hijo = construirArbol(nuevoTablero, profundidad - 1, 3 - jugador, i);
                nodo->hijos.push_back(hijo);
            }
        }
    }

    return nodo;
}

int evaluarTablero(int tablero[FILAS][COLUMNAS]) {
    // Esta es una función de evaluación muy simple.
    // Puedes personalizarla según las reglas específicas de tu juego.

    int puntaje = 0;

    // Evaluar las filas
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS - 3; ++j) {
            puntaje += evaluarVentana(tablero[i][j], tablero[i][j + 1], tablero[i][j + 2], tablero[i][j + 3]);
        }
    }

    // Evaluar las columnas
    for (int i = 0; i < FILAS - 3; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            puntaje += evaluarVentana(tablero[i][j], tablero[i + 1][j], tablero[i + 2][j], tablero[i + 3][j]);
        }
    }

    // Evaluar diagonales ascendentes
    for (int i = 3; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS - 3; ++j) {
            puntaje += evaluarVentana(tablero[i][j], tablero[i - 1][j + 1], tablero[i - 2][j + 2], tablero[i - 3][j + 3]);
        }
    }

    // Evaluar diagonales descendentes
    for (int i = 3; i < FILAS; ++i) {
        for (int j = 3; j < COLUMNAS; ++j) {
            puntaje += evaluarVentana(tablero[i][j], tablero[i - 1][j - 1], tablero[i - 2][j - 2], tablero[i - 3][j - 3]);
        }
    }

    return puntaje;
}
int evaluarVentana(int c1, int c2, int c3, int c4) {
    // Esta función asigna un puntaje a una ventana de 4 fichas consecutivas.

    int puntaje = 0;

    // Puntajes arbitrarios, ajusta según tu estrategia de evaluación
    if (c1 == JUGADOR_MAX) {
        puntaje = 1;
    } else if (c1 == JUGADOR_MIN) {
        puntaje = -1;
    }

    if (c2 == JUGADOR_MAX) {
        puntaje *= 10;
    } else if (c2 == JUGADOR_MIN) {
        puntaje *= -10;
    }

    if (c3 == JUGADOR_MAX) {
        puntaje *= 100;
    } else if (c3 == JUGADOR_MIN) {
        puntaje *= -100;
    }

    if (c4 == JUGADOR_MAX) {
        puntaje *= 1000;
    } else if (c4 == JUGADOR_MIN) {
        puntaje *= -1000;
    }

    return puntaje;
}

int obtenerMejorMovimientoIA(int tablero[FILAS][COLUMNAS], int profundidad, Nodo* raiz) {
    int movimientosValidos[COLUMNAS];
    int numMovimientos = 0;

    for (int i = 0; i < COLUMNAS; ++i) {
        if (movimientoValido(tablero, i)) {
            movimientosValidos[numMovimientos++] = i;
        }
    }

    int mejorMovimiento = movimientosValidos[0];
    int mejorEvaluacion = INT_MIN;

    for (int i = 0; i < numMovimientos; ++i) {
        int nuevaColumna = movimientosValidos[i];
        int nuevoTablero[FILAS][COLUMNAS];
        std::memcpy(nuevoTablero, tablero, sizeof(tablero));
        realizarMovimiento(nuevoTablero, nuevaColumna, JUGADOR_MAX);

        // Busca el nodo hijo correspondiente a la columna actual
        Nodo* nodoHijo = nullptr;
        for (Nodo* hijo : raiz->hijos) {
            if (hijo->columna == nuevaColumna) {
                nodoHijo = hijo;
                break;
            }
        }

        if (nodoHijo != nullptr) {
            int evaluacion = minimax(nodoHijo, profundidad - 1, false, INT_MIN, INT_MAX);

            if (evaluacion > mejorEvaluacion) {
                mejorEvaluacion = evaluacion;
                mejorMovimiento = nuevaColumna;
            }
        }
    }

    return mejorMovimiento;
}

    
int main(){

    int tablero[FILAS][COLUMNAS] = {0}; // Inicializa el tablero según tu juego
    int profundidadMaxima = 3; // Ajusta la profundidad máxima según tus necesidades

    while (!esTerminal(tablero)) {
        // Turno del jugador
        int columnaJugador;
        std::cout << "Turno del jugador. Elige una columna (0-6): ";
        std::cin >> columnaJugador;

        while (!movimientoValido(tablero, columnaJugador)) {
            std::cout << "Movimiento no válido. Elige otra columna: ";
            std::cin >> columnaJugador;
        }

        realizarMovimiento(tablero, columnaJugador, JUGADOR_MAX);
        imprimirTablero(tablero);

        // Turno de la IA
        Nodo* raiz = construirArbol(tablero, profundidadMaxima, JUGADOR_MIN, columnaJugador);
        int columnaIA = obtenerMejorMovimientoIA(tablero, profundidadMaxima,raiz);
        realizarMovimiento(tablero, columnaIA, JUGADOR_MIN);
        std::cout << "La IA elige la columna: " << columnaIA << std::endl;
        imprimirTablero(tablero);
    }








return 0;
}