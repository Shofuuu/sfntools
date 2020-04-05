#include <config.h>
#include <cli.h>

class Conf{
private:
    std::string _write,_value,_key,_object;
    bool _verb=0;
public:
    int _find_(std::string txt);
    void showHelp(std::string arg);
    int writeOutput(void);
    std::string getKey(void);
    int setKey(std::string key);
    std::string getObject(void);
    int setObject(std::string obj);
    std::string getValue(void);
    int setValue(std::string val);
    std::string getFlName(void);
    int setFlName(std::string fl);
    std::string ftext(std::string txt);
    void setVerbose(void);
    bool getVerbose(void);
    int purge_(void);
    int readData(void);
};

int main(int argc, char* argv[]){
    Conf c;
    int wrt=0,rd=0,dl=0,temp=0;

    if(argc<2)
        print_error(std::string("Kekurangan argumen!\n")+concat("try ",concat(argv[0]," --help")));
    else{
        for(int scan=1;scan<argc;scan++){
            if(c.ftext(std::string(argv[scan]))=="--help" || c.ftext(std::string(argv[scan]))=="-h"){
                temp++;
                if(scan!=(argc-1)){
                    print_warning("beberapa task tidak dilaksanakan!");
                    c.showHelp(std::string(argv[0]));
                    for(int x=scan+1;x<argc;x++)
                        print_error(concat(std::string(argv[x])," gagal di laksanakan!"));
                    break;
                }else
                    c.showHelp(std::string(argv[0]));
            }else if(c.ftext(std::string(argv[scan]))=="write" ||  c.ftext(std::string(argv[scan]))=="w"){
                if(wrt>1)
                    print_error("Hanya bisa menulis satu berkas konfig!");
                else 
                    c.setFlName(std::string(argv[scan]));
                wrt++;
            }else if(c.ftext(std::string(argv[scan]))=="read" ||  c.ftext(std::string(argv[scan]))=="r"){
                if(rd>1)
                    print_error("Hanya bisa membaca satu berkas konfig!");
                else 
                    c.setFlName(std::string(argv[scan]));
                rd++;
            }else if(c.ftext(std::string(argv[scan]))=="key" || c.ftext(std::string(argv[scan]))=="k")
                c.setKey(std::string(argv[scan]));
            else if(c.ftext(std::string(argv[scan]))=="object" || c.ftext(std::string(argv[scan]))=="o")
                c.setObject(std::string(argv[scan]));
            else if(c.ftext(std::string(argv[scan]))=="value" || c.ftext(std::string(argv[scan]))=="v")
                c.setValue(std::string(argv[scan]));
            else if(c.ftext(std::string(argv[scan]))=="verbose" || c.ftext(std::string(argv[scan]))=="vb")
                c.setVerbose();
            else if(c.ftext(std::string(argv[scan]))=="delete" || c.ftext(std::string(argv[scan]))=="d"){
                c.setObject(std::string(argv[scan]));
                dl++;
            }else{
                print_error(concat("tidak ditemukan perintah ",std::string(argv[scan])));
                break;
            }
        }
        
        if(dl>0)
            c.purge_();
        else if(wrt>0)
            c.writeOutput();
        else if(rd>0)
            c.readData();
        else
            if(!(temp>0))
                print_error("fatal error, i/o empty!");
        print_info("done..");
    }

    return 0;
}

