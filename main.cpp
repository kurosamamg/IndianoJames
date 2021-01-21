#include "Laberinto.h"
#include "ConsoleControl.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>

using namespace std;

void leerPuntuaciones(vector<string> *nombre, vector<string> *pts) {
	fstream file;
	string linea;

	// LLEGIR PUNTUACIONS
	file.open("puntuaciones.pts", ios::in);
	if (file.is_open()) {
		while (getline(file, linea))
		{
			nombre->push_back(linea.substr(0, linea.find(":")));
			pts->push_back(linea.substr(linea.find(":") + 1, linea.size() - linea.find(":")));
		}

		file.close();
	}
	//

}

void saveScore(int pts, string name) {
	vector<string> nombre;
	vector<string> puntos;

	// LLEGIR PUNTUACIONS
	fstream file;
	string linea;
	file.open("puntuaciones.pts", ios::in);
	if (file.is_open()) {
		while (getline(file, linea))
		{
			nombre.push_back(linea.substr(0, linea.find(":")));
			puntos.push_back(linea.substr(linea.find(":") + 1, linea.size() - linea.find(":")));
		}
		file.close();
	}
	//

	//ACTUALITZAR FITXER DE PUNTUACIONS
	ofstream fileOUT;
	fileOUT.open("puntuaciones.pts");
	if (fileOUT.is_open()) {
		if (puntos.size() > 0)
		{
			bool entra = false;
			for (int i = 0; i < puntos.size(); i++)
			{
				if (pts > stoi(puntos[i]) && !entra) { //SI ES MES GRAN ESCRIU LA NOVA PUNTUACIO
					fileOUT << name << ": " << pts << "\n"; entra = true; i--;
				}
				else {
					fileOUT << nombre[i] << ": " << puntos[i] << "\n";
					if (i == puntos.size() - 1 && !entra) //ES LA PUNTUACIO MES PETITA
					{
						fileOUT << name << ": " << pts << "\n";
					}
				}
			}
		}
		else {
			fileOUT << name << ": " << pts << "\n";
		}
		fileOUT.close();
		//

	}
}

int menuPrincipal() {
	int action = 0;
	int select = 1;

	do {
		//JUGAR -> action = 1
		//COMO JUGAR -> action = 2
		//SALIR -> action = 3

		//CONSOLE WIDTH AND HEIGHT //COPIAR Y PEGAR DONDE QUIERA USAR windowColums y windowRows PARA SABER EL TAMAÑO DE LA VENTANA
		//SUELO USARLO PARA CENTRAR TEXTOS
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		int windowColumns, windowRows;

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		windowColumns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		windowRows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

		//

		ConsoleClear();

		//DIBUJAR MENU CON RECUADRO
		ConsoleXY((windowColumns / 2) - 17, (windowRows / 2) - 4);
		cout << "+--------------------------------+";
		ConsoleXY((windowColumns / 2) - 17, (windowRows / 2) - 3);
		cout << "|                                |";
		ConsoleXY((windowColumns / 2) - 17, (windowRows / 2) - 2);
		cout << "|               JUGAR            |";
		ConsoleXY((windowColumns / 2) - 17, (windowRows / 2) - 1);
		cout << "|               PUNTUACIONS      |";
		ConsoleXY((windowColumns / 2) - 17, (windowRows / 2));
		cout << "|               SALIR            |";
		ConsoleXY((windowColumns / 2) - 17, (windowRows / 2) + 1);
		cout << "|                                |";
		ConsoleXY((windowColumns / 2) - 17, (windowRows / 2) + 2);
		cout << "+--------------------------------+";

		//

		switch (select) {
		case 1:
			ConsoleXY((windowColumns / 2) - 7, (windowRows / 2) - 2);
			cout << "--->";
			break;
		case 2:
			ConsoleXY((windowColumns / 2) - 7, (windowRows / 2) - 1);
			cout << "--->";
			break;
		case 3:
			ConsoleXY((windowColumns / 2) - 7, (windowRows / 2));
			cout << "--->";
			break;
		}


		//CAMBIAR SELECCION MEDIANTE TECLADO
		int tecla = 0;
		while (tecla != KB_DOWN && tecla != KB_UP && tecla != KB_ENTER && tecla != KB_ESCAPE)
		{
			tecla = ConsoleInKey();
		}

		if (tecla == KB_DOWN) {
			if (select < 3) select += 1;
			else select = 1;
		}
		else if (tecla == KB_UP) {
			if (select > 1) select -= 1;
			else select = 3;
		}
		else if (tecla == KB_ENTER) {
			action = select;
		}
		else if (tecla == KB_ESCAPE) return 3;

		//
	} while (action == 0);

	return action;
}

