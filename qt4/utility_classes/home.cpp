/*
 * the QDir class provides access to directory structures
 * and their contents.
 */

#include <QTextStream>
#include <QDir>

int main()
{
	QTextStream out(stdout);
	QString home = QDir::homePath();
	out << home <<endl;
}
