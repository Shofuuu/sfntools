#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include "cli.h"
#include "fileutil.h"

std::string username="", keydata, valuedata, argname;
bool access_write=false, access_read=false, username_check=false,
	 help_msg=false, list=false, access_change=false, change_pass=false,
	 access_delete=false, change_key=false;
void help();
void authentication();
int getch();
std::string getpassword(const char* text);
void listkey();

int main(int argc, char* argv[]){
	fileutil file("~");
	std::string temp("");
	bool start=false;
	argname=std::string(argv[0]);

	if(argc<2){
		print_error("Kesalahan dalam memproses argument!");
		print_info("Gunakan argument \'--help\' untuk menampilkan pesan bantuan");
	}else{
		for(int range=0;range<argc;range++){
			if(std::string(argv[range])=="-usr" || std::string(argv[range])=="--user"){
				username_check=true;
				username=(std::string(argv[range+1]));
				start=true;
			}else if(std::string(argv[range])=="--help"){
				help_msg=true;
				start=true;
			}else if(std::string(argv[range])=="-wrt" || std::string(argv[range])=="--write"){
				keydata=file.convert(std::string(argv[range+1]));
				valuedata=file.convert(std::string(argv[range+2]));
				access_write=true;
				start=true;
			}else if(std::string(argv[range])=="-shw" || std::string(argv[range])=="--show"){
				keydata=file.convert(std::string(argv[range+1]));
				access_read=true;
				start=true;
			}else if(std::string(argv[range])=="-lst" || std::string(argv[range])=="--list"){
				list=true;
				start=true;
			}else if(std::string(argv[range])=="-updat" || std::string(argv[range])=="--update-data"){
				keydata=file.convert(std::string(argv[range+1]));
				valuedata=file.convert(std::string(argv[range+2]));
				access_change=true;
				start=true;
			}else if(std::string(argv[range])=="-chgpwd" || std::string(argv[range])=="--change-password"){
				change_pass=true;
				start=true;
			}else if(std::string(argv[range])=="-del" || std::string(argv[range])=="--delete"){
				keydata=file.convert(std::string(argv[range+1]));
				access_delete=true;
				start=true;
			}else if(std::string(argv[range])=="-chgky" || std::string(argv[range])=="--change-key"){
				keydata=file.convert(std::string(argv[range+1]));
				valuedata=file.convert(std::string(argv[range+2]));
				change_key=true;
				start=true;
			}
		}
		if(start==false){
			for(int scan=1;scan<argc;scan++){
				if(scan!=(argc-1)){
					temp+=std::string(argv[scan]);
					temp+=" ";
				}else
					temp+=std::string(argv[scan]);
			}
			print_error((std::string("Perintah \'")+temp+"\' tidak ditemukan!").c_str());
			exit(0);
		}
		authentication();
	}

	return 0;
}

