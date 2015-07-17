#include "util.h"

GtkWidgetClass *get_widget_class(Gtk::Widget *w)
{
    return GTK_WIDGET_CLASS(G_OBJECT_GET_CLASS(w->gobj()));
}
