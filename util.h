#include <gtkmm.h>

template <typename Ret = void, typename... Args>
Ret call_slot_base(sigc::slot_base *slot, Args... args)
{
    return (*static_cast<sigc::slot<Ret, Args...>*>(slot))(args...);
}

GtkWidgetClass *get_widget_class(Gtk::Widget *w);
