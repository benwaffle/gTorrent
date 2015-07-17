CXX = clang++
CXXFLAGS = $(shell pkg-config --cflags gtkmm-3.0 libtorrent-rasterbar) -std=c++14 -g
LDLIBS   = $(shell pkg-config --libs   gtkmm-3.0 libtorrent-rasterbar) -g
all: main.cc libtorrent_gsource.cc ui.cc util.cc resources.c
	$(CXX) $(CXXFLAGS) $(LDLIBS) main.cc -o main
resources.c: $(shell glib-compile-resources --generate-dependencies resources.xml)
	glib-compile-resources --generate-source --target=$@ resources.xml
