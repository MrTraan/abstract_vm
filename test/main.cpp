#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <Parser.hpp>
#include <Exception.hpp>

#define BEGIN_SHOULD_THROW() bool hasThrown = false; \
							try {

#define END_SHOULD_THROW(E) } catch (const E &e) { \
		hasThrown = true; \
	} \
	REQUIRE(hasThrown == true);

#define END_SHOULD_NOT_THROW() } catch (const Exception &e) { \
		hasThrown = true; \
	} \
	REQUIRE(hasThrown == false);

std::string printProgram(std::vector<std::string> program) {
	std::string res = "";

	for (auto s : program) {
		res += s + "; ";
	}
	return res;
}


static std::vector<std::vector<std::string>> invalidTokens = {
	{"push int12(3)", "exit"},
	{"pope", "exit"},
	{"push int8(a)", "exit"},
	{"push int8()", "exit"},
	{"push int16(-4.)", "exit"},
	{"push int16(-4", "exit"},
	{"push int16)", "exit"},
	{"push", "exit"},
	{"add int(16)", "exit"},
	{"assert", "exit"},
	{"push int16(-4.)"}
};

static std::vector<std::vector<std::string>> validTokens = {
	{"push int16(3)", "exit"},
	{"pop", "exit"},
	{"push int8(3.432)", "exit"},
	{"push int8(-432)", "exit"},
	{"push int16(-4.432)", "exit"},
	{"push int32(-4.432)", "exit"},
	{"push float(-4.432)", "exit"},
	{"push double(-4.432)", "exit"},
	{"assert int32(3214)", "exit"},
	{"print", "exit"},
	{"dump", "exit"},
	{"dump", "exit", "dump", "exit"},
	{"dump;lol", "exit"},
	{"dump", ";lol", "dump", "exit"}
};

static std::vector<std::vector<std::string>> invalidPrograms = {
	// Overflow
	{"push int8(600)", "exit"},
	{"push int8(125)", "push int8(125)", "add", "exit"},
	// Underflow
	{"push int8(-600)", "exit"},
	{"push int8(-125)", "push int8(-125)", "add", "exit"},
	// 	Pop on empty stack
	{"pop", "exit"},
	{"push int8(2)", "push int8(2)", "pop", "pop", "pop", "exit"},
	// Division by 0
	{"push int8(6)", "push double(0.0)", "div", "exit"},
	{"push int8(6)", "push double(0.0)", "mod", "exit"},
	{"push double(6.0)", "push int8(0)", "div", "exit"},
	{"push double(6.0)", "push int8(0)", "mod", "exit"},
	// Less than two  value with math
	{"add", "exit"},
	{"push int8(3)", "div", "exit"},
	{"push int8(3)", "push int8(3)", "mul", "sub", "exit"},
	{"push int8(3)", "push int8(3)", "pop", "mod", "exit"},
	// Print
	{"print", "exit"}
};

static std::vector<std::vector<std::string>> invalidAssertPrograms = {
	{"push int16(3)", "print", "exit"},
	{"push int8(6)", "assert int16(6)", "exit"},
	{"push int16(7)", "assert int16(6)", "exit"}
};

TEST_CASE( "Parser", "[parser]" ) {
	SECTION("Throw on invalid token") {
		for (auto t : invalidTokens) {
			BEGIN_SHOULD_THROW()
			parseFile(t);
			END_SHOULD_THROW(SyntaxException)
		}
	}
	SECTION("Accept valid tokens") {
		for (auto t : validTokens) {
			BEGIN_SHOULD_THROW()
			parseFile(t);
			END_SHOULD_NOT_THROW()
		}
	}
}

TEST_CASE( "Runtime", "[runtime]" ) {
		for (auto p : invalidPrograms) {
			SECTION(printProgram(p)) {
				BEGIN_SHOULD_THROW()
				auto tokens = parseFile(p);
				executeProgram(tokens);
				END_SHOULD_THROW(RuntimeException)
			}
		}
}

TEST_CASE( "Assertion", "[runtime]" ) {
		for (auto p : invalidAssertPrograms) {
			SECTION(printProgram(p)) {
				BEGIN_SHOULD_THROW()
				auto tokens = parseFile(p);
				executeProgram(tokens);
				END_SHOULD_THROW(AssertionException)
			}
		}
}
