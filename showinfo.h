#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
char* fnameToPath(char*,char*);
void subfile(char*,int);
void checkStat(char*,char*,int);
int isShowFile(int,char);
void printAllInfo(char*,struct stat);
void showFileInfo(char*,struct stat,int);
void setFileColor(char*);