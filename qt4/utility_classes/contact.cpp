/*
 * The QString class is used to work with strings.
 * this is probably the most import utility class
 * available in QT4 programming library
 */

// this example concatenates three strings

#include <QTextStream>

int main()
{
	QString a = "Disziplin ";
	QString b = " ist ";
	QString c = "Macht.\n";

	QTextStream out(stdout);
	out << a + b +c;
}
