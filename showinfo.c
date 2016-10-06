#include "fileinfo.h"
#ifndef _SHOWINFO
    #define _SHOWINFO
    #include "showinfo.h"
#endif
//将不带路径的文件名转化为带路径的完整名
char* fnameToPath(char* dirname,char *fname)
{
    char *pname=(char*)malloc(sizeof(char)*256);
    strcpy(pname,dirname);
    int len=strlen(pname);
    pname[len]='/';
    pname[len+1]='\0';
    strcat(pname,fname); 
    return pname;
}
void subfile(char *dirname,int flag)
{
    DIR *dir_ptr=NULL;
    struct dirent *direntp;
    if((dir_ptr=opendir(dirname))==NULL){
        fprintf(stderr,"ls:cannot open %s\n",dirname);
    }
    else{
        //readdir逐个读取目录下的子文件
        while((direntp=readdir(dir_ptr))!=NULL){
            checkStat(dirname,direntp->d_name,flag);
        }
        if(flag==0||flag==1)
            puts("");
        closedir(dir_ptr);
    }
}
//获取文件对应的属性
void checkStat(char* dirname,char *filename,int flag)
{
    struct stat info;
    //filename是不带路径的文件名
    char* pathname=fnameToPath(dirname,filename);
    if(lstat(pathname,&info)==-1)
        perror(pathname);
    else
        showFileInfo(filename,info,flag);
}
//判断隐藏文件是否需输出
int isShowFile(int flag,char c)
{
    if((flag==0||flag==2)&&c=='.')
        return -1;
    return 0;    
}
void setFileColor(char* mode)
{
    char c=mode[0];
    int exc=0;
    if(mode[3]=='x'||mode[6]=='x'||mode[9]=='x')
        exc=1;
    if(exc==1&&c=='-')
        c='x';
    printf("%s",getColor(c));
}
//输出文件的各种属性
void printAllInfo(char* filename,struct stat info)
{
    char *mode=getMode(info.st_mode);
    printf("%s",mode);
    printf("%4d",(int)info.st_nlink);
    printf(" %-4s",getUsrName(info.st_uid));
    printf(" %-4s",getGrpName(info.st_gid));
    printf(" %8ld ",(long)info.st_size);
    printf(" %.12s",4+ctime(&info.st_mtime));
    setFileColor(mode);
    printf(" %s\n",filename);
    printf("\033[0m");
}
void showFileInfo(char* filename,struct stat info,int flag)
{
    static int numOfFile=0;
    if(isShowFile(flag,filename[0])==0){
        if(flag==2||flag==3)
             printAllInfo(filename,info);
        else{
            if(numOfFile&&numOfFile%3==0)
                puts("");
            char *mode=getMode(info.st_mode);
            setFileColor(mode);
            printf("%-25s ",filename);
            printf("\033[0m");
            numOfFile++;
        }

    }
}      
