
.DEFAULT_GOAL := test

include include.mk
	
u-*    : CXXFLAGS +=-Wno-unused-variable

t-* u-*    : *.h
t-gz*  t-gunzip : LDFLAGS  += -lgzstream -lz

#CXXFLAGS +=  -D ASMLIB -I .. -I /usr/local/include
#LDFLAGS  +=  -L /usr/local/lib/ -l:alibelf64o.a -lgsl

test:	u-array u-powi
	./u-array
	./u-powi

t-timer: t-timer.cc
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS) -o $@ 


allt: t-timer t-equal t-gzstream t-gzip


install:
	mkdir -p /usr/local/include/lvvlib/
	cp *.h   /usr/local/include/lvvlib/

clean:
	rm -f *.html
	git clean -df


