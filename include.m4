changequote(«,»)dnl
changecom(«//»)
undefine(«format»)


define(«ADD», «
	pushdef(«tmp», eval($1+$2))
	undefine($1)
	define(«$1»,tmp)
	popdef(«tmp»)
»)dnl

define(«INCR», «define(«$1»,incr($1))»)dnl    


