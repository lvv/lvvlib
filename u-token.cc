
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

	b=s_empty;  e=b+strlen(b);  tb=get_tb(b,e);     te=get_te(tb,e);    CHECK_ARE_EQUAL(te-tb,0);
	b=s_a;	    e=b+strlen(b);  tb=get_tb(b,e);    	te=get_te(tb,e);    CHECK_ARE_EQUAL(te-tb,1); CHECK(std::equal(tb,te,"a"  ));
	b=s_aaa;    e=b+strlen(b);  tb=get_tb(b,e);    	te=get_te(tb,e);    CHECK_ARE_EQUAL(te-tb,3); CHECK(std::equal(tb,te,"aaa"));
	b=s_aaas;   e=b+strlen(b);  tb=get_tb(b,e);    	te=get_te(tb,e);    CHECK_ARE_EQUAL(te-tb,3); CHECK(std::equal(tb,te,"aaa"));
	b=s_saaa;   e=b+strlen(b);  tb=get_tb(b,e);    	te=get_te(tb,e);    CHECK_ARE_EQUAL(te-tb,3); CHECK(std::equal(tb,te,"aaa"));
	b=s_saaas;  e=b+strlen(b);  tb=get_tb(b,e);     te=get_te(tb,e);    CHECK_ARE_EQUAL(te-tb,3); CHECK(std::equal(tb,te,"aaa"));


	/*
	{
	pos_t  b = "\" (as in, \"What in the Sam Hill is that?\"). Its";
	pos_t  e = b+strlen(b);
	pos_t  tb;
	pos_t  te = b;
	while ((tb=get_tb(te,e)) != e) {
		te=get_te(tb,e);     
		cerr << string(tb,te) << endl;
	}
	}

	*/
	
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
