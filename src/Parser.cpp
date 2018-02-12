#include "Parser.hpp"
#include <vector>
#include <regex>
#include <string>

std::vector<Operation> parseFile(std::vector<std::string> &content)
{
	std::vector<Operation> instructionList;
	std::regex comment("^;.*");
	std::regex simpleInstruction("^(\\w+)$");
	std::regex richInstruction("^(\\w+) (\\w+)\\((\\d+(?:\\.\\d+)?)\\)$");
	
	std::smatch match;
	for (auto line : content) {
		if (line.length() == 0)
			continue;
		if (std::regex_search(line, comment))
			continue;
		if (std::regex_search(line, match, simpleInstruction))
		{
			auto it = wordsToOp.find(match[1]);
			if (it == wordsToOp.end()) {
				std::cout << "Invalid token: " << match[1] << "\n";
				continue;
			}
			Operation op = { .instruction = it->second };
			instructionList.push_back(op);
		}
		else if (std::regex_search(line, match, richInstruction))
		{
			auto itOp = wordsToOp.find(match[1]);
			if (itOp == wordsToOp.end()) {
				std::cout << "Invalid token: " << match[1] << "\n";
				continue;
			}
			auto itOperand = wordsToOperand.find(match[2]);
			if (itOperand == wordsToOperand.end()) {
				std::cout << "Invalid token: " << match[2] << "\n";
				continue;
			}
			Operation op = {
				.instruction = itOp->second,
				.operandType = itOperand->second,
				.arg = match[3]
			};
			instructionList.push_back(op);
		}
		else
			std::cout << line << " matches nothing\n";
	}
	return instructionList;
}
