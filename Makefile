# **********************************************
# * Makefile para programas escritos em C++   **
# * Utilizando SDL2 e OpenGL                  **
# *                                           **
# *  Autor: Ricky Lemes Habegger              **
# *                                           **
# **********************************************
# ==============================================

#-----------------------------------------------
#----              Variaveis                ----
#-----------------------------------------------

# Nome do projeto
NOME_PROJ=Simulador

# Arquivos fonte
C_SOURCE=$(wildcard ./src/*.cpp)

# Arquivo headers
H_SOURCE=$(wildcard ./include/*.hpp)

# Objetos que serão gerados
OBJ=$(subst .cpp,.o,$(subst src,objetos,$(C_SOURCE)))

FLAGS=-lSDL2  \
      -lGL \
      -lGLEW \
	  -lfreetype \

# Compilador
CC=g++

INCLUDE="include"

# Flags para o compilador
CC_FLAGS=-c         \
         -g         \
         -Wall      \
         -Wextra    \
         -W         \
         -pedantic-errors \
         -pedantic
         -std=c98 \

# Comando para apagar arquivo não nescessarios
RM = rm -rf

#-----------------------------------------------
#----       Targets de Compilação           ----
#-----------------------------------------------

# Criar os objetos e executavel
all: pastaDeObjetos $(NOME_PROJ)
	@ echo "\e[01mArquivo binario criado: \e[01;04;32m$(NOME_PROJ)\e[00m"

# linkar os objetos e gerar o executavel
$(NOME_PROJ): $(OBJ)
	@ echo " "
	@ echo "\e[01mCriando arquivo binario:\e[01;32m $@ \e[00m"
	@ $(CC) $(FLAGS) $^ -o $@

# Compilar todas as sources
./objetos/%.o: ./src/%.cpp ./include/%.hpp
	@ echo "Compilando: \e[00;31m $< \e[00m"
	@ $(CC) $< $(CC_FLAGS) -o $@ -I $(INCLUDE)

# Compilar a main
./objetos/main.o: ./src/main.cpp $(H_SOURCE)
	@ echo "Compilando: \e[00;31m $< \e[00m"
	@ $(CC) $< $(CC_FLAGS) -o $@ -I $(INCLUDE)

pastaDeObjetos:
	@ mkdir -p objetos

# Remover os objetos gerados na compilacao
clear:
	@ $(RM) ./objetos/* $(PROJ_NAME) *~
	@ rmdir --ignore-fail-on-non-empty objetos

# Remover os objetos e remover o executavel
reset: clear
	@ $(RM) $(NOME_PROJ)

# Recompilar o programa do inicio
rebuild: reset all

# Gerar o executavel e executar
run: all
	@ ./$(NOME_PROJ) 

# Evita ambiguidade com arquivo da source
.PHONY: all clean

# Variaveis internas
# $@    Nome da regra. 
# $<    Nome da primeira dependência 
# $^ 	Lista de dependências
# $? 	Lista de dependências mais recentes que a regra.
# $* 	Nome do arquivo sem sufixo
