#pragma once
#define PARCELAS 32
#define SIZELABERINTO PARCELAS*PARCELAS
#include <stdlib.h> // srand, rand
#include <time.h> // time
#include <vector>
#include "tinyptc.h"

#define WIDTH PARCELAS*3*10
#define HEIGHT PARCELAS*3*10
#define ptcSIZE WIDTH*HEIGHT

struct salas{
	int x;
	int y;
};

struct pj {
	int x;
	int y;
	bool sword;
	int hp;
	bool alive;
	bool won;
	int pts;
};

struct enemy {
	int x;
	int y;
};

class Laberinto
{
	int _laberinto[PARCELAS][PARCELAS]; //GENERACION RAPIDA DEL LABERINTO
	int _laberintoTratado[PARCELAS*3][PARCELAS*3]; //LABERINTO TRANSFORMADO A ORGANIZACION MAS COMODA PARA GENERAR EL RENDER Y CONTROLAR POSICIONES
	std::vector<salas> _controlSalas;
	int _pixelPantalla[ptcSIZE];
	pj _personaje;
	std::vector<enemy> _enemies;
	salas _StartSpot;
	bool _gotTreasure;
	
public:
	Laberinto();
	~Laberinto();

	//INIT
	void generar();
	void colocarElemntos();
	void generarEnemigos();
	//

	//RENDER
	void draw();
	void drawEnemies();
	void getPantalla(int (&pixel)[ptcSIZE + (40 * WIDTH)]); //DEJA ESPACIO EN LA PARTE SUPERIOR PARA AÑADIR EL HUD
	void addHUD(int(&pixel)[ptcSIZE + (40 * WIDTH)]);
	//

	//UPDATE
	void moveEnemies();
	void checkEnemyColisions();
	void moverPJ(int dir); //CONTROLA COLISIONES DEL JUGADOR DESPUES DE MOVERLO
	void checkHP();
	//

	bool getAlive() { return _personaje.alive; }
	bool getWon() {	return _personaje.won; }
	int getHP() { return _personaje.hp; }
	int getPTS() { return _personaje.pts; }
};

