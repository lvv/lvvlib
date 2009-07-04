

WEB_DESTDIR ?= /tmp/localweb
ASCIIDOC ?= asciidoc --unsafe
.PHONY = show localweb

show: localweb
	firefox $(WEB_DESTDIR)/index.html


%.html: %.txt
	rm -f $@
	$(ASCIIDOC)  -o $@  $<

localweb:	index.html
	mkdir -p           $(WEB_DESTDIR)
	cp -uv $^ .*.png   $(WEB_DESTDIR)

clean:
	rm -f *.html
	git clean -df
