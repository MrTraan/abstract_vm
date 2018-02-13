#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

#include <IOperand.hpp>
#include <OperandFactory.hpp>
#include "Parser.hpp"
#include "Exception.hpp"

void executeProgram(std::vector<Operation>& instructions);

void trim(std::string& s) {
	size_t p = s.find_first_not_of(" \t");
	s.erase(0, p);

	p = s.find_last_not_of(" \t");
	if (std::string::npos != p)
		s.erase(p + 1);
}

std::vector<std::string> readFile(std::istream &stream) {
	std::vector<std::string> lines;
	std::string line;

	while (std::getline(stream, line)) {
		trim(line);
		if (line == ";;")
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
			source = readFile(std::cin);
		} else {
			std::ifstream file(av[1]);
			if (!file.is_open())
				throw Exception("Unable to open file " + std::string(av[1]));
			source = readFile(file);
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

void executeProgram(std::vector<Operation>& instructions) {
	OperandFactory factory;
	std::deque<IOperand const*> stack;

	for (auto& inst : instructions) {
		switch (inst.instruction) {
			case PUSH:
				stack.push_front(factory.createOperand(inst.operandType, inst.arg));
				break;
			case POP: {
						  auto first = stack.front();
						  stack.pop_front();
						  delete first;
						  break;
					  }
			case PRINT: {
							auto elem = stack.front();
							std::cout << elem->toString() << "\n";
							break;
						}
			case DUMP:
						for (auto& elem : stack) {
							std::cout << elem->toString() << "\n";
						}
						break;
			case ADD: {
						  auto first = stack.front();
						  stack.pop_front();
						  auto second = stack.front();
						  stack.pop_front();
						  stack.push_front(*second + *first);
						  delete first;
						  delete second;
						  break;
					  }
			case SUB: {
						  auto first = stack.front();
						  stack.pop_front();
						  auto second = stack.front();
						  stack.pop_front();
						  stack.push_front(*second - *first);
						  delete first;
						  delete second;
						  break;
					  }
			case MUL: {
						  auto first = stack.front();
						  stack.pop_front();
						  auto second = stack.front();
						  stack.pop_front();
						  stack.push_front(*second * *first);
						  delete first;
						  delete second;
						  break;
					  }
			case DIV: {
						  auto first = stack.front();
						  stack.pop_front();
						  auto second = stack.front();
						  stack.pop_front();
						  stack.push_front(*second / *first);
						  delete first;
						  delete second;
						  break;
					  }
			case MOD: {
						  auto first = stack.front();
						  stack.pop_front();
						  auto second = stack.front();
						  stack.pop_front();
						  stack.push_front(*second % *first);
						  delete first;
						  delete second;
						  break;
					  }
			case ASSERT: {
							 auto compare = factory.createOperand(inst.operandType, inst.arg);
							 auto first = stack.front();
							 if (first->getType() != compare->getType() || first->toString() != compare->toString())
								 throw AssertionException(first->toString() + " != " + compare->toString());
							 delete compare;
							 break;
						 }
			case EXIT:
						 return;
		}
	}
}
