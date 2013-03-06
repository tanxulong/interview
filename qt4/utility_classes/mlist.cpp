/*
 * The QList is one of the generic QT4's containers.
 * It is used to store a list of values and provides
 * fast index-based access as well as insertions and
 * removals.
 */

#include <QTextStream>
#include <QList>

int main()
{
	QTextStream out(stdout);

	QList<QString> list;
	list << "Balzac" << "Tolstoy" << "Guldbrassen"
		<< "London" << "Galsworthy" << "Sienkiewicz";
	
	qSort(list);	// we sort alphabetically the list
	
	for (int i = 0; i < list.size(); i++)
	{
		out<< list.at(i) <<endl;
	}
}
