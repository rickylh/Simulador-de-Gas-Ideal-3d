#include "Texto.hpp"
#include "Principal.hpp"

Texto::Texto(std::string fonte)
	: shader("Shaders/Texto.vertex", "Shaders/Texto.frag")
	, VAO (0)
	, VBO (0)
	, string("Nova String")
	, cor(1.0f, 1.0f, 1.0f)
	, escala(1.0f)
	, posicao (0.0f, 0.0f) {
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	inicializar(fonte);
}


Texto::~Texto()
{
}

GLvoid Texto::carregarFonte(std::string fonte) {
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		std::cout << "Texto::incicializar: "
		<< "Erro ao incializar FreeType"
		<< std::endl;
	}

	FT_Face face;
	if (FT_New_Face(ft, fonte.c_str(), 0, &face)) {
		std::cout << "Texto::incicializar: "
		<< "Erro ao carregar fonte FreeType"
		<< std::endl;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLuint textura;
	for (GLubyte c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "Texto::incicializar: "
			<< "Erro ao carregar glifo FreeType"
			<< std::endl;
			continue;
		}
		glGenTextures(1, &textura);
		glBindTexture(GL_TEXTURE_2D, textura);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		// Opcoes de textura
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Novo caractere
		Caractere caractere = {
			textura,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<GLuint>(face->glyph->advance.x)
		};
		caracteres.insert(std::pair<GLchar, Caractere>(c, caractere));
	}

	// dasabilitar e desalocar
	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

GLvoid Texto::inicializar(std::string fonte) {
	glm::mat4 projecao = glm::ortho(0.0f, static_cast<GLfloat>(Principal::largura), 0.0f, static_cast<GLfloat>(Principal::altura));
	shader.usarPrograma();
	glUniformMatrix4fv(shader.getVariavelUniforme("projecao"), 1, GL_FALSE, glm::value_ptr(projecao));

	carregarFonte(fonte);

	// Configura VAO e VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	shader.desabilitarPrograma();
}

GLvoid Texto::desenhar() {
    shader.usarPrograma();

    glUniform3f(shader.getVariavelUniforme("textColor"), cor.x, cor.y, cor.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
	GLfloat x = posicao.x;
	GLfloat y = posicao.y;

	Caractere ch;
    for (c = string.begin(); c != string.end(); c++) {
        ch = caracteres[*c];

        GLfloat xpos = x + ch.deslocamento.x * escala;
        GLfloat ypos = y - (ch.tamanho.y - ch.deslocamento.y) * escala;

        GLfloat w = ch.tamanho.x * escala;
        GLfloat h = ch.tamanho.y * escala;

        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },            
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }           
        };

        glBindTexture(GL_TEXTURE_2D, ch.texturaID);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.distanciaProximo >> 6) * escala;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
	shader.desabilitarPrograma();
}

Texto& Texto::setString(std::string str) {
	string = str;
	return *this;
}

std::string Texto::getString() {
	return string;
}

Texto& Texto::setCor(GLfloat r, GLfloat g, GLfloat b) {
	cor = glm::vec3(r, g, b);
	return *this;
}

Texto& Texto::setCor(glm::vec3 cor) {
	this->cor = cor;
	return *this;
}

glm::vec3 Texto::getCor() {
	return cor;
}

Texto& Texto::setEscala(GLfloat escala) {
	this->escala = escala;
	return *this;
}

GLfloat Texto::getEscala() {
	return escala;
}

Texto& Texto::setPosicao(GLfloat x, GLfloat y) {
	posicao = glm::vec2(x, y);
	return *this;
}

Texto& Texto::setPosicao(glm::vec2 pos) {
	posicao = pos;
	return *this;
}

glm::vec2 Texto::getPosicao() {
	return posicao;
}
