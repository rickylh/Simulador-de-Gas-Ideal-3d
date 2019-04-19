#pragma once
#include "Objeto.hpp"

class Cubo: public Objeto {
public:
	Cubo(GLfloat aresta = 1.0f);
	GLvoid criar(GLfloat aresta = 1.0f); 
	GLvoid setAresta(GLfloat aresta);
	GLfloat getAresta() const;
	~Cubo();
};
