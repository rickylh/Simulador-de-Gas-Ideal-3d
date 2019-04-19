#pragma once
#include "Std.hpp"
#include "Cubo.hpp"
#include "Shader.hpp"
#include "ListaParticulas.hpp"
#include "Texto.hpp"
#include "Grafico.hpp"

class Simulador {
private:
	GLfloat tempo;
	GLfloat massaParticula;
	GLuint numeroParticulas;
	GLfloat raioParticulas;

	GLfloat tamanho_caixa;
	Cubo caixa;
	ListaParticulas particulas;
	Shader* shader;
	GLvoid calcular();
	GLvoid desenharDados();
	Texto texto;

	GLfloat N;
	GLfloat Ni;
	GLfloat somaVelocidades = 0;
	glm::vec3 K;
	GLfloat energiaCinetica;
	GLfloat area;
	GLfloat volume;
	GLfloat pressao;
	GLfloat pressao_i;

	Grafico distribuicaoVelocidades;

public:
	Simulador(GLuint numero_particulas = 300);
	~Simulador();
	GLvoid atualizar();
	GLvoid desenhar();
	GLvoid setShader(Shader* shader);
};

