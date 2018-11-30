#ifndef SERVER_H
#define SERVER_H

#include <vector>

#include "PacoteOut.h"
#include "PacoteIn.h"
#include "Header.h"
#include "Dado.h"

class Servidor{
	public:
		explicit Servidor(int porta);
		~Servidor();
		void Inicia();
		std::vector< HTTP::Header > &requests;	
		std::vector< HTTP::Header > sendRequest;
		std::vector< HTTP::Header > &responses;
		std::vector< HTTP::Header > sendResponse;
	private:
		PacoteIn pIn;
		PacoteOut pOut;		

};
#endif
