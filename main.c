#include <stdio.h>
#include <string.h>
#ifndef _SHOWINFO
    #define _SHOWINFO
    #include "showinfo.h"
#endif
int main(int argc,char *argv[])
{
    int isA=0,isL=0;
    int dirst=1;
    //读取是否包含 -l -a参数
    for(int i=1;i<argc&&i<=2;i++){
        if(strcmp(argv[i],"-a")==0)
            isA=1;
        else if(strcmp(argv[i],"-l")==0)
            isL=2;
        else if(strcmp(argv[i],"-al")==0||strcmp(argv[i],"-la")==0){
            isA=1;
            isL=2;
        }
        else
            break;
        dirst=i+1;
    }
    /*flag用来表示ls参数类型，取值0-3
      0：无参
      1: -a
      2: -l
      3: -al
    */
    int flag=isA+isL;
    //未输入路径则查询当前路径
    if(dirst==argc)
        subfile(".",flag);
    else{
        //依次处理每个路径
        for(int i=dirst;i<argc;i++){
            if(dirst!=argc-1)
                printf("%s:\n",argv[i]);
            subfile(argv[i],flag);
            if(i!=argc-1) puts("");
        }
    }   
    return 0;
}
