// Simple unit test.
// Part of lvvlib - https://github.com/lvv/lvvlib
// Copyright (c) 2000-2013
// Leonid Volnitsky (Leonid@Volnitsky.com)
				
				#ifndef LVV_CHECK_H
				#define LVV_CHECK_H
#include <iostream>
	using std::cout;
	using std::endl;
//#include <lvv/math.h>

				namespace check {
				
///////////////////////////////////////////////////////////////////////////////////// TEST MACROS
static __attribute__((unused)) bool all_pass=true;
static bool result=false;
#define PASS "    pass    "
#define FAIL ">>> FAIL <<<"
#define RESULT   std::cout << (check::result ? PASS : FAIL) << " "  << __LINE__ << "\t\t";


#define CHECK(e)                check::result=(e);           check::all_pass = check::all_pass  && check::result;   RESULT; std::cout << "check:        \t" #e  << std::endl;

/*
#define CHECK_ARE_FP_EQUAL(e1,e2)  result=(eq((e1),(e2)));  all_pass = (all_pass && result); RESULT; \
	if (result) std::cout <<  "are equal:     \t" << #e1 "\t ==  " #e2  << std::endl; \
	else	    std::cout <<  "are equal:     \t" << #e1 "\t ==  " #e2  << "     (values: " << (e1) << ",  " << (e2) << ")" << std::endl;
*/

#define CHECK_TYPES_ARE_SAME(T,U)  check::result=std::is_same<T,U>::value;  check::all_pass = (check::all_pass && check::result); RESULT; \
	if (check::result) std::cout <<  "same:     \t" << #T "\t ==  " #U  << std::endl; \
	else	           std::cout <<  "same:     \t" << #T "\t ==  " #U  << "     (values: " << type2name<T>() << ",  " << type2name<U>() << ")" << std::endl;

#define CHECK_ARE_EQUAL(e1,e2)  check::result=((e1)==(e2));  check::all_pass = (check::all_pass && check::result); RESULT; \
	if (check::result) std::cout <<  "are equal:     \t" << #e1 "\t ==  " #e2  << std::endl; \
	else	           std::cout <<  "are equal:     \t" << #e1 "\t ==  " #e2  << "     (values: " << (e1) << ",  " << (e2) << ")" << std::endl;

#define CHECK_NOT_EQUAL(e1,e2)  check::result=((e1)!=(e2));  check::all_pass = (check::all_pass && check::result); RESULT; \
	if (check::result) std::cout <<  "are not equal: \t" << #e1 "\t !=  " #e2  << std::endl; \
	else	           std::cout <<  "are not equal: \t" << #e1 "\t !=  " #e2  << "   values: " << (e1) << ",  " << (e2) <<  std::endl;


#define CHECK_EXIT \
	std::cout << (check::all_pass ? "\n------------ all pass ------------\n" : "\n!!!!!!!!!  SOME FAILED  !!!!!!!!\n"); \
	exit(check::all_pass ? 0 : 1);

// aliases
#define	CHECKeq		CHECK_ARE_EQUAL
#define	CHECKneq	CHECK_NOT_EQUAL

				}; 	// namespace check
				#endif  // LVV_CHECK_H
