/*
 * in this example, we print the contents of a file to the 
 * console. the text will be in Hungarian language.
 * so we must set the correct codec.
 */

#include <QTextStream>
#include <QFile>

int main()
{
	QFile data("szerelem");

	QString line;

	if (data.open(QFile::ReadOnly))
	{
		QTextStream in(&data);
		QTextStream out(stdout);

		out.setCodec("UTF-8");
		in.setCodec("UTF-8");

		do {
			line = in.readLine();
			out<< line << endl;
		} while (!line.isNull());
	}
}
