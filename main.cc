#include <gtkmm.h>

#include <libtorrent/session.hpp>
#include <memory>

using namespace libtorrent;
using namespace Glib;

// unified builds are fast
extern "C" {
	#include "resources.c"
}
#include "util.cc"
#include "libtorrent_gsource.cc"
#include "ui.cc"
