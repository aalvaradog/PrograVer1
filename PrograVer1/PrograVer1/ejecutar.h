#pragma once
#include <iostream>
#include "lista.h"
#include "token.h"
#include <queue>
#include "tokenizador.h"

using namespace std;

class ejecutar {
	//Token var;
public:
	ejecutar(queue<Token> q, enlaceT &base ) {
		//utilizar un ciclo con un switch adentro que vaya recorriendo la cola y dependiendo del tipo llame a x función
		//algunos tipos quizá no sean necesario crearles una función o quizá ni si quiera haya que tormarlos en cuenta
		Token var;
		while (!q.empty()) {
			switch (q.front().tipo) {
			case 0://variable
				var = q.front();
				q.pop();
				break;
			case 1://asignación
				q.pop();
				break;
			case 3://punto y coma
				q.pop();
				break;
			case 4://numero
				break;
			case 5://siguiente
				avanzar(var, q);
				break;
			case 6://apunta a valor
				apuntarValor(var, q);
				break;
			case 7://crear un nuevo nodo
				crearNodo(var, q);
				break;
			default:
				break;
			}
		}
		if (buscarV(var, base) == false) {
			base = new nodo(var);
		}
	}
	void crearNodo(Token &var, queue<Token> &q) {
		if (q.front().tipo == 7){
			int x = q.front().valor;
			q.pop();
			if (q.front().tipo == 0) {
				Token var2 = q.front();
				q.pop();
				if (q.front().tipo == 5) {
					avanzar(var, q);
				}
				var.elemento = new Nodo(x, q.front().elemento);
			}
			else {
				var.elemento = new Nodo(x);
			}
		}
	}
	void avanzar(Token &var, queue<Token> &q){
		if (q.front().tipo == 5) {
			while (q.front().tipo != 5) {
				var.elemento = var.elemento->sig;
				q.pop();
			}
		}
	}
	int apuntarValor(Token &var, queue<Token> &q) {
		int valor = var.elemento->v;
		q.pop();
		return valor;
	}
	bool buscarV(Token t, enlaceT e) {
		enlaceT base = e;
		while (base) {
			if (base->t.nombre == t.nombre) {
				base->t=t;
				return true;
			}
			else {
				base = base->sig;
			}
		}
		return false;
	}
};
