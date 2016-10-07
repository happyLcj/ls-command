#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef _HEAD_
    #define _HEAD_
    #include "showinfo.h"
    #include "parameter.h"
#endif
int main(int argc,char *argv[])
{
    int num=0,pamter=0;
    char wrongPmt=' ';
    char** dirname=(char**)malloc(argc);
    //判断参数类型
    for(int i=1;i<argc&&wrongPmt==' ';i++){
        int len=strlen(argv[i]);
        if(argv[i][0]=='-'){
            for(int j=1;j<len&&wrongPmt==' ';j++){
                switch(argv[i][j]){
                    case 'a': pamter|=ALL_FILE;break;
                    case 'l': pamter|=LONG_FORMAT;break;
                    case 'i': pamter|=INODE;break;
                    default: wrongPmt=argv[i][j];
                }
            }
        }
        else{
            dirname[num]=(char*)malloc(sizeof(char)*(len+2));
            strcpy(dirname[num],argv[i]);
            num++;
        }
    }
    if(wrongPmt!=' '){
        printf("ls: 不适用的选项 -%c\n",wrongPmt);
        exit(0);
    }
    if(num==0)
        subfile(".",pamter,0);
    else{
        //依次处理每个路径
        int isPrintDirname=(num>1?1:0);
        for(int i=0;i<num;i++){
            subfile(dirname[i],pamter,isPrintDirname);
            if(i!=num-1) puts("");
        }
    }   
    return 0;
}
