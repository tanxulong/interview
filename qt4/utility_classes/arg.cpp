// shows an argument substitution

#include <QTextStream>

int main()
{
	QString string = "What if I gave you %1 red roses?";
	int num = 21;

	QTextStream out(stdout);
	out<< string.arg(num) << endl;
}
