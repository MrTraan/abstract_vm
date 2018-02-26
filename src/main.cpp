#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

#include <IOperand.hpp>
#include <OperandFactory.hpp>
#include "Parser.hpp"
#include "Exception.hpp"

static void trim(std::string& s) {
	size_t p = s.find_first_not_of(" \t");
	s.erase(0, p);

	p = s.find_last_not_of(" \t");
	if (std::string::npos != p)
		s.erase(p + 1);
}

std::vector<std::string> readFile(std::istream &stream, bool isStdin) {
	std::vector<std::string> lines;
	std::string line;

	while (std::getline(stream, line)) {
		trim(line);
		if (isStdin == true && line == ";;")
			break;
		if (line.length() > 0) {
			lines.push_back(line);
		}
	}
	return lines;
}

int main(int ac, char** av) {
	try {
		std::vector<std::string> source;
		if (ac <= 1) {
			source = readFile(std::cin, true);
		} else {
			std::ifstream file(av[1]);
			if (!file.is_open())
				throw Exception("Unable to open file " + std::string(av[1]));
			source = readFile(file, false);
			file.close();
		}
		auto instructions = parseFile(source);
		executeProgram(instructions);
	} catch (const Exception &e) {
		std::cerr << e.what() << "\n";
		return (1);
	}
	return (0);
}
