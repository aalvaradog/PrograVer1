#include "pch.h"
#include <iostream>
#include <string>
#include "tokenizador.h"
#include "ejecutar.h"

using namespace std;
int main()
{
	string a, b;
	getline(cin, a);
	tokenizador x = tokenizador(a);
	Token token = Token(x.tokens.front());
	cout << token.tipo;
	ejecutar eje = ejecutar(x.tokens);
}