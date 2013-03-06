// This code example will create a database
// and insert some data into it

#include <my_global.h>
#include <mysql.h>

int main(int argc, char **argv)
{
	// Initiation of a connection handle structure
	MYSQL *conn;
		/* we declare a pointer to a MYSQL structure.
		 * This structure will server as a connection 
		 * handler
		 * the mysql_init() function obtains a connection
		 * handler
		 */
	conn = mysql_init(NULL);
		/*
		 * we check the return value.If the function fails,
		 * we print the error message and terminate the
		 * application
		 */
	if (conn == NULL)
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(EXIT_FAILURE);
	}
	// Creation of a connection
		/*
		 * the mysql_real_connect() function establishes a 
		 * connection to the database.We provide connection 
		 * handler, host name, user name and password 
		 * parameters to the function.The other four 
		 * parameters are the database name, port number,
		 * unix socket and finally the client flag.
		 */
	if (mysql_real_connect(conn, "localhost", "root", "asdf", "testdb", 0, NULL, 0) == NULL)
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(EXIT_FAILURE);
	}
	// Execution of a query
		/*
		 * The mysql_query() executes the SQL statement.
		 * In our case, the statement creates a new database
		 */
	if (mysql_query(conn, "CREATE TABLE writers(name VARCHAR(25))"))
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(EXIT_FAILURE);
	}
	mysql_query(conn, "INSERT INTO writers VALUES('Leo Tolstoy')");
	mysql_query(conn, "INSERT INTO writers VALUES('Jack London')");
	mysql_query(conn, "INSERT INTO writers VALUES('Honore de Balzac')");
	mysql_query(conn, "INSERT INTO writers VALUES('Lion Feuchtwanger')");
	mysql_query(conn, "INSERT INTO writers VALUES('Emile Zola')");

	// Closing of the connection
	mysql_close(conn);
	return 0;
}
