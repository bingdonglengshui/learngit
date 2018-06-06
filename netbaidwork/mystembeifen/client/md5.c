#include <stdlib.h>
#include <openssl/md5.h>
#include<stdio.h>
#include<string.h>
#define BUFSIZE 1024*16

int do_fp(FILE *f,char*);
int pt(unsigned char *md,char*);
#if !defined(_OSD_POSIX) && !defined(__DJGPP__)
int read(int, void *, unsigned int);
#endif
int  md5sum( char *filename,char*tempbuf)
{
	int i,err=0;
	FILE *IN;
			IN=fopen(filename,"r");
			if (IN == NULL)
			{
				perror(filename);
				err++;
            }
			do_fp(IN,tempbuf);
			fclose(IN);
}

int do_fp(FILE *f,char* tempbuf)
{
	MD5_CTX c;
	unsigned char md[MD5_DIGEST_LENGTH];
	int fd;
	int i;
	static unsigned char buf[BUFSIZE];

	fd=fileno(f);
	MD5_Init(&c);
	for (;;)
	{
		i=read(fd,buf,BUFSIZE);
		if (i <= 0) break;
		MD5_Update(&c,buf,(unsigned long)i);
	}
	MD5_Final(&(md[0]),&c);
	pt(md,tempbuf);
}

int  pt(unsigned char *md,char *tempbuf)
{
	int i;
	char kkk[20]={0};
	for (i=0; i<MD5_DIGEST_LENGTH; i++)
	{
		sprintf(kkk,"%02x",md[i]);
		strcat(tempbuf,kkk);
		bzero(kkk,20);
	}
}
