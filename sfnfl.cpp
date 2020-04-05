#include "sfnfl.h"
#include <cli.h>

int main(int argc, char* argv[]){
	if(argc<2) help_msg();
	else{
		SFNFL fl(argv[argc-1]);

		//priority
		for(int scan=1;scan<argc;scan++){
			if(std::string(argv[scan])=="-v")
				fl.set_verbose_status(true);
			else if(std::string(argv[scan])=="-fO")
				fl.set_file_output_name(std::string(argv[scan+1]));
			else if(std::string(argv[scan])=="-l0")
				fl.set_skip_line_status(true);
			else{
				if(std::string(argv[scan]).find("\"")==std::string::npos && scan!=(argc-1)){
					print_error(std::string(argv[scan])+": command not found!");
					return -2;
				}
			}
		}

		if(fl.file_exist()!=true){
			print_error("Unable to find the specific file!");
			return -1;
		}

		//cofiguration option
		for(int scan=1;scan<argc;scan++){
			if(std::string(argv[scan])=="-tP")
				fl.set_prepend_text(std::string(argv[scan+1]));
			else if(std::string(argv[scan])=="-tA")
				fl.set_append_text(std::string(argv[scan+1]));
			else if(std::string(argv[scan])=="-cR")
				fl.set_replace_char(argv[scan+1],argv[scan+2]);
			else if(std::string(argv[scan])=="-lC")
				fl.set_continue_text(std::string(argv[scan+1]));
		}
		fl.write_output();
	}

	return 0;
}
