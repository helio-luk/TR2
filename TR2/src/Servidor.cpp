#include <cstdlib>
#include <cstdio>
#include <memory>

#include "Servidor.hpp"
#include "Header.hpp"


Servidor::Servidor(int numPorta) : requests(pacoteIn.requestsRecebidos)
							, responses(pacoteOut.responsesRecebidos)
							, pacoteIn( numPorta )
							, pacoteOut() {}



Servidor::~Servidor() = default;

void Servidor::Inicia(){
	printf("teste\n");
}
