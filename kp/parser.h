#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>
#include <iostream>

class Configuration {
    public:
        std::string id;
        std::string name;
        std::string path;
        
        void printConfiguration() {
            std::cout << id << '\n' << name << '\n' << path <<"\n\n";
        }
};

std::vector<Configuration> iniParser(std::string);
#endif