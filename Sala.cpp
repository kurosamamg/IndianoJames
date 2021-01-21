#include "Sala.h"



Sala::Sala()
{
	_visited = false;
	_type = 0;
}


Sala::~Sala()
{
}

void Sala::setType(int d)
{
	switch (d) {
	case 1:
		_type += 1;
		break;
	case 2:
		_type += 2;
		break;
	case 3:
		_type += 4;
		break;
	case 4:
		_type += 8;
		break;

	}
}
