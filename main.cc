#include <gtkmm.h>
#include <libtorrent/session.hpp>
#include <iostream>
#include <deque>

using namespace std;
using namespace libtorrent;
using namespace Glib;

// what the fuck
template <typename Ret = void, typename... Args>
static Ret call(sigc::slot_base *slot, Args... args)
{
  return (*static_cast<sigc::slot<Ret, Args...>*>(slot))(args...);
}

struct LTSource : public Source
{
    shared_ptr<session> sess;
    alert *a = nullptr;

    LTSource(shared_ptr<session> sess) : sess(sess) {}

    bool prepare(int& timeout)
    {
      timeout = -1;
      a = sess->pop_alert().release();
      return a != nullptr;
    }

    bool check()
    {
      return a != nullptr;
    }

    bool dispatch(sigc::slot_base *slot)
    {
      if (slot && a) {
        call(slot, a);
        a = nullptr;
      }
      return true;
    }

    void set_callback(sigc::slot<void, alert*> slot)
    {
      this->connect_generic(slot);
    }
};

struct App : public Gtk::Application
{
    shared_ptr<session> sess;
    unique_ptr<LTSource> lt;

    App() : Gtk::Application("me.gtorrent")
    {
        sess = make_shared<session>();
        sess->set_alert_mask(alert::all_categories);
        sess->start_dht();
        sess->start_lsd();
        sess->start_upnp();
        sess->start_natpmp();
    }

    ~App() {
        sess->stop_dht();
        sess->stop_lsd();
        sess->stop_upnp();
        sess->stop_natpmp();
    }

    Gtk::TextView *tv = nullptr;
    Gtk::ScrolledWindow *scroll = nullptr;

    void on_activate()
    {
        Gtk::Application::on_activate();

        auto builder = Gtk::Builder::create_from_file("window.ui");

        Gtk::ApplicationWindow *win = nullptr;
        Gtk::Button *button = nullptr;
        builder->get_widget("window", win);
        builder->get_widget("add_torrent", button);
        builder->get_widget("log", tv);
        builder->get_widget("scroll", scroll);

        add_window(*win);

        button->signal_clicked().connect(sigc::slot<void>([&]() {
          add_torrent_params add;
          add.ti = new torrent_info("debian.torrent");
          sess->async_add_torrent(add);
        }));

        lt = make_unique<LTSource>(sess);
        lt->attach();
        lt->set_callback([&](alert *a){
          string msg{a->what()};
          msg += "\n";
          tv->get_buffer()->insert_at_cursor(msg);

          auto adj = scroll->get_vadjustment();
          adj->set_value(adj->get_upper());

          delete a;
        });

        win->show_all();
    }
};

int main(int argc, char *argv[])
{
    return App().run(argc, argv);
}
