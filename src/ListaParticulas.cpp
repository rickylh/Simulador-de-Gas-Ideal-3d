#include "ListaParticulas.hpp"
#include "Principal.hpp"
#include <time.h>

ListaParticulas::ListaParticulas(GLint numero_de_particulas, GLfloat raio, GLfloat massa, GLfloat tCaixa)
	: particula(raio, 30)
	, numero_colisoes_caixa(0)
	, numero_de_particulas(numero_de_particulas)
	, massa_particula(massa) 
	, tamanho_caixa(tCaixa) {
	inicializarPosicoes();
	inicializarVelocidades();
}

ListaParticulas::~ListaParticulas() {
	velocidades.clear();
	posicoes.clear();
}

GLvoid ListaParticulas::atualizarPosicoes() {
	for (GLuint i = 0; i < posicoes.size(); i++) {
		posicoes[i] += velocidades[i] * Principal::deltaTime();
	}
}

GLvoid ListaParticulas::realizarColisoes() {
	colisoesEntreParticulas();
	colisoesCaixa();
}

GLvoid ListaParticulas::colisoesCaixa() {
	GLfloat raio = particula.getRaio() * 2.0f;
	GLfloat tam = tamanho_caixa / 2.0f;
	for (GLuint i = 0; i < posicoes.size(); i++) {
		glm::vec3& pos = posicoes.at(i);
		glm::vec3& vel = velocidades.at(i);
		if (pos.x + raio > tam && vel.x > 0.0f) {
			vel.x *= -1.0f;
			pos.x = 2.0f * tam - 2.0f * raio - pos.x;
			numero_colisoes_caixa++;
			momento_linear += -2.0f * vel.x * massa_particula;
		}
		else if (pos.x - raio < -tam && vel.x < 0.0f) {
			vel.x *= -1.0f;
			pos.x = -2.0f * tam + 2.0f * raio - pos.x;
			numero_colisoes_caixa++;
			momento_linear += 2.0f * vel.x * massa_particula;
		}
		if (pos.y + raio > tam && vel.y > 0.0f) {
			vel.y *= -1.0f;
			pos.y = 2.0f * tam - 2.0f * raio - pos.y;
			numero_colisoes_caixa++;
			momento_linear += -2.0f * vel.y * massa_particula;
		}
		else if (pos.y - raio < -tam && vel.y < 0.0f) {
			vel.y *= -1.0f;
			pos.y = -2.0f * tam + 2.0f * raio - pos.y;
			numero_colisoes_caixa++;
			momento_linear += 2.0f * vel.y * massa_particula;
		}
		if (pos.z + raio > tam && vel.z > 0.0f) {
			vel.z *= -1.0f;
			pos.z = 2.0f * tam - 2.0f * raio - pos.z;
			numero_colisoes_caixa++;
			momento_linear += -2.0f * vel.z * massa_particula;
		}
		else if (pos.z - raio < -tam && vel.z < 0.0f) {
			vel.z *= -1.0f;
			pos.z = -2.0f * tam + 2.0f * raio - pos.z;
			numero_colisoes_caixa++;
			momento_linear += 2.0f * vel.z * massa_particula;
		}
	}
}

GLvoid ListaParticulas::colisoesEntreParticulas() {
	GLfloat raio;
	glm::vec3 distancia;
	GLfloat diferenca;
	for (GLuint i = 0; i < GLuint(posicoes.size()); i++) {
		for (GLuint j = i + 1; j < GLuint(posicoes.size()); j++) {
			raio = particula.getRaio() * 2.0f;
			distancia = posicoes.at(i) - posicoes.at(j);
			if ((distancia.x * distancia.x) + (distancia.y * distancia.y) + (distancia.z * distancia.z)
				< (raio * raio)) {
				diferenca = raio - std::sqrt((distancia.x * distancia.x)
										   + (distancia.y * distancia.y)
								           + (distancia.z * distancia.z));
				aplicarColisao(i, j, diferenca);
			}
		}
	}
}

