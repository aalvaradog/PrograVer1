#include "pch.h"
#include <iostream>
#include <string>
#include "tokenizador.h"

using namespace std;
int main()
{
	string a, b;
	cin >> a;
	tokenizador x = tokenizador(a);
	Token token = Token(x.tokens.front());
	cout << token.tipo;
}