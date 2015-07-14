CXX = clang++
CXXFLAGS = $(shell pkg-config --cflags gtkmm-3.0 libtorrent-rasterbar) -std=c++14 -g
LDLIBS   = $(shell pkg-config --libs   gtkmm-3.0 libtorrent-rasterbar) -g
all: main
clean:
	rm main
