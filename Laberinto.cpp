#include "Laberinto.h"

/*
Descripció: Inicialitza l'objecte laberint
Entrada:
Retorna:
*/
Laberinto::Laberinto()
{
	for (int i = 0; i < PARCELAS; i++) {
		for (int j = 0; j < PARCELAS; j++) {
			_laberinto[i][j] = 0;
		}
	}

	for (int i = 0; i < PARCELAS*3; i++) {
		for (int j = 0; j < PARCELAS*3; j++) {
			_laberintoTratado[i][j] = 0;
		}
	}

	_personaje.x = 0;
	_personaje.y = 0;
	_personaje.sword = false;
	_personaje.alive = true;
	_personaje.won = false;
	_personaje.hp = 100;
	_personaje.pts = 0;

	_gotTreasure = false;
}

Laberinto::~Laberinto()
{
}

/*
Descripció: Comproba que la vida del jugador no arribi a 0.
Entrada:
Retorna:
*/
void Laberinto::checkHP()
{
	if (_personaje.hp < 1)
	{
		_personaje.alive = false;
	}
}

/*
Descripció: genera un laberinto aleatorio y lo transforma en un array el triple de grande para poder dibujarlo y calcular colisiones.
Entrada:
Retorna:
*/
void Laberinto::generar()
{
	bool izq = false, der = false, up = false, down = false;
	int controlTotalVisitadas = 1;

	salas positionSalas;

	positionSalas.x = rand() % PARCELAS;
	positionSalas.y = rand() % PARCELAS;

	while (controlTotalVisitadas < SIZELABERINTO) {

		if (!izq || !der || !up || !down)
		{
			int rndDir = rand() % 4 + 1;

			switch (rndDir) {
				case 1: //GO UP
					if (positionSalas.y > 0) {
						if (_laberinto[positionSalas.x][positionSalas.y - 1] == 0) {
							_laberinto[positionSalas.x][positionSalas.y] += 1;
							_laberinto[positionSalas.x][positionSalas.y - 1] += 4;

							_controlSalas.push_back(positionSalas);
							positionSalas.y -= 1;
							controlTotalVisitadas++;
							izq = false; der = false; up = false; down = false;
						}
						else {
							up = true;
						}
					}
					else {
						up = true;
					}
					break;
				case 2: //GO RIGHT
					if (positionSalas.x < PARCELAS - 1) {
						if (_laberinto[positionSalas.x + 1][positionSalas.y] == 0) {
							_laberinto[positionSalas.x][positionSalas.y] += 2;
							_laberinto[positionSalas.x + 1][positionSalas.y] += 8;

							_controlSalas.push_back(positionSalas);
							positionSalas.x += 1;
							controlTotalVisitadas++;
							izq = false; der = false; up = false; down = false;
						}
						else {
							der = true;
						}
					}
					else {
						der = true;
					}
					break;
				case 3:	//GO DOWN
					if (positionSalas.y < PARCELAS - 1) {
						if (_laberinto[positionSalas.x][positionSalas.y + 1] == 0) {
							_laberinto[positionSalas.x][positionSalas.y] += 4;
							_laberinto[positionSalas.x][positionSalas.y + 1] += 1;

							_controlSalas.push_back(positionSalas);
							positionSalas.y += 1;
							controlTotalVisitadas++;
							izq = false; der = false; up = false; down = false;
						}
						else {
							down = true;
						}
					}
					else {
						down = true;
					}
					break;
				case 4: //GO LEFT
					if (positionSalas.x > 0) {
						if (_laberinto[positionSalas.x - 1][positionSalas.y] == 0) {
							_laberinto[positionSalas.x][positionSalas.y] += 8;
							_laberinto[positionSalas.x - 1][positionSalas.y] += 2;

							_controlSalas.push_back(positionSalas);
							positionSalas.x -= 1;
							controlTotalVisitadas++;
							izq = false; der = false; up = false; down = false;
						}
						else {
							izq = true;
						}
					}
					else {
						izq = true;
					}
					break;
			}
		}
		else {
			if (_controlSalas.size() - 1 > 0)
			{
				positionSalas.x = _controlSalas[_controlSalas.size() - 1].x;
				positionSalas.y = _controlSalas[_controlSalas.size() - 1].y;
				_controlSalas.pop_back();
			}

			izq = false; der = false; up = false; down = false;
		}
	}
	
	for (int i = 0; i < PARCELAS; i++)
	{
		for (int j = 0; j < PARCELAS; j++)
		{
			int x = i * 3;
			int y = j * 3;

			switch (_laberinto[i][j]) {
			case 1:
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x][y + l] = 1;
				}
				_laberintoTratado[x + 1][y + 2] = 1;
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x + 2][y + l] = 1;
				}
				break;
			case 2:
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x][y + l] = 1;
				}
				_laberintoTratado[x + 1][y] = 1;
				_laberintoTratado[x + 1][y + 2] = 1;
				_laberintoTratado[x + 2][y] = 1;
				_laberintoTratado[x + 2][y + 2] = 1;
				break;
			case 3:
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x][y + l] = 1;
				}
				_laberintoTratado[x + 1][y + 2] = 1;
				_laberintoTratado[x + 2][y] = 1;
				_laberintoTratado[x + 2][y + 2] = 1;
				break;
			case 4:
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x][y + l] = 1;
				}
				_laberintoTratado[x + 1][y] = 1;
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x + 2][y + l] = 1;
				}
				break;
			case 5:
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x][y + l] = 1;
				}
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x + 2][y + l] = 1;
				}
				break;
			case 6:
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x][y + l] = 1;
				}
				_laberintoTratado[x + 1][y] = 1;
				_laberintoTratado[x + 2][y] = 1;
				_laberintoTratado[x + 2][y + 2] = 1;
				break;
			case 7:
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x][y + l] = 1;
				}
				_laberintoTratado[x + 2][y] = 1;
				_laberintoTratado[x + 2][y + 2] = 1;
				break;
			case 8:
				_laberintoTratado[x][y] = 1;
				_laberintoTratado[x][y + 2] = 1;
				_laberintoTratado[x + 1][y] = 1;
				_laberintoTratado[x + 1][y + 2] = 1;
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x + 2][y + l] = 1;
				}
				break;
			case 9:
				_laberintoTratado[x][y] = 1;
				_laberintoTratado[x][y + 2] = 1;
				_laberintoTratado[x + 1][y + 2] = 1;
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x + 2][y + l] = 1;
				}
				break;
			case 10:
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x + l][y] = 1;
				}
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x + l][y + 2] = 1;
				}
				break;
			case 11:
				_laberintoTratado[x][y] = 1;
				_laberintoTratado[x + 2][y] = 1;
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x + l][y + 2] = 1;
				}
				break;
			case 12:
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x + l][y] = 1;
				}
				_laberintoTratado[x + 2][y + 1] = 1;
				_laberintoTratado[x][y + 2] = 1;
				_laberintoTratado[x + 2][y + 2] = 1;
				break;
			case 13:
				_laberintoTratado[x][y] = 1;
				_laberintoTratado[x + 2][y] = 1;
				_laberintoTratado[x + 2][y + 1] = 1;
				_laberintoTratado[x][y + 2] = 1;
				_laberintoTratado[x + 2][y + 2] = 1;
				break;
			case 14:
				for (int l = 0; l < 3; l++)
				{
					_laberintoTratado[x + l][y] = 1;
				}
				_laberintoTratado[x][y + 2] = 1;
				_laberintoTratado[x + 2][y + 2] = 1;
				break;
			case 15:
				_laberintoTratado[x][y] = 1;
				_laberintoTratado[x + 2][y] = 1;
				_laberintoTratado[x][y + 2] = 1;
				_laberintoTratado[x + 2][y + 2] = 1;
				break;

			}
		}
	}
}

