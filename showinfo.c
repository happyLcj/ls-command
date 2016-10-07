#include "fileinfo.h"
#ifndef _HEAD_
    #define _HEAD_
    #include "showinfo.h"
    #include "parameter.h"
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
void subfile(char *dirname,int pamter,int isPrintDirname)
{
    struct stat info;
    if(lstat(dirname,&info)==-1){
        fprintf(stderr,"ls:Cannot access '%s':No such file or directory\n",dirname);
    }
    else{
        if(!S_ISDIR(info.st_mode)){
            showFileInfo(dirname,info,pamter);
        }
        else{
            DIR *dir_ptr=NULL;
            struct dirent *direntp;
            if((dir_ptr=opendir(dirname))==NULL){
                fprintf(stderr,"ls:Cannot access '%s':No such file or directory\n",dirname);
            }
            else{
                if(isPrintDirname)
                    printf("%s:\n",dirname);
                numOfFile=0;
                //readdir逐个读取目录下的子文
                while((direntp=readdir(dir_ptr))!=NULL){
                    checkStat(dirname,direntp->d_name,pamter);
                }
                closedir(dir_ptr);
            }
        }
        if(!IS_LONG(pamter))
            puts("");
    }
}
//获取文件对应的属性
void checkStat(char* dirname,char *filename,int pamter)
{
    struct stat info;
    //filename是不带路径的文件名
    char* pathname=fnameToPath(dirname,filename);
    if(lstat(pathname,&info)==-1)
        perror(pathname);
    else
        showFileInfo(filename,info,pamter);
}
//判断隐藏文件是否需输出
int isShowFile(int pamter,char c)
{
    if(!IS_ALL(pamter)&&c=='.')
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
void printAllInfo(char* filename,struct stat info,int pamter)
{
    if(IS_INODE(pamter))
        printf("%-9d",info.st_ino);
    char *mode=getMode(info.st_mode);
    printf("%s",mode);
    printf("%4d",(int)info.st_nlink);
    printf(" %-8s",getUsrName(info.st_uid));
    printf(" %-8s",getGrpName(info.st_gid));
    printf(" %8ld",(long)info.st_size);
    printf(" %.12s",4+ctime(&info.st_mtime));
    setFileColor(mode);
    printf(" %s\n",filename);
    printf("\033[0m");
}
void showFileInfo(char* filename,struct stat info,int pamter)
{
    if(isShowFile(pamter,filename[0])==0){
        if(IS_LONG(pamter))
             printAllInfo(filename,info,pamter);
        else{
            //无-l时：有-i参数，两个文件信息显示在一行
            //       无-i,三个文件信息显示在一行
            if(numOfFile&&((IS_INODE(pamter)&&numOfFile%2==0)
              ||(!IS_INODE(pamter)&&numOfFile%3==0)))
                    puts("");
            if(IS_INODE(pamter))
                printf("%-9d",info.st_ino);
            char *mode=getMode(info.st_mode);
            setFileColor(mode);
            printf("%-25s ",filename);
            printf("\033[0m");
            numOfFile++;
        }
    }
}      
