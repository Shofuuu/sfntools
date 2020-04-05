#include <fstream>
#include <algorithm>
#include <limits>
#include <cstring>
#include <cstdlib>
#include "cli.h"

std::string fl_name;
class fileutil{
public:
	fileutil(std::string file_name){fl_name=file_name;}

	int write_data(std::string key,std::string val);
	std::string read_data(std::string key);
	bool check_data(std::string data);
	bool find_data(std::string data);
	std::string read_all_key();
	std::string read_all_value();
	int count_all_key();
	int replace_data(std::string old_d, std::string new_d);
	void file_copy(std::string file_name, std::string new_name);
	void clear_content(std::string file_name);
	std::string encrypt_data(std::string raw_text);
	std::string decrypt_data(std::string raw_text);
	std::string convert(std::string raw_text);
	std::string convert_read(std::string raw_text);
};

std::fstream & filter(std::fstream & fl, unsigned int line_num){
	fl.seekg(std::ios::beg);
	for(int x=0;x<(line_num-1);++x)
		fl.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	return fl;
}

int fileutil::write_data(std::string key,std::string val){
	std::ofstream write(std::string(fl_name).c_str(),std::ios::app);
	std::ifstream read(std::string(fl_name).c_str());
	std::string line("");
	bool exist=true;

	if(key.find(" ")!=std::string::npos)
		std::replace(key.begin(), key.end(), ' ', '~');

	write<<std::endl<<"-=[|DATABASE-SAVED-DATA-BEGIN|]=-"<<std::endl
		 <<"@KEY>"<<key<<std::endl<<val
		 <<std::endl<<"-=[|DATABASE-SAVED-DATA-END|]=-"<<std::endl;
	
	write.close();
}
std::string fileutil::read_data(std::string key){
	std::fstream read(std::string(fl_name).c_str(),std::ios::in);
	std::string line(""),value="##!EMPTY##";
	int count=0;

	if(key.find(" ")!=std::string::npos)
		key.replace(key.begin(), key.end(), ' ', '~');
	while(std::getline(read,line)){
		count++;
		if(line.find((std::string("@KEY>")+encrypt_data(key)).c_str())!=std::string::npos){
			filter(read,count+1);
			read>>value;
			if(value!="-=[|DATABASE-SAVED-DATA-BEGIN|]=-" || value!="-=[|DATABASE-SAVED-DATA-END|]=-"){
				return value;
				break;
			}
		}
	}
}
bool fileutil::check_data(std::string key){
	std::fstream read(std::string(fl_name).c_str(),std::ios::in);
	std::string line("");
	bool exist=false;

	if(key.find(" ")!=std::string::npos)
		key.replace(key.begin(), key.end(), ' ', '~');
	/*while(std::getline(read,line))
		if(line.find((std::string("@KEY>")+key).c_str())!=std::string::npos)
			exist=true;*/
	while(read>>line)
		if(line==(std::string("@KEY>")+key).c_str())
			exist=true;

	return exist;
}
bool fileutil::find_data(std::string key){
	std::fstream read(std::string(fl_name).c_str(),std::ios::in);
	std::string line("");
	bool exist=false;

	if(key.find(" ")!=std::string::npos)
		key.replace(key.begin(), key.end(), ' ', '~');
	while(std::getline(read,line))
		if(line.find(key)!=std::string::npos)
			exist=true;

	return exist;
}
std::string fileutil::read_all_key(){
	std::fstream read(std::string(fl_name).c_str(),std::ios::in);
	std::string value;
	std::size_t found;

	while(read>>value){
		found=value.find("@KEY>");
		if(found!=std::string::npos){
			value.replace(value.begin(),value.begin()+5,"");
			if(encrypt_data(value)!=encrypt_data("P4$$WrD5@vEd"))
				std::cout<<"~> "<<convert_read(decrypt_data(value))<<std::endl;
		}
	}
	std::cout<<std::endl;
	print_status((std::string("Total ")+bold("KEY")+" yang tersimpan adalah "+istr(count_all_key()-1)).c_str());
	exit(0);
}
int fileutil::count_all_key(){
	std::fstream read(std::string(fl_name).c_str(),std::ios::in);
	std::string value;
	std::size_t found;
	int count=0;

	while(read>>value){
		found=value.find("@KEY>");
		if(found!=std::string::npos)
			count++;
	}
	return count;
}
int fileutil::replace_data(std::string old_d, std::string new_d){
	file_copy(fl_name,concat(fl_name,".backup"));
	std::fstream read((fl_name+".backup").c_str(),std::ios::in);
	std::fstream write(fl_name.c_str(),std::ios::out);
	std::string temp;
	//bool found=false;

	if(!read||!write)
		return 1;
	while(read>>temp){
		if(temp==old_d){
			temp=new_d;
			//found=true;
		}
		
		if(temp=="-=[|DATABASE-SAVED-DATA-END|]=-")
			temp+="\n";
		temp+="\n";
		write<<temp;
		//if(found) break;
	}
	write.close();
	read.close();
	clear_content((fl_name+".backup").c_str());
}
void fileutil::file_copy(std::string file_name, std::string new_name){
	std::fstream read(file_name.c_str(),std::ios::in);
	std::fstream write(new_name.c_str(),std::ios::out);
	std::string temp;

	while(read>>temp)
		write<<temp<<std::endl;

	write.close();
	read.close();
}
std::string fileutil::encrypt_data(std::string raw_text){
	char key[2][100]={
		{'ƚ','ƛ','Ɯ','Ɲ','ƞ','Ɵ','Ơ','ơ','Ƣ','ƣ','Ƥ','ƥ','Ʀ',
		 'Ƨ','Ʃ','ƪ','Ǣ','ƾ','ƿ','ǂ','ǁ','Ǆ','ȼ','Ƚ','ↈ','Ƀ',
		 'ȴ','ȵ','ȶ','ȸ','ʨ','ᵆ','ᶲ','ʫ','ʬ','ʭ','ʮ','ᴒ','ᴓ',
		 'ᴔ','ᴕ','ᴖ','ᴗ','ᴤ,','ᴥ'},
		{'a','b','c','d','e','f','g','h','i','j','k','l','m',
		 'n','o','p','q','r','s','t','u','v','w','x','y','z',
		 'A','I','U','E','O','|','1','2','3','4','5','6','7',
		 '8','9','0',':','='}
	};

	for(int x=0;x<44;x++){
		if(raw_text.find(key[1][x])!=std::string::npos)
			std::replace(raw_text.begin(), raw_text.end(), key[1][x],key[0][x]);
	}

	return raw_text;
}
std::string fileutil::decrypt_data(std::string raw_text){
	char key[2][100]={
		{'ƚ','ƛ','Ɯ','Ɲ','ƞ','Ɵ','Ơ','ơ','Ƣ','ƣ','Ƥ','ƥ','Ʀ',
		 'Ƨ','Ʃ','ƪ','Ǣ','ƾ','ƿ','ǂ','ǁ','Ǆ','ȼ','Ƚ','ↈ','Ƀ',
		 'ȴ','ȵ','ȶ','ȸ','ʨ','ᵆ','ᶲ','ʫ','ʬ','ʭ','ʮ','ᴒ','ᴓ',
		 'ᴔ','ᴕ','ᴖ','ᴗ','ᴤ,','ᴥ'},
		{'a','b','c','d','e','f','g','h','i','j','k','l','m',
		 'n','o','p','q','r','s','t','u','v','w','x','y','z',
		 'A','I','U','E','O','|','1','2','3','4','5','6','7',
		 '8','9','0',':','='}
	};

	for(int x=0;x<44;x++){
		if(raw_text.find(key[0][x])!=std::string::npos)
			std::replace(raw_text.begin(), raw_text.end(), key[0][x],key[1][x]);
	}

	return raw_text;
}
void fileutil::clear_content(std::string file_name){
	std::fstream write(file_name.c_str(),std::ios::out);
	write<<"";
	write.close();
}
std::string fileutil::convert(std::string raw_text){
	if(raw_text.find(" ")!=std::string::npos)
		std::replace(raw_text.begin(), raw_text.end(), ' ', '~');
	return (raw_text);
}
std::string fileutil::convert_read(std::string raw_text){
	if(raw_text.find("~")!=std::string::npos)
		std::replace(raw_text.begin(), raw_text.end(), '~', ' ');
	return (raw_text);
}
