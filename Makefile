
.DEFAULT_GOAL := fit
	
t-*     : lvvlib.h lvvmath.h lvvcheck.h
t-gz*  t-gunzip : LDFLAGS  += -lgzstream -lz

LDFLAGS += -lgsl -lgslcblas

fit: t-fit
	t-fit | gph
	
allt: t-timer t-equal t-gzstream t-gzip

include include.mk
