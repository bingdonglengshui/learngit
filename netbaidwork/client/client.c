#include"func.h"
void sockapi(char*config,int off,int* fd)
{   
   char buf[20]={0};
   FILE *fp;
   fp=fopen(config,"r");
   if(fp==NULL)
	   perror("fopen");
   fgets(buf,20,fp);
   fclose(fp);
   char temp[20]={0};
    strcpy(temp,strtok(buf," "));
	char temp1[20]={0};
    strcpy(temp1,strtok(NULL," "));
	*fd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==*fd)
	{
		perror("socket");
		return ;
	}
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(temp1)+off);
	ser.sin_addr.s_addr=inet_addr(temp);
	int ret=connect(*fd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(-1==ret)
	{
		perror("connect");
		return ;
	}
}
	int main(int argc,char* argv[])
	{ char configname[20]="config.txt";
		int off=0;
		int sfd;
       sockapi(configname,off,&sfd);
		while(1){
			char temp[20]={0};
			printf("注册 或 登录\n");
			scanf("%s",temp);
			int eixtflag=0;
			checkchm(temp,sfd,&eixtflag);
			if(eixtflag==1)
				break;
	        	}
		return 0;
	}
	int recv_n(int sfd,char* p,int len)
	{
		int ret;
		int total=0;
		while(total<len)
		{
			ret=recv(sfd,(char*)p+total,len-total,0);
			total=total+ret;
		}
		return 0;
	}

	int send_n(int sfd,char* p,int len)
	{
		int ret;
		int total=0;
		while(total<len)
		{
			ret=send(sfd,p+total,len-total,0);
			if(-1==ret)
			{
				return -1;
			}
			total=total+ret;
		}
		return 0;
	}

