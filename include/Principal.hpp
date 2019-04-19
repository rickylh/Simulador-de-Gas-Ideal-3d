#pragma once
#include "Std.hpp"
#include "Janela.hpp"
#include "Camera.hpp"
#include "Simulador.hpp"
#include "Teclado.hpp"

class Principal {
private:
	GLboolean executando;
	GLboolean mouse_ativo;
	Uint64 tempoAnterior;
	SDL_Event evento;

	Janela janela;
	Camera camera;
	Simulador simulador;
	Shader shader;

	GLvoid loopEventos();
	GLvoid desenharFPS();
	GLvoid atualizarDeltaTime();
	GLvoid atualizarVisualizacao();

	GLuint projecao;
	GLuint visualizacao;
	glm::mat4 mVisualizacao;
	glm::mat4 mProjecao;

	Texto texto;
	GLuint  numero_de_frames;
	GLfloat tempo_total;

	static GLfloat _delta_time;
public:
	Principal(int numero_particulas = 500);
	~Principal();

	GLvoid executar();
	static GLfloat deltaTime();

	static const GLint largura;
	static const GLint altura;
};