void puntuaciones(vector<string> *nombres, vector<string> *pts) {
	leerPuntuaciones(nombres, pts);
}

int main()
{
	vector<string> *ptsNames = new vector<string>();
	vector<string> *ptsMax = new vector<string>();
	srand(time(NULL));
	bool endGame = false, playing = false, howto = false;
	int tecla = 0;
	do {

		//MENU PRINCIPAL [JUGAR - COMO JUGAR - SALIR]
		int menuaction = menuPrincipal(); //RECIBO DE LA FUNCIÓN QUÉ OPCION HE ELEGIDO
		switch (menuaction) {
			case 1:
				playing = true;
				break;
			case 2:
				howto = true;
				break;
			case 3:
				endGame = true;
				break;
			default:
				break;
		}
		//

		if (howto) //MOSTRAR PUNTUACIONS
		{
			//JUGAR -> action = 1
			//COMO JUGAR -> action = 2
			//SALIR -> action = 3

			//CONSOLE WIDTH AND HEIGHT //COPIAR Y PEGAR DONDE QUIERA USAR windowColums y windowRows PARA SABER EL TAMAÑO DE LA VENTANA
			//SUELO USARLO PARA CENTRAR TEXTOS
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			int windowColumns, windowRows;

			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			windowColumns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			windowRows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
			//

			puntuaciones(ptsNames, ptsMax); 
			ConsoleClear();
			for (int i = 0; i < ptsNames->size(); i++) 
			{
				ConsoleXY((windowColumns / 2) - 6, (windowRows / 2) - 5 + i);
				cout << ptsNames->at(i) << ": " << ptsMax->at(i);
				if (i == 9) { //MOSTRA NOMES LES 10 PUNTUACIONS MES ALTES
					i = ptsNames->size() + 1;
				}
			}
			ConsoleSetColor(BLACK, BLACK);
			system("pause");
			ConsoleSetColor(WHITE, BLACK);
			ptsNames->clear();
			ptsMax->clear();
			howto = false;
		}

		if (playing) //OBRIR LABERINT
		{
			//INIT
			int puntosJugador = 0;
			Laberinto * laberinto = new Laberinto();
			laberinto->generar();
			laberinto->colocarElemntos();
			laberinto->generarEnemigos();
			int pixel[ptcSIZE+(40*WIDTH)];
			int tecla = 0;
			if (!ptc_open("Dungeon", WIDTH, HEIGHT + 40)) return 1;
			//

			while (laberinto->getAlive() && tecla != 27 && !laberinto->getWon()) {
				tecla = ptc_keyPress;

				//INPUT
				switch (tecla)
				{
				case 37:
					laberinto->moveEnemies();
					laberinto->moverPJ(4); ptc_keyPress = 0;
					break;
				case 38:
					laberinto->moveEnemies();
					laberinto->moverPJ(1); ptc_keyPress = 0;
					break;
				case 39:
					laberinto->moveEnemies();
					laberinto->moverPJ(2); ptc_keyPress = 0;
					break;
				case 40:
					laberinto->moveEnemies();
					laberinto->moverPJ(3); ptc_keyPress = 0;
					break;
				}
				//

				//UPDATE
				laberinto->checkEnemyColisions();
				laberinto->checkHP();
				//

				//RENDER
				laberinto->draw();
				laberinto->drawEnemies();
				laberinto->getPantalla(pixel);
				laberinto->addHUD(pixel);
				ptc_update(pixel);
				//

				tecla = ptc_keyPress;
				}

			if (laberinto->getWon()) //WON THE GAME CARTEL
			{
				puntosJugador = laberinto->getPTS();
				puntosJugador += laberinto->getHP() * 25;
				tecla = 0; ptc_keyPress = 0;
				do {
					laberinto->draw();
					laberinto->getPantalla(pixel);
					ptc_update(pixel);
					tecla = ptc_keyPress;
				} while (tecla == 0);

			}

			if (!laberinto->getAlive()) //LOST THE GAME (TANCA)
			{
				tecla = 0; ptc_keyPress = 0;
				do {
					laberinto->draw();
					laberinto->getPantalla(pixel);
					ptc_update(pixel);
					tecla = ptc_keyPress;
				} while (tecla == 0);
			}

			
			tecla = 0; ptc_keyPress = 0;
			ptc_close();

			if (laberinto->getWon()) //GUARDAR PUNTUACIO AL GUANYAR
			{
				string nombreJugador;
				ConsoleClear();
				ConsoleXY(5,5);
				cout << "NOMBRE: ";
				cin >> nombreJugador;

				saveScore(puntosJugador, nombreJugador);
			}

			delete laberinto;
			playing = false;
		}

	} while (!endGame);
	delete ptsNames;
	delete ptsMax;
	return 0;
}
