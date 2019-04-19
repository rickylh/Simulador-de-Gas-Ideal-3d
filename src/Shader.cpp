#include "Shader.hpp"
#include "Std.hpp"
#include <fstream>
#include <sstream>

Shader::Shader()
	: programaID (1)
	, projecao(1)
	, transformacao(1) {
}

Shader::Shader(const GLchar* vertex_path, const GLchar* fragment_path)
	: programaID (0)
	, projecao(0)
	, transformacao(0) {
	criarDeArquivo(vertex_path, fragment_path);
}

Shader::~Shader() {
	limparShader();
}

GLvoid Shader::criarDeString(const GLchar* vertex, const GLchar* fragment) {
	programaID = glCreateProgram();
	if (!programaID) {
		std::cerr << "Shader::criarDeString -> "
		<< "Não foi possivel criar o programa: "
		<< std::endl;
	}
	compilarShader(vertex, GL_VERTEX_SHADER);
	compilarShader(fragment, GL_FRAGMENT_SHADER);

	GLint sucesso;
	GLchar log[2048] = { 0 };
	glLinkProgram(programaID);
	glGetProgramiv(programaID, GL_LINK_STATUS, &sucesso);
	if (!sucesso) {
		glGetProgramInfoLog(programaID, sizeof(log), NULL, log);
		std::cerr << "Shader::criarDeString -> "
			<< "Não foi possivel linkar o programa: "
			<< log
			<< std::endl;
	}
	glValidateProgram(programaID);
	glGetProgramiv(programaID, GL_VALIDATE_STATUS, &sucesso);
	if (!sucesso) {
		glGetProgramInfoLog(programaID, sizeof(log), NULL, log);
		std::cerr << "Shader::criarDeString -> "
			<< "Não foi possivel validar o programa: "
			<< log << " -> "
			<< vertex
			<< fragment
			<< std::endl;
	}
	projecao = glGetUniformLocation(programaID, "projecao");
	transformacao = glGetUniformLocation(programaID, "transformacao");
	vizualizacao = glGetUniformLocation(programaID, "vizualizacao");
}

GLvoid Shader::criarDeArquivo(const GLchar* vertex_path, const GLchar* fragment_path) {
	std::string vertexCodigo = lerArquivo(vertex_path);
	std::string fragmentCodigo = lerArquivo(fragment_path);
	criarDeString(vertexCodigo.c_str(), fragmentCodigo.c_str());
}

std::string Shader::lerArquivo(const GLchar* local) {
	std::string codigo;
	std::ifstream codigoStream(local, std::ios::in);
	if (codigoStream.is_open()) {
		std::stringstream sstr;
		sstr << codigoStream.rdbuf();
		codigo = sstr.str();
		codigoStream.close();
	}
	return(codigo);
}

GLvoid Shader::compilarShader(const GLchar* codigo, GLenum tipo) {
	GLuint shader = glCreateShader(tipo);
	GLint tamanhoCodigo = (GLint) strlen(codigo);
	glShaderSource(shader, 1, &codigo, &tamanhoCodigo);
	glCompileShader(shader);
	GLint sucesso = false;
	GLchar* log = new GLchar[2048];
	log[0] = '0';
	glGetShaderiv(shader, GL_COMPILE_STATUS, &sucesso);
	if (!sucesso) {
		glGetShaderInfoLog(shader, 2048, NULL, log);
		std::cerr << "Shader::adicionarShader -> "
		<< "Nao foi possivel compilar o shader "
		<< tipo
		<< std::endl;
	}
	glAttachShader(programaID, shader);
}

GLvoid Shader::usarPrograma() {
	glUseProgram(programaID);
}

GLvoid Shader::desabilitarPrograma() {
	glUseProgram(0);
}

GLuint Shader::getVariavelUniforme(const GLchar* nome) {
	return glGetUniformLocation(programaID, nome);
}

GLvoid Shader::limparShader() {
	if (programaID) {
		glDeleteProgram(programaID);
		programaID = 0;
	}
	projecao = 0;
	transformacao = 0;
}
