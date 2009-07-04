
#include ../Makefile

WEB_DESTDIR ?= /tmp/localweb
ASCIIDOC ?= asciidoc --unsafe
.PHONY = show localweb

show: localweb
	firefox $(WEB_DESTDIR)/array.html


%.html: %.txt
	rm -f $@
	$(ASCIIDOC)  -o $@  $<

localweb:	array.html
	mkdir -p  $(WEB_DESTDIR)
	cp -uv $^ $(WEB_DESTDIR)

clean:
	rm -f *.html
	git clean -df
