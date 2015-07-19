#pragma once

#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/listboxrow.h>
#include <gtkmm/progressbar.h>

#include <libtorrent/torrent.hpp>
#include <gtkmm/image.h>

using namespace libtorrent;

struct TorrentListRow : public Gtk::ListBoxRow
{
    Gtk::Grid grid;
    Gtk::Image icon;
    Gtk::Label name, status, eta;
    Gtk::ProgressBar progressbar;
    torrent_handle handle;

    TorrentListRow(torrent_handle);
};
