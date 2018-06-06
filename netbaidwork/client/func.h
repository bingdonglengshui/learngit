#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/select.h>
#include<sys/time.h>
#include<stdlib.h>
#include<time.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/msg.h>
#include<signal.h>
#include<pthread.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include <unistd.h>
#include <shadow.h>
#include <errno.h>
#include<crypt.h>
#include <openssl/md5.h>
int do_fp(FILE *f,char*);
int pt(unsigned char *md,char*);
int  md5sum( char *filename,char*);
typedef struct {
	pid_t pid;
	int fd;
	short busy;
}Data,*pData;
void creat_proce(pData ,int);
void processa(int);
void recv_fd(int ,int* );
void send_fd(int ,int );
typedef struct{
     int cmd;
	 char user[16];
	 int len;
	char buf[1000];
}train;
typedef struct {
	char salt[12];
	char passwdtwxt[100];
}passtx;
void send_file(int);
int  send_n(int ,char*,int );
int recv_n(int,char*,int );
void checkchm(char*,int,int*);
void get_rand_str(char s[]);
void sockapi(char*,int,int* );
void *pthreadhand1(void* );
void *pthreadhand2(void* );
typedef struct station{
	int procode;
	int ppfile;
	char user[15];
	char filename[15];
	int cmd;
}stmes;




