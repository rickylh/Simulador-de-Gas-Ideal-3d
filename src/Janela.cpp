#include "Janela.hpp"
#include "Std.hpp"

Janela::Janela(GLuint largura, GLuint altura, std::string titulo)
	: largura (largura)
	, altura (altura)
	, titulo_da_janela (titulo)
    , janela(NULL) 
    , renderizadorSDL(NULL) {
	inicializar();
}

GLvoid Janela::inicializar() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Não foi possivel inicializar o SDL."
		<< std::endl;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	GLint flags_janela = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	janela = SDL_CreateWindow (
		titulo_da_janela.c_str(),
		10,
		10,
		largura,
		altura,
		flags_janela);
    contexto = SDL_GL_CreateContext(janela);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Não foi possivel inicializar o glew."
		<< std::endl;
	}
	glViewport(0, 0, largura, altura);
	glEnable(GL_DEPTH_TEST);
}

Janela::~Janela() {
	titulo_da_janela.clear();
	SDL_GL_DeleteContext(contexto);
	SDL_DestroyWindow(janela);
	SDL_Quit();
}

GLvoid Janela::limparJanela() {
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLvoid Janela::renderizar() {
	SDL_GL_SwapWindow(janela);
}

SDL_Renderer* Janela::getRenderizador() {
	return renderizadorSDL;
}
