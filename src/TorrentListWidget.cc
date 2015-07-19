#include "TorrentListWidget.h"

TorrentListWidget::TorrentListWidget(Gtk::ListBox::BaseObjectType *cobject,
                                     const Glib::RefPtr<Gtk::Builder> builder) :
        Gtk::ListBox{cobject}
{ }

void TorrentListWidget::add(torrent_handle handle)
{
    std::cout << "adding " << handle.status().name << "\n";
    auto row = new TorrentListRow{handle};
    Gtk::ListBox::add(*row);
    torrents[handle] = row;
}

void TorrentListWidget::update(std::vector<torrent_status> statuses)
{
    for (auto &status : statuses) {
        TorrentListRow *row = torrents[status.handle];
        std::cout << status.name << "\n";
    }
}
