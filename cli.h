#ifndef CLI_H_INCLUDED
#define CLI_H_INCLUDED
#include <iostream>
#include <sstream>

/* FOREGROUND */
#define knormal  "\x1B[0m"
#define kred  "\x1B[31m"
#define kgreen  "\x1B[32m"
#define kyellow  "\x1B[33m"
#define kblue  "\x1B[34m"
#define kmagenta  "\x1B[35m"
#define kcyan  "\x1B[36m"
#define kwhite  "\x1B[37m"

#define red(x) kred x knormal
#define green(x) kgreen x knormal
#define yellow(x) kyellow x knormal
#define blue(x) kblue x knormal
#define magenta(x) kmagenta x knormal
#define cyan(x) kcyan x knormal
#define white(x) kwhite x knormal

#define bold(x) "\x1B[1m" x knormal
#define underline(x) "\x1B[4m" x knormal

/*#define print_error(perr) std::cout<<bold(red("[-] "))<<perr<<'\n'
#define print_status(pstat) std::cout<<bold(green("[+] "))<<pstat<<'\n'
#define print_warning(pwarn) std::cout<<bold(yellow("[!] "))<<pwarn<<'\n'
#define print_info(pinfo) std::cout<<bold(blue("[info] "))<<pinfo<<'\n'*/

void  print_error(std::string perr){ std::cout<<bold(red("[-] "))<<perr<<'\n'; }
void print_status(std::string pstat){ std::cout<<bold(green("[+] "))<<pstat<<'\n'; }
void print_warning(std::string pwarn){ std::cout<<bold(yellow("[!] "))<<pwarn<<'\n'; }
void print_info(std::string pinfo){ std::cout<<bold(blue("[info] "))<<pinfo<<'\n'; }

inline int __NUM__=0;
#define cstr(x) std::string(x).c_str()
#define concat(x,y) (std::string(x)+y).c_str()
#define istr(x) static_cast<std::ostringstream&>((std::ostringstream()<<std::dec<<x)).str()
#define DEBUG(x) std::cout<<"#DBG("<<__NUM__++<<") \x1B[1m"<<x<<"\x1B[0m"<<std::endl

#endif // CLI_H_INCLUDED
