
#include ../Makefile

WEB_DESTDIR ?= /tmp/html
ASCIIDOC ?= asciidoc

show: web_install
	firefox $(WEB_DESTDIR)/index.html


index.html: index.txt
	$(ASCIIDOC)  -o $@  $<

web_install: index.html 
	mkdir -p  $(WEB_DESTDIR)
	cp -uv $^ $(WEB_DESTDIR)

clean:
	rm -f *.html
	git clean -df