int getch(){
	int ch;
	struct termios t_old, t_new;

	tcgetattr(STDIN_FILENO, &t_old);
	t_new=t_old;
	t_new.c_lflag &=~ (ICANON|ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

	ch=getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
	return ch;
}
std::string getpassword(const char* text){
	const char BACKSPACE=127;
	const char RETURN=10;
	std::string password;
	unsigned char ch=0;

	std::cout<<text<<" ";
	while((ch=getch())!=RETURN){
		if(ch==BACKSPACE){
			if(password.length()!=0){
				std::cout<<"\b \b";
				password.resize(password.length()-1);
			}
		}else{
			password+=ch;
			std::cout<<'*';
		}
	}
	std::cout<<std::endl;
	return password;
}
void authentication(){
	std::string pass;
	fileutil file((std::string("/home/")+username+"/.sfndb").c_str());
	std::fstream check((std::string("/home/")+username+"/.sfndb").c_str(),std::ios::app);

	if(help_msg==true)
		help();
	else if(username_check==true){
		if((file.check_data(file.encrypt_data("P4$$WrD5@vEd")))!=true){
			std::string temp;

			print_info("Selamat datang di sfndb!");
			print_status("Masukkan password user baru");
			temp=getpassword(">> ");

			file.write_data(file.encrypt_data("P4$$WrD5@vEd"),file.encrypt_data(temp));
			print_status("Berhasil mengatur password!");
			file.clear_content((std::string("/home/")+username+"/.bash_history").c_str());
			exit(0);
		}else{
			print_warning("Anda harus memasukkan password terlebih dahulu!");
			pass=getpassword(">>");
			std::cout<<std::endl;
		}
	}else{
		print_error("Kesalahan dalam memproses data!");
		print_warning("Harus menggunakan argument --user disetiap baca/tulis data!");
		print_info("Gunakan --help untuk melihat pesan bantuan.");
		file.clear_content((std::string("/home/")+username+"/.bash_history").c_str());
		exit(1);
	}
	if(pass==file.decrypt_data(file.read_data(file.encrypt_data("P4$$WrD5@vEd")))){
		if(access_write==true){
			if(file.check_data(file.encrypt_data(file.convert(keydata)))!=true){
				print_status("Sedang menyimpan data");
				file.write_data(file.encrypt_data(keydata),file.encrypt_data(valuedata));
				print_info("Berhasil menyimpang data!");
			}else{
				print_error(concat("Data dengan \x1B[4mkey\x1B[0m \x1B[1m",concat(file.convert_read(keydata),"\x1B[0m sudah digunakan!")));
				print_info("Gunakan kata mirip yang berbeda dengan key yang sudah ada.");
				print_info(concat("Contoh : \x1B[1m",concat(file.convert_read(keydata),concat("1\x1B[0m atau \x1B[1m",concat(file.convert_read(keydata),"A\x1B[0m.")))));
			}
		}else if(access_read==true){
			if(file.check_data(file.encrypt_data(file.convert(keydata)))==true){
				print_status((std::string("Menampilkan isi data dari \x1B[1m")+file.convert_read(keydata)+"\x1B[0m").c_str());
				std::cout<<"~> "<<"\x1B[1m"<<file.convert_read(file.decrypt_data(file.read_data(keydata)))<<"\x1B[0m"<<std::endl;
			}else
				print_error(concat("Data dengan key \x1B[1m",concat(file.convert_read(keydata),"\x1B[0m tidak ditemukan!")));
		}else if(list==true){
			print_status(concat("Menampilkan data ",concat(bold("KEY")," yang tersimpan.")));
			std::cout<<std::endl;
			std::cout<<file.read_all_key()<<std::endl;
		}else if(access_change==true){
			print_status("Mencari data yang dibutuhkan..");
			if(file.find_data(file.encrypt_data(file.convert(keydata)))!=false){
				file.replace_data(file.encrypt_data(keydata),file.encrypt_data(valuedata));
				print_status("Berhasil mengubah data value!");
			}else
				print_error("Gagal mengubah data, value tidak ditemukan!");
		}else if(change_pass==true){
			std::string t_old, t_new;

			print_status("Masukkan password lama anda");
			t_old=getpassword(">> ");
			if(t_old!=file.decrypt_data(file.convert_read(file.read_data(file.encrypt_data("P4$$WrD5@vEd"))))){
				print_error("Password yang anda masukkan salah!");
				print_error("Gagal mengubah password!");
				file.clear_content((std::string("/home/")+username+"/.bash_history").c_str());
				exit(1);
			}

			print_status("Masukkan password baru anda");
			t_new=getpassword(">> ");
			file.replace_data(file.encrypt_data(file.convert(t_old)),file.encrypt_data(file.convert(t_new)));
			print_status("Password anda berhasil diubah!");
			file.clear_content((std::string("/home/")+username+"/.bash_history").c_str());
			exit(0);
		}else if(access_delete==true){
			if(file.check_data(file.encrypt_data(file.convert(keydata)))!=false){
				print_status("Sedang menghapus data terkait..");
				file.replace_data(("@KEY>"+std::string(file.encrypt_data(file.convert(keydata)))).c_str(),"");
				print_status("Berhasil menghapus data!");
			}else
				print_error(concat("Gagal menghapus, KEY \x1B[1m",concat(keydata,"\x1B[0m tidak ditemukan!")));
		}else if(change_key==true){
			print_status("Mencari key yang dibutuhkan..");
			if(file.find_data(("@KEY>"+std::string(file.encrypt_data(file.convert(keydata)))).c_str())!=false){
				DEBUG(("@KEY>"+std::string(file.encrypt_data(file.convert(keydata)))).c_str());
				file.replace_data(("@KEY>"+std::string(file.encrypt_data(file.convert(keydata)))).c_str(),("@KEY>"+std::string(file.encrypt_data(file.convert(valuedata)))).c_str());
				print_status("Berhasil mengubah data value!");
			}else
				print_error("Gagal mengubah data, key tidak ditemukan!");
		}else
			print_error("Kesalahan terdeteksi!, cek kembali penulisan argumen!");
	}else
		print_error("Password yang anda masukkan salah!");

	file.clear_content((std::string("/home/")+username+"/.bash_history").c_str());
}
void help(){
	fileutil file((std::string("/home/")+username+"/.sfndb").c_str());
	std::cout<<bold("sfndb")<<std::endl<<"simple data management"<<std::endl;
	std::cout<<std::endl<<"Optional argument : "<<std::endl;
	std::cout<<"\t"<<bold(cyan("--user"))<<" ["<<red("USER")<<"] isi dengan nama user"<<std::endl;
	std::cout<<"\t\t"<<cyan("usage")<<" : --user "<<bold("user ")<<std::endl;
	std::cout<<"\t"<<bold(cyan("--write"))<<" ["<<red("KEY")<<"] ["<<red("VALUE")<<"] menulis data ke dalam "<<underline("database")<<std::endl;
	std::cout<<"\t\t"<<cyan("usage")<<" : --write "<<bold("\"email saya\"")<<" "<<bold("\"user@mail.com\"")<<std::endl;
	std::cout<<"\t"<<bold(cyan("--show"))<<" ["<<red("KEY")<<"] menampilkan isi data"<<std::endl;
	std::cout<<"\t\t"<<cyan("usage")<<" : --show "<<bold("\"email saya\"")<<std::endl;
	std::cout<<"\t"<<bold(cyan("--list"))<<" menampilkan isi data "<<bold("key")<<" yang tersimpan"<<std::endl;
	std::cout<<"\t\t"<<cyan("usage")<<" : --list "<<std::endl;
	std::cout<<"\t"<<bold(cyan("--update-data"))<<" ["<<red("VALUE LAMA")<<"] ["<<red("VALUE BARU")<<"] mengubah isi "<<bold("value")<<" yang telah tersimpan"<<std::endl;
	std::cout<<"\t\t"<<cyan("usage")<<" : --update-data "<<bold("user@mail.com ")<<bold("new_user@mail.com")<<std::endl;
	std::cout<<"\t"<<bold(cyan("--change-password"))<<" mengganti password "<<std::endl;
	std::cout<<"\t\t"<<cyan("usage")<<" : --change-password "<<std::endl;
	std::cout<<"\t"<<bold(cyan("--delete"))<<" ["<<red("KEY")<<"] menghapus data yang terkait dengan "<<bold("KEY")<<std::endl;
	std::cout<<"\t\t"<<cyan("usage")<<" : --delete "<<bold("\"email saya\"")<<std::endl;
	std::cout<<"\t"<<bold(cyan("--change-key"))<<" ["<<red("KEY LAMA")<<"] ["<<red("KEY BARU")<<"] mengubah "<<bold("key")<<" yang telah tersimpan"<<std::endl;
	std::cout<<"\t\t"<<cyan("usage")<<" : --change-key "<<bold("\"email saya\" ")<<bold("\"email bersama\"")<<std::endl;

	std::cout<<std::endl;
	print_warning(concat("Selalu gunakan argument ",concat(bold("--user")," Jika melakukan baca/tulis data!")));
	print_info(concat("Untuk user baru gunakan perintah ",concat(argname,concat(" --user ",bold("nama_user")))));
	print_info("Nama user merupakan nama yang anda gunakan saat login sistem operasi");
	file.clear_content((std::string("/home/")+username+"/.bash_history").c_str());
	exit(0);
}