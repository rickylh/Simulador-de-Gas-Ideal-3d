#include "Simulador.hpp"
#include "Principal.hpp"
#include "Grafico.hpp"

Simulador::Simulador(GLuint numero_particulas)
	: tempo(0)
	, massaParticula(1.0f)
	, numeroParticulas(numero_particulas)
	, raioParticulas(0.1f)
    , tamanho_caixa(10.0f)
	, caixa(tamanho_caixa)
	, particulas(numeroParticulas, raioParticulas, massaParticula, tamanho_caixa)
	, texto ("Fontes/Arial.ttf")
	, distribuicaoVelocidades(particulas.getVelocidades()) {
	texto.setEscala(0.5f);

	area = 6 * tamanho_caixa * tamanho_caixa;
	volume = tamanho_caixa * tamanho_caixa * tamanho_caixa
		- (numeroParticulas * 4.0f * GLfloat(M_PI) / 3.0f * raioParticulas * raioParticulas * raioParticulas);
}

Simulador::~Simulador() {
	shader = NULL;
}

GLvoid Simulador::atualizar() {
	particulas.atualizar();
	calcular();
	desenhar();
}

GLvoid Simulador::calcular() {
	if (tempo > 25.0f) {
		tempo = 0;
		particulas.resetarContadores();
	}
	tempo += Principal::deltaTime();

	GLfloat somaVelocidades = 0;
	const std::vector<glm::vec3>& velocidades = particulas.getVelocidades();
	for (auto vel : velocidades) {
		somaVelocidades += std::sqrt(vel.x * vel.x + vel.y * vel.y + vel.z * vel.z);
	}

	N = somaVelocidades / (4.0f * volume);
	Ni = particulas.getNumeroColisoesCaixa() / area / tempo;

	K = particulas.getEnergiaCinetica();
	energiaCinetica = K.x + K.y + K.z;

	pressao = (2 * energiaCinetica) / (3 * volume);
	pressao_i = particulas.getMomentoLinear() / (area * tempo);

	distribuicaoVelocidades.atualizar(velocidades);
}

GLvoid Simulador::desenharDados() {
	texto.setPosicao(0.01f * Principal::largura, 0.95f * Principal::altura)
		.setEscala(0.5f)
		.setString("Tempo: " + std::to_string(GLuint(tempo)) + " s")
		.desenhar();

	texto.setPosicao(0.85f * Principal::largura, 0.95f * Principal::altura)
		.setEscala(0.4f)
		.setString("Massa: " + std::to_string(massaParticula))
		.desenhar();

	texto.setPosicao(0.85f * Principal::largura, 0.90f * Principal::altura)
		.setString("Area: " + std::to_string(area))
		.desenhar();

	texto.setPosicao(0.85f * Principal::largura, 0.85f * Principal::altura)
		.setString("Particulas: " + std::to_string(numeroParticulas))
		.desenhar();

	texto.setPosicao(0.01f * Principal::largura, 0.85f * Principal::altura)
		.setEscala(0.5f)
		.setString("N:  " + std::to_string(N))
		.desenhar();

	texto.setPosicao(0.01f * Principal::largura, 0.80f * Principal::altura)
		.setEscala(0.5f)
		.setString("Ni: " + std::to_string(Ni))
		.desenhar();

	texto.setPosicao(0.01f * Principal::largura, 0.70f * Principal::altura)
		.setString("K: " + std::to_string(K.x + K.y + K.z))
		.desenhar();

	texto.setPosicao(0.01f * Principal::largura, 0.65f * Principal::altura)
		.setString("Kx: " + std::to_string(K.x))
		.desenhar();

	texto.setPosicao(0.01f * Principal::largura, 0.62f * Principal::altura)
		.setString("Ky: " + std::to_string(K.y))
		.desenhar();

	texto.setPosicao(0.01f * Principal::largura, 0.59f * Principal::altura)
		.setString("Kz: " + std::to_string(K.z))
		.desenhar();

	texto.setPosicao(0.01f * Principal::largura, 0.50f * Principal::altura)
		.setString("P:  " + std::to_string(pressao))
		.desenhar();

	texto.setPosicao(0.01f * Principal::largura, 0.46f * Principal::altura)
		.setString("Pi: " + std::to_string(pressao_i))
		.desenhar();

}

GLvoid Simulador::desenhar() {
	if (shader != NULL) {
		shader->usarPrograma();
		particulas.desenhar();
		caixa.desenhar();
		shader->desabilitarPrograma();
	}

	distribuicaoVelocidades.desenhar();
	desenharDados();
}

GLvoid Simulador::setShader(Shader* shader) {
	this->shader = shader;
	particulas.setUniformTransformacao(shader->getVariavelUniforme("transformacao"));
	caixa.setUniformTransfomacao(shader->getVariavelUniforme("transformacao"));
}
