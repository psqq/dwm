
all: build

build:
	mkdir -p build
	export CC=/usr/bin/clang && export CXX=/usr/bin/clang++ && cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
	cd build && make -j4

rebuild:
	cd build && make -j4

install: rebuild
	cd build && sudo make install

transient: src/transient.c
	cc src/transient.c -o transient -lX11

man: all
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1

clean:
	rm -rf build

.PHONY: all build rebuild install man clean