int Conf::_find_(std::string txt){
    int len=0;
    for(int x=0;x<txt.length();x++){
        if(txt[x]==':')
            break;
        len++;
    }
    return len+1;
}
void Conf::showHelp(std::string arg){
    int max=7;
    std::string option[max][2]={
        {" --help | -h","pesan bantuan cara menggunakan program dan keterangan"},
        {" key | k","atur key data yang akan ditulis"},
        {" object | o","atur object pada key yang ditunjuk"},
        {" value | v","atur isi dari object pada suatu key"},
        {" write | w","berkas output file konfigurasi"},
        {" verbose | vb","menampilkan pesan aktivitas"},
        {" delete | d","menghapus object yang dicari"}
    };
    std::cout<<"Usage : "<<arg<<" [OPTION]\n";
    std::cout<<"OPTION : \n";
    for(int x=0;x<max;x++)
        std::cout<<option[x][0]<<"\t\t"<<option[x][1]<<"\n";
    std::cout<<"\nKunjungi dan temukan program lain di https://github.com/Sfndude\n";
}
int Conf::writeOutput(void){
    std::ifstream read;
    std::string flname,obj,_key,val;

    flname=getFlName();
    obj=getObject();
    _key=getKey();
    val=getValue();
    
    flname=flname.replace(flname.begin(),flname.begin()+_find_(flname),"");
    if(getVerbose()==1){
        if(!read.good())
            print_status("creating new configuration file..");
        else
            print_status("found existing configuration file.");
    }
    Config c(flname);
    _key=_key.replace(_key.begin(),_key.begin()+_find_(_key),"");
    if(getVerbose()==1){
        if(c.exist(_key)==0)
            print_status("writing new key in configuration file.");
        else
            print_status("found existing key in configuration file.");
    }
    obj=obj.replace(obj.begin(),obj.begin()+_find_(obj),"");
    if(getVerbose()==1){
        if(c.exist(obj)==0)
            print_status("adding new object to "+_key+".");
        else
            print_status("found existing object at "+_key+".");
    }
    val=val.replace(val.begin(),val.begin()+_find_(val),"");
    if(getVerbose()==1){
        if(c.exist(val)==0)
            print_status("adding new value to object "+obj+".");
        else
            print_status("overwriting new value to object "+obj+".");
    }

    c.key(_key);
    c.write(obj,val);
}
std::string Conf::getKey(void){return _key;}
int Conf::setKey(std::string key){_key=key;}
std::string Conf::getObject(void){return _object;}
int Conf::setObject(std::string obj){_object=obj;}
std::string Conf::getValue(void){return _value;}
int Conf::setValue(std::string val){_value=val;}
std::string Conf::getFlName(void){return _write;}
int Conf::setFlName(std::string fl){_write=fl;}
std::string Conf::ftext(std::string txt){
    std::string data;
    for(int x=0;x<txt.length();x++){
        if(txt[x]==':')
            break;
        else
            data+=txt[x];
    }
    return data;
}
void Conf::setVerbose(void){_verb=1;}
bool Conf::getVerbose(void){return _verb;}
int Conf::purge_(void){
    std::string _obj,_fl,_key;
    _obj=getObject();
    _fl=getFlName();
    _key=getKey();
    _obj.replace(_obj.begin(),_obj.begin()+_find_(_obj),"");
    _fl.replace(_fl.begin(),_fl.begin()+_find_(_fl),"");
    _key.replace(_key.begin(),_key.begin()+_find_(_key),"");

    if(getVerbose()==1){
        if(_fl.empty()){
            print_error("config file not found!");
            return -1;
        }
    }

    if(getVerbose()==1){
        print_status("deleting "+_obj+"..");
        if(_key.empty()){
            print_error("can\'t find existing key!");
            return -1;
        }else
            print_status("found existing key!");

        if(_obj.empty()){
            print_error("can\'t find existing object!");
            return -1;
        }else
            print_status("found existing object!");
    }
    Config c(_fl);
    c.key(_key);
    if(c.purge(_obj)!=0)
        print_error("object not found");
    else
        print_status("object deleted!");
}
int Conf::readData(void){
    std::string flname,_key,_obj;

    flname=getFlName();
    _key=getKey();
    _obj=getObject();
    flname=flname.replace(flname.begin(),flname.begin()+_find_(flname),"");
    _key=_key.replace(_key.begin(),_key.begin()+_find_(_key),"");
    _obj=_obj.replace(_obj.begin(),_obj.begin()+_find_(_obj),"");

    Config c(flname);
    if(getVerbose()==1){
        if(c.exist(_key)==(-1)){
            print_status("found existing key.");
            if(c.exist(_obj)==(1))
                print_status("found existing object.");
            else{
                print_error("object not found!");
                return -1;
            }
        }else{
            print_error("key not found.");
            return -1;
        }
    }
    c.key(_key);
    if(getVerbose()==1)
        std::cout<<"[OUTPUT] "<<c.read(_obj)<<"\n";
    else
        std::cout<<c.read(_obj)<<"\n";
}