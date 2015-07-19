#pragma once

#include <gtkmm/builder.h>
#include <gtkmm/listbox.h>
#include <libtorrent/torrent.hpp>

#include "TorrentListRow.h"

using namespace libtorrent;

struct TorrentListWidget : public Gtk::ListBox
{
    TorrentListWidget(BaseObjectType *, const Glib::RefPtr<Gtk::Builder>&);

    std::map<torrent_handle, TorrentListRow *> torrents{};

    void add_torrent(torrent_handle);

    void update(std::vector<torrent_status>);
};