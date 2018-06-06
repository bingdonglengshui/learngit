#include"func.h"
void* pthreadhand1 (void*aal)
{stmes mmt;
	train t;
	int off=0;
	int sfd;
sockapi("config.txt",off,&sfd);
     t.cmd=500;
	 send(sfd,&t,24,0);
	  send(sfd,&t,26,0);
	mmt=*(stmes*)aal;
	send(sfd,&mmt,sizeof(mmt),0);
	char md5buf[100]={0};
	md5sum(mmt.filename,md5buf);   
	struct stat stabuf;
	stat(mmt.filename,&stabuf);
	t.cmd=stabuf.st_size;
	t.len=strlen(md5buf);
	strcpy(t.buf,md5buf);
	send(sfd,&t,26,0);
	send(sfd,&t,26+t.len,0);
	recv(sfd,&t,4,0);
	if(t.cmd==404)
	{
		bzero(&t,sizeof(train));
		int ffd;
		ffd=open(mmt.filename,O_RDWR);
		if(ffd==-1)
			perror("opne");
		while((t.len=read(ffd,t.buf,sizeof(t.buf)))>0)
		{    
			send_n(sfd,(char*)&t,24+t.len);
		}
		send_n(sfd,(char*)&t,24+t.len);
		printf("\r100.00%%\n");
		close(ffd);
	}
	else{
		printf("\r100.00%%\n");
	}
	pthread_exit(NULL);
}

