#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
//#include <windows.h>
#define CHAR_TYPE 1
#define STRING_TYPE 2
#define INT_TYPE 3
#define DOUBLE_TYPE 4
#define FLOAT_TYPE 5

int xpos,ypos,
    get_y,get_x1,
    get_x2;
struct FORM{
    char CHAR[250];
    char* STRING;
    int INT;
    float FLOAT, DOUBLE;
}Form;
/*void move(int x,int y){
	COORD coord;coord.X=x;coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}*/
void move(int x,int y){printf("%c[%d;%df",0x1B,y,x);}
void draw_grub(int x1, int y1,int x2,int y2,char* title){
    x1+=1; y1+=1;
    xpos=x1+1; ypos=y1+1;
    get_y=y2-1; get_x1=x1;
    get_x2=x2;
    move(x1-1,y1);
    printf("\x1B[1m┌");
    for(int _x=x1;_x<x2;_x++){
        move(_x,y1);
        printf("─");
    }
    move(x1+2,y1);
    printf("┤\x1B[32m%s\x1B[0m├",title);
    move(x2,y1);
    printf("\x1B[1m┐");
    for(int _y=y1+1;_y<y2;_y++){
        move(x1-1,_y);
        printf("│");
    }
    move(x1-1,y2);
    printf("└");
    for(int _y=y1+1;_y<y2;_y++){
        move(x2,_y);
        printf("│");
    }
    move(x2,y2);
    printf("┘");
    for(int _x=x1;_x<x2;_x++){
        move(_x,y2);
        printf("─");
    }
    printf("\x1B[0m");
}
void draw_box(int x1, int y1,int x2,int y2){
    x1+=1; y1+=1;
    xpos=x1+1; ypos=y1+1;
    get_y=y2-1; get_x1=x1;
    get_x2=x2;
    move(x1-1,y1);
    printf("\x1B[1m┌");
    for(int _x=x1;_x<x2;_x++){
        move(_x,y1);
        printf("─");
    }
    move(x2,y1);
    printf("┐");
    for(int _y=y1+1;_y<y2;_y++){
        move(x1-1,_y);
        printf("│");
    }
    move(x1-1,y2);
    printf("└");
    for(int _y=y1+1;_y<y2;_y++){
        move(x2,_y);
        printf("│");
    }
    move(x2,y2);
    printf("┘");
    for(int _x=x1;_x<x2;_x++){
        move(_x,y2);
        printf("─");
    }
    printf("\x1B[0m");
}
void write(const char* txt,...){
    char data[2];
	int max=strlen(txt);
    va_list arr;

    va_start(arr,txt);
    if(ypos>get_y)
        ypos=get_y;
    move(xpos,ypos);
    if(max>(get_x2-get_x1))
    	max=(get_x2-get_x1)-1;
    for(int x=0;x<max;x++){
        data[0]=txt[x];
        data[1]=txt[x+1];
        if(strcmp(data,"%d")==0){
            printf("%d",va_arg(arr,int));
            x++;
        }else if(strcmp(data,"%i")==0){
            printf("%i",va_arg(arr,int));
            x++;
        }else if(strcmp(data,"%c")==0){
            printf("%s",va_arg(arr,char*));
            x++;
        }else if(strcmp(data,"%s")==0){
            printf("%s",va_arg(arr,char*));
            x++;
        }else if(strcmp(data,"%f")==0){
            printf("%f",va_arg(arr,double));
            x++;
        }else printf("%c",txt[x]);
    }
    ypos++;
    va_end(arr);
}
void delay(int _time){
    int count=0;
    while(_time<_time*10000000)
        count++;
}
void draw_form(char* _p,int x, int y, unsigned char type){
    char _ask[100];
    int _ask_i;
    float _ask_f;

    draw_box(x+2,y,x+(5+strlen(_p)),3+y);
    move(x+4,2+y);
    //printf("\x1B[34m\x1B[1m%s\x1B[0m",_p);
    printf("%s",_p);
    draw_box(x+5+strlen(_p),y,x+((strlen(_p)*4)+5),3+y);
    move(x+strlen(_p)+7,2+y);
    if(type==CHAR_TYPE){
        gets(_ask);
        strcpy(Form.CHAR,_ask);
    }else if(type==STRING_TYPE){
        gets(_ask);
        strcpy(&Form.STRING,_ask);
    }else if(type==INT_TYPE){
        scanf("%i",&_ask_i);
        Form.INT=_ask_i;
    }else if(type==DOUBLE_TYPE){
        scanf("%f",&_ask_f);
        Form.DOUBLE=_ask_f;
    }else if(type==FLOAT_TYPE){
        scanf("%f",&_ask_f);
        Form.FLOAT=_ask_f;
    }
}