#include<stdio.h>
#include<pwd.h>
#include<grp.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
char* getUsrName(uid_t);
char* getGrpName(gid_t);
char* getMode(mode_t);
char* getColor(char);
