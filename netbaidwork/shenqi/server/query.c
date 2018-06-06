 #include "factory.h"
int query(char*argv1,char*buf)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="data";
	char query[300]={0};
	sprintf(query,"%s",argv1);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		return -1;
	}
	t=mysql_query(conn,query);
	if(t)
	{
		return -1;
	}else{
		res=mysql_use_result(conn);
		if(res)
	{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
				for(t=0;t<mysql_num_fields(res);t++)
				{
				
				 strcat(buf,row[t]);
				 
				}
			
			}

			
		}
		else 
			return -1;
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}
