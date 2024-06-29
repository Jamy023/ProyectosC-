#include <iostream>
#include <vector>
#include <windows.h>
#include "Utilidades.hpp"
#include "Clase.hpp"

using namespace std;

void torpedosDisponibles(int contador) {
    if (contador == 2) {
        setColor(2);
        cout << "||";
    } else if (contador == 1) {
        setColor(2);
        cout << "|";
        setColor(4);
        cout << "|";
    } else {
        setColor(4);
        cout << "||";
    }
    setColor(7);
}

int main() {
    int contadorBomba = 0;
    int fila, tamano, fila2;
    char direccion, columna, columna2, verificacion;
    int opcion;
    Tablero tableroAliado(10, 15);
    Tablero tableroEnemigo(10, 15);
    int contador = 2;

    do {
        system("cls");
        drawNavalBattle();
        cout << "\t\t\t\t\tMenu Principal" << endl;
        cout << "\t\t\t\t\t1. Colocar barcos" << endl;
        cout << "\t\t\t\t\t2. Jugar" << endl;
        cout << "\t\t\t\t\t3. Salir" << endl;
        cout << "\t\t\t\t\tSelecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                do {
                    system("cls");
                    tableroAliado.mostrarBarcos();
                    tableroAliado.mostrarTableroAliado();
                    cout << endl;
                    gotoxy(1, 18);
                    cout << "Ingresa la fila en la que deseas colocar el barco: ";
                    cin >> fila;
                    cout << "Ingresa la columna en la que deseas colocar el barco (A-J): ";
                    cin >> columna;
                    columna = obtenerValorNumerico(columna);
                    if (columna == -1) {
                        cout << "Columna inválida. Intenta de nuevo." << endl;
                        system("pause");
                        break;
                    }
                    cout << "Ingresa el tamaño del barco: ";
                    cin >> tamano;
                    cout << "Ingresa la dirección del barco (H para horizontal, V para vertical): ";
                    cin >> direccion;
                    tableroAliado.colocarBarco(fila, columna, tamano, direccion);
                    cout << endl;
                    tableroAliado.mostrarTableroAliado();
                    system("pause");
                } while (!tableroAliado.barcosCompletos());
                break;

            case 2:
                if (!tableroAliado.barcosCompletos()) {
                    cout << "Debes colocar todos los barcos antes de jugar." << endl;
                    system("pause");
                } else {
                    do {
                        system("cls");
                        gotoxy(50, 3);
                        cout << "Torpedos: ";
                        torpedosDisponibles(contador);
                        tableroAliado.mostrarBarcos();
                        tableroAliado.mostrarTableroAliado();
                        tableroEnemigo.mostrarTableroEnemigo();

                        int opcionM = 0;
                        cout << "1. Disparar en tablero aliado" << endl;
                        cout << "2. Disparar en tablero enemigo" << endl;
                        cout << "Elige una opción: ";
                        cin >> opcionM;

                        switch (opcionM) {
                            case 1:
                                int tipo;
                                cout << "Tipo de disparo que deseas realizar:" << endl;
                                cout << "1 - Disparo normal" << endl;
                                cout << "2 - Torpedo" << endl;
                                cout << "3 - Bomba" << endl;
                                cin >> tipo;
                                cout << endl;
                                switch (tipo) {
                                    case 1:
                                        cout << "Ingresa la fila en que deseas disparar: ";
                                        cin >> fila2;
                                        cout << "Ingresa la columna en que deseas disparar: ";
                                        cin >> columna2;
                                        columna2 = obtenerValorNumerico(columna2);
                                        if (columna2 == -1) {
                                            cout << "Columna inválida. Intenta de nuevo." << endl;
                                            system("pause");
                                            break;
                                        }
                                        tableroAliado.realizarDisparo(fila2, columna2);
                                        tableroAliado.mostrarTableroAliado();
                                        system("pause");
                                        break;
                                    case 2:
                                        if (contador < 1) {
                                            cout << "No puedes usar más torpedos." << endl;
                                            system("pause");
                                        } else {
                                            int fila3;
                                            cout << "Ingresa la fila a la que deseas disparar: ";
                                            cin >> fila3;
                                            tableroAliado.realizarDisparoTorpedo(fila3, tableroAliado);
                                            contador = contador - 1;
                                            if (tableroAliado.hayTresBarcosHundidos()) {
                                                contadorBomba = 3;
                                            }
                                            system("pause");
                                        }
                                        break;
                                    case 3:
                                        int fila5;
                                        char columna3;
                                        cout << "Fila de bomba: ";
                                        cin >> fila5;
                                        cout << "Columna de bomba: ";
                                        cin >> columna3;
                                        columna3 = obtenerValorNumerico(columna3);
                                        tableroAliado.realizarDisparoBomba(fila5, columna3, tableroAliado);
                                        system("pause");
                                        break;
                                }
                                break;

                            case 2:
                                int tipo2;
                                cout << "Tipo de disparo que deseas realizar:" << endl;
                                cout << "1 - Disparo normal" << endl;
                                cout << "2 - Torpedo" << endl;
                                cout << "3 - Bomba" << endl;
                                cin >> tipo2;

                                switch (tipo2) {
                                    case 1:
                                        cout << "Ingresa la fila en que deseas disparar: ";
                                        cin >> fila2;
                                        cout << "Ingresa la columna en que deseas disparar: ";
                                        cin >> columna2;
                                        columna2 = obtenerValorNumerico(columna2);
                                        if (columna2 == -1) {
                                            cout << "Columna inválida. Intenta de nuevo." << endl;
                                            system("pause");
                                            break;
                                        }
                                        cout << "Hubo impacto? (S/N): ";
                                        cin >> verificacion;
                                        tableroEnemigo.realizarDisparoEnemigo(fila2, columna2, verificacion, tableroEnemigo);
                                        break;
                                    case 2:
                                        int fila3;
                                        char columna8;
                                        char verificacion;
                                        cout << "Ingresa la fila a la que deseas disparar: ";
                                        cin >> fila3;
                                        cout << "Hubo impacto? (S/N): ";
                                        cin >> verificacion;
                                        if (verificacion == 'S') {
                                            int fila8;
                                            cout << "Fila: ";
                                            cin >> fila8;
                                            cout << "Columna: ";
                                            cin >> columna8;
                                            columna8 = obtenerValorNumerico(columna8);
                                            tableroEnemigo.realizarDisparoTorpedoaliado(fila8, columna8, tableroEnemigo);
                                            tableroEnemigo.realizarDisparoEnemigotorpedo(fila8, columna8, tableroEnemigo);
                                        }
                                        break;
                                    case 3:
                                        int fila4;
                                        char columna6;
                                        char verificacion4;
                                        cout << "Fila de bomba: ";
                                        cin >> fila4;
                                        cout << "Columna de bomba: ";
                                        cin >> columna6;
                                        columna6 = obtenerValorNumerico(columna6);
                                        tableroEnemigo.realizarDisparoBomba(fila4, columna6, tableroEnemigo);
                                        do {
                                            cout << "Hubo impacto? (S/N): ";
                                            cin >> verificacion4;
                                            int fila8;
                                            char columna8;
                                            cout << "Fila: ";
                                            cin >> fila8;
                                            cout << "Columna: ";
                                            cin >> columna8;
                                            columna8 = obtenerValorNumerico(columna8);
                                            tableroEnemigo.realizarDisparoEnemigotorpedo(fila8, columna8, tableroEnemigo);
                                        } while (verificacion4 == 'S');
                                        break;
                                }
                                break;
                        }
                    } while (!tableroAliado.todosBarcosHundidos());
                }
                break;
            case 3:
                cout << "Saliendo del juego." << endl;
                break;
            default:
                cout << "Opción inválida." << endl;
                break;
        }
    } while (opcion != 3);

    return 0;
}
