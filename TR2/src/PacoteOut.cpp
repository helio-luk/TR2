#include<cstdlib>
#include<cstdio>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include <iostream>
#include <sstream>
#include<string.h>

#include "PacoteOut.hpp"


PacoteOut::PacoteOut() = default;
PacoteOut::~PacoteOut() = default;

int socketOut = -1;
struct addrinfo clienteEnd;
struct addrinfo *cEnd;

ssize_t PacoteOut::Send(HTTP::Header msg){
	memset(&clienteEnd, 0, sizeof(clienteEnd));
	clienteEnd.ai_family = AF_UNSPEC;
	clienteEnd.ai_socktype = 0;
	clienteEnd.ai_flags = 0;
	clienteEnd.ai_protocol =IPPROTO_TCP;
	int j=0;
	int i;
	char aux[127];
	 strcpy(aux,msg.host.c_str());
	for(i=strlen(aux)-1; j<2; i--)
	{
		if(aux[i]=='/')
		{
			j++;
		}
			aux[i]='\0';
	}
	printf("%s",aux);
	int info;
	do{
		info = getaddrinfo(aux, msg.porta.c_str(), &clienteEnd, &cEnd);
		printf("\naqui %d\n", info);
	}while(info==-3);
	 if(info == 0){
		socketOut = socket(AF_INET, SOCK_STREAM, 0);
		if(socketOut < 0){
			printf("error ao criar socket");
			exit(1);
		}
		if(connect(socketOut, cEnd->ai_addr, cEnd->ai_addrlen) < 0){
			printf("error no socket");
			exit(1);
		}
	 }

	printf("\n%d\n", socketOut); //dando -1
	ssize_t enviado = send(socketOut, msg.to_string().c_str(), msg.to_string().length(), 0);
	if(enviado < 0){
		printf("nao foi possivel enviar dado\n");
		exit(1);
	}else{
		return enviado;
	}
	return -1;
}

void PacoteOut::responseRecebido(){
	int valread = 0;
	std::string mensagem("");

	do{
		char buffer[1024];
		valread = static_cast<int>(read(socketOut, buffer, sizeof(buffer)));
		mensagem += std::string(buffer, static_cast<unsigned long>(valread));
	}while(valread == 1024);
	if(valread > 0){
		responsesRecebidos.push_back(HTTP::Header(mensagem));
	}else{
		printf("falha na leitura");
		exit(1);
	}
}
