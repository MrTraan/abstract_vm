#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <Parser.hpp>
#include <Exception.hpp>

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

#define BEGIN_SHOULD_THROW() bool hasThrown = false; \
							try {

#define END_SHOULD_THROW() } catch (const Exception &e) { \
		hasThrown = true; \
	} \
	REQUIRE(hasThrown == true);

#define END_SHOULD_NOT_THROW() } catch (const Exception &e) { \
		hasThrown = true; \
	} \
	REQUIRE(hasThrown == false);


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
	{"dump", "exit", "dump", "exit"}
};

TEST_CASE( "Parser", "[parser]" ) {
	SECTION("Throw on invalid token") {
		for (auto t : invalidTokens) {
			BEGIN_SHOULD_THROW()
			parseFile(t);
			END_SHOULD_THROW()
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

