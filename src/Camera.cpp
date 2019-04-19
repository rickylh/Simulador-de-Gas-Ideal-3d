#include "Camera.hpp"
#include "Teclado.hpp"
#include "Principal.hpp"

Camera::Camera(glm::vec3 posicao, glm::vec3 cima, GLfloat theta, GLfloat phi, GLfloat velocidadeMovimento, GLfloat velocidadoRotacao)
	: posicaoInicial (posicao)
	, thetaInicial (theta)
	, phiInicial (phi)
	, posicao (posicao)
	, frente (glm::vec3(0.0f, 0.0f, -1.0f))
	, cimaGlobal(cima)
	, theta (theta)
	, phi (phi)
	, velocidadeMovimento (velocidadeMovimento)
	, velocidadeRotacao (velocidadoRotacao) {
	atualizar();
}

void Camera::controleTeclado () {
	GLfloat velocidade = velocidadeMovimento * Principal::deltaTime();
	if (Teclado::getEvento(SDLK_w)) {
		posicao += frente * velocidade;
	}
	if (Teclado::getEvento(SDLK_s)) {
		posicao -= frente * velocidade;
	}
	if (Teclado::getEvento(SDLK_a)) {
		posicao -= direita * velocidade;
	}
	if (Teclado::getEvento(SDLK_d)) {
		posicao += direita * velocidade;
	}
	if (Teclado::getEvento(SDLK_0)) {
		resetar();
	}
}

void Camera::controleMouse(SDL_Event* evento) {
	GLfloat xDelta = xMouseAnterior - evento->motion.x;
	GLfloat yDelta = yMouseAnterior - evento->motion.y;

	xMouseAnterior = (GLfloat) evento->motion.x;
	yMouseAnterior = (GLfloat) evento->motion.y;

	xDelta *= -velocidadeRotacao;
	yDelta *=  velocidadeRotacao;

	if (phi > 89.0f) {
		phi = 89.0f;
	}
	if (phi < -89.0f) {
		phi = -89.0f;
	}

	theta += xDelta;
	phi += yDelta;
	atualizar();
}

glm::mat4 Camera::calcularMatriz() {
	return glm::lookAt(posicao, posicao + frente, cima);
}

void Camera::atualizar() {
	frente.x = cos(glm::radians(theta)) * cos(glm::radians(phi));
	frente.y = sin(glm::radians(phi));
	frente.z = sin(glm::radians(theta)) * cos(glm::radians(phi));
	frente = glm::normalize(frente);

	// normalizar produto vetorial (vetor ortogonal)
	direita = glm::normalize(glm::cross(frente, cimaGlobal));
	cima = glm::normalize(glm::cross(direita, frente));
}

GLvoid Camera::ativarMouse(GLfloat xPos, GLfloat yPos) {
	xMouseAnterior = xPos;
	yMouseAnterior = yPos;
}
GLvoid Camera::resetar() {
	posicao = posicaoInicial;
	phi = phiInicial;
	theta = thetaInicial;
	atualizar();
}

Camera::~Camera() {
}
