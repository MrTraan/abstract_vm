#pragma once

#include <map>
#include "IOperand.hpp"

enum eInstruction {
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	PUSH,
	POP,
	DUMP,
	ASSERT,
	PRINT,
	EXIT
};

static std::map<std::string, eInstruction> wordsToOp = {
	{ "add", ADD },
	{ "sub", SUB },
	{ "mul", MUL },
	{ "div", DIV },
	{ "mod", MOD },
	{ "push", PUSH },
	{ "pop", POP },
	{ "dump", DUMP },
	{ "assert", ASSERT },
	{ "print", PRINT },
	{ "exit", EXIT }
};

static std::map<std::string, eOperandType> wordsToOperand = {
	{ "int8", INT_8 },
	{ "int16", INT_16 },
	{ "int32", INT_32 },
	{ "float", FLOAT },
	{ "double", DOUBLE }
};

static std::map<eOperandType, std::string> operandToWords = {
	{ INT_8, "int8" },
	{ INT_16, "int16" },
	{ INT_32, "int32" },
	{ FLOAT, "float" },
	{ DOUBLE, "double" }
};

typedef struct {
	eInstruction instruction;
	eOperandType operandType;
	std::string arg;
} Operation;

std::vector<Operation> parseFile(std::vector<std::string> &content);
