#pragma once
#include "Std.hpp"

class Janela {
private:
	GLuint largura;
	GLuint altura;
	std::string titulo_da_janela;
	SDL_Window* janela;
	SDL_GLContext contexto;
	SDL_Renderer* renderizadorSDL;

public:
	Janela(GLuint largura = 800, GLuint altura = 600, std::string titulo = "Janela OpenGL");
	~Janela();
	GLvoid inicializar();
	GLvoid limparJanela();
	GLvoid renderizar();
	SDL_Renderer* getRenderizador();
};