void* pthreadhand2 (void*aal)
{
	stmes mmt;
	train t;
	int off=0;
	      int sfd;
	     sockapi("config.txt",off,&sfd);
		 t.cmd=501;
		 send(sfd,&t,24,0);
		  send(sfd,&t,26,0);
	mmt=*(stmes*)aal;
	send(sfd,&mmt,sizeof(stmes),0);
	recv(sfd,&t,4,0);
	int filelen=t.cmd;
	time_t now,before;
	int ffd;
	int  total=0;
	int ret;
	float filetotal=0.0;
	char nnn[20]={0};
	sprintf(nnn,"%s.temp",mmt.filename);
	char buf[1000];
	struct stat statbuf;
	int l=stat(nnn,&statbuf);
	if(l!=-1&&filelen-statbuf.st_size>10000000)
	{total=total+statbuf.st_size; 
		t.cmd=404;
		t.len=statbuf.st_size;
		filetotal=statbuf.st_size;
		send(sfd,&t,26,0);
		ffd=open(nnn,O_RDWR|O_CREAT|O_APPEND,0600);
	}
	else
	{ 
		t.cmd=403;
		send(sfd,&t,26,0);
		ffd=open(nnn,O_RDWR|O_CREAT,0600);
	}
	while(total<filelen)
	{bzero(buf,sizeof(buf));
		if(filelen-total>1000)
		{
			ret=recv(sfd,buf,sizeof(buf),0);
		}
		else {
			ret=recv(sfd,buf,filelen-total,0);

		}
		if(ret==0)
			goto end;
		write(ffd,buf,ret);
		total=total+ret;

	}
end:
	printf("\r100.00%%\n");
			rename(nnn,mmt.filename);

}
void checkchm(char*temp,int sfd,int*fl)
{   train t;int i,cmd;
	bzero(&t,sizeof(train));
	char passwd[10];
	char rand[8]={0};
	char passwd1[10];
	char buf1[15]={0};
	char buf2[15]={0};
	char userbuf[15]={0};
	char psstx[1000]={0};
	char salt[20]={0};
	char *commod[10]={"cd","ls","puts","gets","remove","pwd","mkdir","login","useradd","exit"};
	for(i=0;i<10;i++)
	{ 
		if(!strcmp(temp,commod[i])) 
		{	
			cmd=401+i;
			t.cmd=cmd;
			send(sfd,&t,24,0);
			send(sfd,&t,26,0);
			switch(i)
			{
				case 8:
					{

l3:printf("输入用户名\n");
   scanf("%s",userbuf);
l1:strcpy(passwd,getpass("请输入密码\n"));	 
   strcpy(passwd1,getpass("请确认输入\n"));
   if(!strcmp(passwd,passwd1))
   {puts("ok");
   }
   else {
	   puts("密码不一致");
	   goto l1;
   }
   bzero(&t,sizeof(train));
   strcpy(t.user, userbuf);
   get_rand_str(rand);
   sprintf(salt,"%s%s","$6$",rand);
   strcpy(psstx,crypt(passwd,salt));
   t.len=sizeof(psstx);
   strcpy(t.buf,psstx);
   send(sfd,&t,26,0);
   send(sfd,&t,26+t.len,0);
   recv(sfd,&t,4,0);
   if(t.cmd==102)
   {
	   puts("注册成功\n");
   }
   else{
	   puts("用户名已被注册\n");
	   goto l3;
   }
					}
					break;
				case 7:
					printf("输入用户名\n");                    
					scanf("%s",userbuf);
					strcpy(passwd,getpass("请输入密码\n"));
					strcpy(t.user,userbuf);
					send(sfd,&t,26,0);
					recv(sfd,&t,4,0);
					if(t.cmd==101)
					{
						puts("密码错误或用户不存在\n");
						break;
					}
					bzero(&t,sizeof(train));
					recv(sfd,&t,26,0);
					int len=t.len;
					recv(sfd,&t,26+len,0);
					strcpy(psstx,crypt(passwd,t.buf));
					t.len=strlen(psstx);
					send(sfd,&t,26,0);
					strcpy(t.buf,psstx);
					send(sfd,&t,26+t.len,0);
					recv(sfd,&t,4,0);
					if(t.cmd==102)
					{puts("登录成功");
						while(1)
						{   bzero(buf1,15);
							bzero(buf2,15);
							puts("输入命令");
							scanf("%s",buf1);
							char ch;
							if((ch=getchar())!='\n')
								scanf("%s",buf2);
							else;
							for(i=0;i<10;i++)
							{
								if(!strcmp(buf1,commod[i])) 
								{	
									cmd=401+i;
									t.cmd=cmd;
									t.len=strlen(buf2);
									strcpy(t.buf,buf2);
									send(sfd,&t,24,0);
									send(sfd,&t,26,0);
									send(sfd,&t,26+t.len,0);
									switch(i)
									{case 0:
										break;
										case 2:
										{
											stmes aal;
											bzero(&t,sizeof(train));
											recv(sfd,&t,26,0);
											aal.procode=t.cmd;
											aal.ppfile=t.len;
											strcpy(aal.filename,buf2);
											strcpy(aal.user,t.user);
											pthread_t ppl;
											pthread_create(&ppl,NULL,pthreadhand1,&aal);
										}
										break;
										case 3:
										{
											stmes aal;
											bzero(&t,sizeof(train));
											recv(sfd,&t,26,0);
											aal.procode=t.cmd;
											aal.ppfile=t.len;
											strcpy(aal.filename,buf2);
											strcpy(aal.user,t.user);
											pthread_t ppll;
											pthread_create(&ppll,NULL,pthreadhand2,&aal);
										}

										break;
										case 1:
										case 5:
										bzero(&t,sizeof(train));
										recv(sfd,&t,26,0);
										int len=t.len;
										recv(sfd,&t,26+len,0);
										puts(t.buf);
										break;
										case 6:
										bzero(&t,sizeof(train));
										recv(sfd,&t,4,0);
										if(t.cmd==203)
											puts("文件已存在");
										else
											puts("创建成功");

										break;	
										case 9:
										puts("bye");
										*fl=1;

										return;
										break;	  
										default:
										break;

									}            
								}
							}
						}
					}
					else
					{
						puts("用户名或密码错误\n");
					}
					break;
				default:
					break;
			}

		}
	}

}
