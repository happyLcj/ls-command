#include "fileinfo.h"
//通过用户id得到用户名
char* getUsrName(uid_t uid)
{
    struct passwd* pw_ptr=NULL;
    char* str=(char*)malloc(sizeof(char)*10);
    if((pw_ptr=getpwuid(uid))==NULL){
        sprintf(str,"%d",uid);
    }   
    else{
        sprintf(str,"%s",pw_ptr->pw_name);
    }
    return str;       
}
//通过组id得到组名
char* getGrpName(gid_t gid)
{
    struct group* grp_ptr=NULL;
    char* str=(char*)malloc(sizeof(char)*10);
    if((grp_ptr=getgrgid(gid))==NULL){
        sprintf(str,"%d",gid);
    }   
    else{
        sprintf(str,"%s",grp_ptr->gr_name);
    }
    return str;       
}
//解码st_mode,得到mode属性
char *getMode(mode_t mode)
{
    char* str=(char*)malloc(sizeof(char)*12);
    strcpy(str,"----------");
    if(S_ISREG(mode)) str[0]='-';
    else if(S_ISDIR(mode)) str[0]='d';
    else if(S_ISCHR(mode)) str[0]='c';
    else if(S_ISBLK(mode)) str[0]='b';
    else if(S_ISLNK(mode)) str[0]='l';
    else if(S_ISFIFO(mode)) str[0]='p';   

    if(mode&S_IRUSR) str[1]='r';
    if(mode&S_IWUSR) str[2]='w';
    if(mode&S_IXUSR) str[3]='x';       

    if(mode&S_IRGRP) str[4]='r';
    if(mode&S_IWGRP) str[5]='w';
    if(mode&S_IXGRP) str[6]='x';

    if(mode&S_IROTH) str[7]='r';
    if(mode&S_IWOTH) str[8]='w';
    if(mode&S_IXOTH) str[9]='x';
    str[10]='\0';
    return str;
}
