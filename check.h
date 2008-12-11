
#include <iostream>
///////////////////////////////////////////////////////////////////////////////////// TEST MACROS
static __attribute__((unused)) bool all_pass=true;
//static __attribute__((unused)) bool result=false;
static bool result=false;
#define PASS "    pass    "
#define FAIL ">>> FAIL <<<"
#define RESULT   std::cout << (result ? PASS : FAIL) << " "  << __LINE__ << " \t";


#define CHECK(e)                result=(e);           all_pass = (all_pass && result); RESULT; std::cout << "check:        \t" #e  << std::endl;

#define	CHECKeq		CHECK_ARE_EQUAL
#define	CHECKneq	CHECK_NOT_EQUAL

#define CHECK_ARE_EQUAL(e1,e2)  result=((e1)==(e2));  all_pass = (all_pass && result); RESULT; \
	if (result) std::cout <<  "are equal:     \t" << #e1 "  ==  " #e2  << std::endl; \
	else	    std::cout <<  "are equal:     \t" << #e1 "  ==  " #e2  << "     (values: " << (e1) << ",  " << (e2) << ")" << std::endl;

#define CHECK_NOT_EQUAL(e1,e2)  result=((e1)!=(e2));  all_pass = (all_pass && result); RESULT; \
	if (result) std::cout <<  "are not equal: \t" << #e1 "  !=  " #e2  << std::endl; \
	else	    std::cout <<  "are not equal: \t" << #e1 "  !=  " #e2  << "   values: " << (e1) << ",  " << (e2) <<  std::endl;


