#include "Dump.hpp"

Dump::Dump() = default;
Dump::~Dump() = default;

void Dump::DumpHtml(std::string corpo){
	unsigned int start = static_cast<unsigned int>(corpo.find("<"));
	if(start = 0){
		FILE *fp = fopen("dump/dump.html", "w+");
		if(fp == nullptr)
			printf("Arquivo Nao existe \n");
		else{
			fprintf(fp, corpo.c_str());
			fclose(fp);
			prinft("Dump Criado\n");
		}
	}

}
