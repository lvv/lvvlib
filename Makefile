
.DEFAULT_GOAL := it
	
t-*     : lvvlib.h lvvmath.h lvvcheck.h
t-gz*  t-gunzip : LDFLAGS  += -lgzstream -lz

LDFLAGS += -lgsl -lgslcblas

t-root: LDFLAGS +=  -lgsl -lgslcblas -lm -L /usr/local/lib -lo2scl_base -lo2scl_other
t-root: CXXFLAGS +=  -I/usr/local/include/o2scl

it: t-model
	t-model | gp
	
allt: t-timer t-equal t-gzstream t-gzip

include include.mk
