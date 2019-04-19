#pragma once
#include "Std.hpp"

class Shader {
private:
	GLuint programaID;
	GLuint projecao;
	GLuint transformacao;
	GLuint vizualizacao;
	GLvoid compilarShader(const GLchar * codigo, GLenum tipo);
public:
	Shader();
	Shader(const GLchar* vertex_path, const GLchar* fragment_path);
	~Shader();
	GLvoid usarPrograma();
	GLvoid desabilitarPrograma();
	std::string lerArquivo(const GLchar* local);
	GLvoid criarDeString(const GLchar* vertex, const GLchar* fragment);
	GLvoid criarDeArquivo(const GLchar* vertex_path, const GLchar* fragment_path);
	GLvoid limparShader();
	GLuint getVariavelUniforme(const GLchar* nome);
};

