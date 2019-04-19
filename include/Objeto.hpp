#pragma once
#include "Std.hpp"

class Objeto {
public:
	Objeto(GLenum tipo_primitivo = GL_TRIANGLES);
	~Objeto();

	virtual GLvoid criar();
	virtual GLvoid criar(GLfloat* vertices, GLuint* indices, GLuint num_de_vertices, GLuint num_de_indices);
	virtual GLvoid atribuirPonteiros();

	GLvoid gerarBuffer();
	GLvoid desabilitarBuffer();

	GLvoid deletar();
	virtual GLvoid desenhar();

	GLvoid setPosicao(glm::vec3 posicao);
	GLvoid setPosicao(GLfloat x, GLfloat y, GLfloat z);
	glm::vec3 getPosicao();
	GLvoid atualizarPosicao(glm::vec3 deltaPosicao);
	GLvoid atualizarPosicao(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ);

	GLvoid setEscala(glm::vec3 posicao);
	GLvoid setEscala(GLfloat x, GLfloat y, GLfloat z);
	glm::vec3 getEscala();
	GLvoid atualizarEscala(glm::vec3 deltaEscala);
	GLvoid atualizarEscala(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ);

	GLvoid setUniformTransfomacao(GLuint uTransformacao);

protected:
	GLuint VBO;
	GLuint VAO;
	GLuint IBO;
	GLenum tipo_primitivo;
	std::vector<GLuint> indices;
	std::vector<GLfloat> vertices;

	GLuint uniformTransformacao;
	glm::vec3 posicao;
	glm::vec3 escala;
};

