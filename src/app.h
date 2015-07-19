#pragma once

#include <libtorrent/session.hpp>
#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/listbox.h>
#include <gtkmm/button.h>
#include <gtkmm/menubutton.h>

#include "ltsource.h"
#include "TorrentListWidget.h"

struct App : public Gtk::Application {
    std::shared_ptr<libtorrent::session> sess;
    LTSource lt;

    Gtk::ApplicationWindow *window{nullptr};
    TorrentListWidget *torrent_list{nullptr};
    Gtk::Button *open_file{nullptr};
    Gtk::MenuButton *paste_link{nullptr};
    Gtk::MenuButton *settings{nullptr};

    App();

    ~App();

    void on_activate();

    void handle_alert(libtorrent::alert *);
};