/*
Descripció: llena el array de pixeles de ptc con el laberinto
Entrada:
Retorna:
*/
void Laberinto::draw()
{
	for (int j = PARCELAS*3; j > 0; j--)
	{
		for  (int i = 0; i < PARCELAS*3; i++)
		{
			if (_laberintoTratado[i][j] == 0) {
				for (int p = 0; p < 10; p++)
				{
					for (int x = 0; x < 10; x++)
					{
						if (((j * 10 + p) * WIDTH + (i * 10 + x)) < ptcSIZE)
						{
							_pixelPantalla[(j * 10 + p) * WIDTH + (i * 10 + x)] = 255 * 256 * 256 + 255 * 256 + 255;
						}
					}
				}
			} else if (_laberintoTratado[i][j] == 1) {
				for (int p = 0; p < 10; p++)
				{
					for (int x = 0; x < 10; x++)
					{
						if (((j * 10 + p) * WIDTH + (i * 10 + x)) < ptcSIZE)
						{
							_pixelPantalla[(j * 10 + p) * WIDTH + (i * 10 + x)] = 0 * 256 * 256 + 0 * 256 + 0;
						}
					}
				}
			}
			else if (_laberintoTratado[i][j] == 2) {
				for (int p = 0; p < 10; p++)
				{
					for (int x = 0; x < 10; x++)
					{
						if (((j * 10 + p) * WIDTH + (i * 10 + x)) < ptcSIZE)
						{
							_pixelPantalla[(j * 10 + p) * WIDTH + (i * 10 + x)] = 50 * 256 * 256 + 205 * 256 + 50;
						}
					}
				}
			}
			else if (_laberintoTratado[i][j] == 3) {
				for (int p = 0; p < 10; p++)
				{
					for (int x = 0; x < 10; x++)
					{
						if (((j * 10 + p) * WIDTH + (i * 10 + x)) < ptcSIZE)
						{
							_pixelPantalla[(j * 10 + p) * WIDTH + (i * 10 + x)] = 255 * 256 * 256 + 215 * 256 + 0;
						}
					}
				}
			}
			else if (_laberintoTratado[i][j] == 5) {
				for (int p = 0; p < 10; p++)
				{
					for (int x = 0; x < 10; x++)
					{
						if (((j * 10 + p) * WIDTH + (i * 10 + x)) < ptcSIZE)
						{
							_pixelPantalla[(j * 10 + p) * WIDTH + (i * 10 + x)] = 255 * 256 * 256 + 127 * 256 + 80;
						}
					}
				}
			}
			else if (_laberintoTratado[i][j] == 8) { //ESCALERAS

				if (_gotTreasure)
				{
					for (int p = 0; p < 10; p++)
					{
						for (int x = 0; x < 10; x++)
						{
							if (((j * 10 + p) * WIDTH + (i * 10 + x)) < ptcSIZE)
							{
								_pixelPantalla[(j * 10 + p) * WIDTH + (i * 10 + x)] = 128 * 256 * 256 + 128 * 256 + 128;
							}
						}
					}

					//SPRITE ESCALERAS
					_pixelPantalla[(j * 10 + 1) * WIDTH + (i * 10 + 2)] = 0 * 256 * 256 + 0 * 256 + 0;
					_pixelPantalla[(j * 10 + 1) * WIDTH + (i * 10 + 7)] = 0 * 256 * 256 + 0 * 256 + 0;

					_pixelPantalla[(j * 10 + 3) * WIDTH + (i * 10 + 2)] = 0 * 256 * 256 + 0 * 256 + 0;
					_pixelPantalla[(j * 10 + 3) * WIDTH + (i * 10 + 7)] = 0 * 256 * 256 + 0 * 256 + 0;

					_pixelPantalla[(j * 10 + 5) * WIDTH + (i * 10 + 2)] = 0 * 256 * 256 + 0 * 256 + 0;
					_pixelPantalla[(j * 10 + 5) * WIDTH + (i * 10 + 7)] = 0 * 256 * 256 + 0 * 256 + 0;

					_pixelPantalla[(j * 10 + 7) * WIDTH + (i * 10 + 2)] = 0 * 256 * 256 + 0 * 256 + 0;
					_pixelPantalla[(j * 10 + 7) * WIDTH + (i * 10 + 7)] = 0 * 256 * 256 + 0 * 256 + 0;

					for (int t = 2; t < 7; t++)
					{
						_pixelPantalla[(j * 10 + 2) * WIDTH + (i * 10 + t)] = 0 * 256 * 256 + 0 * 256 + 0;
					}

					for (int t = 2; t < 7; t++)
					{
						_pixelPantalla[(j * 10 + 4) * WIDTH + (i * 10 + t)] = 0 * 256 * 256 + 0 * 256 + 0;
					}

					for (int t = 2; t < 7; t++)
					{
						_pixelPantalla[(j * 10 + 6) * WIDTH + (i * 10 + t)] = 0 * 256 * 256 + 0 * 256 + 0;
					}
					//
				}
				else {
					for (int p = 0; p < 10; p++)
					{
						for (int x = 0; x < 10; x++)
						{
							if (((j * 10 + p) * WIDTH + (i * 10 + x)) < ptcSIZE)
							{
								_pixelPantalla[(j * 10 + p) * WIDTH + (i * 10 + x)] = 255 * 256 * 256 + 255 * 256 + 255;
							}
						}
					}
				}

			}
			else if (_laberintoTratado[i][j] == 9) { //PERSONAJE
				for (int p = 0; p < 10; p++)
				{
					for (int x = 0; x < 10; x++)
					{
						if (((j * 10 + p) * WIDTH + (i * 10 + x)) < ptcSIZE)
						{
							_pixelPantalla[(j * 10 + p) * WIDTH + (i * 10 + x)] = 255 * 256 * 256 + 255 * 256 + 255;
						}
					}
				}

				int colorPlayer = 0 * 256 * 256 + 0 * 256 + 255;

				//SPRITE PERSONAJE
				_pixelPantalla[(j * 10 + 0) * WIDTH + (i * 10 + 4)] = colorPlayer;
				_pixelPantalla[(j * 10 + 0) * WIDTH + (i * 10 + 7)] = colorPlayer;

				_pixelPantalla[(j * 10 + 1) * WIDTH + (i * 10 + 4)] = colorPlayer;
				_pixelPantalla[(j * 10 + 1) * WIDTH + (i * 10 + 7)] = colorPlayer;

				_pixelPantalla[(j * 10 + 2) * WIDTH + (i * 10 + 4)] = colorPlayer;
				_pixelPantalla[(j * 10 + 2) * WIDTH + (i * 10 + 5)] = colorPlayer;
				_pixelPantalla[(j * 10 + 2) * WIDTH + (i * 10 + 6)] = colorPlayer;
				_pixelPantalla[(j * 10 + 2) * WIDTH + (i * 10 + 7)] = colorPlayer;

				_pixelPantalla[(j * 10 + 3) * WIDTH + (i * 10 + 5)] = colorPlayer;
				_pixelPantalla[(j * 10 + 3) * WIDTH + (i * 10 + 6)] = colorPlayer;

				_pixelPantalla[(j * 10 + 4) * WIDTH + (i * 10 + 3)] = colorPlayer;
				_pixelPantalla[(j * 10 + 4) * WIDTH + (i * 10 + 4)] = colorPlayer;
				_pixelPantalla[(j * 10 + 4) * WIDTH + (i * 10 + 5)] = colorPlayer;
				_pixelPantalla[(j * 10 + 4) * WIDTH + (i * 10 + 6)] = colorPlayer;
				_pixelPantalla[(j * 10 + 4) * WIDTH + (i * 10 + 7)] = colorPlayer;
				_pixelPantalla[(j * 10 + 4) * WIDTH + (i * 10 + 8)] = colorPlayer;

				_pixelPantalla[(j * 10 + 5) * WIDTH + (i * 10 + 5)] = colorPlayer;
				_pixelPantalla[(j * 10 + 5) * WIDTH + (i * 10 + 6)] = colorPlayer;

				_pixelPantalla[(j * 10 + 6) * WIDTH + (i * 10 + 4)] = colorPlayer;
				_pixelPantalla[(j * 10 + 6) * WIDTH + (i * 10 + 5)] = colorPlayer;
				_pixelPantalla[(j * 1-0 + 6) * WIDTH + (i * 10 + 6)] = colorPlayer;
				_pixelPantalla[(j * 10 + 6) * WIDTH + (i * 10 + 7)] = colorPlayer;

				_pixelPantalla[(j * 10 + 7) * WIDTH + (i * 10 + 4)] = colorPlayer;
				_pixelPantalla[(j * 10 + 7) * WIDTH + (i * 10 + 5)] = colorPlayer;
				_pixelPantalla[(j * 10 + 7) * WIDTH + (i * 10 + 6)] = colorPlayer;
				_pixelPantalla[(j * 10 + 7) * WIDTH + (i * 10 + 7)] = colorPlayer;

				_pixelPantalla[(j * 10 + 8) * WIDTH + (i * 10 + 5)] = colorPlayer;
				_pixelPantalla[(j * 10 + 8) * WIDTH + (i * 10 + 6)] = colorPlayer;
				//
			}
		}
	}

	if (_personaje.won)
	{
		for (int i = (HEIGHT / 4); i < ((HEIGHT) - HEIGHT / 4); i++)
		{
			for (int j = (WIDTH / 4); j < ((WIDTH) - WIDTH / 4) ; j++)
			{
				_pixelPantalla[i * WIDTH + j] = 128 * 256 * 256 + 128 * 256 + 128;
			}
		}

		//WRITE YOU WON

			int startY = (HEIGHT / 2) + 55;
			int startX = (WIDTH / 2) - 70;

			//DRAW Y

				for (int i = 0; i < 3 * 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - i) * WIDTH + startX + j + 10] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - i) * WIDTH + startX + j + 30] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - 20 - i) * WIDTH + startX + j + 20] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

			//DRAW O

				for (int i = 0; i < 3 * 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - 10 - i) * WIDTH + startX + j + 50] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 3 * 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - 10 - i) * WIDTH + startX + j + 80] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 2 * 10; j++)
					{
						_pixelPantalla[(startY - i) * WIDTH + startX + j + 60] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 2 * 10; j++)
					{
						_pixelPantalla[(startY - i - 40) * WIDTH + startX + j + 60] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

			//DRAW U

				for (int i = 0; i < 5 * 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - i) * WIDTH + startX + j + 100] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 5 * 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - i) * WIDTH + startX + j + 130] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 2 * 10; j++)
					{
						_pixelPantalla[(startY - i - 40) * WIDTH + startX + j + 110] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

			//SET Y
			startY = (HEIGHT / 2) - 10;

			//DRAW W
				
				for (int i = 0; i < 4 * 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - i) * WIDTH + startX + j] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 4 * 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - i) * WIDTH + startX + j + 40] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - i - 40) * WIDTH + startX + j + 10] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - i - 40) * WIDTH + startX + j + 30] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - i - 30) * WIDTH + startX + j + 20] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

			//DRAW O

				for (int i = 0; i < 3 * 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - 10 - i) * WIDTH + startX + j + 60] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 3 * 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - 10 - i) * WIDTH + startX + j + 90] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 2 * 10; j++)
					{
						_pixelPantalla[(startY - i) * WIDTH + startX + j + 70] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 2 * 10; j++)
					{
						_pixelPantalla[(startY - i - 40) * WIDTH + startX + j + 70] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

			//DRAW N

				for (int i = 0; i < 5 * 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - i) * WIDTH + startX + j + 110] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 5 * 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - i) * WIDTH + startX + j + 140] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - i - 10) * WIDTH + startX + j + 120] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						_pixelPantalla[(startY - i - 20) * WIDTH + startX + j + 130] = 0 * 256 * 256 + 0 * 256 + 0;
					}
				}
	}
}

