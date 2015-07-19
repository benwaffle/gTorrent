#pragma once

#include <libtorrent/session.hpp>
#include <glibmm/main.h>

struct LTSource : public Glib::Source
{
    std::shared_ptr<libtorrent::session> sess;
    libtorrent::alert *a = nullptr;

    LTSource(std::shared_ptr<libtorrent::session> sess);

    bool prepare(int &timeout);

    bool check();

    bool dispatch(sigc::slot_base *slot);

    void set_callback(sigc::slot<void, libtorrent::alert *> slot);
};