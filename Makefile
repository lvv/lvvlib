
#.DEFAULT_GOAL := t-cdf-model-gp

include include.mk
	
t-*     : lvv.h math.h check.h
t-gz*  t-gunzip : LDFLAGS  += -lgzstream -lz

CXXFLAGS=  -D ASMLIB -I .. -I /usr/local/include
LDFLAGS=  -L /usr/local/lib/ -l:alibelf64o.a

t-timer: t-timer.cc
        $(CXX) $(CXXFLAGS) $< $(LDFLAGS) -o $@ 

t-root: LDFLAGS  +=  -lgsl -lgslcblas -lm -L /usr/local/lib -lo2scl_base -lo2scl_other
t-root: CXXFLAGS +=  -I/usr/local/include/o2scl

allt: t-timer t-equal t-gzstream t-gzip

install:
	mkdir -p /usr/local/include/lvvlib/
	cp *.h   /usr/local/include/lvvlib/

clean:
	rm -f *.html
	git clean -df

