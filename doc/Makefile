
#include ../Makefile

WEB_DESTDIR ?= /tmp/html
ASCIIDOC ?= /usr/local/bin/asciidoc --unsafe

show: web_install
	firefox $(WEB_DESTDIR)/index.html


%.html: %.txt
	$(ASCIIDOC)  -o $@  $<

web_install: index.html array.html
	mkdir -p  $(WEB_DESTDIR)
	cp -uv $^ $(WEB_DESTDIR)

clean:
	rm -f *.html
	git clean -df
