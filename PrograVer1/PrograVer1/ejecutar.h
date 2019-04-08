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
	ejecutar(queue<Token> q) {
		//utilizar un ciclo con un switch adentro que vaya recorriendo la cola y dependiendo del tipo llame a x función
		//algunos tipos quizá no sean necesario crearles una función o quizá ni si quiera haya que tormarlos en cuenta
		Token var;
		while (q.empty()) {
			Token entrada = q.front();
			q.pop();
			switch (entrada.tipo) {
			case 0://variable
				var = entrada;
				q.pop();
				break;
			case 1://asignación
				q.pop();
				break;
			case 3://punto y coma
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
	}
	void crearNodo(Token &var, queue<Token> &q) {
		if (q.front().tipo == 1) {
			q.pop();
			if (q.front().tipo == 7) {
				var.elemento = new Nodo(q.front().valor);
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
};
