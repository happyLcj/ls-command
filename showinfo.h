#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
int numOfFile;
char* fnameToPath(char*,char*);
void subfile(char*,int,int);
void checkStat(char*,char*,int);
int isShowFile(int,char);
void printAllInfo(char*,struct stat,int);
void showFileInfo(char*,struct stat,int);
void setFileColor(char*);