
.DEFAULT_GOAL := u-array-r

include include.mk
	

t-* u-*    : *.h

#CXXFLAGS +=  -D ASMLIB -I .. -I /usr/local/include
#LDFLAGS  +=  -L /usr/local/lib/ -l:alibelf64o.a -lgsl

id:
	@echo "****ID  " $(ID) |cat -A
	@echo "****_cc " $(_cc) |cat -A
	@echo "****_rev " $(_rev) |cat -A
	@echo "****_date " $(_date) |cat -A
	@echo "****_cpu " $(_cpu) |cat -A
	@echo "****_mhz " $(_mhz) |cat -A

test:	u-array u-powi
	./u-array
	./u-powi

testall:	u-array u-powi
	./u-array
	./u-powi

b-array: SPEED = OPTIMIZE

b-array-m: b-array
	g++      -DID='"."' b-array.cc -o b-array   -Wall -std=c++0x  -I /home/lvv/p/ -I /usr/include/boost-1_37/  -DNDEBUG  -DNOCHECK   -I /usr/local/include -Wstrict-aliasing=2  -pipe -Wno-reorder -Wno-sign-compare  -O3 -fwhole-program --combine  -fopenmp -fomit-frame-pointer -funsafe-loop-optimizations  -march=opteron -static	
	-O3

t-timer: t-timer.cc
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS) -o $@ 


allt: t-timer t-equal t-gzstream t-gzip



install:
	mkdir -p /usr/local/include/lvvlib/
	cp *.h   /usr/local/include/lvvlib/

clean:
	rm -f *.html
	git clean -df


WEB_DESTDIR ?= /tmp/html-lopti
ASCIIDOC ?= /usr/local/bin/asciidoc

show: web_install                                                                                                                                              
	firefox $(WEB_DESTDIR)/index.html

index.html: README.txt
	$(ASCIIDOC)  -o $@  $<

web_install: index.html 
	mkdir -p  $(WEB_DESTDIR)
	cp -uv $^ $(WEB_DESTDIR)


