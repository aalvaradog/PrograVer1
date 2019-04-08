#pragma once
#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include "lista.h"

using namespace std;

enum TipoToken {
	variable, asignacion, puntero,
	puntoComa, numero, siguiente, 
	pvalor, crear
};

string vToken[16]{ "->", ";", "=", };

class Token {
public:
	TipoToken tipo;
	int valor = 0;
	string nombre;
	bool ocupada = false;
	enlace elemento;

	//Verifica si el string que recibe esta compuesto �nicamente por n�meros
	static bool todosDigitos(string s) {
		unsigned int i = 0;
		bool ok = true;
		while (i < s.length() && ok) {
			ok = s[i] >= '0' && s[i] <= +'9';
			i++;
		}
		return ok;
	}
	//Verifica si el string que recibe est� compuesto �nicamente por letras
	static bool todosLetras(string s) {
		unsigned int i = 0;
		bool ok = true;
		while (i < s.length() && ok) {
			ok = s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z' || s[i]==' ';
			i++;
		}
		return ok;
	}
	//constructor para declarar variables tipo Token vac�as
	Token() {
	}
	Token(string s) {
		if (s.length() >= 0 && todosDigitos(s)) {
			tipo = numero;
			valor = atoi(s.c_str());
		}
		else {
			if (s.length() > 0 && todosLetras(s)) {
				if (s == "sig") {
					tipo = siguiente;
				}
				else if (s == "v") {
					tipo = pvalor;
				}
				else if (s == "new Nodo") {
					tipo = crear;
				}
				else{
					tipo = variable;
					nombre = s;
				}
			}
			else {
				if (s.length() <= 2) {
					switch (s[0]) {
					case ';':
						tipo = puntoComa;
						break;
					case '=':
						tipo = asignacion;
						break;
					default:
						tipo = puntero;
					}
				}
			}

		}
	}
};

#endif // TOKEN_H
