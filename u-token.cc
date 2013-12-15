
#include "check.h"

//#include <ro/ro.h>
//#include <scc/simple.h>
//#include <lvv/lvv.h>

using namespace std;

#include "token.h"
#include <string.h>


int main() {

	//////////////////////////////////////////////////////// GET_TB / GET_TE
	pos_t  b,e, tb,te;

	pos_t  s_empty = "";
	pos_t  s_s     = "  ";
	pos_t  s_a     = "a";
	pos_t  s_aaa   = "aaa";
	pos_t  s_saaa  = "  aaa";
	pos_t  s_aaas  = "aaa  ";
	pos_t  s_saaas = "  aaa  ";

	#define GET_TB(S)	get_tb(S, S+strlen(S))
	#define GET_TE(S)	get_tb(S, S+strlen(S))

	CHECK(   GET_TB(s_empty) == s_empty);
	CHECK(   GET_TB(s_s)     == s_s+2);
	CHECK(   GET_TB(s_a)     == s_a);
	CHECK(   GET_TB(s_aaa)   == s_aaa);
	CHECK(   GET_TB(s_saaa)  == s_saaa+2);
	CHECK(   GET_TB(s_saaas) == s_saaas+2);

	tb=GET_TB(s_empty);		te=GET_TE(s_empty);		CHECK((std::equal(tb,te+1,""   )));
	tb=GET_TB(s_a);			te=GET_TE(s_a);			CHECK((std::equal(tb,te+1,"a"  )));
	tb=GET_TB(s_aaa);		te=GET_TE(s_aaa);		CHECK((std::equal(tb,te+1,"aaa")));
	tb=GET_TB(s_aaas);		te=GET_TE(s_aaas);		CHECK((std::equal(tb,te+1,"aaa")));
	tb=GET_TB(s_saaa);		te=GET_TE(s_saaa);		CHECK((std::equal(tb,te+1,"aaa")));
	tb=GET_TB(s_saaas);		te=GET_TE(s_saaas);		CHECK((std::equal(tb,te+1,"aaa")));


	/*
	get_tb(s_empty, s_empty+strlen(s_empty)
	while ((tb=get_tb(te,e)) != e) {
		te=get_te(tb,e);					 assert(tb<te);
		hs[tokens++] = hash(tb,te);

		if (tokens>max_tokens) return; 			// ignore if name is too big
		if (tokens==max_comb)  break;                   // for big names hash only max_comp tokens
	}*/

	
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
