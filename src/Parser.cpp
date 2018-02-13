#include <vector>
#include <regex>
#include <string>

#include "Parser.hpp"
#include "Exception.hpp"

bool isSimpleInstruction(eInstruction instruction) {
	if (instruction == PUSH ||
			instruction == ASSERT)
		return false;
	return true;
}

bool isRichInstruction(eInstruction instruction) {
	if (instruction == PUSH ||
			instruction == ASSERT)
		return true;
	return false;
}

std::vector<Operation> parseFile(std::vector<std::string> &content)
{
	std::vector<Operation> instructionList;
	std::regex comment("^;.*");
	std::regex simpleInstruction("^(\\w+)$");
	std::regex richInstruction("^(\\w+) (\\w+)\\((-?\\d+(?:\\.\\d+)?)\\)$");
	bool hasExitStatement = false;

	std::smatch match;
	for (auto line : content) {
		if (std::regex_search(line, comment))
			continue;
		if (std::regex_search(line, match, simpleInstruction))
		{
			auto it = wordsToOp.find(match[1]);
			if (it == wordsToOp.end())
				throw SyntaxException("Invalid token: " + std::string(match[1]));
			if (!isSimpleInstruction(it->second))
				throw SyntaxException("Argument missing to instruction " + std::string(match[1]));
			Operation op = { .instruction = it->second };
			if (op.instruction == EXIT)
				hasExitStatement = true;
			instructionList.push_back(op);
		}
		else if (std::regex_search(line, match, richInstruction))
		{
			auto itOp = wordsToOp.find(match[1]);
			if (itOp == wordsToOp.end())
				throw SyntaxException("Invalid token: " + std::string(match[1]));
			if (isSimpleInstruction(itOp->second))
				throw SyntaxException("Instruction " + std::string(match[1]) + " should not have an argument");
			auto itOperand = wordsToOperand.find(match[2]);
			if (itOperand == wordsToOperand.end())
				throw SyntaxException("Invalid token: " + std::string(match[2]));
			Operation op = {
				.instruction = itOp->second,
				.operandType = itOperand->second,
				.arg = match[3]
			};
			instructionList.push_back(op);
		}
		else
			throw SyntaxException("Invalid statement: " + line);
	}
	if (!hasExitStatement)
		throw SyntaxException("Program doesnt have an exit statement");
	return instructionList;
}
