#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
int main(int argc,char* argv[])
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char buf[1000]={0};
	char* database="data";//要访问的数据库名称
	char query[300]="select filetype  from file where filename=";
	sprintf(query,"%s'%s'",query,argv[1]);
	puts(query);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
	//	printf("Query made...\n");
		res=mysql_use_result(conn);
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
				//printf("num=%d\n",mysql_num_fields(res));//列数
				for(t=0;t<mysql_num_fields(res);t++)
				{
						strcat(buf,row[t]);
						strcat(buf,"    ");
				}
		strcat(buf,"121212121212121212121212\n");
			}
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
printf("12%s12",buf);
	return 0;
}
