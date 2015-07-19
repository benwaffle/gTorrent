#include "ltsource.h"
#include "util.h"

LTSource::LTSource(std::shared_ptr<libtorrent::session> sess) :
        Glib::Source{},
        sess{sess}
{ }

bool LTSource::prepare(int &timeout)
{
    timeout = 0; // no fds, don't block
    return check();
}

bool LTSource::check()
{
    if (!a)
        a = sess->pop_alert().release();
    return a != nullptr;
}

bool LTSource::dispatch(sigc::slot_base *slot)
{
    if (a && slot) {
        call_slot_base(slot, a);
        a = nullptr;
    }
    return true;
}

void LTSource::set_callback(sigc::slot<void, libtorrent::alert *> slot)
{
    this->connect_generic(slot);
}
