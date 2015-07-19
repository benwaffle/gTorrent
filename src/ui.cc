#include <map>
#include <vector>

#include <libtorrent/session.hpp>
#include <libtorrent/alert_types.hpp>

#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/stock.h>

#include "app.h"

using namespace libtorrent;

struct MagnetPopover : public Gtk::Popover
{
    Gtk::Entry entry;

    MagnetPopover(Gtk::MenuButton &button) :
            Gtk::Popover(button)
    {
        button.set_popover(*this);
        entry.show();
        this->add(entry);
    }
};

void App::on_activate()
{
    Gtk::Application::on_activate();

    auto builder = Gtk::Builder::create_from_resource("/gtorrent/window.ui");

    builder->get_widget("window", window);
    builder->get_widget_derived("torrent_list", torrent_list);
    builder->get_widget("open_file", open_file);
    builder->get_widget("paste_link", paste_link);
    builder->get_widget("settings", settings);

    new MagnetPopover(*paste_link);

    open_file->signal_clicked().connect([&]() {
        Gtk::FileChooserDialog fc{*window, "Open a .torrent"};
        fc.add_button("Open", Gtk::RESPONSE_ACCEPT);
        fc.add_button("Cancel", Gtk::RESPONSE_CANCEL);

        auto filter = Gtk::FileFilter::create();
        filter->set_name(".torrent files");
        filter->add_mime_type("application/x-bittorrent");
        fc.set_filter(filter);

        auto result = fc.run();
        if (result == Gtk::RESPONSE_ACCEPT) {
            auto file = fc.get_file();

            add_torrent_params add;
            add.ti = new torrent_info{file->get_path()};
            sess->async_add_torrent(add);
        }
    });

    lt.set_callback(sigc::mem_fun(*this, &App::handle_alert));
    lt.attach();

    Glib::signal_timeout().connect(sigc::bind_return(
            sigc::mem_fun(*sess, &libtorrent::session::post_torrent_updates),
            true), 100);
    Glib::signal_timeout().connect(sigc::bind_return([&]() {
        session_status status = sess->status();
        window->set_title(std::to_string(status.download_rate) + " B/s");
    }, true), 100);

    this->add_window(*window);
    window->show_all();
}

void App::handle_alert(alert *al)
{
    switch (al->type()) {
        case state_update_alert::alert_type: {
            state_update_alert *update = static_cast<state_update_alert *>(al);
            torrent_list->update(update->status);
            break;
        }

        case torrent_added_alert::alert_type: {
            torrent_added_alert *added = static_cast<torrent_added_alert *>(al);
            torrent_list->add_torrent(added->handle);
            break;
        }
    }

    delete al;
}

App::App() :
        Gtk::Application("me.gtorrent"),
        sess{std::make_shared<session>()},
        lt{sess}
{
    sess->set_alert_mask(alert::all_categories);
    sess->start_dht();
    sess->start_lsd();
    sess->start_upnp();
    sess->start_natpmp();
}

App::~App()
{
    sess->stop_dht();
    sess->stop_lsd();
    sess->stop_upnp();
    sess->stop_natpmp();
}
