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
		Token var = q.front();
		q.pop();
		if (q.front().tipo == 1) {
			q.pop();
			if (q.front().tipo == 7) {
				var.elemento = new Nodo(q.front().valor);
			}
		}
	}
};
