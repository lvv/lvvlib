
.DEFAULT_GOAL := t-cdf-model-gp
	
t-*     : lvv.h math.h check.h
t-gz*  t-gunzip : LDFLAGS  += -lgzstream -lz

LDFLAGS += -lgsl -lgslcblas

t-cdf-model: t-cdf-model.cc *.h

t-root: LDFLAGS  +=  -lgsl -lgslcblas -lm -L /usr/local/lib -lo2scl_base -lo2scl_other
t-root: CXXFLAGS +=  -I/usr/local/include/o2scl

allt: t-timer t-equal t-gzstream t-gzip

install:
	cd /usr/local &&  git checkout lvvlib 
	mkdir -p /usr/local/include/lvvlib/
	cp *.h   /usr/local/include/lvvlib/
	cd /usr/local &&  git add /usr/local/include/lvvlib
	cd /usr/local &&  git commit -a -m up
	cd /usr/local &&  git checkout installed
	cd /usr/local &&  git merge lvvlib


include include.mk
