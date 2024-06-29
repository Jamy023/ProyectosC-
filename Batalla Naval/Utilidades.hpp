#ifndef UTILIDADES_H_
#define UTILIDADES_H_
#include <unistd.h>
#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

const string RESET = "\033[0m";
const string BLUE = "\033[34m";
const string RED = "\033[31m";
const string YELLOW = "\033[33m";

void gotoxy(int x, int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

string convertirANumero(int numero) {
    std::string letra;
    while (numero > 0) {
        int modulo = (numero - 1) % 26;
        letra = char('A' + modulo) + letra;
        numero = (numero - modulo) / 26;
    }
    return letra;
}

int obtenerValorNumerico(char letra) {
    if (letra >= 'A' && letra <= 'Z') {
        return letra - 'A' + 1;
    } else if (letra >= 'a' && letra <= 'z') {
        return letra - 'a' + 1;
    } else {
        return -1;
    }
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawNavalBattle() {
    std::cout << "\t\t\t                           |    |    |" << std::endl;
    std::cout << "\t\t\t                         )_)  )_)  )_)" << std::endl;
    std::cout << "\t\t\t                        )___))___))___)" << std::endl;
    std::cout << "\t\t\t                        )____)____)_____)" << std::endl;
    std::cout << "\t\t\t                      _____|____|____|_____" << std::endl;
    std::cout << "\t\t\t             _______/_______________________\\____" << std::endl;
    std::cout << "\t\t\t  ~~~~~~~~~~ \\ooooooooooooooooooooooooooooooooo/ ~~~~~~~" << std::endl;
    std::cout << "\t\t\t   ~~~~~~~~~~\\________________________________/ ~~~~~~~~" << std::endl;
    std::cout << "\t\t\t                            |    |    |" << std::endl;
    std::cout << "\t\t\t                           )_)  )_)  )_)" << std::endl;
    std::cout << "\t\t\t                          )___))___))___)" << std::endl;
    std::cout << "\t\t\t                         )____)____)_____)" << std::endl;
    std::cout << "\t\t\t                       _____|____|____|_____" << std::endl;
    std::cout << "\t\t\t              _______/_______________________\\____" << std::endl;
    std::cout << "\t\t\t   ~~~~~~~~~~ \\ooooooooooooooooooooooooooooooooo/ ~~~~~~~~~" << std::endl;
    std::cout << "\t\t\t  ~~~~~~~~~~~~ \\________________________________/ ~~~~~~~~~~" << std::endl;
    std::cout << "\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "\t\t\t     ~~~~~~ ~~~~~~~~~~~~ ~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~" << std::endl;
    std::cout << "\t\t\t  ~~~~~~~~~~~ ~~~~~~~~~~~~~ ~~~~~ ~~~~~~~~~~~~ ~~~~~~~~~~~~" << std::endl;
    std::cout << "\t\t\t     ~~~~~~~~~~ ~~~~~~~~ ~~~~~~~~~~~~ ~~~~~~~~~~~~ ~~~~~~~" << std::endl;
    std::cout << "\t\t\t   ~~~~~~~~~~ ~~~~~~~~~~~ ~~~~~~ ~~~~~~~~~~~~ ~~~~~~~~~~~~" << std::endl;
    std::cout << "\t\t\t  ~~~~~~~~ ~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~ ~~~" << std::endl;

    cout<<endl;
    cout<<endl;
    
}

 #endif