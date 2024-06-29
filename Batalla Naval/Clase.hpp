#ifndef TABLERO_H_
#define TABLERO_H_
#include <unistd.h>
#include <iostream>
#include <vector>
#include <windows.h>

#include "Utilidades.hpp"


using namespace std;

struct Barco {
    int tamano;
    int impactos;
    vector<pair<int, int>> coordenadas;
    bool hundido() const { return impactos >= tamano; }
};
class Tablero {
private:
    vector<vector<char>> tablero;
    int filas;
    int columnas;
    vector<Barco> barcos;

public:
    Tablero(int f, int c) : filas(f), columnas(c) {
        tablero.resize(filas, vector<char>(columnas, 254));
    }

    void mostrarTableroAliado() {
        const int offsetFila = 5;
        const int offsetColumna = 5;

        gotoxy(offsetColumna, offsetFila - 1);
        for (int j = 0; j < columnas; ++j) {
            setColor(7);
            cout << char('A' + j) << ' ';
        }
        cout << RESET << endl;

        for (int i = 0; i < filas; ++i) {
            gotoxy(offsetColumna - 3, offsetFila + i);
            setColor(7);
            cout << i + 1 << ' ';

            gotoxy(offsetColumna, offsetFila + i);
            for (int j = 0; j < columnas; ++j) {
                char celda = tablero[i][j];
                if (celda == 'B') {
                    setColor(12);
                    cout << celda << ' ' << RESET;
                } else if (celda == 'X') {
                    cout << RED << celda << ' ' << RESET;
                } else if (celda == 'O') {
                    cout << YELLOW << celda << ' ' << RESET;
                } else {
                    cout << BLUE << celda << ' ';
                }
            }
        }
        cout << RESET << endl;
        
       
    }
    
    
  


    void mostrarTableroEnemigo() {
        const int offsetFila = 5;
        const int offsetColumna = 80;

        gotoxy(offsetColumna, offsetFila - 1);
        for (int j = 0; j < columnas; ++j) {
            setColor(7);
            cout << char('A' + j) << ' ';
        }
        cout << RESET << endl;

        for (int i = 0; i < filas; ++i) {
            gotoxy(offsetColumna - 3, offsetFila + i);
            setColor(7);
            cout << i + 1 << ' ';

            gotoxy(offsetColumna, offsetFila + i);
            for (int j = 0; j < columnas; ++j) {
                char celda = tablero[i][j];
                if (celda == 'B') {
                    setColor(12);
                    cout << celda << ' ' << RESET;
                } else if (celda == 'X') {
                    cout << RED << celda << ' ' << RESET;
                } else if (celda == 'O') {
                    cout << YELLOW << celda << ' ' << RESET;
                } else {
                    cout << BLUE << celda << ' ';
                }
            }
        }
        cout << RESET << endl;
    }

   


    void realizarDisparo(int fila, int columna ) {
        char r = 254;
        fila--;
        columna--;
        if (tablero[fila][columna] == 'B') {
            tablero[fila][columna] = 'X';
            cout << "Impacto  en " <<fila + 1 << ", " << convertirANumero(columna+ 1)  << endl;
            for (auto& barco : barcos) {
                for (auto& coord : barco.coordenadas) {
                    if (coord.first == fila && coord.second == columna) {
                        barco.impactos++;
                        if (barco.hundido()) {
                             setColor(6);
                             tablero[fila][columna] = 'X';
                             setColor(7);
                            cout << "¡Barco Hundido" << endl;
                        }
                        break;
                    }
                }
            }
        } else if (tablero[fila][columna] == r) {
            tablero[fila][columna] = 'O';
            
            cout << "Sin impacto" << endl;
            
        } else {
            cout << "Ya has disparado en esa posición." << endl;
        }
    }
    void realizarDisparoEnemigotorpedo(int fila, int columna,  Tablero& tableroEnemigo ) {
    char r = 254; 
    fila--;
    columna--;

   
    
       
        tableroEnemigo.tablero[fila][columna] = 'X';
        cout << "Impacto en "<<fila <<","<<columna << endl;


        
    } 

