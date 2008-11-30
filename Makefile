
#.DEFAULT_GOAL := t-cdf-model-gp

include include.mk
	
t-*     : lvv.h math.h check.h
t-gz*  t-gunzip : LDFLAGS  += -lgzstream -lz

LDFLAGS += -lgsl -lgslcblas

t-cdf-model: t-cdf-model.cc *.h

t-root: LDFLAGS  +=  -lgsl -lgslcblas -lm -L /usr/local/lib -lo2scl_base -lo2scl_other
t-root: CXXFLAGS +=  -I/usr/local/include/o2scl

allt: t-timer t-equal t-gzstream t-gzip

install:
	mkdir -p /usr/local/include/lvvlib/
	cp *.h   /usr/local/include/lvvlib/

clean:
	rm -f *.html
	git clean

