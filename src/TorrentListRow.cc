#include "TorrentListRow.h"

TorrentListRow::TorrentListRow(torrent_handle handle) :
        Gtk::ListBoxRow(),
        handle{handle}
{
    this->set_selectable(false);

    name.set_halign(Gtk::Align::ALIGN_START);
    status.set_halign(Gtk::Align::ALIGN_START);
    progressbar.set_hexpand(true);
    progressbar.set_valign(Gtk::Align::ALIGN_CENTER);
    progressbar.set_show_text(true);
    eta.set_halign(Gtk::Align::ALIGN_END);

    grid.attach(name, 0, 0, 1, 1);
    grid.attach(status, 0, 1, 1, 1);
    grid.attach(progressbar, 0, 2, 2, 1);
    grid.attach(eta, 1, 1, 1, 1);

    this->add(grid);
    this->show_all();
}
