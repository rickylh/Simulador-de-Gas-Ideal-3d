#pragma once

#include "Std.hpp" 
#include <iostream>

class Teclado {
private:
	static GLboolean* teclas;

public:
	Teclado();
	~Teclado();
	static GLboolean ativar();
	static GLvoid desativar();
	static GLboolean atualizar(SDL_Event* evento);
	static GLboolean marcarEvento(GLuint evento, GLboolean flag);
	static GLboolean getEvento(GLuint evento);
};

