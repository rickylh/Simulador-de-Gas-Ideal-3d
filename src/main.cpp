#include "Principal.hpp"

int main(int argc, char* argv[]) {
    int numero_de_particulas = 1000;
    if (argc >= 2) {
        numero_de_particulas = atoi(argv[1]);
    }
	Principal p(numero_de_particulas);
	p.executar();
	return 0;
}
