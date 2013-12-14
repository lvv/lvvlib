
							namespace {

// names, token
struct  strref_t  {
	strref_t  ()                   : b(nullptr), e(nullptr)		{};
	strref_t  (pos_t b, pos_t e) : b(b), e(e)			{};
	strref_t  (const char* cs)					{ b=cs; e=cs; while(*e) ++e; };

	pos_t b, e;
	size_t size() const { return e-b; };
	//explicit operator std::string () const { return std::string(b,e); };
};

std::ostream&   operator<< (std::ostream& os, const strref_t& s)  {
	return os << " (" << std::string(s.b,s.e) << ") ";
};


struct  is_t {
	is() { for (auto c: " \t\n\r-,.:'~`!@#$%^&*()_-+={}[]|\\|:;\"',<>./?")  separato[c]=1; }
	char separator[256]={0};
};

is_t	is;



pos_t	get_tb(pos_t b, pos_t e)  { return std::find_if_not (b,e, [](char c){ return c==' ' || c=='\t' || c=='\n'; }); };
pos_t	get_te(pos_t b, pos_t e)  { return std::find_if     (b,e, [](char c){ return c==' ' || c=='\t' || c=='\n'; }); };

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

bool	are_equal_token_chains(strref_t n1, strref_t n2)  { return are_equal_token_chains(n1.b, n1.e,  n2.b, n2.e); }
bool	is_head_of(strref_t n1, strref_t n2, pos_t& match_e)  { return is_head_of(n1.b, n1.e,  n2.b, n2.e, match_e); }

							}
