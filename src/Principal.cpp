#include "Principal.hpp"
#include "Std.hpp"
#include "Texto.hpp"

GLfloat Principal::_delta_time(1.0f);

const GLint Principal::altura(1080);
const GLint Principal::largura(1920);

Principal::Principal(int numero_particulas)
	: executando(GL_TRUE)
    , mouse_ativo(false)
	, tempoAnterior(0)
	, janela(largura, altura, "Simulador Gas Ideal")
	, camera(glm::vec3(1.0f, 0.0f, -16.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 7.0f, 0.4f)
    , simulador(numero_particulas)
	, shader("Shaders/Principal.vertex", "Shaders/Principal.frag")
	, texto("Fontes/Arial.ttf")
	, numero_de_frames(0)
	, tempo_total(0.0f) {

	texto.setEscala(0.5f);
	texto.setPosicao(largura * 0.92f, altura * 0.03f);

	Teclado::ativar();

	tempoAnterior = SDL_GetPerformanceCounter();

	simulador.setShader(&shader);
	mVisualizacao = getIdentidade4x4();

	shader.usarPrograma();
	projecao = shader.getVariavelUniforme("projecao");
	visualizacao = shader.getVariavelUniforme("visualizacao");
	mProjecao = glm::perspective(45.0f, (GLfloat)largura / (GLfloat)altura, 0.1f, 100.0f);
	glUniformMatrix4fv(projecao, 1, GL_FALSE, glm::value_ptr(mProjecao));
	shader.desabilitarPrograma();
}

Principal::~Principal() {
	Teclado::desativar();
}

GLvoid Principal::executar() {
	while (executando) {
		janela.limparJanela();
		loopEventos();
		camera.controleTeclado();
		atualizarVisualizacao();
 		simulador.atualizar();
		atualizarDeltaTime();
		desenharFPS();
		janela.renderizar();
	}
}

GLvoid Principal::loopEventos() {
	while (SDL_PollEvent(&evento)) {
		if (Teclado::atualizar(&evento)) {
			continue;
		}
		switch (evento.type) {
		case SDL_QUIT:
			executando = GL_FALSE;
			break;
		case SDL_MOUSEMOTION:
			if (mouse_ativo) {
				camera.controleMouse(&evento);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouse_ativo = GL_TRUE;
			camera.ativarMouse((GLfloat) evento.button.x, (GLfloat) evento.button.y);
			break;
		case SDL_MOUSEBUTTONUP:
			mouse_ativo = GL_FALSE;
			break;
		}
	}
    if (Teclado::getEvento(SDLK_q)) {
        executando = GL_FALSE;
    }
}

GLvoid Principal::atualizarDeltaTime() {
	Uint64 novo = SDL_GetPerformanceCounter();
	_delta_time = GLfloat(novo - tempoAnterior) / (GLfloat)SDL_GetPerformanceFrequency();
	tempoAnterior = novo;
}

GLvoid Principal::desenharFPS() {
	numero_de_frames++;
	tempo_total += _delta_time;

	if (numero_de_frames > 300) {
		numero_de_frames = 0;
		tempo_total = 0;
	}

	texto.setString(std::to_string(GLuint(numero_de_frames / tempo_total)) + " FPS")
		 .desenhar();
}

GLvoid Principal::atualizarVisualizacao() {
	shader.usarPrograma();
	glUniformMatrix4fv(visualizacao, 1, GL_FALSE, glm::value_ptr(camera.calcularMatriz()));
	shader.desabilitarPrograma();
}

GLfloat Principal::deltaTime() {
	return _delta_time;
}
