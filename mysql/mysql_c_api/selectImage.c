//This code example will select images from MySQL database

#include <my_global.h>
#include <mysql.h>

int main(int argc, char **argv)
{
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;

	unsigned long *lengths;
	FILE *fp;

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(EXIT_FAILURE);
	}
	if (mysql_real_connect(conn, "localhost", "root", "asdf", "testdb", 0, NULL, 0) == NULL)
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(EXIT_FAILURE);
	}

	fp = fopen("image.png2", "wb");

	if (mysql_query(conn, "SELECT data FROM images WHERE id=1"))
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(EXIT_FAILURE);
	}

	result = mysql_store_result(conn);
	fwrite(row[0], lengths[0], 1, fp);
	mysql_free_result(result);

	fclose(fp);
	mysql_close(conn);
	return 0;
}
