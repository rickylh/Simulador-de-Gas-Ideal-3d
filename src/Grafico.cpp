#include "Grafico.hpp"
#include "Principal.hpp"
#include "Teclado.hpp"

Grafico::Grafico(const std::vector<glm::vec3> velocidades) 
	: VAO (0)
	, VBO (0)
	, IBO (0)
	, divisoes(50)
	, posicao (-2.8f, -1.6f, -3.0f)
	, escala (1.0f, 1.0f, 1.0f)
	, cor (1.0f, 0.0f, 0.0f, 1.0f)
	, shader ("Shaders/Grafico.vertex", "Shaders/Grafico.frag")
	, texto ("Fontes/Arial.ttf") {

	shader.usarPrograma();
	uniformProjecao = shader.getVariavelUniforme("projecao");
	uniformTransformacao = shader.getVariavelUniforme("transformacao");
	uniformCor = shader.getVariavelUniforme("cor");
	glm::mat4 mProjecao = glm::perspective(45.0f, (GLfloat)Principal::largura / (GLfloat)Principal::altura, 0.1f, 100.0f);
	glUniformMatrix4fv(uniformProjecao, 1, GL_FALSE, glm::value_ptr(mProjecao));
	glUniform4f(uniformCor, cor.x, cor.y, cor.z, cor.w);
	shader.desabilitarPrograma();
	
	std::vector<GLuint> distribuicao;
	distribuicao.insert(distribuicao.begin(), divisoes + 1, 0);
	GLfloat velMaxima(4.0f);

	for (GLuint i = 0; i < velocidades.size(); i++) {
		GLfloat vel = sqrt(velocidades[i].x * velocidades[i].x
						 + velocidades[i].y * velocidades[i].y
						 + velocidades[i].z * velocidades[i].z);

		if (vel <= velMaxima) {
			distribuicao[GLuint(vel / velMaxima * divisoes)]++;
		}
	}

	GLfloat maiorNumeroParticulas = GLfloat(velocidades.size()) / 10;
	// eixo x -> velocidade
	// eixo y -> numero de particulas com a velocidade
	for (GLuint i = 0; i <= divisoes ; i++) {
		vertices.push_back((GLfloat(i) / divisoes * 2.5f )); // x
		vertices.push_back(GLfloat(distribuicao[i]) / GLfloat (maiorNumeroParticulas)); // y
	}

	for (GLuint i = 0; i < divisoes; i++) {
		indices.push_back(i);
		indices.push_back(i+1);
	}

	criar();
}


Grafico::~Grafico() {
	deletar();
}

GLvoid Grafico::criar() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size() , &vertices[0], GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(vertices[0]), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLvoid Grafico::deletar() {
	if (VAO) {
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	if (VBO) {
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
	if (IBO) {
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}
	vertices.clear();
	indices.clear();
}

GLvoid Grafico::desenhar() {
	// Habilitar
	shader.usarPrograma();

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);


	// Calcular posicao e escala
	glm::mat4 mTransformacao = glm::translate(getIdentidade4x4(), posicao);
	mTransformacao = glm::scale(mTransformacao, escala);
	glUniformMatrix4fv(uniformTransformacao, 1, GL_FALSE, glm::value_ptr(mTransformacao));

	// desenhar
	glDrawElements(GL_LINES, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0);

	//desabilitar
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	shader.desabilitarPrograma();
}

GLvoid Grafico::setPosicao(glm::vec3 posicao) {
	this->posicao = posicao;
}

GLvoid Grafico::setPosicao(GLfloat x, GLfloat y, GLfloat z) {
	posicao = glm::vec3(x, y, z);
}

glm::vec3 Grafico::getPosicao() {
	return posicao;
}

GLvoid Grafico::atualizarPosicao(glm::vec3 deltaPosicao) {
	posicao += deltaPosicao;
}

GLvoid Grafico::atualizarPosicao(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ) {
	posicao += glm::vec3(deltaX, deltaY, deltaZ);
}

GLvoid Grafico::setEscala(glm::vec3 escala) {
	this->escala = escala;
}

GLvoid Grafico::setEscala(GLfloat x, GLfloat y, GLfloat z) {
	escala = glm::vec3(x, y, z);
}

glm::vec3 Grafico::getEscala() {
	return escala;
}

GLvoid Grafico::atualizarEscala(glm::vec3 deltaEscala) {
	escala += deltaEscala;
}

GLvoid Grafico::atualizarEscala(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ) {
	escala += glm::vec3(deltaX, deltaY, deltaZ);
}

GLvoid Grafico::atualizar(const std::vector<glm::vec3>& velocidades) {
	vertices.clear();

	GLfloat dv = 50.0f;
	std::vector<GLuint> distribuicao;
	distribuicao.insert(distribuicao.begin(), GLuint(dv) + 1, 0);
	GLfloat velMaxima(4.0f);

	for (GLuint i = 0; i < velocidades.size(); i++) {
		GLfloat vel = sqrt(velocidades[i].x * velocidades[i].x
  					   	 + velocidades[i].y * velocidades[i].y
 						 + velocidades[i].z * velocidades[i].z);

		if (vel <= velMaxima) {
			distribuicao[GLuint(vel / velMaxima * dv)]++;
		}
	}

	GLfloat maiorNumeroParticulas = GLfloat(velocidades.size()) / 10.0f;
	// eixo x -> velocidade
	// eixo y -> numero de particulas com a velocidade
	for (GLuint i = 0; i <= dv ; i++) {
		vertices.push_back((GLfloat(i) / dv * 2.5f )); // x
		vertices.push_back(GLfloat(distribuicao[i]) / GLfloat (maiorNumeroParticulas)); // y
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices[0]) * vertices.size(), &vertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
