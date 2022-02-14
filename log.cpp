#include <fstream>
#include <string>

void log(std::string str) {
    std::ofstream outfile;
    outfile.open("other/log.txt", std::ios_base::app);
    outfile << str+"\n"; 
}

void clear_log() {
    std::ofstream outfile;
    outfile.open("other/log.txt");
    outfile << ""; 
}
