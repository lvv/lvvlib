
///////////////////////////////////////////////////////////////////////////////////// TEST MACROS
static __attribute__((unused) bool all_pass=true;
static __attribute__((unused) bool result=false;
#define PASS "    pass   "
#define FAIL ">>> FAIL <<<"
#define RESULT   cout << (result ? PASS : FAIL) << " "  << __LINE__ << " 	";


#define CHECK(e)                result=(e);           all_pass = (all_pass && result); RESULT; cout << "check:    " #e  << endl;

#define CHECK_ARE_EQUAL(e1,e2)  result=((e1)==(e2));  all_pass = (all_pass && result); RESULT; cout << "are equal: " << result << \
        " "   #e1 " = " << (e1) << \
        "	" #e2 " = " << (e2) << endl;

#define CHECK_NOT_EQUAL(e1,e2)  result=((e1)!=(e2));  all_pass = (all_pass && result); RESULT; cout << "not equal: " << result << \
        " "   #e1 " = " << (e1) << \
        "	" #e2 " = " << (e2) << endl;


