#pragma once
#include "Objeto.hpp"
#include "Shader.hpp"
#include "Texto.hpp"
#include "Std.hpp"

class Grafico {
public:
	Grafico(const std::vector<glm::vec3> velocidades);
	~Grafico();

	GLvoid criar();
	GLvoid deletar();
	GLvoid desenhar();

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

	GLvoid atualizar(const std::vector<glm::vec3>& velocidades);

private:
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;

	GLuint divisoes;

	std::vector<GLuint> indices;
	std::vector<GLfloat> vertices;

	GLuint uniformTransformacao;
	GLuint uniformProjecao;
	GLuint uniformCor;

	glm::vec3 posicao;
	glm::vec3 escala;
	glm::vec4 cor;

	Shader shader;
	Texto texto;
};
