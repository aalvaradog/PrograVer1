#include "pch.h"
#include <iostream>
#include <string>
#include "tokenizador.h"
#include "ejecutar.h"
#include "lista.h"

using namespace std;
int main()
{
	while (true) {
		enlaceT base;
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