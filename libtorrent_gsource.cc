struct LTSource : public Source
{
	session& sess;
	alert *a = nullptr;

	LTSource(session& sess) :
		sess(sess)
	{ }

	bool prepare(int& timeout)
	{
		timeout = 0; // no fds, don't block
		return check();
	}

	bool check()
	{
		if (!a)
			a = sess.pop_alert().release();
		return a != nullptr;
	}

	bool dispatch(sigc::slot_base *slot)
	{
		if (a && slot) {
			call_slot_base(slot, a);
			a = nullptr;
		}
		return true;
	}

	void set_callback(sigc::slot<void, alert*> slot)
	{
		this->connect_generic(slot);
	}
};
