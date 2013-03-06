// about making a string uppercase or lowercase

#include <QTextStream>

int main()
{
	QString string = "The history of my life.";

	QTextStream out(stdout);
	out << string.toLower() << endl;
	out << string.toUpper() << endl;

}
