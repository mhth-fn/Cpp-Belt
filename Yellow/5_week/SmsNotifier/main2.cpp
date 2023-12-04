
class INotifier{
public:
	virtual void Notify(const string& message) const = 0;
};

class SmsNotifier : public INotifier {
public:
	SmsNotifier(const string& n)
	: num(n) {}

	void Notify(const string& mes) const
	{
		SendSms(num, mes);
	}

	const string num;
};

class EmailNotifier : public INotifier {
public:
	EmailNotifier(const string& email)
	: mail(email){}

	void Notify(const string& mes) const{
		SendEmail(mail, mes);
	}

	const string mail;
};


void Notify(INotifier& notifier, const string& message) {
  notifier.Notify(message);
}
