#pragma once
#include <iostream>
#include <string>
#include "token.h"
#include <queue>
using namespace std;

class tokenizador {
	string s;
public:
	queue<Token> tokens;
	tokenizador(string entrada) {
		s = entrada;
		int i = 0;
		string x;
		while ( i < entrada.length()) {
			if(entrada[i] >= 'a' && entrada[i] <= 'z') {
				while (entrada[i] != '-' && entrada[i] != ';' & entrada[i] != '=') {
					x += entrada[i];
					i++;
				}
				Token obj = Token(x);
				tokens.push(obj);
				x = "";
			}
			else if (entrada[i] == '-' && entrada[i+1] == '>') {
				x ="->";
				Token obj = Token(x);
				tokens.push(obj);
				i += 2;
				x = "";
			}
			else {
				x = entrada[i];
				Token obj = Token(x);
				tokens.push(obj);
				x = "";
				i++;
			}
		}
		cout << x;
	}
};