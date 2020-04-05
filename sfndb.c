#include <stdio.h>
#include <string.h>

char* check_arg(char* arg);


int main(int argc, char* argv[]){
	if(argc<2)
		printf("Shofuwan DataBase. Simple database system\n\nby Muh. Shofuwan Anwar 2018 REV.1\n");

	return 0;
}

char* check_arg(char* arg){
	char str[100];
	for(short check=0;check<strlen(arg);check++){
		if(arg[check]=='\0')
			break;
		str[check]+=arg[check];
	}
}