/*
Descripció: Afegeix l'Sprite de cada enemic a la posicio adecuada dins l'array del frame actual.
Entrada:
Retorna:
*/
void Laberinto::drawEnemies()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		//SPRITE ENEMIGO
		_pixelPantalla[(_enemies[i].y * 10 + 0) * WIDTH + (_enemies[i].x * 10 + 4)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 0) * WIDTH + (_enemies[i].x * 10 + 7)] = 255 * 256 * 256 + 0 * 256 + 0;

		_pixelPantalla[(_enemies[i].y * 10 + 1) * WIDTH + (_enemies[i].x * 10 + 4)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 1) * WIDTH + (_enemies[i].x * 10 + 7)] = 255 * 256 * 256 + 0 * 256 + 0;

		_pixelPantalla[(_enemies[i].y * 10 + 2) * WIDTH + (_enemies[i].x * 10 + 4)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 2) * WIDTH + (_enemies[i].x * 10 + 5)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 2) * WIDTH + (_enemies[i].x * 10 + 6)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 2) * WIDTH + (_enemies[i].x * 10 + 7)] = 255 * 256 * 256 + 0 * 256 + 0;

		_pixelPantalla[(_enemies[i].y * 10 + 3) * WIDTH + (_enemies[i].x * 10 + 5)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 3) * WIDTH + (_enemies[i].x * 10 + 6)] = 255 * 256 * 256 + 0 * 256 + 0;

		_pixelPantalla[(_enemies[i].y * 10 + 4) * WIDTH + (_enemies[i].x * 10 + 3)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 4) * WIDTH + (_enemies[i].x * 10 + 4)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 4) * WIDTH + (_enemies[i].x * 10 + 5)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 4) * WIDTH + (_enemies[i].x * 10 + 6)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 4) * WIDTH + (_enemies[i].x * 10 + 7)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 4) * WIDTH + (_enemies[i].x * 10 + 8)] = 255 * 256 * 256 + 0 * 256 + 0;

		_pixelPantalla[(_enemies[i].y * 10 + 5) * WIDTH + (_enemies[i].x * 10 + 5)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 5) * WIDTH + (_enemies[i].x * 10 + 6)] = 255 * 256 * 256 + 0 * 256 + 0;

		_pixelPantalla[(_enemies[i].y * 10 + 6) * WIDTH + (_enemies[i].x * 10 + 4)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 6) * WIDTH + (_enemies[i].x * 10 + 5)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 6) * WIDTH + (_enemies[i].x * 10 + 6)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 6) * WIDTH + (_enemies[i].x * 10 + 7)] = 255 * 256 * 256 + 0 * 256 + 0;

		_pixelPantalla[(_enemies[i].y * 10 + 7) * WIDTH + (_enemies[i].x * 10 + 4)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 7) * WIDTH + (_enemies[i].x * 10 + 5)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 7) * WIDTH + (_enemies[i].x * 10 + 6)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 7) * WIDTH + (_enemies[i].x * 10 + 7)] = 255 * 256 * 256 + 0 * 256 + 0;

		_pixelPantalla[(_enemies[i].y * 10 + 8) * WIDTH + (_enemies[i].x * 10 + 5)] = 255 * 256 * 256 + 0 * 256 + 0;
		_pixelPantalla[(_enemies[i].y * 10 + 8) * WIDTH + (_enemies[i].x * 10 + 6)] = 255 * 256 * 256 + 0 * 256 + 0;
		//
	}
}

