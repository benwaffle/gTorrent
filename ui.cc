struct MagnetPopover : public Gtk::Popover
{
    Gtk::Entry entry;

    MagnetPopover(Gtk::MenuButton& button) :
        Gtk::Popover(button)
    {
        button.set_popover(*this);
        entry.show();
        this->add(entry);
    }
};

struct TorrentListRow : public Gtk::ListBoxRow
{
    Gtk::Grid grid;
    Gtk::Label name, status, eta;
    Gtk::ProgressBar progressbar;

    TorrentListRow() :
        Gtk::ListBoxRow{}
    {
        name.set_halign(Gtk::Align::ALIGN_START);
        status.set_halign(Gtk::Align::ALIGN_START);
        progressbar.set_hexpand(true);
        progressbar.set_valign(Gtk::Align::ALIGN_CENTER);
        eta.set_halign(Gtk::Align::ALIGN_END);

        grid.attach(name, 0, 0, 1, 1);
        grid.attach(status, 0, 1, 1, 1);
        grid.attach(progressbar, 0, 2, 2, 1);
        grid.attach(eta, 1, 1, 1, 1);

        this->add(grid);
    }
};

struct App : public Gtk::Application
{
    session sess;
    LTSource lt{sess};

    Gtk::ApplicationWindow *window{nullptr};
    Gtk::ListBox *torrent_list{nullptr};
    Gtk::Button *open_file{nullptr};
    Gtk::MenuButton *paste_link{nullptr};
    Gtk::MenuButton *settings{nullptr};

	void on_activate()
	{
		Gtk::Application::on_activate();

		auto builder = Gtk::Builder::create_from_resource("/gtorrent/window.ui");

        builder->get_widget("window", window);
        builder->get_widget("torrent_list", torrent_list);
        builder->get_widget("open_file", open_file);
        builder->get_widget("paste_link", paste_link);
        builder->get_widget("settings", settings);

		this->add_window(*window);
        new MagnetPopover(*paste_link);

		/*
		button->signal_clicked().connect([&]() {
			add_torrent_params add;
			add.ti = new torrent_info("debian.torrent");
			sess->async_add_torrent(add);
		});
		*/

		lt.attach();
		lt.set_callback([&](alert *a){
			// std::string msg{a->what()}; msg += "\n";
			delete a;
		});

        for (int i{0}; i < 10; ++i)
            torrent_list->add(*Gtk::manage(new TorrentListRow));

		window->show_all();
	}

	App() :
        Gtk::Application{"me.gtorrent"}
	{
		sess.set_alert_mask(alert::all_categories);
		sess.start_dht();
		sess.start_lsd();
		sess.start_upnp();
		sess.start_natpmp();
	}

	~App()
	{
		sess.stop_dht();
		sess.stop_lsd();
		sess.stop_upnp();
		sess.stop_natpmp();
	}
};

int main(int argc, char *argv[])
{
	return App{}.run(argc, argv);
}
