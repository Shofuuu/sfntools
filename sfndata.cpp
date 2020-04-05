#include "sfndata.h"

int main(int argc, char* argv[]){
	if(argc<2)
		std::cout<<"[-] Kekurangan argumen!"<<std::endl;
	else{
		for(int scan=0;scan<argc;scan++){
			for(int checkf=0;checkf<ARG_DATA;checkf++){
				if((arg.argumen[checkf][ARGFIRST])==std::string(argv[scan])){
					if(arg.argument[checkf][ARGTYPE]=="ARGUMENT")
						arg.argument[checkf][SAVEARG]=std::string(argv[scan]);
					else
						arg.argument[checkf][SAVEARG]="TRUE";
				}else if((arg.argument[checkf][ARGSECOND])==std::string(argv[scan])){
					if((arg.argument[checkf][ARGTYPE])=="ARGUMENT")
						arg.argument[checkf][SAVEARG]=std::string(argv[scan]);
					else
						arg.argument[checkf][SAVEARG]="TRUE";
				}
			}
		}
	}

	return 0;
}