#include <iostream>
#include <string>

#include "fileman.h"

int main()
{
    std::string str = load_text("../res/main.fragment");
    
    std::cout << str << std::endl;

    return 0;
}