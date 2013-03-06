/*
 * The QFile is a class for reading from and writing to files
 * in the first example, we write a sentence to a file
 */

#include <QTextStream>
#include <QFile>

int main()
{
	QFile data("myfile");

	if (data.open(QFile::WriteOnly))
	{
		QTextStream out(&data);
		out<<"You make me want to be a better man."<<endl;
	}
}

