
#include "check.h"

#ifdef LVV
#include <ro/ro.h>
#include <scc/simple.h>
#include <lvv/lvv.h>
#endif

using namespace std;

#include "token.h"


int main() {

       PR1(are_equal_token_chains("", ""));
       PR1(are_equal_token_chains("", " "));
       PR1(are_equal_token_chains("", " "));
       PR1(are_equal_token_chains(" ", " "));
       PR1(are_equal_token_chains("\t", "\n"));
       PR1(are_equal_token_chains("a", "a"));
       PR1(are_equal_token_chains("a", "b"));
       PR1(are_equal_token_chains(" a", "a "));
       PR1(are_equal_token_chains("aa\tbb", " aa  bb "));
       PR1(are_equal_token_chains(" aa \n bb\t\n", "aa bb"));
       PR1(are_equal_token_chains("A b C", "A b C"));

       PR1(are_equal_token_chains("1 2 3", "1 2 3"));
       PR1(are_equal_token_chains("1 2 3", "1 2 E"));
       PR1(are_equal_token_chains("1 2 3", "E 2 3"));

       PR1(are_equal_token_chains("1 2 3 4", "1 2 3 4"));
       PR1(are_equal_token_chains("1 2 3 4", "1 2 3 E"));
       PR1(are_equal_token_chains("E 2 3 4", "1 2 3 4"));

       PR1(are_equal_token_chains("1 2 3 4 5", "1 2 3 4 5"));
       PR1(are_equal_token_chains("1 2 3 4 5", "1 2 3 4 E"));
       PR1(are_equal_token_chains("E 2 3 4 5", "1 2 3 4 5"));

       PR1(are_equal_token_chains("1 2 3 4 5 6", "1 2 3 4 5 6"));
       PR1(are_equal_token_chains("1 2 3 4 5 6", "1 2 3 4 5 E"));
       PR1(are_equal_token_chains("E 2 3 4 5 6", "1 2 3 4 5 0"));

       PR1(are_equal_token_chains("1 2 3 4 5 6 7", "1 2 3 4 5 6 7"));
       PR1(are_equal_token_chains("1 2 3 4 5 6 7", "1 2 3 4 5 6 E"));
       PR1(are_equal_token_chains("E 2 3 4 5 6 7", "1 2 3 4 5 6 7"));

       pos_t p;
       PR1(is_head_of("", "",p));
       PR1(is_head_of("", " ",p));
       PR1(is_head_of("", " ",p));
       PR1(is_head_of(" ", " ",p));
       PR1(is_head_of("\t", "\n",p));
       PR1(is_head_of("a", "a",p));
       PR1(is_head_of("a", "b",p));
       PR1(is_head_of(" a", "a ",p));
       PR1(is_head_of("aa\tbb", " aa  bb ",p));
       PR1(is_head_of(" aa \n bb\t\n", "aa bb",p));
       PR1(is_head_of("A b C", "A b C",p));

       PR1(is_head_of("", "e",p));
       PR1(is_head_of("", " e",p));
       PR1(is_head_of("", " e",p));
       PR1(is_head_of(" ", " e",p));
       PR1(is_head_of("\t", "\ne",p));
       PR1(is_head_of("a", "ae",p));
       PR1(is_head_of("a", "be",p));
       PR1(is_head_of(" a", "a e",p));
       PR1(is_head_of("aa\tbb", " aa  bb e",p));
       PR1(is_head_of(" aa \n bb\t\n", "aa bbe",p));
       PR1(is_head_of("A b C", "A b Ce",p));
}
