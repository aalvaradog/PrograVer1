#pragma once
#include "token.h"

typedef struct Nodo* enlace;

struct Nodo {
	int v;
	enlace sig;
	Nodo(int v) : v{ v }, sig{ nullptr }{}
	Nodo(int v, enlace sig) : v{ v }, sig{ sig }{}
};

typedef struct nodo* enlaceT;

struct nodo {
	Token t;
	enlaceT sig;
	nodo(Token t) : t{ t }, sig{ nullptr }{}
	nodo(Token t, enlaceT sig) : t{ t }, sig{ sig }{}
};