#include "pch.h"
#include <iostream>
#include <string>
#include "tokenizador.h"
#include "ejecutar.h"
#include "lista.h"
#include <list>

using namespace std;
int main()
{
	list<Token> base;
	while (true) {
		string a;
		//obtiene la entrada
		getline(cin, a);
		if (a == "0") {
			break;
		}
		tokenizador x = tokenizador(a, base);
		ejecutar eje = ejecutar(x.tokens, base);
	}
}