    void realizarDisparoEnemigo(int fila, int columna, int verificacion,  Tablero& tableroEnemigo ) {
    char r = 254; 
    fila--;
    columna--;

   
    if (verificacion == 'S') {
       
        tableroEnemigo.tablero[fila][columna] = 'X';
        cout << "Impacto en "<<fila <<","<<columna << endl;

        
    } 
    // Si la variable de verificación indica que no hubo impacto ('N'), marcar la casilla como agua ('O')
    else if (verificacion == 'N') {
        tableroEnemigo.tablero[fila][columna] = 'O';
        cout << "sin impacto" << endl;
    } 
 
    else {
        cout << "Error: Valor de verificacion no reconocido." << endl;
    }
}
void realizarDisparoBomba(int fila, int columna, Tablero& tableroAliado) {
    char r = 254; // Carácter para representar el agua en el tablero
    fila--; // Convertir de coordenadas de jugador a índices de vector
    columna--;

    // Disparar la bomba en un área de 5x5 alrededor de la posición especificada
    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            int nuevaFila = fila + i;
            int nuevaColumna = columna + j;
            // Verificar si la nueva posición está dentro de los límites del tablero
            if (nuevaFila >= 0 && nuevaFila < tableroAliado.filas && nuevaColumna >= 0 && nuevaColumna < tableroAliado.columnas) {
                if (tableroAliado.tablero[nuevaFila][nuevaColumna] == 'B') {
                    realizarDisparo(nuevaFila + 1, nuevaColumna + 1); // Realizar el disparo en el tablero aliado
                } else if (tableroAliado.tablero[nuevaFila][nuevaColumna] == r) {
                    realizarDisparo(nuevaFila + 1, nuevaColumna + 1); // Realizar el disparo en el tablero aliado
                }
            }
        }
    }
}
  void hundirBarco(Barco& barco) {
        for (auto& coord : barco.coordenadas) {
            tablero[coord.first][coord.second] = 'X';
        }
        barco.impactos = barco.tamano;
    }

    void realizarDisparoTorpedo(int fila,Tablero& tableroCOCO) {
        fila--;
        char r = 254;
        for (int j = 0; j < columnas; ++j) {
             if(tablero[fila][j]== r){
                            tableroCOCO.realizarDisparo(fila + 1, j + 1);
                        } 
            if (tablero[fila][j] == 'B') {
                for (auto& barco : barcos) {
                    for (auto& coord : barco.coordenadas) {
                        if (coord.first == fila && coord.second == j) {
                           
                            hundirBarco(barco);
                            cout << "Torpedo impacta y hunde el barco en la fila " << fila + 1 << "!" << endl;
                            break;
                        }
                        
                    }
                }
                break;
               
            }
        }
    }
    void realizarDisparoTorpedoaliado(int fila, int columna3, Tablero& tableroAliado) {
    char r = 254; 
    fila--; 
    columna3 --;
    

   
    for (int j = 0; j < columna3; ++j) {
        if (tableroAliado.tablero[fila][j] == 'B') {
            realizarDisparo(fila + 1, j + 1); // Realizar el disparo en el tablero aliado
            break;
        } else if (tableroAliado.tablero[fila][j] == r) {
            realizarDisparo(fila + 1, j + 1); // Realizar el disparo en el tablero aliado
        }
    }
}

void colocarBarco(int fila, int columna, int tamano, char direccion) {
    fila--;
    columna--;

    Barco nuevoBarco;
    nuevoBarco.tamano = tamano;
    nuevoBarco.impactos = 0;

    // Verificar si aún se pueden agregar más barcos del tamaño dado
    int cuentaBarcos = 0;
    for (const auto& barco : barcos) {
        if (barco.tamano == tamano) {
            cuentaBarcos++;
        }
    }

    if ((tamano == 2 && cuentaBarcos >= 3) ||
        (tamano == 3 && cuentaBarcos >= 3) ||
        (tamano == 4 && cuentaBarcos >= 2) ||
        (tamano == 5 && cuentaBarcos >= 2)) {
        cout << "No puedes colocar más barcos de tamaño " << tamano << "." << endl;
        system("pause");
        return;
    }

    // Restricciones para colocar el barco
    if (direccion == 'H') {
        if (columna + tamano > columnas) {
            cout << "BARCO NO SE PUEDE UBICAR AHI" << endl;
            system("pause");
            return;
        }
        for (int i = 0; i < tamano; ++i) {
            tablero[fila][columna + i] = 'B';
            nuevoBarco.coordenadas.push_back({fila, columna + i});
        }
    } else if (direccion == 'V') {
        if (fila + tamano > filas) {
            cout << "BARCO NO SE PUEDE UBICAR AHI" << endl;
            system("pause");
            return;
        }
        for (int i = 0; i < tamano; ++i) {
            tablero[fila + i][columna] = 'B';
            nuevoBarco.coordenadas.push_back({fila + i, columna});
        }
    }

    barcos.push_back(nuevoBarco);
}


void mostrarBarcos() {
    gotoxy(50, 5);
    cout << "Barcos: " << endl;

    for (int i = 0; i < barcos.size(); ++i) {
        gotoxy(50, 6 + i); // Ajuste para imprimir cada barco en una línea nueva
        cout << "Barco " << i + 1 << ": ";
        setColor(2);
        for (int j = 0; j < barcos[i].tamano - barcos[i].impactos; ++j) {
            cout << '|'; // Parte no impactada
        }
        setColor(4);
        for (int j = 0; j < barcos[i].impactos; ++j) {
            cout << '|'; // Parte impactada
        }
        cout << RESET << endl;
    }
}

   bool barcosCompletos() {
        return (barcos.size() == 2
        );
    }
     bool todosBarcosHundidos() const {
        for (const auto& barco : barcos) {
            if (!barco.hundido()) {
                return false;
            }
        }
        return true;
    }
    bool hayTresBarcosHundidos() const {
    int barcosHundidos = 0;
    for (const auto& barco : barcos) {
        if (barco.hundido()) {
            barcosHundidos++;
        }
    }
    return barcosHundidos == 3;
}


};
#endif