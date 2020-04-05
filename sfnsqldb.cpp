#include "cli.h"

int main(){
	std::string data[14][3]={
		{"1804500379","PETRUS ANGGA JUNIYANTA","D3 TEKNOLOGI INSTRUMENTASI"},
		{"1804502378","MUHAMMAD SHOFUWAN ANWAR","D3 TEKNOLOGI INSTRUMENTASI"},
		{"1804503808","DIMAS RICKY ALFANDI","D3 TEKNOLOGI INSTRUMENTASI"},
		{"1804510566","VIRA ANGGRAENI SAFITRI","D3 TEKNOLOGI INSTRUMENTASI"},
		{"1804520207","SIGIT PRATOMO","D3 TEKNOLOGI INSTRUMENTASI"},
		{"1804521391","RAMADHAN RACHMAD PRAKOSA","D3 TEKNOLOGI INSTRUMENTASI"},
		{"1804523391","RIZQY IKHWAN RIFAI","D3 TEKNOLOGI INSTRUMENTASI"},
		{"1804523559","LONDA ANDALUCIA","D3 TEKNOLOGI INSTRUMENTASI"},
		{"1804525643","MIFTAHUDIN FAUZI","D3 TEKNOLOGI INSTRUMENTASI"},
		{"1804526137","FATKHA HADI YAHYA","D3 TEKNOLOGI INSTRUMENTASI"},
		{"1804526252","ATUR TOTO DWIJAYANTO","D3 TEKNOLOGI INSTRUMENTASI"},
		{"1804528051","ANDI GILANG PANGESTU","D3 TEKNOLOGI INSTRUMENTASI"},
		{"1804531077","SEPTA ADI NUGROHO","D3 TEKNOLOGI INSTRUMENTASI"},
		{"1804533193","MUHAMMAD ABDUL AZIS","D3 TEKNOLOGI INSTRUMENTASI"}
	};
	std::string command[10]={
		"Authentication..",
		"Brute forcing..",
		"Done!",
		"scanned 2983 data stored in \'SELEKSI UTUL\'",
		"All done.",
		"Clearing cache, cookies and foot print in server.."	
	};

	std::cout<<"brute force email? (y/n) : n"<<std::endl;
	std::cout<<"login> adminutulugm2018@ugm.ac.id"<<std::endl<<std::endl;
	std::cout<<"brute force password?(y/n) : y"<<std::endl;
	std::cout<<"file> /mnt/linux-data/shofuwan/password/pwd.lst"<<std::endl<<std::endl;

	for(int x=0;x<6;x++)
		print_status(command[x]);
	
	std::cout<<"database> show all || filter \'TEKNOLOGI INSTRUMENTASI\'"<<std::endl;

	for(int x=0;x<14;x++){
		std::cout<<"+----------------+-------------------------+-------------------------------+"<<std::endl;
		std::cout<<"| "<<data[x][0]<<"     | "<<data[x][1]<<"  | "<<data[x][2]<<" |"<<std::endl;
	}
	print_status("Done all databases filter pushed to standart output");

	return 0;
}
