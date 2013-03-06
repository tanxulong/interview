/*
 * QTime class provides clock time functions
 * In the following example, we print the current local time
 * to the console
 */
#include <QTextStream>
#include <QTime>

int main()
{
	QTextStream out(stdout);

	QTime qtime = QTime::currentTime();
	QString stime = qtime.toString(Qt::LocalDate);

	out << stime <<endl;
}