/*
Descripció: omple l'array amb tot el que toca mostrar al frame actual
Entrada: Array de pixels que es mostraran per pantalla
Retorna:
*/
void Laberinto::getPantalla(int (&pixel)[ptcSIZE + (40 * WIDTH)])
{
	for (int i = 0; i < ptcSIZE; i++)
	{
		pixel[i] = _pixelPantalla[i];
	}
}

/*
Descripció: Afegeix el HUD apropiat per al frame actual
Entrada: Array de pixels que es mostraran per pantalla
Retorna:
*/
void Laberinto::addHUD(int(&pixel)[ptcSIZE + (40 * WIDTH)])
{
	//LIMPIA ESPACIO DEL HUD
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			pixel[(HEIGHT + 39 - j) * WIDTH + i] = 0;
		}
	}

	//BARRA DE VIDA
	int color = 0;
	if (_personaje.hp > 75)
	{
		color = 255 * 256;
	} else if (_personaje.hp > 30)
	{
		color = 255 * 256 * 256 + 127 * 256 + 80;
	} else
	{
		color = 255 * 256 * 256;
	}

	for (int i = 0; i < (_personaje.hp*1.5); i++)
	{
		for (int j = 0; j < 20; j++)
		{
			pixel[(HEIGHT + 10 + j) * WIDTH + (i + 10)] = color;
		}
	}

	//ICONOS DE FEEDBACK -- ESPADA
	if (_personaje.sword)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				pixel[(HEIGHT + 10 + j) * WIDTH + (i + WIDTH - 30)] = 255 * 256;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			pixel[(HEIGHT + 27) * WIDTH + (i + WIDTH - 14)] = 0;
		}

		int offsetX = 15;
		int offsetY = 0;

		while (offsetY < 11) {
			for (int i = 0; i < 4; i++)
			{
				pixel[(HEIGHT + 26 - offsetY) * WIDTH + ((i*2) + WIDTH - offsetX)] = 0; offsetX++;
			}
			offsetY++;
			offsetX -= 3;
		}

		for (int i = 0; i < 3; i++)
		{
			pixel[(HEIGHT + 16) * WIDTH + (i + WIDTH - 25)] = 0;
		}

		for (int i = 0; i < 4; i++)
		{
			pixel[(HEIGHT + 15) * WIDTH + (i + WIDTH - 27)] = 0;
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				pixel[(HEIGHT + 14 - j) * WIDTH + (i + WIDTH - 27)] = 0;
			}
		}

		offsetX = 0;
		for (int j = 0; j < 7; j++)
		{
			for (int i = 0; i < 2; i++)
			{
				pixel[(HEIGHT + 21 - j) * WIDTH + (i + WIDTH - 26 + offsetX)] = 0;
			}
			offsetX++;
		}
		pixel[(HEIGHT + 14) * WIDTH + (WIDTH - 27 + offsetX)] = 0;

		for (int i = 0; i < 20; i++)
		{
			pixel[(HEIGHT + 30) * WIDTH + (WIDTH - 30 + i)] = 255*256*256 + 255*256 + 255;
		}

		for (int i = 0; i < 20; i++)
		{
			pixel[(HEIGHT + 10) * WIDTH + (WIDTH - 30 + i)] = 255 * 256 * 256 + 255 * 256 + 255;
		}

		for (int i = 0; i < 20; i++)
		{
			pixel[(HEIGHT + 30 - i) * WIDTH + (WIDTH - 30)] = 255 * 256 * 256 + 255 * 256 + 255;
		}

		for (int i = 0; i < 20; i++)
		{
			pixel[(HEIGHT + 30 - i) * WIDTH + (WIDTH - 10)] = 255 * 256 * 256 + 255 * 256 + 255;
		}

	}
}

