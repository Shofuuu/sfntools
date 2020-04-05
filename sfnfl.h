#include <fstream>
#include <algorithm>
#include <cstring>
#include <cli.h>
#include <time.h>

void help_msg(){
    std::string options[7][2]={
        {"-fO [..]","Specify output filename"},
        {"-tP [..]","Prepend text on every line"},
        {"-tA [..]","Append text on every line"},
        {"-cR [..] [..]","Replace char with custom char"},
        {"-lC [..]","Continue or skip the line if contain text"},
        {"-l0","Skip the line if not contain any text"},
        {"-v","Enable verbose message"}
    };

    std::cout<<"SFNFL file tool v0.0.3"<<std::endl;
    std::cout<<"Usage : sfnfl [option] [value] [...] [ifstream]"<<std::endl;
    std::cout<<"OPTIONS:"<<std::endl;

    //print options
    for(int c=0;c<7;c++)
        std::cout<<"   "<<options[c][0]<<" : "<<options[c][1]<<std::endl;
}

class SFNFL{
private:
    std::string fl_name,f_out,fl;
    std::string pre_txt,app_txt,con_txt;
    std::string rep_c[2];
    bool raw=false;
    bool verbose_stat=false;
    bool skip_line=false;
    bool get_verbose_status(void){return verbose_stat;}
    std::string get_file_output_name(void){return f_out;}
    std::string get_filter_name(void);
    std::string get_prepend_text(void){return pre_txt;}
    std::string get_append_text(void){return app_txt;}
    std::string get_replace_char(int x){return rep_c[x];}
    std::string get_continue_text(void){return con_txt;}
    int get_total_line(void);
    bool get_skip_line_status(void){return skip_line;}
    std::string replace_all(std::string str, const std::string& from, const std::string& to);
public:
    SFNFL(std::string fl){
        fl_name = fl;
    }
    bool file_exist(void);
    void set_file_output_name(std::string fl){f_out=fl;}
    void set_verbose_status(bool stat){verbose_stat=stat;}
    void set_prepend_text(std::string text){pre_txt=text;}
    void set_append_text(std::string text){app_txt=text;}
    void set_replace_char(std::string c,std::string c_){rep_c[0]=c;rep_c[1]=c_;}
    void set_continue_text(std::string text){con_txt=text;}
    void set_skip_line_status(bool stat){skip_line=stat;}
    void write_output(void);
};

//PRIVATE
std::string SFNFL::get_filter_name(void){
    if(get_file_output_name()==""){
        if(raw==false) fl = fl_name+"_sfnfl";
        raw=true;
        return fl;
    }else
        return get_file_output_name();
}
std::string SFNFL::replace_all(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos=0;
    while((start_pos=str.find(from,start_pos))!=std::string::npos) {
        str.replace(start_pos,from.length(),to);
        start_pos+=to.length();
    }
    return str;
}

//PUBLIC
bool SFNFL::file_exist(void){
    std::ifstream f(fl_name.c_str());
    return f.good();
}
void SFNFL::write_output(void){
    clock_t start = clock();

    std::fstream read(fl_name.c_str(),std::ios::in);
    std::ofstream write(get_filter_name().c_str());
    std::string str("");

    if(get_verbose_status()==true){
        print_info(std::string("file : ")+fl_name);
        print_info(std::string("output : ")+get_filter_name());
    }

    while(std::getline(read,str)){
        if(get_verbose_status()==true)
            print_status(str);
        if(get_replace_char(0)!="")
            if(str.find(get_replace_char(0))!=std::string::npos)
                str=replace_all(str,get_replace_char(0),get_replace_char(1));
        if(get_continue_text()!="")
            if(str.find(get_continue_text())!=std::string::npos) continue;
        if(get_skip_line_status()==true)
            if(str=="") continue;
        write<<get_prepend_text()<<str<<get_append_text()<<std::endl;
    }

    if(get_verbose_status()==true)
        print_info(std::string("Time elapsed : ")+std::to_string((double)(clock()-start)/CLOCKS_PER_SEC));
}