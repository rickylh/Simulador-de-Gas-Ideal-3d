#include "Objeto.hpp"

Objeto::Objeto(GLenum tipo_primitivo)
	: VBO (0)
	, VAO (0)
	, IBO (0)
	, tipo_primitivo (tipo_primitivo)
	, posicao (0.0f, 0.0f, 0.0f)
	, escala (1.0f, 1.0f, 1.0f) {
}


Objeto::~Objeto() {
	
}

GLvoid Objeto::criar(GLfloat* vertices, GLuint* indices, GLuint tam_vertices, GLuint tam_indices) {
	// verifica se ja existia um objeto
	deletar();

	this->indices.assign(indices, indices + tam_indices);
	this->vertices.assign(vertices, vertices + tam_vertices);
	
	gerarBuffer();
	atribuirPonteiros();
	desabilitarBuffer();
}

GLvoid Objeto::criar() {
	if (vertices.empty() || indices.empty()) {
		std::cerr << "Objeto::criar -> "
		<< "Nenhum vertice ou incice fornecido"
		<< std::endl;
		return;
	}
	gerarBuffer();
	atribuirPonteiros();
	desabilitarBuffer();
}

GLvoid Objeto::atribuirPonteiros() {
	// glVertexAttribPointer
	// indice -> posicao na matriz de vertices
	// tamanho -> numero de componentes do vertice
	// tipo -> tipo de cada componente
	// normalizar? GL_TRUE : GL_FALSE
	// numero de bytes necessarios até o proximo vertice de mesmo tipo (todos os componentes)
		// (0 significa que os dados estao compactados)
	// deslocamento nos componentes de um mesmo vertex ate os componentes desejados

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(vertices[0]), 0);
	glEnableVertexAttribArray(0);
}

GLvoid Objeto::gerarBuffer() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size() , &vertices[0], GL_STATIC_DRAW);
}

GLvoid Objeto::desabilitarBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLvoid Objeto::deletar() {
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

GLvoid Objeto::desenhar() {
	// Habilitar
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Calcular posicao e escala
	glm::mat4 mIdentidade(
		glm::vec4 (1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4 (0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4 (0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f)
	);
	glm::mat4 mTransformacao = glm::translate(mIdentidade, posicao);
	mTransformacao = glm::scale(mTransformacao, escala);
	glUniformMatrix4fv(uniformTransformacao, 1, GL_FALSE, glm::value_ptr(mTransformacao));

	// desenhar
	glDrawElements(tipo_primitivo, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0);

	//desabilitar
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLvoid Objeto::setPosicao(glm::vec3 posicao) {
	this->posicao = posicao;
}

GLvoid Objeto::setPosicao(GLfloat x, GLfloat y, GLfloat z) {
	posicao = glm::vec3(x, y, z);
}

glm::vec3 Objeto::getPosicao() {
	return posicao;
}

GLvoid Objeto::atualizarPosicao(glm::vec3 deltaPosicao) {
	posicao += deltaPosicao;
}

GLvoid Objeto::atualizarPosicao(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ) {
	posicao += glm::vec3(deltaX, deltaY, deltaZ);
}

GLvoid Objeto::setEscala(glm::vec3 escala) {
	this->escala = escala;
}

GLvoid Objeto::setEscala(GLfloat x, GLfloat y, GLfloat z) {
	escala = glm::vec3(x, y, z);
}

glm::vec3 Objeto::getEscala() {
	return escala;
}

GLvoid Objeto::atualizarEscala(glm::vec3 deltaEscala) {
	escala += deltaEscala;
}

GLvoid Objeto::atualizarEscala(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ) {
	escala += glm::vec3(deltaX, deltaY, deltaZ);
}

GLvoid Objeto::setUniformTransfomacao(GLuint uTransformacao) {
	uniformTransformacao = uTransformacao;
}