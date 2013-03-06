// This code example will Retrieving data the database
/* Create a connection
 * Execute query
 * Get the result set
 * Fetch all available rows
 * Free the result set
 */

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
	MYSQL_RES *result;
	MYSQL_ROW row;
	int  num_fields;
	int i;

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
		 * We execute the query, that will retrieve all
		 * names from the writers database
		 */
	if (mysql_query(conn, "SELECT * FROM writers"))
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(EXIT_FAILURE);
	}
		/*
		 * We get the result set
		 */
	result = mysql_store_result(conn);
		/*
		 * We get the number of fields in the table
		 */
	num_fields = mysql_num_fields(result);
		
		/*
		 * We fetch the rows and print them to the screen
		 */
	while ((row = mysql_fetch_row(result)))
	{
		for (i = 0; i < num_fields; i++)
		{
			printf("%s ", row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}
	// Free the resources.
	mysql_free_result(result);
	// Closing of the connection
	mysql_close(conn);
	return 0;
}
