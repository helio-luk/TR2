#include <cstdlib>
#include <cstdio>
#include <memory>

#include "Servidor.hpp"

Servidor::Servidor(int numPorta) : requests(pacoteIn.requestsRecebidos), responses(pacoteOut.responsesRecebidos), pacoteIn(porta), pacoteOut(){}
Servidor::~Servidor() = default;

void Servidor::Inicia(){
	printf("teste\n");
}
