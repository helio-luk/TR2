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
	while(true){
	pacoteIn.accConexao();
	pacoteIn.getRequests();

	if(!requestsRecebidos.empty())
		std::swap( requestsRecebidos, sendRequest );

	if(!sendRequest.empty()) {
		printf("\nEnviando %d request(s)...\n", (int) sendRequest.size());

		for (auto &i : sendRequest) {
			printf("\nEnviando request para %s:%s\n", i.host.c_str(), i.porta.c_str());
			printf("\n%s\n", i.to_string().c_str());
			if(pacoteOut.Send(i) == -1){
				printf("\nNão foi possível enivar request\n");
				exit(1);
			}
		}

		sendRequest.clear();
	}

	pacoteOut.responseRcv();

	if(!responsesRecebidos.empty())
		std::swap(responsesRecebidos, sendRequest);

	if(!sendRequest.empty()) {
		printf("\nEnviando %d response(s)...\n", (int) sendRequest.size());

		for(auto &i : sendResponse) {
			printf("\nResponse: \n%s\n", i.to_string().c_str());
			if(pacoteIn.Send(i) == -1){
				printf("\nNão foi possível enivar response\n");
				exit(1);
			}
		}

		sendResponse.clear();
	}
}
}
