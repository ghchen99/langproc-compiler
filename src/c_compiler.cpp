#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ast.hpp"
//extern "C" int yydebug;

extern "C" FILE *yyin;

int main(int argc, char *argv[]){
    //yydebug = 1;
    //std::fstream fs;
    //fs.open(argv[2]);
    yyin = fopen(argv[2], "r");
    const Base* ast = parseAST();

    std::cout << std::endl;
    freopen(argv[4], "w", stdout);


    if(static_cast<std::string>(argv[1]) == "--translate"){
        //ofstream outfile;
        //outfile.open(argv[4]);
        Py myPython;
        std::stringstream ss1, ss2;
        ast->printPy(ss1, myPython);
        
        
        if(myPython.flag == 1){
            ss2 << "class Pointer:\n";
            ss2 << "\tdef __init__(self, lval, index = 0):\n";
            ss2 << "\t\tself.lval = lval\n";
            ss2 << "\t\tself.index = index\n\n";
            ss2 << "\tdef deref(self, *_set):\n";
            ss2 << "\t\tif isinstance(self.lval, list):\n";
            ss2 << "\t\t\tif len(_set) > 0:\n";
            ss2 << "\t\t\t\tself.lval[self.index] = _set[0]\n";
            ss2 << "\t\t\treturn self.lval[self.index]\n";
            ss2 << "\t\treturn self.lval(*_set)\n\n";
            ss2 << "\tdef __add__(self, i):\n";
            ss2 << "\t\tassert isinstance(i, int)\n";
            ss2 << "\t\treturn Pointer(self.lval, self.index + i)\n\n";
            ss2 << "\tdef __sub__(self, i):\n";
            ss2 << "\t\tassert isinstance(i, int)\n";
            ss2 << "\t\treturn Pointer(self.lval, self.index - i)\n\n";
            ss2 << "\tdef __iadd__(self, i):\n";
            ss2 << "\t\tassert isinstance(i, int)\n";
            ss2 << "\t\tself.index += i\n\n";
            ss2 << "\tdef __isub__(self, i):\n";
            ss2 << "\t\tassert isinstance(i, int)\n";
            ss2 << "\t\tself.index -= i\n\n";
            ss2 << "\tdef __getitem__(self, i):\n";
            ss2 << "\t\tassert isinstance(i, int)\n";
            ss2 << "\t\tif isinstance(self.lval, list):\n";
            ss2 << "\t\t\treturn self.lval[self.index + i]\n";
            ss2 << "\t\treturn self.lval()\n\n";
            ss2 << "\tdef __setitem__(self, i, v):\n";
            ss2 << "\t\tassert isinstance(i, int)\n";
            ss2 << "\t\tif isinstance(self.lval, list):\n";
            ss2 << "\t\t\tself.lval[self.index + i] = v\n";
            ss2 << "\t\t\treturn v\n";
            ss2 << "\t\tself.lval(v)\n";
            ss2 << "\t\treturn v\n\n";
        }
        std::cout << ss2.str();
        std::cout << ss1.str();
        std::cout << std::endl;
        std::cout << std::endl;
        //outfile.close();
        std::cout << "# Boilerplat" << std::endl;
        std::cout << "if __name__ == \"__main__\":" << std::endl;
        std::cout << "    import sys" << std::endl;
        std::cout << "    ret=main()" << std::endl;
        std::cout << "    sys.exit(ret)" << std::endl;
    }

    else if (static_cast<std::string>(argv[1]) == "-S"){
        MIPZ myMIPS;
        ast->printMIPS("Hi", std::cout, myMIPS);
        std::cout<<std::endl;
    }

    return 0;
}
