// This code example will create a database.

#include <my_global.h>
#include <mysql.h>

int main(int argc, char **argv)
{
	MYSQL *conn;
	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(EXIT_FAILURE);
	}
	if (mysql_real_connect(conn, "localhost", "root", "asdf", NULL, 0, NULL, 0) == NULL)
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(EXIT_FAILURE);
	}
	if (mysql_query(conn, "create database testdb"))
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(EXIT_FAILURE);
	}
	mysql_close(conn);
	return 0;
}