/*
Descripció: coloca un tesoro, varias espadas y comida en el laberinto. Finalmente coloca el personaje en la posicion inicial.
Entrada:
Retorna:
*/
void Laberinto::colocarElemntos()
{
	//ESPADAS
	int ok = 0;
	int randX, randY;
	while (ok < PARCELAS / 2) {
		randX = rand() % PARCELAS;
		randY = rand() % PARCELAS;

		if (_laberinto[randX][randY] == 1 || _laberinto[randX][randY] == 2 || _laberinto[randX][randY] == 4 || _laberinto[randX][randY] == 8) {
			_laberintoTratado[randX*3 + 1][randY*3 + 1] = 2;
			ok++;
		}
	}

	//TESORO
	ok = 0;
	while (ok < 1) {
		randX = rand() % PARCELAS;
		randY = rand() % PARCELAS;

		if (_laberinto[randX][randY] == 1 || _laberinto[randX][randY] == 2 || _laberinto[randX][randY] == 4 || _laberinto[randX][randY] == 8) {
			_laberintoTratado[randX * 3 + 1][randY * 3 + 1] = 3;
			ok++;
		}
	}

	//COMIDA
	ok = 0;
	while (ok < (PARCELAS * 3)) {
		randX = rand() % (PARCELAS * 3);
		randY = rand() % (PARCELAS * 3);

		bool okX = false, okY = false;

		if (((randX - 1) % 3 == 0)) okX = true;
		if (((randY - 1) % 3 == 0)) okY = true;

		if (_laberintoTratado[randX][randY] == 1 && (okX || okY))
		{
			_laberintoTratado[randX][randY] = 5;
			ok++;
		}

	}

	randX = rand() % PARCELAS;
	randY = rand() % PARCELAS;
	_laberintoTratado[randX * 3 + 1][randY * 3 + 1] = 9;
	_personaje.x = randX;
	_personaje.y = randY;
	_StartSpot.x = randX;
	_StartSpot.y = randY;
}

