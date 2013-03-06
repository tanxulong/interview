// this example builds a string by means of appending text
// one after the other
#include <QTextStream>

int main()
{
	QString string = "Whether I shall ";
	string.append("turn out to be the hero of my own life, \n");
	string.append("or whether that station will be held by anybody else, \n");
	string.append("these pages must show.\n");

	QTextStream out(stdout);
	out<< string;
}
