
#include ../Makefile

DESTDIR ?= /tmp/html-lvvlib
ASCIIDOC ?= asciidoc

show: install
	firefox $(DESTDIR)/index.html


index.html: index.txt
	$(ASCIIDOC)  -o $@  $<

install: index.html 
	mkdir -p  $(DESTDIR)
	cp -uv $^ $(DESTDIR)

clean:
	rm -f *.html
	git clean -df
