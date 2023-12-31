#include <iostream>
#include <limits>
#include <vector>
#include <cstring> 
#include <fstream>
#include <sstream>
#include "conect4.h"

using namespace std;

bool verificarTablero(int tablero[6][7]);
void cargarPartida(const string& nombreArchivo, int matriz[6][7]);
void guardarPartida(string nombreArchivo, int tablero[6][7]);

int main(){
//Se crean tableros aqui para mejor manejo a la hora de usar el archivo "partida.txt"
    int tablero[6][7] = {0}; // Inicializa el tablero según tu juego
    int tableroGuardado[6][7] = {0}; //Tablero auxiliar para guardar la partida
    int profundidadMaxima; // Profundidad máxima del árbol para poder brindar mas exactitud a la respuesta de la IA
    conect4 conect4;// Se crea el objeto conect4
    int op;
    //VERIFICAR SI EXITE PARTIDA GUARDADA OSEA QUE EL TABLERO NO ESTE LLENO DE 0
    cargarPartida("partida.txt",tableroGuardado);
    if (verificarTablero(tableroGuardado)) {
    
        while(op != 1 && op != 2){
        cout<<"Existe una partida guardada"<<endl;
        cout<<"Deseas Continuar? 1. Si 2. No" <<endl;
        
        cin>>op;
        if(op == 1){
            cargarPartida("partida.txt", tablero);
            cout<<"Partida Cargada"<<endl;
            conect4.imprimirTablero(tablero);
        }else if (op==2){
            cout<<"Se crea Nueva Partida"<<endl;
        }else{
            cout<<"Numero no valido"<<endl;
        } 
        }      
    }
    //Ingresar la dificultad
    op=0;
    bool finBucle = false;
    while (!finBucle) {
        cout << "Ingresa el tipo de Dificultad al Juego" << endl;
        cout << "1. Facil" << endl;
        cout << "2. Normal" << endl;
        cout << "3. Dificil" << endl;
        cin >> op;

        switch (op) {
            case 1:
                profundidadMaxima = 2;
                finBucle = true;
                break;
            case 2:
                profundidadMaxima = 4;
                finBucle= true;
                break;
            case 3:
                profundidadMaxima = 8;
                finBucle = true;

                break;
            default:
                cout << "Numero no valido" << endl;
                break;
        }
    }
    finBucle = false;
    while (!conect4.esTerminal(tablero) && !finBucle) {
        
        //Movimientos del jugador
        int columnaJugador;
        cout << "Turno del jugador. Elige una columna (0-6): ";
        cin >> columnaJugador;
        while (!conect4.movimientoValido(tablero, columnaJugador)) {
        cout << "Movimiento no válido, elige otra columna: ";
        cin >> columnaJugador;
        }
        conect4.realizarMovimiento(tablero, columnaJugador, JUGADOR_MAX);
        conect4.imprimirTablero(tablero);


        //Movimientos de la IA
        conect4.movimientoIA(tablero, profundidadMaxima, columnaJugador);
        //Esta parte hacela una funcion 
        op=0;
        //Guardar la partida si el jugador desea
        while(op!=1 && op!=2){
        cout<<"Quieres terminar la partida?"<<endl;
        cout<<"1. Si 2. No"<<endl;
        cin>>op;
        if(op==1){
            guardarPartida("partida.txt", tablero);
            finBucle=true;
            break;
        }else if(op==2){
            cout<<"Se Continua el juego"<<endl;
        }
    }
    }
cout<<"Programa Cerrado"<<endl;
return 0;
}
//VEIRIFCA SI EL TABLERO ESTA LLENO DE 0
bool verificarTablero(int tablero[6][7]) {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (tablero[i][j] != 0) {
                return true;
            }
        }
    }
    cout<<"Tablero vacio"<<endl;
    return false;
}    
//CARGA EL ARCHIVO CON LA PARTIDA GUARDADA en el txt
void cargarPartida(const std::string& nombreArchivo, int matriz[6][7]) {
    ifstream archivo(nombreArchivo);

    // Verifica si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    int filas = 0;

   
    string linea;
    
    while (getline(archivo, linea) && filas < 6) {
        stringstream ss(linea);
        string elemento;
        int columnas = 0;

        // Divide la línea en elementos usando la coma como delimitador
        while (getline(ss, elemento, ',') && columnas < 7) {
            // Convierte cada elemento a entero y lo asigna a la matriz
            matriz[filas][columnas] = stoi(elemento);
            ++columnas;
        }

        ++filas;
    }

    

    archivo.close();
}
void guardarPartida(string nombreArchivo, int tablero[6][7]) {
    ofstream archivo(nombreArchivo);
    if(archivo.is_open()){
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                archivo << tablero[i][j];
                if(j<7-1){
                    archivo <<",";
                }
            }
            archivo << endl;
        }
        archivo.close();
    }
    else{
        cout<<"No se pudo abrir el archivo"<<endl;
    }
}


