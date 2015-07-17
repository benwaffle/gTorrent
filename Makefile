CXX = clang++
CXXFLAGS = $(shell pkg-config --cflags gtkmm-3.0 libtorrent-rasterbar) -std=c++14 -g -O2

# resources.c
CC = clang
CFLAGS = $(shell pkg-config --cflags gtk+-3.0) -g

LDLIBS   = $(shell pkg-config --libs   gtkmm-3.0 libtorrent-rasterbar) -g

# main.cc forces make to link objects with $(CXX)
main:              \
	main.cc    \
	ltsource.o \
	ui.o       \
	util.o     \
	resources.o

resources.c: resources.xml $(shell glib-compile-resources --generate-dependencies resources.xml)
	glib-compile-resources --generate-source --target=$@ $<


.PHONY: clean
clean:
	-rm *.o resources.c