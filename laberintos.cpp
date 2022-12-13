#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <list>

#define filas 19    // Define posicion en Y
#define columnas 95 // Define posicion en X

using namespace std;

void ShowConsoleCursor(bool showFlag);

enum Direc
{
    IZQUIERDA,
    DERECHA,
    ARRIBA,
    ABAJO
};

void gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

class Jugador
{
private:
    int posX;
    int posY;
    char imagen = 220;

public:
    Direc direccion;
    Jugador()
    {
        this->posY = 1;
        this->posX = 1;
    }
    int getPosX()
    {
        return this->posX;
    }
    int getPosY()
    {
        return this->posY;
    }
    char getImagen()
    {
        return this->imagen;
    }
    void move()
    {
        switch (direccion)
        {
        case ARRIBA:
            this->posY--;
            break;
        case IZQUIERDA:
            posX = posX - 1;
            break;
        case ABAJO:
            this->posY++;
            break;
        case DERECHA:
            posX = posX + 1;
            break;
        }
    }
};

class Salida
{
private:
    int posX;
    int posY;
    char imagen = 219;

public:
    Salida(int Y, int X)
    {
        this->posY = Y;
        this->posX = X;
    }
    int getPosX()
    {
        return this->posX;
    }
    int getPosY()
    {
        return this->posY;
    }
};

class Juego
{
public:
    int killSwitch = 0; // KillSwitch general del juego
    int fin = 0;        // KillSwitch para la detección de teclas
    clock_t comienzoPrograma,finPrograma; //Timestamps donde se guarda el comienzo del juego y el final
    Jugador jugador;
    list<Salida> listaSalidas;

    Juego()
    {
        system("CLS");
        cout << "Inicio del menu";
        for (int i = 0; i < 3; i++)
        {
            Sleep(500);
            cout << " .";
        }
        Sleep(1000);
    }

    void setup()
    {
        char tecla = ' ';

        system("CLS");
        // Creacion del mapa con limites
        char Matriz[filas][columnas] = {
            "##############################################################################################",
            "#           #     #     #  #        #  #  #           #     #     #                          #",
            "#  #  ####  ####  #  ####  #  ####  #  #  #  #  #  #  #  #  #  #  #  ###################  ####",
            "#  #  #  #        #           #        #     #  #  #     #  #  #     #        #        #  #  #",
            "####  #  ####  ################  #  #  #  ################  #######  #  ####  #  #######  #  #",
            "#  #     #     #                 #  #        #  #     #  #  #  #              #  #           #",
            "#  #  #  #############  #######  #  ####  ####  #  #  #  #  #  #  #  #######  #  ##########  #",
            "#  #  #  #  #  #     #     #  #  #  #        #  #  #  #     #     #        #              #  #",
            "#  #  ####  #  #  #######  #  ##########  #  #  #  ####  ####  #######  #  ####  ####  ####  #",
            "#  #                    #  #        #     #  #  #  #              #  #  #     ####     #     #",
            "#  #  #############  #  #  #  #  #######  #  #  #  #  #############  ####  ####  ####  #######",
            "#     #              #     #  #        #  #  #        #                       #              #",
            "#  #  #  ###################  #  #######  #  ##########  ##########  ####  ####  #  ####  ####",
            "#  #     #     #     #        #  #        #  #  #  #  #  #              #  #     #  #  #  #  #",
            "##########  #######  #######  #  #  #######  #  #  #  ####  ####  #  ####  ####  ####  ####  #",
            "#     #  #        #        #  #        #  #              #  #  #  #  #     #     #  #     #  #",
            "####  #  #######  #  ####  #  ##########  #  ####  ####  #  #  #  #  #######  ####  ####  #  #",
            "#                       #              #        #  #        #     #  #                        ",
            "##############################################################################################"};

        while (tecla < 49 || tecla > 51)
        {
            system("CLS");
            cout << " _____                                _      _   _       _               _       _        " << endl;
            cout << "|  ___|                              | |    | | | |     | |             (_)     | |       " << endl;
            cout << "| |__ ___  ___ __ _ _ __   __ _    __| | ___| | | | __ _| |__   ___ _ __ _ _ __ | |_ ___  " << endl;
            cout << "|  __/ __|/ __/ _` | '_ L / _` |  / _` |/ _ L | | |/ _` | '_ L / _ L '__| | '_ L| __/ _ L " << endl;
            cout << "| |__L__ L (_| (_| | |_) | (_| | | (_| |  __/ | | | (_| | |_) |  __/ |  | | | | | || (_) |" << endl;
            cout << "L____/___/L___L__,_| .__/ L__,_|  L__,_|L___|_| |_|L__,_|_.__/ L___|_|  |_|_| |_|L__L___/ " << endl;
            cout << "                   | |                                                                    " << endl;
            cout << "                   |_|         " << endl;
            cout << "Principios de juego:" << endl << endl;
            cout << "El jugador tendra que recorrer el laberinto con la presencia de una o mas salidas de color amarillo" << endl;
            cout << "a las cuales debera entrar en contacto para escapar." << endl;
            cout << "Controles:" << endl;
            cout << "W = Moverse hacia arriba" << endl;
            cout << "A = Moverse hacia la izquierda" << endl;
            cout << "D = Moverse hacia la derecha" << endl;
            cout << "S = Moverse hacia abajo" << endl << endl;
            cout << "Escriba la cantidad de salidas que desea: (1-3)" << endl;
            tecla = getch();
            if (tecla == '1')
            {
                Salida salida1 = Salida(93, 17);
                listaSalidas.push_back(salida1);
            }
            else if (tecla == '2')
            {
                Salida salida1 = Salida(14, 13);
                listaSalidas.push_back(salida1);
                Salida salida2 = Salida(46, 5);
                listaSalidas.push_back(salida2);
                
            }
            else if (tecla == '3')
            {
                Salida salida1 = Salida(93, 17);
                listaSalidas.push_back(salida1);
                Salida salida2 = Salida(46, 5);
                listaSalidas.push_back(salida2);
                Salida salida3 = Salida(14, 13);
                listaSalidas.push_back(salida3);
            }
            cout << tecla;
            Sleep(500);
        }

        // COMIENZO DEL JUEGO
        inicio(Matriz, killSwitch, jugador, listaSalidas);
    }

