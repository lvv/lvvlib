// splits string into tokens
// part of lvvlib - https://github.com/lvv/lvvlib
				
#include<algorithm>
	using std::find_if;
	using std::find_if_not;

#include <assert.h>
							namespace {

typedef  const char*   	pos_t;

// names, token
struct  strref  {
	strref  ()                   : b(nullptr), e(nullptr)		{};
	strref  (pos_t b, pos_t e)   : b(b), e(e)			{};
	strref  (const char* cs)					{ b=cs; e=cs; while(*e) ++e; };

	pos_t b, e;
	size_t size() const { return e-b; };
	operator std::string () const { return std::string(b,e); };
	bool operator==(const char* p)        const { const char* pe=p;  while(*pe) ++pe;  return  e-b == pe-p  &&  std::equal(b,e, p); };
	bool operator==(const std::string& s) const { return  size_t(e-b) == s.size()   &&  std::equal(b,e, s.begin()); };
};

__attribute__((unused)) 
std::ostream&   operator<< (std::ostream& os, const strref& s)  {
	return os << " (" << std::string(s.b,s.e) << ") ";
};


struct  is_t {
	is_t() { for (auto c: " \t\n\r-,.:'~`!@#$%^&*()_-+={}[]|\\|:;\"',<>./?")  separator[(size_t)c]=1; }
	char separator[256]={0};
};

is_t	is;



////pos_t	get_tb(pos_t b, pos_t e)  { return std::find_if_not (b,e, [](char c){ return   c==' ' || c=='\t' || c=='\n' ; }); };
//pos_t	get_tb(pos_t b, pos_t e)  { assert(b<=e); return std::find_if     (b,e, [](char c){ return !(c==' ' || c=='\t' || c=='\n'); }); };
//pos_t	get_te(pos_t b, pos_t e)  { assert(b<=e); return std::find_if     (b,e, [](char c){ return   c==' ' || c=='\t' || c=='\n' ; }); };

pos_t	get_tb(pos_t b, pos_t e)  { assert(b<=e); return std::find_if     (b,e, [](char c){ return !is.separator[(size_t)c]; }); };
pos_t	get_te(pos_t b, pos_t e)  { assert(b<=e); return std::find_if     (b,e, [](char c){ return  is.separator[(size_t)c]; }); };

bool	are_equal_token_chains (pos_t b1, pos_t e1, pos_t b2, pos_t e2)  {

		pos_t   tb1;
		pos_t   te1 = b1;     

		pos_t   tb2;
		pos_t   te2 = b2;     

	while (
		(tb1=get_tb(te1,e1)),
		(tb2=get_tb(te2,e2)),
		tb1!=e1  &&  tb2!=e2  
	) {
		te1=get_te(tb1,e1);
		te2=get_te(tb2,e2);
		if ( !((te1-tb1)==(te2-tb2) && std::equal (tb1,te1, tb2)) )  return false;
	}

	return tb1==e1  &&  tb2==e2;
}

bool	is_head_of (pos_t b1, pos_t e1, pos_t b2, pos_t e2, pos_t& match_e)  {
                                          // (b1,e1) - token chain;  
					  // (b2,e2) - string; 
					  // reuturns true if (b2,e2) starts with (b1,e1) and sets end of match in  match_e
		pos_t   tb1;               
		pos_t   te1 = b1;     

		pos_t   tb2;
		pos_t   te2 = b2;     

	while (
		(tb1=get_tb(te1,e1)),
		(tb2=get_tb(te2,e2)),
		tb1!=e1  &&  tb2!=e2  
	) {
		te1=get_te(tb1,e1);
		te2=get_te(tb2,e2);
		if ( !((te1-tb1)==(te2-tb2) && std::equal (tb1,te1, tb2)) )  return false;
	}

	
	if ( tb1==e1) {			// if 1st ended -> match
		match_e = te2;
		return true;
	}  else {
		return false;
	}
}

bool	are_equal_token_chains(strref n1, strref n2)      { return are_equal_token_chains(n1.b, n1.e,  n2.b, n2.e); }
bool	is_head_of(strref n1, strref n2, pos_t& match_e)  { return is_head_of(n1.b, n1.e,  n2.b, n2.e, match_e); }

							}
