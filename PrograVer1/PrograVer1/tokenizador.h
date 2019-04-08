#pragma once
#include <iostream>
#include <string>
#include "token.h"
#include <queue>
using namespace std;

class tokenizador {
	string s;
public:
	queue<Token> tokens;
	tokenizador(string entrada) {
		s = entrada;
		int i = 0;
		string x;
		while ( i < entrada.length()) {
			//validacion para las variables e instrucciones
			//verifica si el string que recibe es una letra y lo va almacenando en una variable para despues crear un objeto de tipo Token
			if(entrada[i] >= 'a' && entrada[i] <= 'z') {
				while (entrada[i] != '-' && entrada[i] != ';' & entrada[i] != '=' & entrada[i]!='(') {
					x += entrada[i];
					i++;
				}
				Token obj = Token(x);
				x = "";
				//si se encuentra un parantesis quiere decir que el token lleva alguna valor necesario para su creación, ej: new Nodo(int)
				if (entrada[i] == '(') {
					string y;
					i++;
					while (entrada[i] != ')') {
						y += entrada[i];
						i++;
					}
					obj.valor = atoi(y.c_str());
					i++;
				}
				tokens.push(obj);
			}
			//De momento no se ha encontrado una utilidad para el símbolo "->" así que no se incluye en la lista de Tokens
			else if (entrada[i] == '-' && entrada[i+1] == '>') {
				//x ="->";
				//Token obj = Token(x);
				//tokens.push(obj);
				i += 2;
				x = "";
			}
			else {
				//si se llega a este punto significa que lo que se esta evaluando es un símbolo, la clase token se encarga de averiguar cual es
				x = entrada[i];
				Token obj = Token(x);
				tokens.push(obj);
				x = "";
				i++;
			}
		}
	}
};