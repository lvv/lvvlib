
.DEFAULT_GOAL := t-multimin-gp
	
t-*     : lvv.h math.h check.h
t-gz*  t-gunzip : LDFLAGS  += -lgzstream -lz

LDFLAGS += -lgsl -lgslcblas

t-root: LDFLAGS +=  -lgsl -lgslcblas -lm -L /usr/local/lib -lo2scl_base -lo2scl_other
t-root: CXXFLAGS +=  -I/usr/local/include/o2scl

allt: t-timer t-equal t-gzstream t-gzip

install:
	cd /usr/local
	git checkout -b lvvlib 
	mkdir -p /usr/local/include/lvvlib/
	cp *.h   /usr/local/include/lvvlib/
	git commit -a -m up


include include.mk
