#include "factory.h"
void  insert(char *p1)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="data";
	char query[200]={0};
	sprintf(query,"insert into %s ",p1);
	puts(query);
	conn=mysql_init(NULL);
	mysql_real_connect(conn,server,user,password,database,0,NULL,0);
	mysql_query(conn,query);
	mysql_close(conn);
	return ;
}