    void inicio(char Matriz[filas][columnas], int killSwitch, Jugador jugador, list<Salida> listaSalidas)
    {
        int contadorAuxiliar = 0;
        int Xprevio, Yprevio;

        list<Salida>::iterator lit;
        lit = listaSalidas.begin();
        while (lit != listaSalidas.end())
        {
            Matriz[lit->getPosX()][lit->getPosY()]='X';
            lit++;
        }

        printMapa(Matriz);
        comienzoPrograma = time(NULL);

        while (killSwitch != 1)
        {
            Sleep(150); // Velocidad de movimiento de jugador 

            // JUGADOR movimiento + coliciones //
            if (!colisionParedes(Matriz, jugador))
            {
                jugador.move();
                if (fin)
                {
                    break;
                }
            }

            // Este if con contadorAuxiliar está hecho para que no se borre lo que está en el comienzo del mapa (Coords iniciales de Xprevio y Yprevio)
            if (contadorAuxiliar == 1)
            {
                gotoxy(Xprevio, Yprevio);
                cout << " "; // Borrar la imagen previa del jugador
            }
            else
            {
                contadorAuxiliar++;
            }

            // Dibujar la imagen del jugador
            gotoxy(jugador.getPosX(), jugador.getPosY());
            cout << "\033[32m" << jugador.getImagen();
            Xprevio = jugador.getPosX();
            Yprevio = jugador.getPosY();
            // FIN JUGADOR //

            // Salida //
            // Dibujar la imagen de las Salidas

            /*---------------- DETECCION DE TECLAS ------------------------*/

            if (_kbhit())
            {
                switch (_getch())
                {
                case 'a':
                    jugador.direccion = IZQUIERDA;
                    break;
                case 'd':
                    jugador.direccion = DERECHA;
                    break;
                case 'w':
                    jugador.direccion = ARRIBA;
                    break;
                case 's':
                    jugador.direccion = ABAJO;
                    break;
                case 'x':
                    killSwitch = 1;
                    break;
                }
            }
        }
    }

    bool colisionParedes(char v[filas][columnas], Jugador jugador)
    {
        if (
            jugador.direccion == ARRIBA && v[jugador.getPosY() - 1][jugador.getPosX()] == '#' ||
            jugador.direccion == DERECHA && v[jugador.getPosY()][jugador.getPosX() + 1] == '#' ||
            jugador.direccion == IZQUIERDA && v[jugador.getPosY()][jugador.getPosX() - 1] == '#' ||
            jugador.direccion == ABAJO && v[jugador.getPosY() + 1][jugador.getPosX()] == '#')
        {
            return true;
        }
        else if (
            jugador.direccion == DERECHA && v[jugador.getPosY()][jugador.getPosX() + 1] == 'X' ||
            jugador.direccion == ARRIBA && v[jugador.getPosY()-1][jugador.getPosX()] == 'X' ||
            jugador.direccion == IZQUIERDA && v[jugador.getPosY()][jugador.getPosX()-1] == 'X')
        {
            fin = 1;
            Sleep(1000);
            victoria(comienzoPrograma,finPrograma);
        }
        else
        {
            return false;
        }
    }

    void victoria(clock_t comienzoPrograma,clock_t finPrograma)
    {
        finPrograma = time(NULL);
        system("CLS");
        cout<<"  ______       _                     _                                                                    _       _ "<<endl;
        cout<<" |  ____|     | |                   | |                                                                  | |     | |"<<endl;
        cout<<" | |__   _ __ | |__   ___  _ __ __ _| |__  _   _  ___ _ __   __ _      ___  ___  ___ __ _ _ __   __ _ ___| |_ ___| |"<<endl;
        cout<<" |  __| | '_ L| '_ L / _ L| '__/ _` | '_ L| | | |/ _ L '_ L / _` |    / _ L/ __|/ __/ _` | '_ L / _` / __| __/ _ L |"<<endl;
        cout<<" | |____| | | | | | | (_) | | | (_| | |_) | |_| |  __/ | | | (_| |_  |  __/L__ L (_| (_| | |_) | (_| L__ L ||  __/_|"<<endl;
        cout<<" |______|_| |_|_| |_|L___/|_|  L__,_|_.__/ L__,_|L___|_| |_|L__,_( )  L___||___/L___L__,_| .__/ L__,_|___/L__L___(_)"<<endl;
        cout<<"                                                                 |/                      | |                        "<<endl;
        cout<<"                                                                                         |_|                        "<<endl;
        cout<<endl<<endl<<"Escapaste en "<<(finPrograma-comienzoPrograma)<<" segundos";
    }

    void printMapa(char v[filas][columnas])
    {
        system("CLS");
        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                if (v[i][j] == '#')
                {
                    cout << char(219);
                }
                else if (v[i][j] == 'X')
                {
                    cout << "\033[33m" << char(219) << "\033[0m";
                }
                else
                {
                    cout << v[i][j];
                }
            }
            cout << endl;
        }
    }
};

// Eliminar el cursor de el exe para que no se vea afectado visualmente el movimiento del jugador
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int main()
{
    ShowConsoleCursor(false);
    Juego juego;
    juego.setup();
    return 0;
}
