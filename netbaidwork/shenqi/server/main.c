#include"factory.h"
int fps[2];
void signalhand(int singnum)
{write(fps[1],&singnum,4);
}

int main(int argc,char**argv)
{
	char buf[30]={0};
	FILE *fp;
	fp=fopen("config.txt","r");
	if(fp==NULL)
		perror("fopen");
	fgets(buf,30,fp);
	fclose(fp);
	char temp[20]={0};
	strcpy(temp,strtok(buf," "));
	char temp1[20]={0};
	strcpy(temp1,strtok(NULL," "));
	int num1=atoi(strtok(NULL," "));
    int num2=atoi(strtok(NULL," "));
	int pthread_num=num1;
	int pthread_capacity=num2;
	factory fac;
	bzero(&fac,sizeof(factory));
	factory_init(&fac,pthread_num,pthread_capacity);
	factory_start(&fac);
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	int reuse=1;
	int ret;
	pipe(fps);
	signal(SIGINT,signalhand);
	ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	if(-1==ret)
	{
		perror("setsockopt");
		return -1;
	}
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(temp1));
	ser.sin_addr.s_addr=inet_addr(temp);
	ret=bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(-1==ret)
	{
		perror("bind");
		return -1;
	}
	listen(sfd,pthread_capacity);
	int new_fd;
	pnode_t pnew;
	int epf=epoll_create(1);
	struct epoll_event events,*eve;
	eve=(struct epoll_event*)calloc(5,sizeof(struct epoll_event ));
	bzero(&events,sizeof(struct epoll_event));
	events.events=EPOLLIN;
	events.data.fd=fps[0];
	epoll_ctl(epf,EPOLL_CTL_ADD,fps[0],&events);
	events.events=EPOLLIN;
	events.data.fd=sfd;
	epoll_ctl(epf,EPOLL_CTL_ADD,sfd,&events);
	int i,j;
	int gg;
	while(1)
	{ 
		gg=epoll_wait(epf,eve,5,-1);
		for(i=0;i<gg;i++)
		{
			if(eve[i].data.fd==sfd)
			{  
				new_fd=accept(sfd,NULL,NULL);
				train t;
				recv(new_fd,&t,24,0);
				if(t.cmd!=500&&t.cmd!=501)
				{  
					pnew=(pnode_t)calloc(1,sizeof(node_t));
					pnew->nd_sockfd=new_fd;
					pthread_mutex_lock(&fac.que.que_mutex);
					qu_inser(&fac.que,pnew);
					pthread_mutex_unlock(&fac.que.que_mutex);
					pthread_cond_signal(&fac.cond);
				}else{
					pnew=(pnode_t)calloc(1,sizeof(node_t));
					pnew->nd_sockfd=new_fd;
					pthread_mutex_lock(&fac.que.que_mutex);
					fdqu_inser(&fac.que,pnew);
					pthread_mutex_unlock(&fac.que.que_mutex);
					pthread_cond_signal(&fac.cond);
				}
			}
			if(eve[i].data.fd==fps[0])
			{
				read(fps[0],&j,4);
				pthread_cond_signal(&fac.cond);
				pthread_mutex_lock(&fac.que.que_mutex);
				qu_dele(&fac.que);
				pnew=(pnode_t)calloc(1,sizeof(node_t));
				pnew->nd_sockfd=0;
				qu_inser(&fac.que,pnew);
				pthread_mutex_unlock(&fac.que.que_mutex);
				int k=0;
				for(j=0;j<pthread_num;j++)
				{
					pthread_join(*(fac.pth+j),(void**)&k);

				}
				pthread_mutex_destroy(&fac.que.que_mutex);
				pthread_cond_destroy(&fac.cond);
				free(fac.pth);
				free(eve);
				pthread_exit(0);
			}
		}
	}
}
