/*
 * Some people prefer to put their image into the database,
 * prefer to keep them on the file system for their 
 * applications.Technical diffculties aries when we work 
 * with millions of images.
 * Images are binary data.MySQL database has a special data
 * type to store binary data called 
 * BLOB (binary large object)
 */

#include <my_global.h>
#include <mysql.h>

int main(int argc, char **argv)
{
	MYSQL *conn;

	int len, size;
	char data[1000*1024];	// Image can be max 1 MB
	char chunk[2*1000*1024+1];
	char query[1024*5000];

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

	fp = fopen("image.png", "rb");
	size = fread(data, 1, 1024*1000, fp);
	// here we open the image and read it into the data array
	mysql_real_escape_string(conn, chunk, data, size);
	
	/*
	 * Binary data can obtain special characters, that might
	 * cause troubles in the statements.We must escape them.
	 * The mysql_real_escape_string() puts the encoded data
	 * into the chunk array.In theory, every character might
	 * be a special character. That's why the chunk array 
	 * two times as big as the data array. The function also
	 * adds a terminating null character.
	 */
	
	// these two code lines prepare the MySQL query
	char *stat = "INSERT INTO images(id, data) VALUES('1', '%s')";
	len = snprintf(query, sizeof(stat) + sizeof(chunk), stat, chunk);

	mysql_real_query(conn, query, len);
	
	fclose(fp);
	mysql_close(conn);
	return 0;
}
