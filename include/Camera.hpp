#pragma once
#include "Std.hpp"

class Camera
{
private:
	glm::vec3 posicaoInicial;
	GLfloat thetaInicial;
	GLfloat phiInicial;

	glm::vec3 posicao;
	glm::vec3 frente;
	glm::vec3 cima;
	glm::vec3 direita;
	glm::vec3 cimaGlobal;

	GLfloat theta;
	GLfloat phi;

	GLfloat velocidadeMovimento;
	GLfloat velocidadeRotacao;

	GLfloat xMouseAnterior;
	GLfloat yMouseAnterior;

	GLvoid atualizar();

public:
	Camera(glm::vec3 posicao, glm::vec3 cima, GLfloat theta, GLfloat phi, GLfloat velocidadeMovimento, GLfloat velocidadoRotacao);
	GLvoid controleTeclado();
	GLvoid controleMouse(SDL_Event* evento);
	GLvoid ativarMouse(GLfloat xPos, GLfloat yPos);
	glm::mat4 calcularMatriz();
	GLvoid resetar();
	~Camera();
};

