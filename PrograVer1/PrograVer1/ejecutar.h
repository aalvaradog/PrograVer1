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
	ejecutar(queue<Token> q, list<Token> &base ) {
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
				avanzar(var);
				break;
			case 6://apunta a valor
				apuntarValor(var, q);
				break;
			case 7://crear un nuevo nodo
				q.pop();
				crearN(var.elemento, var.ciclos, q);
				break;
			default:
				break;
			}
		}
		if (buscarV(var, base) == false) {
			base.push_front(var);
		}
	}
	void crearN(enlace &q, int v, queue<Token> &c) {
		if (c.front().tipo == 4) {
			int x = c.front().valor;
			c.pop();
			if (!q) {
				if (!c.empty() && c.front().tipo == 0) {
					q = new Nodo(x, c.front().elemento);
					c.pop();
				}
				else {
					q = new Nodo(x);
				}
			}
			else {
				enlace p = q;
				while (p->sig && v > 0) {
					p = p->sig;
					v--;
				}
				if (!c.empty() && c.front().tipo == 0) {
					p->sig = new Nodo(x, c.front().elemento);
					c.pop();
				}
				else {
					p->sig = new Nodo(x, p->sig);
				}
			}
		}
		else {
			if (c.front().ciclos != 0) {
				avanzar(c.front());
			}
			int x = c.front().elemento->v;
			c.pop();
			c.pop();
			if (!q) {
				if (!c.empty() && c.front().tipo == 0) {
					q = new Nodo(x, c.front().elemento);
					c.pop();
				}
				else {
					q = new Nodo(x);
				}
			}
			else {
				enlace p = q;
				while (p->sig && v > 0) {
					p = p->sig;
					v--;
				}
				if (!c.empty() && c.front().tipo == 0) {
					p->sig = new Nodo(x, c.front().elemento);
					c.pop();
				}
				else {
					p->sig = new Nodo(x, p->sig);
				}
			}
		}
	}
	void avanzar(Token &p){
		while (p.ciclos != 0) {
			p.elemento = p.elemento->sig;
			p.ciclos--;
		}
	}
	int apuntarValor(Token &var, queue<Token> &q) {
		int valor = var.elemento->v;
		q.pop();
		return valor;
	}
	bool buscarV(Token t, list<Token> &e) {
		list<Token> base = e;
		while (base.size()!=0) {
			if (base.front().nombre == t.nombre) {
				base.front()=t;
				return true;
			}
			else {
				base.pop_front();
			}
		}
		return false;
	}
};
