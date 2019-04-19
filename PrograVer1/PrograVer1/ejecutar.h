#pragma once
#include <iostream>
#include "lista.h"
#include "token.h"
#include <queue>
#include "tokenizador.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

class ejecutar {
	bool repeat = false;
	int valor=0;
public:
	ejecutar(queue<Token> entrada, list<Token> &l ) {
		procesarTokens(entrada, l);
	}
	void procesarTokens(queue<Token> q, list<Token> &base) {
		//utilizar un ciclo con un switch adentro que vaya recorriendo la cola y dependiendo del tipo llame a x funci�n
		//algunos tipos quiz� no sean necesario crearles una funci�n o quiz� ni si quiera haya que tormarlos en cuenta
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
			case 1://asignaci�n
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
				break;
			case 6://apunta a valor
				//apuntarValor(var, q);
				q.pop();
				if ((q.empty() && asignar == false) || q.front().tipo==3) {
					retornarV(var);
				}
				break;
			case 7://crear un nuevo nodo
				q.pop();
				crearN(var.elemento, var.ciclos, q);
				var.ciclos = 0;
				guardar(var, base);
				break;
			case 9://while
				q.pop();
				fWhile(q, base);
				break;
			case 10://repeat
				q.pop();
				repeat = true;
				repetidor(q, base);
				break;
			case 11://asignacion 0
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
	void actualizar(Token &t, list<Token> &l) {
		list<Token> base = l;
		vaciarLista(l);
		while (base.size() != 0) {
			if (base.front().nombre == t.nombre) {
				base.front().ciclos = t.ciclos;
				t = base.front();
				l.push_front(t);
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
			queue<Token> copia;
			int con = q.front().ciclos;
			while (q.front().ciclos != 0) {
				p = p->sig;
				q.front().ciclos--;
			}
			q.front().ciclos = con;
			while(p){
				copia = q;
				copia.pop();
				procesarTokens(copia, base);
				actualizar(q.front() , base);
				valor++;
				p = p->sig;
				
			}
		}
		else {
			enlace p = q.front().elemento;
			queue<Token> copia;
			while(p){
				copia = q;
				copia.pop();
				procesarTokens(copia, base);
				actualizar(q.front(), base);
				valor++;
				p = p->sig;
			}
		}
		q.front().ciclos = 0;
		actualizar(q.front(), base);
		vaciarCola(q);
	}
	void repetidor(queue<Token> &q, list<Token> &base) {
		int p = q.front().valor;
		q.pop();
		queue<Token> copia;
		valor = 1;
		while (p!=0) {
			q.front().ciclos = valor-1;
			copia = q;
			procesarTokens(copia, base);
			valor++;
			p--;
		}
		valor = p;
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
		if (valor != 0) {
			avanzar(t, valor);
		}
		else if (t.ciclos != 0) {
			avanzar(t, t.ciclos);
		}
		cout <<"Valor: "<< t.elemento->v<<endl;
	}
	//esta funcion se encarga de la instrucciones de tipo "new Nodo()"
	void crearN(enlace &q, int v, queue<Token> &c) {
		if (c.front().tipo == 4 || c.front().tipo==12) {
			int x;
			if (c.front().tipo == 12 && repeat == true) {
				x = valor;
			}
			else if (c.front().tipo == 12) {
				srand(time(NULL));
				x = 1 + rand() % (99 - 1);
			}
			else {
				x = c.front().valor;
			}
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
				avanzar(c.front(), c.front().ciclos);
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
	void avanzar(Token &p, int x){
		while (x != 0) {
			p.elemento = p.elemento->sig;
			x--;
		}
	}
	int apuntarValor(Token &var, queue<Token> &q) {
		int valor = var.elemento->v;
		q.pop();
		return valor;
	}
	//vac�a una lista
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
	//Esta funci�n realiza asignaciones de tipo referencia puntero=referencia puntero 
	//y referencia campo=referencia campo
	void asignacion(Token &var, queue<Token> &q) {
		Token var2 = q.front();
		q.pop();
		if (!q.empty() && q.front().tipo == 6) {
			if (var2.ciclos != 0) {
				avanzar(var2, var2.ciclos);
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
				avanzar(var2, var2.ciclos);
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
