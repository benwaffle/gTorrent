#pragma once

#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/listboxrow.h>
#include <gtkmm/progressbar.h>

#include <libtorrent/torrent.hpp>

using namespace libtorrent;

struct TorrentListRow : public Gtk::ListBoxRow
{
    Gtk::Grid grid;
    Gtk::Label name, status, eta;
    Gtk::ProgressBar progressbar;
    torrent_handle handle;

    TorrentListRow(torrent_handle);
};
