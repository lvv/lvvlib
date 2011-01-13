
.DEFAULT_GOAL := u-array-r

include include.mk
	

u-*    : CXXFLAGS +=
#t-* u-*    : *.h

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

t-png: CXXFLAGS += -I..  -O3  -Wall -march=native -DNDEBUG -I /home/lvv/p/ -std=c++0x  -lpng

t-lin-r: t-lin
	echo -e "aaaa\n1 2 3\nA: 11 22 33 44" | ./t-lin


b-array-m: b-array
	g++      -DID='"."' b-array.cc -o b-array   -Wall -std=c++0x  -I /home/lvv/p/ -I /usr/include/boost-1_41/  -DNDEBUG  -DNOCHECK   -I /usr/local/include -Wstrict-aliasing=2  -pipe -Wno-reorder -Wno-sign-compare  -O3 -fwhole-program --combine  -fopenmp -fomit-frame-pointer -funsafe-loop-optimizations  -march=opteron -static	
	-O3

t-timer: t-timer.cc
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS) -o $@ 


allt: t-timer t-equal t-gzstream t-gzip



install:
	rm -rf   /usr/local/include/{lvv,lvvlib}/
	mkdir -p /usr/local/include/lvv/
	cp *.h   /usr/local/include/lvv/
	ln -sf    /usr/local/include/lvv/   /usr/local/include/lvvlib

debug_install:
	rm -rf   /usr/local/include/{lvv,lvvlib}/
	mkdir -p /usr/local/include/lvv/
	cd /;  ln -vs $(PWD)/*.h   /usr/local/include/lvv/
	ln -sf    /usr/local/include/lvv/   /usr/local/include/lvvlib

clean:
	rm -f *.html
	find -type f -executable -exec rm {} \;
	git clean -df

t-s_pool-r: 
	bash -c 'for i in  {1..222};  do echo ===== $$i ======== ; done  |  ./t-s_pool' 

