
#include "check.h"

//#include <ro/ro.h>
//#include <scc/simple.h>
//#include <lvv/lvv.h>

using namespace std;

#include "token.h"


int main() {

	//////////////////////////////////////////////////////// GET_TB / GET_TE
	
	//////////////////////////////////////////////////////// ARE_EQUAL_TOKEN_CHAINS
	CHECK(   are_equal_token_chains("", ""));
	CHECK(   are_equal_token_chains("", " "));
	CHECK(   are_equal_token_chains("", " "));
	CHECK(   are_equal_token_chains(" ", " "));
	CHECK(   are_equal_token_chains("\t", "\n"));
	CHECK(   are_equal_token_chains("a", "a"));
	CHECK( ! are_equal_token_chains("a", "b"));
	CHECK(   are_equal_token_chains(" a", "a "));
	CHECK(   are_equal_token_chains("aa\tbb", " aa  bb "));
	CHECK(   are_equal_token_chains(" aa \n bb\t\n", "aa bb"));
	CHECK(   are_equal_token_chains("A b C", "A b C"));
	
	CHECK(   are_equal_token_chains("1 2 3", "1 2 3"));
	CHECK( ! are_equal_token_chains("1 2 3", "1 2 E"));
	CHECK( ! are_equal_token_chains("1 2 3", "E 2 3"));
	
	CHECK(   are_equal_token_chains("1 2 3 4", "1 2 3 4"));
	CHECK( ! are_equal_token_chains("1 2 3 4", "1 2 3 E"));
	CHECK( ! are_equal_token_chains("E 2 3 4", "1 2 3 4"));
	
	CHECK(   are_equal_token_chains("1 2 3 4 5", "1 2 3 4 5"));
	CHECK( ! are_equal_token_chains("1 2 3 4 5", "1 2 3 4 E"));
	CHECK( ! are_equal_token_chains("E 2 3 4 5", "1 2 3 4 5"));
	
	CHECK(   are_equal_token_chains("1 2 3 4 5 6", "1 2 3 4 5 6"));
	CHECK( ! are_equal_token_chains("1 2 3 4 5 6", "1 2 3 4 5 E"));
	CHECK( ! are_equal_token_chains("E 2 3 4 5 6", "1 2 3 4 5 6"));
	
	CHECK(   are_equal_token_chains("1 2 3 4 5 6 7", "1 2 3 4 5 6 7"));
	CHECK( ! are_equal_token_chains("1 2 3 4 5 6 7", "1 2 3 4 5 6 E"));
	CHECK( ! are_equal_token_chains("E 2 3 4 5 6 7", "1 2 3 4 5 6 7"));

	//////////////////////////////////////////////////////// IS_HEAD_OF
	pos_t unused;
	CHECK(   is_head_of("", "",unused));
	CHECK(   is_head_of("", " ",unused));
	CHECK(   is_head_of("", " ",unused));
	CHECK(   is_head_of(" ", " ",unused));
	CHECK(   is_head_of("\t", "\n",unused));
	CHECK(   is_head_of("a", "a",unused));
	CHECK( ! is_head_of("a", "b",unused));
	CHECK(   is_head_of(" a", "a ",unused));
	CHECK(   is_head_of("aa\tbb", " aa  bb ",unused));
	CHECK(   is_head_of(" aa \n bb\t\n", "aa bb",unused));
	CHECK(   is_head_of("A b C", "A b C",unused));
	
	CHECK(   is_head_of("", "e",unused));
	CHECK(   is_head_of("", " e",unused));
	CHECK(   is_head_of("", " e",unused));
	CHECK(   is_head_of(" ", " e",unused));
	CHECK(   is_head_of("\t", "\ne",unused));
	CHECK( ! is_head_of("a", "ae",unused));
	CHECK( ! is_head_of("a", "be",unused));
	CHECK(   is_head_of(" a", "a e",unused));
	CHECK(   is_head_of("aa\tbb", " aa  bb e",unused));
	CHECK( ! is_head_of(" aa \n bb\t\n", "aa bbe",unused));
	CHECK( ! is_head_of("A b C", "A b Ce",unused));
	
	CHECK_EXIT;
}
