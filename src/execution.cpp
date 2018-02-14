#include <deque>
#include <vector>
#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "Parser.hpp"
#include "Exception.hpp"

void executeProgram(std::vector<Operation>& instructions) {
	OperandFactory factory;
	std::deque<IOperand const*> stack;

	for (auto& inst : instructions) {
		switch (inst.instruction) {
			case ADD:
			case SUB:
			case MUL:
			case DIV:
			case MOD:
				if (stack.size() < 2) {
					throw RuntimeException("Arithmetic operation on a stack with 0 or 1 element");
				}
				break;
			case POP:
				throw RuntimeException("Pop operation on an empty stack");
			case ASSERT:
				throw RuntimeException("Assert operation on an empty stack");
			default:
				break;
		}
		
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
							if (stack.size() == 0)
								break;
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
