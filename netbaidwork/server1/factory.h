#ifndef __FACTORY_H__
#define __FACTORY_H__
#include"func.h"
#include"workqu.h"
#include <mysql/mysql.h>
#include <string.h>
#define FILENAME "log"
typedef struct {
	pthread_t *pth;
	que_t que;
	pthread_cond_t cond;
	int pthread_num;
	short start_flag;
}factory;
typedef struct {
	int cmd;
    char user[16];
	int len;
	char buf[1000];
}train;
typedef struct{
	int ppcode;
	char username[15];
	int position;
}uPcb;
void factory_init(factory*,int ,int);
void factory_start(factory*);
void* pthread_hand(void *);
void qu_inser(pque_t ,pnode_t);
 void get_que(pque_t ,pnode_t *);
void trans_file(int );
int send_n(int ,char* ,int );
int recv_n(int ,char* ,int);
void qu_dele(pque_t );
void process1(int,uPcb*);
void process2(int,uPcb*);
void process3(int,uPcb*);
void process4(int,uPcb*);
void process5(int,uPcb*);
void process6(int,uPcb*);
void process7(int,uPcb*);
void process8(int);
void process9(int,char*);
int  query(char*,char*);
void  insert(char *);
int  query123(char*,char*);
int  delete(char *p);
int update(char *p);
#endif
