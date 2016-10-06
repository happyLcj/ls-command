#include "fileinfo.h"
#include "showinfo.h"
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
    if(stat(pathname,&info)==-1)
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
//输出文件的各种属性
void printAllInfo(char* filename,struct stat info)
{
    printf("%s",getMode(info.st_mode));
    printf("%4d",(int)info.st_nlink);
    printf(" %-4s",getUsrName(info.st_uid));
    printf(" %-4s",getGrpName(info.st_gid));
    printf(" %8ld ",(long)info.st_size);
    printf(" %.12s",4+ctime(&info.st_mtime));
    printf(" %s\n",filename);
}
void showFileInfo(char* filename,struct stat info,int flag)
{
    static int numOfFile=0;
    if(isShowFile(flag,filename[0])==0){
        if(flag==2||flag==3)
             printAllInfo(filename,info);
        else{
            printf("%-25s ",filename);
            numOfFile++;
            if(numOfFile%3==0)
                puts("");
        }
    }
}      
