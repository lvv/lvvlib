
.DEFAULT_GOAL := t-multimin-gp
	
t-*     : lvvlib.h lvvmath.h lvvcheck.h
t-gz*  t-gunzip : LDFLAGS  += -lgzstream -lz

LDFLAGS += -lgsl -lgslcblas

t-root: LDFLAGS +=  -lgsl -lgslcblas -lm -L /usr/local/lib -lo2scl_base -lo2scl_other
t-root: CXXFLAGS +=  -I/usr/local/include/o2scl

# t-multimin-gp:

t-model-gp:
	
allt: t-timer t-equal t-gzstream t-gzip

include include.mk
