#include "Teclado.hpp"

Teclado::Teclado() {
	ativar();
}

Teclado::~Teclado() {
	delete[] teclas;
	teclas = NULL;
}

GLboolean Teclado::ativar() {
	if (teclas == NULL) {
		teclas = new GLboolean[1024];
		for (GLint i = 0; i < 1024; i++) {
			teclas[i] = GL_FALSE;
		}
	}
	return (teclas != NULL ? GL_TRUE : GL_FALSE);
}

GLvoid Teclado::desativar() {
	if (teclas != NULL) {
		delete teclas;
		teclas = NULL;
	}
}

GLboolean Teclado::marcarEvento(GLuint evento, GLboolean flag) {
	if (evento < 1024 && teclas != NULL) {
		teclas[evento] = flag;
		return GL_TRUE;
	}
	return GL_FALSE;
}

GLboolean Teclado::getEvento(GLuint evento) {
	if (teclas == NULL) {
		std::cerr << "O Teclado nao foi inicializado"
		<< std::endl;
		return GL_FALSE;
	}
	return (evento < 1024 ? teclas[evento] : GL_FALSE);
}

GLboolean Teclado::atualizar(SDL_Event* evento) {
	if (evento->type == SDL_KEYUP) {
		Teclado::marcarEvento(evento->key.keysym.sym, GL_FALSE);
		return GL_TRUE;
	}
	else if (evento->type == SDL_KEYDOWN) {
		Teclado::marcarEvento(evento->key.keysym.sym, GL_TRUE);
		return GL_TRUE;
	}
	return GL_FALSE;
}

GLboolean* Teclado::teclas (NULL);