GLvoid ListaParticulas::aplicarColisao(GLuint par1, GLuint par2, GLfloat diferenca) {
	// Inverter as velociades no eixo de colisao

	glm::vec3 eixo_colisao = posicoes.at(par1) - posicoes.at(par2);
	glm::vec3 vel1 = velocidades.at(par1);
	glm::vec3 vel2 = velocidades.at(par2);

	glm::vec3 vel_ec_1 = projecaoOrtogonal(vel1, eixo_colisao);
	glm::vec3 vel_ec_2 = projecaoOrtogonal(vel2, eixo_colisao);

	velocidades.at(par1) = vel1 - vel_ec_1 + vel_ec_2;
	velocidades.at(par2) = vel2 - vel_ec_2 + vel_ec_1;

	posicoes.at(par1) += (glm::normalize(vel_ec_2) * diferenca * 0.51f);
	posicoes.at(par2) += (glm::normalize(vel_ec_1) * diferenca * 0.51f);
}

GLvoid ListaParticulas::desenhar() {
	for (auto pos : posicoes) {
		particula.setPosicao(pos);
		particula.desenhar();
	}
}

GLvoid ListaParticulas::setUniformTransformacao(GLuint transformacao) {
	particula.setUniformTransfomacao(transformacao);
}

glm::vec3 ListaParticulas::projecaoOrtogonal(glm::vec3 vetor, glm::vec3 direcao) {
	GLdouble escalar = ((vetor.x * direcao.x) + (vetor.y * direcao.y) + (vetor.z * direcao.z));
	GLdouble quadrado = ((direcao.x * direcao.x) + (direcao.y *direcao.y) + (direcao.z * direcao.z));
	if (quadrado != 0) {
		escalar /= quadrado;
	}
	else {
		return (vetor);
	}
	return (GLfloat(escalar) * direcao);
}

GLuint ListaParticulas::getNumeroColisoesCaixa() {
	return numero_colisoes_caixa;
}

glm::vec3 ListaParticulas::getEnergiaCinetica() {
	glm::vec3 K = glm::vec3(0.0f, 0.0f, 0.0f);
	for (auto vel : velocidades) {
		K += vel * vel;
	}
	K *= massa_particula / 2.0f;
	return K;
}

GLvoid ListaParticulas::inicializarPosicoes() {
	glm::vec3 pos;
	for (GLuint i = 0; i < numero_de_particulas; i++) {
		srand(i + GLuint(time(NULL)));
		pos.x = (rand() % GLuint(tamanho_caixa) - tamanho_caixa * 0.4f);
		pos.y = (rand() % GLuint(tamanho_caixa) - tamanho_caixa * 0.4f);
		pos.z = (rand() % GLuint(tamanho_caixa) - tamanho_caixa * 0.4f);
		posicoes.push_back(pos);
	}
}

GLvoid ListaParticulas::inicializarVelocidades() {
	glm::vec3 vel;
	for (GLuint i = 0; i < numero_de_particulas; i++) {
		srand(i + GLuint(time(NULL)));
		vel.x = GLfloat(rand() % 9);
		vel.y = GLfloat(rand() % 10 + 1);
		vel.z = GLfloat(rand() % 11);
		vel *= rand() % 2 ? -1.0f : 1.0f;

		velocidades.push_back(vel * 0.1f);
	}
}

GLvoid ListaParticulas::resetarContadores() {
	momento_linear = 0;
	numero_colisoes_caixa = 0;
}

GLfloat ListaParticulas::getMomentoLinear() {
	return momento_linear;
}

GLvoid ListaParticulas::atualizar() {
	atualizarPosicoes();
	realizarColisoes();
}

const std::vector<glm::vec3>& ListaParticulas::getVelocidades() const {
	return velocidades;
}
