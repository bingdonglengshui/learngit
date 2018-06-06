#include"factory.h"
void factory_init(factory*p,int pthread_num,int pthread_capacity)
{
	p->pth=(pthread_t *)calloc(pthread_num,sizeof(pthread_t));
	p->que.que_capcacity=pthread_capacity;
	p->pthread_num=pthread_num;
	pthread_cond_init(&p->cond,NULL);
	pthread_mutex_init(&p->que.que_mutex,NULL);
}
void factory_start(factory*p)
{  int i;
	if(!p->start_flag)
	{ 
		for(i=0;i<p->pthread_num;i++)

			pthread_create(p->pth+i,NULL,pthread_hand,p);
	}
	p->start_flag=1;
}
void qu_inser(pque_t h,pnode_t pnew)
{
	if(h->que_head==NULL)
	{
		h->que_head=pnew;
		h->que_tail=pnew;
	}
	else
	{
		h->que_tail->nd_next=pnew;
		h->que_tail=pnew;
	}
	h->que_size++;
}   
void get_que(pque_t h,pnode_t *pcur)
{ *pcur=h->que_head;
	h->que_head=h->que_head->nd_next;
	h->que_size--;
}
void* pthread_hand(void *p)
{   uPcb puser;
	int logfd=open(FILENAME,O_RDWR|O_CREAT|O_APPEND,0600);
		close(1);
dup(logfd)
	close(logfd);
	bzero(&puser,sizeof(uPcb));	
	factory*pp=(factory*)p;
	pnode_t pcur;
	int ret;
	pque_t paa=&pp->que;
	while(1)
	{
		pthread_mutex_lock(&paa->que_mutex);
		if(paa->que_size==0&&paa->fdque_size==0)
		{ 
			pthread_cond_wait(&pp->cond,&paa->que_mutex);
		}
		if(paa->que_size>0)
		{

			if(paa->que_head->nd_sockfd==0)	
			{  
				pthread_mutex_unlock(&paa->que_mutex);
				pthread_cond_signal(&pp->cond);
				printf("pthread finish\n");
				pthread_exit(0); 
			}else{
				get_que(paa ,&pcur);
				pthread_mutex_unlock(&paa->que_mutex);
			}
		}
		else if(paa->fdque_size>0)
		{   
			fdget_que(paa ,&pcur);
			pthread_mutex_unlock(&paa->que_mutex);
			
		}

while(1)
{train t;
	int ret;
	bzero(&t,sizeof(train));
	ret=recv(pcur->nd_sockfd,&t,26,0);
	if(ret==0)
		break;
	switch(t.cmd){
		case 401:
			process1( pcur->nd_sockfd,&puser);
			break;
		case 402:
			process2(pcur->nd_sockfd,&puser);
			break;
		case 403:
		case 404:
			process3(pcur->nd_sockfd,&puser);
			break;
		case 405:
			process5(pcur->nd_sockfd,&puser);
			break;
		case 500:	
			process10(pcur->nd_sockfd);
			break;
		case 501:
			process11(pcur->nd_sockfd);
			break;
		case 406:
			process6( pcur->nd_sockfd,&puser);
			break;
		case 407:
			process7(pcur->nd_sockfd,&puser);
			break;
		case 409 :
			process8(pcur->nd_sockfd);
			break;
		case 408:
			{
				char tempname[15]={0};
				process9(pcur->nd_sockfd,tempname);
				strcpy(puser.username,tempname);
				puser.ppcode=0;
				puser.position=0;
			}
			break;
		case 410:
			{ time_t time2;
				time2=time(NULL);
				printf("client %s eixt   %s\n",puser.username,ctime(&time2));
			}
			goto end;
			break;
		default:
			break;
	}
}
end:
free(pcur);
}
return NULL;
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
void qu_dele(pque_t h)
{ pnode_t pcur=h->que_head;
	while(h->que_head)
	{ pcur=h->que_head;
		if(h->que_head->nd_next)
		{	h->que_head=h->que_head->nd_next;
			free(pcur);
		}
		else
		{
			h->que_head=NULL;
			h->que_tail=NULL;
		}
	}
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

	void fdqu_inser(pque_t h,pnode_t pnew)
{ if(h->fdque_head==NULL)
	{
		h->fdque_head=pnew;
		h->fdque_tail=pnew;
	}
	else
	{
		h->fdque_tail->nd_next=pnew;
		h->fdque_tail=pnew;
	}
	h->fdque_size++;
}   
void fdget_que(pque_t h,pnode_t *pcur)
{ *pcur=h->fdque_head;
	h->fdque_head=h->fdque_head->nd_next;
	h->fdque_size--;
}
