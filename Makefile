.PHONY: all clean distclean

all: build/Makefile
	@make -C build
	@mkdir -p bin
	@cp build/mapcity bin

build/Makefile: CMakeLists.txt
	@mkdir -p build
	@cd build; cmake ..

clean:
	make -C build clean
	rm -rf cache

distclean:
	rm -rf build cache contrib/monoengine bin/mapcity
