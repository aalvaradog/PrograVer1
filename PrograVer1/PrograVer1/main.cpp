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
	int pos = 0;
	while (true) {
		string a;
		//obtiene la entrada
		getline(cin, a);
		if (a == "0") {
			break;
		}
		tokenizador x = tokenizador(a, base);
		ejecutar eje = ejecutar(x.tokens, pos, base);
		if (eje.resultado == true) {
			cout << "OK"<<endl;
		}
		else {
			cout << "Error" << endl;
		}
	}
}