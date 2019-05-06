#pragma once
#include "token.h"

typedef struct Nodo* enlace;

struct Nodo {
	int v;
	int pos;
	enlace sig;
	Nodo(int v) : v{ v }, sig{ nullptr }{}
	Nodo(int v, enlace sig) : v{ v }, sig{ sig }{}
};