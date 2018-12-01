#include "Header.hpp"
namespace HTTP{
	Header::Header(std::string& msg){
		if(!msg.empty()){
			unsigned int start = 0;
			auto end = static_cast<unsigned int>(msg.find("\r\n"));
			linhaComeco = msg.substr(start, end);
			start = end+2;
			while((end = static_cast<unsigned int>(msg.find("\r\n"), start)), end > start){
				std::string linha = msg.substr(start, end-start);
				std::string nomeHost = linha.substr(0, (linha.find(':')));
				std::string valor = linha.substr((linha.find(':'))+2);

				if(nomeHost == "Host"){
					host = valor.substr(0, (valor.find(':')));
					if(valor.size() > (valor.find(':')))
						porta = valor.substr((valor.find(':'))+2);
				}
				campos.push_back(std::make_tuple(nomeHost, valor));
				start = end+2;
			}
			if(host.empty()){
				auto init = static_cast<unsigned int>(linhaComeco.find("//")+2);
				auto fim =  static_cast<unsigned int>(linhaComeco.find("//",init));
				std::string valor = linhaComeco.substr(init, fim - init);
				host = valor.substr(0, (valor.rfind(':')));
				if(valor.size() > (valor.rfind(':'))){
					porta = valor.substr((valor.rfind(':'))+2);
				}
			}
			if(host[0] == '[')
				host = host.substr(1, host.size() - 2);
			if(porta.empty())
				porta = "80";
			corpo = msg.substr(start+2);
			if(!corpo.empty()){
				Dump::DumpHtml(corpo);
			}

		}
	}
	std::string Header::to_string(bool include){
		std::string msg;
		msg += linhaComeco + "\r\n";
		for(auto &i : campos)
			msg += std::get<0>(i)+": "+std::get<1>(i)+"\r\n";
		msg +="\r\n";
		msg += include? corpo : "";
		return msg;

	}

}
