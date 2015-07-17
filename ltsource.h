#include <glibmm.h>
#include <libtorrent/session.hpp>

struct LTSource : public Glib::Source
{
    libtorrent::session& sess;
    libtorrent::alert *a = nullptr;
 
    LTSource(libtorrent::session& sess);
    bool prepare(int& timeout);
    bool check();
    bool dispatch(sigc::slot_base *slot);
    void set_callback(sigc::slot<void, libtorrent::alert*> slot);
};
