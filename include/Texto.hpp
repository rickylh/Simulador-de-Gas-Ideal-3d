#pragma once
#include "Std.hpp"
#include "Shader.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

struct Caractere {
    GLuint texturaID;
    glm::ivec2 tamanho;
    glm::ivec2 deslocamento;
    GLuint distanciaProximo;
};

class Texto {
private:
	std::map<GLchar, Caractere> caracteres;
	Shader shader;
	GLuint VAO;
	GLuint VBO;
	std::string string;
	glm::vec3 cor;
	GLfloat escala;
	glm::vec2 posicao;

public:
	Texto(std::string fonte);
	~Texto();
	GLvoid inicializar(std::string fonte);
	GLvoid desenhar();

	Texto& setString(std::string str);
	std::string getString();

	Texto& setCor(GLfloat r, GLfloat g, GLfloat b);
	Texto& setCor(glm::vec3 cor);
	glm::vec3 getCor();
	
	Texto& setPosicao(GLfloat x, GLfloat y);
	Texto& setPosicao(glm::vec2 pos);
	glm::vec2 getPosicao();

	Texto& setEscala(GLfloat escala);
	GLfloat getEscala();

	GLvoid carregarFonte(std::string fonte);
};


