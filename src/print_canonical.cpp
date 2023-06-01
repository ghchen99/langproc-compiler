#include "ast.hpp"
#include <iostream>
#include <fstream>

int main()
{
    const Base* ast = parseAST();

    MIPZ myMIPS;
    ast->printMIPS("Hi", std::cout, myMIPS);
    std::cout<<std::endl;

    return 0;

}
