#pragma once
#include <iostream>
#include "lista.h"
#include "token.h"
#include <queue>
#include "tokenizador.h"

using namespace std;

class ejecutar {
public:
	ejecutar(queue<Token> entrada, list<Token> &l ) {
		procesarTokens(entrada, l);
	}
	void procesarTokens(queue<Token> q, list<Token> &base) {
		//utilizar un ciclo con un switch adentro que vaya recorriendo la cola y dependiendo del tipo llame a x función
		//algunos tipos quizá no sean necesario crearles una función o quizá ni si quiera haya que tormarlos en cuenta
		Token var;
		bool asignar = false;
		while (!q.empty()) {
			switch (q.front().tipo) {
			case 0://variable
				if (asignar == false) {
					if (buscarV(q.front(), base, var) == false) {
						var = q.front();
					}
					q.pop();
				}
				else {
					if (buscarV(q.front(), base, q.front()) == false) {
					}
					asignacion(var, q);
					guardar(var, base);
				}
				break;
			case 1://asignación
				asignar = true;
				q.pop();
				break;
			case 3://punto y coma
				asignar = false;
				q.pop();
				break;
			case 4://numero
				asigNum(var, q.front().valor);
				q.pop();
				guardar(var, base);
				break;
			case 5://siguiente
				avanzar(var);
				break;
			case 6://apunta a valor
				//apuntarValor(var, q);
				if (q.size() <= 2 && asignar == false) {
					retornarV(var);
				}
				q.pop();
				break;
			case 7://crear un nuevo nodo
				q.pop();
				crearN(var.elemento, var.ciclos, q);
				var.ciclos = 0;
				guardar(var, base);
				break;
			case 9:
				q.pop();
				fWhile(q, base);
				break;
			case 10:
				q.pop();
				repetidor(q, base);
				break;
			case 11:
				q.pop();
				borrar(var);
				guardar(var, base);
			default:
				break;
			}
		}
	}
	void borrar(Token &t) {
		if (t.ciclos == 0) {
			t.elemento = NULL;
		}
		else {
			enlace p = t.elemento;
			enlace q;
			while (t.ciclos-1 != 0) {
				p = p->sig;
			}
			t.ciclos = 0;
			if (p->sig->sig != NULL) {
				q = p->sig;
				p->sig = p->sig->sig;
				delete q;
			}
			else {
				q = p->sig;
				p->sig = NULL;
				delete q;
			}
		}
	}
	void actualizar(Token &t, list<Token> l) {
		list<Token> base = l;
		vaciarLista(l);
		while (base.size() != 0) {
			if (base.front().nombre == t.nombre) {
				t = base.front();
			}
			else {
				l.push_back(base.front());
			}
			base.pop_front();
		}
	}
	void fWhile(queue<Token> &q, list<Token> &base) {
		if (q.front().ciclos != 0) {
			enlace p = q.front().elemento;
			q.pop();
			queue<Token> copia = q;
			while(p->sig){
				copia = q;
				procesarTokens(copia, base);
			}
		}
		else {
			//enlace p = q.front().elemento;
			//q.pop();
			queue<Token> copia;
			while(q.front().elemento){
				copia = q;
				copia.pop();
				procesarTokens(copia, base);
				actualizar(q.front(), base);
			}
		}
		vaciarCola(q);
	}
	void repetidor(queue<Token> &q, list<Token> &base) {
		int p = q.front().valor;
		q.pop();
		queue<Token> copia;
		while (p!=0) {
			copia = q;
			procesarTokens(copia, base);
			p--;
		}
		vaciarCola(q);
	}
	void vaciarCola(queue<Token> &q) {
		while (!q.empty()) {
			q.pop();
		}
	}
	bool buscarV(Token t, list<Token> base, Token &obj) {
		while (base.size() != 0) {
			if (base.front().nombre == t.nombre) {
				base.front().ciclos = t.ciclos;
				obj = base.front();
				return true;
			}
			else {
				base.pop_front();
			}
		}
		return false;
	}
	void guardar(Token &t, list<Token> &q) {
		if (buscarV(t, q) == false) {
			q.push_front(t);
		}
	}
	void retornarV(Token t) {
		if (t.ciclos != 0) {
			avanzar(t);
		}
		cout <<"Valor: "<< t.elemento->v<<endl;
	}
	//esta funcion se encarga de la instrucciones de tipo "new Nodo()"
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
	//realiza asignaciones de tipo referencia campo=valor
	void asigNum(Token t, int x){
		if (t.ciclos != 0) {
			enlace p = t.elemento;
			while (p->sig && t.ciclos > 0) {
				p = p->sig;
				t.ciclos--;
			}
			t.ciclos = 0;
			p->sig->v = x;
		}
		else {
			t.elemento->v = x;
		}

	}
	//avanza x cantidad de nodos en una lista
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
	//vacía una lista
	void vaciarLista(list<Token> &l) {
		while (!l.empty()) {
			l.pop_back();
		}
	}
	//busca si el Token que recibe la funcion ya existe en la lista que funciona como base de datos
	//si existe lo lo sustituye por el antiguo token, sino retorna false
	bool buscarV(Token t, list<Token> &e) {
		list<Token> base = e;
		vaciarLista(e);
		bool resultado=false;
		while (base.size()!=0) {
			if (base.front().nombre == t.nombre) {
				e.push_back(t);
				resultado= true;
			}
			else {
				e.push_back(base.front());
			}
			base.pop_front();
		}
		return resultado;
	}
	//Esta función realiza asignaciones de tipo referencia puntero=referencia puntero 
	//y referencia campo=referencia campo
	void asignacion(Token &var, queue<Token> &q) {
		Token var2 = q.front();
		q.pop();
		if (!q.empty() && q.front().tipo == 6) {
			if (var2.ciclos != 0) {
				avanzar(var2);
			}
			if (var.ciclos != 0) {
				enlace p = var.elemento;
				while (var.ciclos != 0) {
					p = p->sig;
					var.ciclos--;
				}
				p->v = var2.elemento->v;
			}
			else {
				var.elemento->v = var2.elemento->v;
			}
		}
		else {
			if (var2.ciclos != 0) {
				avanzar(var2);
			}
			if (var.ciclos != 0) {
				enlace p = var.elemento;
				while (p->sig && var.ciclos > 0) {
					p = p->sig;
					var.ciclos--;
				}
				var.ciclos = 0;
				p->sig = var2.elemento;
			}
			else {
				var.elemento = var2.elemento;
			}
		}
	}
};
