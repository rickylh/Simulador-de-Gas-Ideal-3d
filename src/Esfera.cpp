#include "Esfera.hpp"

Esfera::Esfera()
	: Objeto (GL_TRIANGLES)
	, qualidade (10) {
	setRaio(1.0f);
}

Esfera::Esfera(GLfloat raio, GLuint qualidade)
	: Objeto (GL_TRIANGLES)
	, qualidade (qualidade) {
	setRaio(raio);
	criar();
}

Esfera::~Esfera() {
}

GLvoid Esfera::criar() {
	calcularVertices();
	calcularIndices();
	Objeto::criar();
}

GLvoid Esfera::criar(GLfloat raio, GLuint qualidade) {
	setRaio(raio);
	this->qualidade = qualidade;
	calcularVertices();
	calcularIndices();
	Objeto::criar();
}

GLvoid Esfera::setRaio(GLfloat raio) {
	setEscala(raio, raio, raio);
}

GLfloat Esfera::getRaio() {
	return (escala.x);
}

GLvoid Esfera::atribuirPonteiros() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(vertices[0]), 0);
	glEnableVertexAttribArray(0);
}

GLvoid Esfera::calcularVertices() {
	GLfloat theta = 0.0f, phi = 0.0f;
	for (GLuint i = 0; i <= qualidade; i++) {
		phi = glm::pi<GLfloat>() * i / (GLfloat)qualidade;
		for (GLint j = 0; j <= (GLint) qualidade; j++) {
			theta = 2 * glm::pi<GLfloat>() * j / (GLfloat)qualidade;
			vertices.push_back(std::sin(phi) * std::cos(theta));
			vertices.push_back(std::cos(phi));
			vertices.push_back(std::sin(phi) * std::sin(theta));
		}
	}
}

GLvoid Esfera::calcularIndices() {
	for (GLuint i = 0; i <= (qualidade + 1) * qualidade; i++) {
		indices.push_back(i);
		indices.push_back(i + qualidade + 1);
		indices.push_back(i + qualidade);

		indices.push_back(i + qualidade + 1);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
}

