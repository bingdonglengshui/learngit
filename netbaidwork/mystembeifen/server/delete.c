#include"factory.h"
int  delete(char *p)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="data";
	char query[200]={0};
	sprintf(query,"%s",p);
	int t,r;
	conn=mysql_init(NULL);
	mysql_real_connect(conn,server,user,password,database,0,NULL,0);
	t=mysql_query(conn,query);
	mysql_close(conn);
	return 0;
}
