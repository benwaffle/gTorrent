#include <gtkmm.h>
#include <libtorrent/session.hpp>

#include "ltsource.h"

struct App : public Gtk::Application
{
    libtorrent::session sess;
    LTSource lt{sess};

    Gtk::ApplicationWindow *window{nullptr};
    Gtk::ListBox *torrent_list{nullptr};
    Gtk::Button *open_file{nullptr};
    Gtk::MenuButton *paste_link{nullptr};
    Gtk::MenuButton *settings{nullptr};

    App();
    ~App();
    void on_activate();
};
