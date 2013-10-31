#include <iostream>
#include "parser.h"

int main()
{
    std::cout << "Hello World!" << std::endl;
    parser *par = new parser();
    par->add(BLOCK, 0, 0);
    std::cout << par->getCount(BLOCK) << std::endl;
    return 0;
}

