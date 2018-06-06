#include"factory.h"
void process1(int fd,uPcb* pt)
{    train t;
	char temp[100]={0};
	char rete[1000]={0};
	recv(fd,&t,26,0);
	int len=t.len;
	recv(fd,&t,26+len,0);
	if(!strcmp(t.buf,".."))
	{ 
		if(pt->position==0);	
		else{
			pt->position=pt->position-1;
			bzero(temp,100); 
			sprintf(temp,"select ppfile from file where user='%s' and procode=%d and code=%d",pt->username,pt->position,pt->ppcode);
			bzero(rete,1000);
			query(temp,rete);
			if(strcmp(rete,""))
			{	 
				pt->ppcode=atoi(rete);

			}
			else
				pt->ppcode=0;
		}
	}
	else{
		sprintf(temp,"select code  from file where filename='%s' and filetype='-'",t.buf);
		query(temp,rete);
		if(strcmp(rete,""))
		{  
			bzero(temp,100); 
			sprintf(temp,"select code from file where user='%s' and procode=%d and filename='%s' or user is NULL and procode=%d",pt->username,pt->position,t.buf,pt->position);
			bzero(rete,1000);
			pt->position++;
			query(temp,rete);
			pt->ppcode=atoi(rete);
		}

	}
}
void process2(int fd,uPcb* pt)
{
	train t;
	char temp[140]={0};
	char rete[1000]={0};
	recv(fd,&t,26,0);
	int len=t.len;
	recv(fd,&t,26+len,0);
	bzero(temp,150); 
	sprintf(temp,"select filetype,filename,filesize  from file where user='%s' and procode=%d and ppfile=%d or user is NULL and procode=%d",pt->username,pt->position,pt->ppcode,pt->position);
	bzero(rete,1000);
	query123(temp,rete);
	t.len=strlen(rete);
	strcpy(t.buf,rete);
	send(fd,&t,26,0);
	send(fd,&t,26+t.len,0);
}
void process3(int fd,uPcb* pt)
{
	train t;
	recv(fd,&t,26,0);
	int len=t.len;
	recv(fd,&t,26+len,0);
	char filename[15]={0};
	strcpy(filename,t.buf);
	bzero(&t,sizeof(train));	
	recv(fd,&t,26,0);
	len=t.len;
	recv(fd,&t,26+len,0);
	off_t filelen=t.cmd;
	char tempmd5[150]={0};
	strcpy(tempmd5,t.buf);
	char temp[200]={0};
	char rete[1000]={0};	
	sprintf(temp,"select code from file where MD5='%s'",tempmd5);
	query(temp,rete);
	int ppnum=atoi(rete);
	if(!strcmp(rete,""))
	{ t.cmd=404;
		send(fd,&t,4,0);
		bzero(&t,sizeof(train));
		char buf[1000]={0};
		int filefd;
		filefd=open(tempmd5,O_RDWR|O_CREAT,0600);
		while(1)
		{   bzero(&t,sizeof(train));
			recv_n(fd,(char*)&t,24);
			if(t.len>0)
			{
				recv_n(fd,buf,t.len);
				write(filefd,buf,t.len);
			}else{
				printf("file recv success\n");
				break;
			}
		}
		close(filefd);	
		bzero(temp,140);
		bzero(rete,1000);	
		sprintf(temp,"file(filename,filesize,user,filetype,MD5,procode,ppfile)values('%s',%ld,'%s','d','%s',%d,%d)",filename,filelen,pt->username,tempmd5,pt->position,pt->ppcode);
		insert(temp);
	}else{
		t.cmd=405;
		send(fd,&t,4,0);
		bzero(temp,140);
		sprintf(temp,"file(filename,filesize,user,filetype,MD5,procode,ppfile,realcode)values('%s',%ld,'%s','d','%s',%d,%d,%d)",filename,filelen,pt->username,tempmd5,pt->position,pt->ppcode,ppnum);
		insert(temp);
	}

}
void process4(int fd,uPcb* pt)
{ 
	train t;
	recv(fd,&t,26,0);
	int len=t.len;
	recv(fd,&t,26+len,0);
	char temp[140]={0};
	char rete[1000]={0};
	sprintf(temp,"select realcode from file where user='%s' and procode=%d and filename='%s'",pt->username,pt->position,t.buf);
	query(temp,rete);
	if(!strcmp(rete,"")||atoi(rete)==0)
	{ 
		 bzero(temp,140);
		bzero(rete,1000);
		sprintf(temp,"select MD5 from file where user='%s' and procode=%d and filename='%s'",pt->username,pt->position,t.buf);
		query(temp,rete);
there:
		signal(SIGPIPE,SIG_IGN);
		struct stat buf;
		stat(rete,&buf);
		int ffd,ret;
		t.cmd=buf.st_size;
		send(fd,&t,4,0);
		recv(fd,&t,24,0);
	   if(t.cmd==404)
		  
	   {
		   long int llnum=t.len;
		   printf("%d\n",t.len);
		ffd=open(rete,O_RDWR,0600);
		ret=sendfile(fd,ffd,&llnum,buf.st_size);
		}else{
		ffd=open(rete,O_RDWR,0600);
		ret=sendfile(fd,ffd,NULL,buf.st_size);
		}
		if(-1==ret)
		{  perror("sendfile");
			goto end;
		}

end:
		close(ffd);
	}else{ 
		bzero(temp,140);
		sprintf(temp,"select MD5 from file where  code=%d",atoi(rete));
		bzero(rete,1000);
		query(temp,rete);
		goto there;
	}
}
void process5(int fd,uPcb* pt)
{
	train t;
	recv(fd,&t,26,0);
	int len=t.len;
	recv(fd,&t,26+len,0);  
	char temp[140]={0};
	char rete[1000]={0};
	sprintf(temp,"select code from file where user='%s' and procode=%d and filename='%s'",pt->username,pt->position,t.buf);
	query(temp,rete);
	if(strcmp(rete,""))
	{     int aab=atoi(rete);
		bzero(temp,140);
		bzero(rete,1000);
		sprintf(temp,"select code from file where  realcode=%d",aab);
		query(temp,rete);
		if(!strcmp(rete,""))
		{
			bzero(temp,140);
			bzero(rete,1000);
			sprintf(temp,"select  MD5 from file where user='%s' and procode=%d and filename='%s'",pt->username,pt->position,t.buf);
			query(temp,rete);
			unlink(rete);
			bzero(temp,140);
			bzero(rete,1000);
			sprintf(temp,"delete from file where user='%s' and procode=%d and filename='%s'",pt->username,pt->position,t.buf);
			delete(temp);

		}else{
			bzero(temp,140);
			bzero(rete,1000);
			sprintf(temp,"update file set user='free' where  code=%d",aab);
			update(temp);
		}

	}
}
void process6( int fd,uPcb* pt)
{ train t;
	printf("pwd");
	recv(fd,&t,26,0);
	int len=t.len;
	recv(fd,&t,26+len,0);
	char temp[150]={0};
	char rete[1000]={0};
	char tempbuf[100]={0};
	char kkk[20]={0};
	char hhlk[20]={0};
	int xlnum;int pxlnum;
	pxlnum=pt->ppcode;
	xlnum=pt->position;
	while(xlnum >0)
	{ 
		xlnum=xlnum-1;
		bzero(temp,150);
		bzero(rete,1000);
		sprintf(temp,"select filename from file where procode=%d and user='%s' and code=%d or user is NULL and procode=%d",xlnum,pt->username,pxlnum,xlnum);
		query(temp,rete);
		bzero(kkk,20);
		sprintf(kkk,"%s/",rete);
		strcpy(hhlk,tempbuf);
		sprintf(tempbuf,"%s%s",kkk,hhlk);
		bzero(temp,150);
		bzero(rete,1000);
		sprintf(temp,"select ppfile from file where procode=%d and user='%s' and code=%d or user is NULL and procode=%d",xlnum,pt->username,pxlnum,xlnum);
		query(temp,rete);		
		pxlnum=atoi(rete);		
	}
	strcpy(kkk,tempbuf);	
	sprintf(tempbuf,"/%s",kkk);	
	t.len=strlen(tempbuf);
	strcpy(t.buf,tempbuf);
	send(fd,&t,26,0);
	send(fd,&t,26+t.len,0);
}
void process7(int fd,uPcb* pt)
{
	train t;
	char temp[100]={0};
	char rete[1000]={0};
	recv(fd,&t,26,0);
	int len=t.len;
	recv(fd,&t,26+len,0);
	sprintf(temp,"select code from file where procode=%d and user='%s'and filename='%s'",pt->position,pt->username,t.buf);
	puts(temp);
	query(temp,rete);
	if(!strcmp(rete,""))
	{t.cmd=202;
		send(fd,&t,4,0); 
		sprintf(temp,"file(filename,filesize,user,filetype,procode,ppfile)values('%s',0,'%s','-',%d,%d)",t.buf,pt->username,pt->position,pt->ppcode);
		insert(temp);
	}
	else{
		t.cmd=203;
		send(fd,&t,4,0);
	}


}
void process8(int fd)
{  train t;
	bzero(&t,sizeof(train));
l4:	recv(fd,&t,26,0);
	int len=t.len;
	recv(fd,&t,26+len,0);
	char salt[11]={0};
	strncpy(salt,t.buf,11);
	char temp[200]={0};
	char rete[1000]={0};
	sprintf(temp,"select userID from user where username='%s'",t.user);
	query(temp,rete);
	puts(t.user);
	if(strcmp(rete,"")!=0)
	{   t.cmd=101;
		send(fd,&t,4,0);
		goto l4;
	}
	else
	{t.cmd=102;
		send(fd,&t,4,0);
		bzero(temp,200);
		sprintf(temp,"user(username,salt, passwd)values('%s','%s','%s')",t.user,salt,t.buf);
		insert(temp);
		printf("client %s login sucess %s",t.user,ctime(NULL));
	}
	
}
void process9(int fd,char*name)
{   train t;int len;
	recv(fd,&t,26,0);
	char rete[1000]={0};
	char temp[200]={0};
	sprintf(temp,"select salt from user where username='%s'",t.user);
	query(temp,rete);
	if(strcmp(rete,"")==0)
	{  
		t.cmd=101;
		send(fd,&t,4,0);
	}
	else{
		t.cmd=102;
		send(fd,&t,4,0);
		t.len=strlen(rete);
		send(fd,&t,26,0);
		strncpy(t.buf,rete,t.len);
		send(fd,&t,37,0);
		recv(fd,&t,26,0);
		len=t.len;
		recv(fd,&t,26+len,0);
		bzero(temp,200);
		bzero(rete,1000);
		sprintf(temp,"select passwd from user where username='%s'",t.user);
		query(temp,rete);
		puts(temp);
		puts(t.user);
		if(strcmp(rete,t.buf)==0)
		{
			t.cmd=102;
			send(fd,&t,4,0);
			strcpy(name,t.user);
		}
		else
		{
			t.cmd=101;
			send(fd,&t,4,0);

		}
		time_t time1;
	time1=time(NULL);	
printf("client %s login %s",t.user,ctime(&time1));
	}
}

