#pragma once
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>


const char* load_text(const char* path)
{
    // if (!std::filesystem::exists(path))
    //     throw std::logic_error("shader loader, path doesn't exists");

    std::ifstream file(path);

    std::string temp;
    std::string out;

    while(std::getline(file, temp)) 
    {
        out += temp + '\n';
    }

    char* out_c = new char [out.length() + 1];
    std::strcpy(out_c, out.c_str()); 

    return out_c;
    // return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}
