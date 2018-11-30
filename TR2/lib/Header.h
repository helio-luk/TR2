#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>
#include <tuple>

#include "Dump.h"

#define campo std::tuple< std::string, std::string >

namespace HTTP{
	struct Header{
		explicit Header(std::string& str);
		std::string to_string(bool include=True);
		std::string linhaComeco;
		std::vector<campo> campos;
		std::string corpo;
		std::string host;
		std::string porta
	};	
};
#endif
