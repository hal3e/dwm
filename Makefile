# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dwm.c util.c
OBJ = ${SRC:.c=.o}

all: dwm stest

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk
stest.o: arg.h config.mk

config.h:
	cp config.def.h $@

dwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

stest: stest.o
	${CC} -o $@ stest.o ${LDFLAGS}

clean:
	rm -f dwm stest stest.o ${OBJ} dwm-${VERSION}.tar.gz

dist: clean
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README arg.h config.def.h config.mk\
		dwm.1 drw.h stest.1 stest.c util.h ${SRC} dwm.png transient.c dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf dwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f dwm stest ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm ${DESTDIR}${PREFIX}/bin/stest
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	sed "s/VERSION/${VERSION}/g" < stest.1 > ${DESTDIR}${MANPREFIX}/man1/stest.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1 ${DESTDIR}${MANPREFIX}/man1/stest.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
		${DESTDIR}${PREFIX}/bin/stest\
		${DESTDIR}${MANPREFIX}/man1/dwm.1\
		${DESTDIR}${MANPREFIX}/man1/stest.1

.PHONY: all clean dist install uninstall
