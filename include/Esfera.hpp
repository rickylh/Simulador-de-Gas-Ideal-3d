#pragma once
#include "Std.hpp"
#include "Objeto.hpp"

class Esfera : public Objeto {
private:
	GLuint qualidade;
	GLvoid atribuirPonteiros();
	GLvoid calcularVertices();
	GLvoid calcularIndices();

public:
	Esfera();
	Esfera(GLfloat raio, GLuint qualidade = 10);
	GLvoid criar();
	GLvoid criar(GLfloat raio, GLuint qualidade = 10);
	GLvoid setRaio(GLfloat raio);
	GLfloat getRaio();
	~Esfera();
};
