
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
void get_rand_str(char s[])
{
	char *str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int i,lstr;
	char ss[2] = {0};
	lstr = strlen(str);
	srand((unsigned int)time((time_t *)NULL));
	for(i = 1; i <= 8; i++){
		sprintf(ss,"%c",str[(rand()%lstr)]);	
		strcat(s,ss);
	}
}