/*
Descripció: Genera un numero de enemigos apropiado para el nivel.
Entrada:
Retorna:
*/
void Laberinto::generarEnemigos()
{
	int numEnemies = PARCELAS / 3;

	for (int i = 0; i < numEnemies; i++)
	{
		enemy tmpEnemy;
		bool playerEqual = false;
		bool transitable = false;
		do
		{
			tmpEnemy.x = rand() % (PARCELAS * 3);
			tmpEnemy.y = rand() % (PARCELAS * 3);

			if (_laberintoTratado[tmpEnemy.x][tmpEnemy.y] == 0) { 
				transitable = true; 
			} else transitable = false;

			if (((tmpEnemy.x / 3) == _personaje.x) && ((tmpEnemy.y / 3) == _personaje.y)) playerEqual = true;
			else playerEqual = false;

		} while (playerEqual || !transitable);
		_enemies.push_back(tmpEnemy);
	}

}

/*
Descripció: Intenta moure els enemics a una posicio aleatoria.
Entrada:
Retorna:
*/
void Laberinto::moveEnemies()
{
	bool izq = false, der = false, up = false, down = false;
	for (int i = 0; i < _enemies.size(); i++)
	{
		int dir;
		bool done = false;

		while (!done)
		{
			dir = rand() % 4 + 1;
			if (izq && der && up && down)
			{
				dir = 5;
			}
			switch (dir)
			{
			default:
				done = true;
				break;
			case 1: //UP
				if (!up)
				{
					if (_enemies[i].y < PARCELAS * 3 - 2)
					{
						if (_laberintoTratado[_enemies[i].x][_enemies[i].y + 1] == 0) //puede ir arriba?
						{
							_enemies[i].y++;
							done = true;
						} else {
							up = true;
						}
					} else {
						up = true;
					}
				}
				break;
			case 2: //DERECHA
				if (!der)
				{
					if (_enemies[i].x < PARCELAS * 3 - 2)
					{
						if (_laberintoTratado[_enemies[i].x + 1][_enemies[i].y] == 0) //puede ir a la derecha?
						{
							_enemies[i].x++;
							done = true;
						}
						else {
							der = true;
						}
					}
					else {
						der = true;
					}
				}
				break;
			case 3: //DOWN
				if (!down)
				{
					if (_enemies[i].y > 1)
					{
						if (_laberintoTratado[_enemies[i].x][_enemies[i].y - 1] == 0) //puede ir abajo?
						{
							_enemies[i].y--;
							done = true;
						}
						else {
							down = true;
						}
					}
					else {
						down = true;
					}
				}
				break;
			case 4: //LEFT
				if (!izq)
				{
					if (_enemies[i].x > 1)
					{
						if (_laberintoTratado[_enemies[i].x - 1][_enemies[i].y] == 0) //puede ir abajo?
						{
							_enemies[i].x--;
							done = true;
						}
						else {
							izq = true;
						}
					}
					else {
						izq = true;
					}
				}
				break;
			}
		}
	}
}

