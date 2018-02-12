#include <iostream>
#include <IOperand.hpp>
#include <OperandFactory.hpp>
#include "Parser.hpp"
#include <vector>
#include <deque>

#include <iostream>
#include <fstream>

std::string readFile(char* path) {
	std::string line;
	std::string total = "";
	std::ifstream myfile(path);

	if (myfile.is_open()) {
		while (std::getline(myfile, line)) {
			total += line;
			total += "\n";
		}
		myfile.close();
		return total;
	}

	else
		std::cout << "Unable to open file";

	return "";
}

int main(int ac, char** av) {
	(void)ac;
	(void)av;
	std::vector<std::string> fakeFile = {
		"; -------------",
		"; sample.avm -",
		"; -------------",
		"",
		"push int32(42)",
		"push int32(33)",
		"add",
		"push float(44.55)",
		"mul",
		"push double(42.42)",
		"push int32(42)",
		"dump",
		"pop",
		"assert"
	};

	auto instructions = parseFile(fakeFile);

	std::deque<IOperand const *> stack;
	OperandFactory factory;

	for (auto &inst : instructions) {
		switch (inst.instruction)
		{
			case PUSH:
				std::cout << "pushing this: " << inst.arg << "\n";
				stack.push_front(factory.createOperand(inst.operandType, inst.arg));
				break;
			case POP:
				{
				auto first = stack.front();
				stack.pop_front();
				delete first;
				break;
				}
			case PRINT:
				{
				auto elem = stack.front();
				std::cout << elem->toString() << "\n";
				break;
				}
			case DUMP:
				for (auto &elem : stack) {
					std::cout << elem->toString() << "\n";
				}
				break;
			case ADD:
				{
				auto first = stack.front();
				stack.pop_front();
				auto second = stack.front();
				stack.pop_front();
				stack.push_front(*first + *second);
				delete first;
				delete second;
				break;
				}
			case SUB:
				{
				auto first = stack.front();
				stack.pop_front();
				auto second = stack.front();
				stack.pop_front();
				stack.push_front(*first - *second);
				delete first;
				delete second;
				break;
				}
			case MUL:
				{
				auto first = stack.front();
				stack.pop_front();
				auto second = stack.front();
				stack.pop_front();
				stack.push_front(*first * *second);
				delete first;
				delete second;
				break;
				}
			case DIV:
				{
				auto first = stack.front();
				stack.pop_front();
				auto second = stack.front();
				stack.pop_front();
				stack.push_front(*first / *second);
				delete first;
				delete second;
				break;
				}
			case MOD:
				{
				auto first = stack.front();
				stack.pop_front();
				auto second = stack.front();
				stack.pop_front();
				stack.push_front(*first % *second);
				delete first;
				delete second;
				break;
				}
			default:
				break;
		}
	}

	/* std::string const tab[2] = {"3.67", "-1.3"}; */
	/* IOperand const* a = factory.createOperand(FLOAT, tab[0]); */
	/* IOperand const* b = factory.createOperand(FLOAT, tab[1]); */

	/* IOperand const* plus = *a + *b; */
	/* IOperand const* minus = *a - *b; */
	/* IOperand const* times = *a * *b; */
	/* IOperand const* divide = *a / *b; */

	/* std::cout << "3.67 + -1.3: " << plus->toString() << "\n"; */
	/* std::cout << "3.67 - -1.3: " << minus->toString() << "\n"; */
	/* std::cout << "3.67 * -1.3: " << times->toString() << "\n"; */
	/* std::cout << "3.67 / -1.3: " << divide->toString() << "\n"; */

	/* delete plus; */
	/* delete minus; */
	/* delete times; */
	/* delete divide; */

	/* if (ac <= 1) */
	/*   return (1); */

	/* std::string data = readFile(av[1]); */

	/* std::cout << data; */

	return (0);
}
