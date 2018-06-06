#include"func.h"
int main(int argc,char* argv[])
{
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret=connect(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(-1==ret)
	{
		perror("connect");
		return -1;
	}
	train t;
	int cmd,i;
	char buf[1000]={0};
	char temp[20]={0};
	while(1){
		printf("注册 或 登录\n");
		scanf("%s",temp);
		int eixtflag=0;
		checkchm(temp,sfd,&eixtflag);
		if(eixtflag==1)
			break;

	}
	close(sfd);
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

