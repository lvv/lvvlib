
.DEFAULT_GOAL := it
	
t-*     : lvvlib.h lvvmath.h lvvcheck.h
t-gz*  t-gunzip : LDFLAGS  += -lgzstream -lz

LDFLAGS += -lgsl -lgslcblas

it: t-model
	t-model | gp
	
allt: t-timer t-equal t-gzstream t-gzip

include include.mk
