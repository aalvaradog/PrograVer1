#include "pch.h"
#include <iostream>
#include <string>
#include "tokenizador.h"
#include "ejecutar.h"

using namespace std;
int main()
{
	string a;
	//obtiene la entrada
	getline(cin, a);
	tokenizador x = tokenizador(a);
	ejecutar eje = ejecutar(x.tokens);
}