/*
Descripció: Comproba les colisions dels enemics amb el jugador.
Entrada:
Retorna:
*/
void Laberinto::checkEnemyColisions()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		bool playerEqual = false;
		if (((_enemies[i].x / 3) == _personaje.x) && ((_enemies[i].y / 3) == _personaje.y)) playerEqual = true;
		else playerEqual = false;

		if (playerEqual) {
			if (_personaje.sword == true)
			{
				_enemies.erase(_enemies.begin() + i); i--;
				_personaje.sword = false;
			} else {
				_personaje.alive = false;
			}
		}
	}
}

/*
Descripció: Intenta moure el jugador en la direccio adequada i controla las colisiones con el entorno (Comida, espadas, tesoro...)
Entrada: direccion (1-UP 2-RIGHT 3-DOWN 4-LEFT)
Retorna:
*/
void Laberinto::moverPJ(int dir)
{
	switch (dir) {
	case 1:
 		if (_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 2] == 5) //comida
		{
			if (_personaje.hp < 75)
			{
				_personaje.hp += 25;
			}
			else {
				_personaje.hp = 100;
			}
			_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 2] = 1;
		}
		if (_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 2] == 0) //se puede mover
		{

			if (_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 4] == 2) //HITS SWORD ON MOVE
			{
				_personaje.sword = true;
				_personaje.pts += 15;
			}
			else if (_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 4] == 3) { //HITS TREASURE ON MOVE
				_gotTreasure = true;
				_personaje.pts += 25 * (_personaje.hp / 20);
			}
			else if (_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 4] == 8 && _gotTreasure) {
				_personaje.won = true;
				_personaje.pts += ((PARCELAS / 3) - _enemies.size()) * 20;
			}

			_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 1] = 0;
			_personaje.y++; _personaje.hp--;
			_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 1] = 9;
		}
		break;
	case 2:
		if (_laberintoTratado[_personaje.x * 3 + 2][_personaje.y * 3 + 1] == 5)
		{
			if (_personaje.hp < 75)
			{
				_personaje.hp += 25;
			}
			else {
				_personaje.hp = 100;
			}
			_laberintoTratado[_personaje.x * 3 + 2][_personaje.y * 3 + 1] = 1;
		}
		if (_laberintoTratado[_personaje.x * 3 + 2][_personaje.y * 3 + 1] == 0)
		{
			if (_laberintoTratado[_personaje.x * 3 + 4][_personaje.y * 3 + 1] == 2) //HITS SWORD ON MOVE
			{
				_personaje.sword = true;
				_personaje.pts += 15;
			}
			else if (_laberintoTratado[_personaje.x * 3 + 4][_personaje.y * 3 + 1] == 3) { //HITS TREASURE ON MOVE
				_gotTreasure = true;
				_personaje.pts += 25 * (_personaje.hp / 20);
			}
			else if (_laberintoTratado[_personaje.x * 3 + 4][_personaje.y * 3 + 1] == 8 && _gotTreasure) {
				_personaje.won = true;
				_personaje.pts += ((PARCELAS / 3) - _enemies.size()) * 20;
			}

			_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 1] = 0;
			_personaje.x++; _personaje.hp--;
			_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 1] = 9;
		}
		break;
	case 3:
		if (_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3] == 5)
		{
			if (_personaje.hp < 75)
			{
				_personaje.hp += 25;
			}
			else {
				_personaje.hp = 100;
			}
			_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3] = 1;
		}
		if (_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3] == 0)
		{
			if (_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 - 2] == 2) //HITS SWORD ON MOVE
			{
				_personaje.sword = true;
				_personaje.pts += 15;
			}
			else if (_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 - 2] == 3) { //HITS TREASURE ON MOVE
				_gotTreasure = true;
				_personaje.pts += 25 * (_personaje.hp / 20);
			}
			else if (_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 - 2] == 8 && _gotTreasure) {
				_personaje.won = true;
				_personaje.pts += ((PARCELAS / 3) - _enemies.size()) * 20;
			}

			_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 1] = 0;
			_personaje.y--; _personaje.hp--;
			_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 1] = 9;
		}
		break;
	case 4:
		if (_laberintoTratado[_personaje.x * 3][_personaje.y * 3 + 1] == 5)
		{
			if (_personaje.hp < 75)
			{
				_personaje.hp += 25;
			}
			else {
				_personaje.hp = 100;
			}
			_laberintoTratado[_personaje.x * 3][_personaje.y * 3 + 1] = 1;
		}
		if (_laberintoTratado[_personaje.x * 3][_personaje.y * 3 + 1] == 0)
		{
			if (_laberintoTratado[_personaje.x * 3 - 2][_personaje.y * 3 + 1] == 2) //HITS SWORD ON MOVE
			{
				_personaje.sword = true;
				_personaje.pts += 15;
			}
			else if (_laberintoTratado[_personaje.x * 3 - 2][_personaje.y * 3 + 1] == 3) { //HITS TREASURE ON MOVE
				_gotTreasure = true;
				_personaje.pts += 25 * (_personaje.hp / 20);
				_personaje.pts += ((PARCELAS / 3) - _enemies.size()) * 20;
			}
			else if (_laberintoTratado[_personaje.x * 3 - 2][_personaje.y * 3 + 1] == 8 && _gotTreasure) {
				_personaje.won = true;
			}

			_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 1] = 0;
			_personaje.x--; _personaje.hp--;
			_laberintoTratado[_personaje.x * 3 + 1][_personaje.y * 3 + 1] = 9;
		}
		break;
	}

	if (_personaje.y != _StartSpot.y && _personaje.x != _StartSpot.x)
	{
		_laberintoTratado[_StartSpot.x * 3 + 1][_StartSpot.y * 3 + 1] = 8;
	}
}

