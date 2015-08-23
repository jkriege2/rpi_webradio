#include "rpi_tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <regex>
#include <iostream>

std::string rpit_readlineFromCommand(const char *command)
{
    FILE *lsofFile_p = popen(command, "r");

    if (!lsofFile_p)
    {
      return std::string();
    }

    char buffer[4096];
    char *line_p = fgets(buffer, sizeof(buffer), lsofFile_p);
    pclose(lsofFile_p);
    return std::string(line_p);
}


float rpit_readCPUTemperatur()
{
    std::string t=rpit_readlineFromCommand("vcgencmd measure_temp");
    std::string num;
    bool state=0;
    for (size_t i=0; i<t.size(); i++) {
        if (state==0) {
            switch (t[i]) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state=1;
                    num.push_back(t[i]);
                    break;
                default: break;
            }
        } else if (state==1) {
            switch (t[i]) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case'.':
                    num.push_back(t[i]);
                    break;
                default:
                    state=2;
                    break;
            }
        } else {
            break;
        }
    }
    //std::cout<<t<<"  => "<<num<<" => "<<atof(num.c_str())<<"\n\n\n";
    return atof(num.c_str());

//    try {

//        std::cout<<"t="<<t<<std::endl;
//        std::regex rx("[0-9]+", std::regex::ECMAScript);
//        std::smatch sm;
//        std::cout<<"made regexp\n";
//        if (std::regex_match(t, sm, rx)) {
//            std::cout<<"matched "<<sm.size()<<"\n";
//            // The first sub_match is the whole string; the next
//            // sub_match is the first parenthesized expression.
//            if (sm.size() > 1) {
//                std::ssub_match base_sub_match = sm[1];
//                std::string base = base_sub_match.str();
//                std::cout<<"match[1]= "<<base<<"  -> "<<atof(base.c_str());
//                return atof(base.c_str());
//            }
//        }
//    } catch(const std::regex_error& e) {
//        std::cerr<<e.what()<<std::endl;
//        if (e.code()== std::regex_constants::error_collate) std::cerr<<"  error_collate\n";
//        if (e.code()== std::regex_constants::error_ctype) std::cerr<<"  error_ctype\n";
//        if (e.code()== std::regex_constants::error_escape) std::cerr<<"  error_escape\n";
//        if (e.code()== std::regex_constants::error_backref) std::cerr<<"  error_backref\n";
//        if (e.code()== std::regex_constants::error_brack) std::cerr<<"  error_brack\n";
//        if (e.code()== std::regex_constants::error_paren) std::cerr<<"  error_paren\n";
//        if (e.code()== std::regex_constants::error_brace) std::cerr<<"  error_brace\n";
//        if (e.code()== std::regex_constants::error_badbrace) std::cerr<<"  error_badbrace\n";
//        if (e.code()== std::regex_constants::error_range) std::cerr<<"  error_range\n";
//        if (e.code()== std::regex_constants::error_space) std::cerr<<"  error_space\n";
//        if (e.code()== std::regex_constants::error_badrepeat) std::cerr<<"  error_badrepeat\n";
//        if (e.code()== std::regex_constants::error_complexity) std::cerr<<"  error_complexity\n";
//        if (e.code()== std::regex_constants::error_stack) std::cerr<<"  error_stack\n";
//     }

//    return -1;

}
