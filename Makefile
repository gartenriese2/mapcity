.PHONY: all clean distclean legacy

all: build/Makefile
	@make -j -C build
	@mkdir -p bin
	@cp build/mapcity bin

legacy: build_legacy/Makefile
	@make -j -C build_legacy
	@mkdir -p bin
	@cp build_legacy/mapcity bin/mapcity_legacy

build_legacy/Makefile: CMakeLists.txt
	@mkdir -p build_legacy
	@cd build_legacy; cmake -DMONOENGINE_LEGACY=1 ..

build/Makefile: CMakeLists.txt
	@mkdir -p build
	@cd build; cmake ..

clean:
	rm -rf build/* build_legacy/* contrib/* bin/*

distclean:
	rm -rf build build_legacy imgui.ini contrib bin dl
