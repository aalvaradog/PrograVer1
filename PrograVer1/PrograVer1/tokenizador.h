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
	tokenizador(string entrada, list<Token> base) {
		s = entrada;
		int i = 0;
		string x;
		Token obj;
		while (i < entrada.length()) {
			//validacion para las variables e instrucciones
			//verifica si el string que recibe es una letra y lo va almacenando en una variable para despues crear un objeto de tipo Token
			if (entrada[i] >= 'a' && entrada[i] <= 'z') {
				while (entrada[i] != '-' && entrada[i] != ';' && entrada[i] != '=' && entrada[i] != '(' && entrada[i] != ')' && entrada[i]!=',') {
					x += entrada[i];
					i++;
				}
				if (x == "sig") {
					obj.ciclos += 1;
					tokens.back() = obj;
					x = "";
				}
				else {
					//buscarV averigua si la variable ya fue creada y le asigna a obj el Token correspondiente a la variable
					//sino crea un nuevo Token
					if (buscarV(x, base, obj) == false) {
						obj = Token(x);
					}
					x = "";
					tokens.push(obj);
				}
			}
			//si se encuentra un parantesis quiere decir que el token lleva alguna valor necesario para su creación, ej: new Nodo(int)
			else if (entrada[i] > '0' && entrada[i] <= '9') {
				while (entrada[i] >= '0' && entrada[i] <= '9') {
					x += entrada[i];
					i++;
				}
				obj = Token(x);
				tokens.push(obj);
				x = "";
			}
			//De momento no se ha encontrado una utilidad para el símbolo "->" así que no se incluye en la lista de Tokens
			else if (entrada[i] == '-' || entrada[i] == '>' || entrada[i]==')' || entrada[i]==',' || entrada[i]=='(') {
				//x ="->";
				//Token obj = Token(x);
				//tokens.push(obj);
				i ++;
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
	bool buscarV(string x, list<Token> base, Token &obj) {
		while (base.size()!=0) {
			if (base.front().nombre == x) {
				obj = base.front();
				return true;
			}
			else {
				base.pop_front();
			}
		}
		return false;
	}
};