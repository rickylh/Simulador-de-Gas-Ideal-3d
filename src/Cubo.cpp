#include "Cubo.hpp"

Cubo::Cubo(GLfloat aresta)
	: Objeto (GL_LINES) {
	setAresta(aresta);
	criar();
}

Cubo::~Cubo()
{
}

GLvoid Cubo::criar(GLfloat aresta) {
	if (aresta != 1.0f) {
		setAresta(aresta);
	}

	GLuint indices[] = {
		0, 1,
		0, 3,
		0, 4,
		2, 1,
		2, 3,
		2, 7,
		6, 3,
		6, 4,
		6, 7,
		5, 1,
		5, 4,
		5, 7
	};
	GLfloat vertices[] = {
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f
	};
	Objeto::criar(vertices, indices, GLuint(3 * 8), GLuint(2 * 12));
}

GLvoid Cubo::setAresta(GLfloat aresta) {
	setEscala(aresta, aresta, aresta);
}

GLfloat Cubo::getAresta() const {
	return (escala.x);
}
