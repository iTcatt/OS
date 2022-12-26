#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>
#include <iostream>

class Configuration {
    public:
        int id;
        int parent;
        std::string path;
        
        void printConfiguration() {
            std::cout << id << '\n' << parent << '\n' << path <<"\n\n";
        }
};

std::vector<Configuration> iniParser(std::string);
#endif