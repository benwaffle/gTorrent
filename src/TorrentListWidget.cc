#include "TorrentListWidget.h"

TorrentListWidget::TorrentListWidget(BaseObjectType *cobject,
                                     const Glib::RefPtr<Gtk::Builder> &builder) :
        Gtk::ListBox{cobject}
{ }

void TorrentListWidget::add_torrent(torrent_handle handle)
{
    auto row = Gtk::manage(new TorrentListRow{handle});
    torrents[handle] = row;
    row->name.set_label(handle.status().name);
    add(*row);
}

std::string state_to_string(torrent_status::state_t st)
{
    switch (st) {
        case torrent_status::state_t::queued_for_checking:
            return "Queued for checking";
        case torrent_status::state_t::checking_files:
            return "Checking files";
        case torrent_status::state_t::downloading_metadata:
            return "Downloading metadata";
        case torrent_status::state_t::downloading:
            return "Downloading";
        case torrent_status::state_t::finished:
            return "Finished";
        case torrent_status::state_t::seeding:
            return "Seeding";
        case torrent_status::state_t::allocating:
            return "Allocating";
        case torrent_status::state_t::checking_resume_data:
            return "Checking resume data";
    }
}

void TorrentListWidget::update(std::vector<torrent_status> statuses)
{
    for (auto &status : statuses) {
        TorrentListRow *row = torrents[status.handle];
        row->name.set_label(status.name);
        row->status.set_label(std::to_string(status.all_time_download) + " B / " +
                                      std::to_string(status.handle.torrent_file()->total_size()) + " B");
        row->progressbar.set_text(state_to_string(status.state));
        row->progressbar.set_fraction(status.progress);
    }
}
