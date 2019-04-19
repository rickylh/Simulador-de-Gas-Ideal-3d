#pragma once
#include "Std.hpp"
#include "Esfera.hpp"

class ListaParticulas {
private:
	Esfera particula;
	std::vector<glm::vec3> velocidades;
	std::vector<glm::vec3> posicoes;

	GLvoid colisoesCaixa();
	GLvoid colisoesEntreParticulas();
	GLvoid aplicarColisao(GLuint par1, GLuint par2, GLfloat diferenca);

	glm::vec3 projecaoOrtogonal(glm::vec3 vetor, glm::vec3 direcao);

	GLuint  numero_colisoes_caixa;
	GLuint  numero_de_particulas;
	GLfloat momento_linear;
	GLfloat massa_particula;
	GLfloat tamanho_caixa;

	GLvoid inicializarPosicoes();
	GLvoid inicializarVelocidades();
	GLvoid atualizarPosicoes();
	GLvoid realizarColisoes();

public:
	ListaParticulas(GLint numero_de_particulas, GLfloat raio, GLfloat massa, GLfloat tCaixa);
	~ListaParticulas();
	
	GLvoid atualizar();
	GLvoid desenhar();
	GLvoid setUniformTransformacao(GLuint transformacao);
	GLvoid resetarContadores();

	GLuint getNumeroColisoesCaixa();
	glm::vec3 getEnergiaCinetica();
	GLfloat getMomentoLinear();
	const std::vector<glm::vec3>& getVelocidades() const;
};
