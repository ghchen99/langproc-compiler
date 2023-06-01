#ifndef H_LOOPS
#define H_LOOPS

#include <iostream>
#include <sstream>

#include "ast_base.hpp"

class Scope
    : public Base
{

protected:
BasePtr scop;

public:
    Scope(BasePtr _scop)
        : scop(_scop)
    {}

    ~Scope(){
      delete scop;
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        scop->printMIPS(reg, out, help);
    }
    virtual void printC (std::ostream &out) const override{
        out << "{" << std::endl;
        scop->printC(out);
        out << "}";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        myPy.indent++;
        scop->printPy(out, myPy);
        myPy.indent--;
    }
};

class For
    : public Base
{

protected:
    BasePtr initial;
    BasePtr condition;
    BasePtr incrementordecrement;
    BasePtr branch;

public:
    For(BasePtr _initial, BasePtr _condition, BasePtr _incrementordecrement, BasePtr _branch)
        : initial(_initial), condition (_condition), incrementordecrement(_incrementordecrement), branch (_branch)
    {}

    ~For(){
        delete condition;
        delete initial;
        delete branch;
        delete incrementordecrement;
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << "for(";
        initial->printC(out);
        out << "; ";
        condition->printC(out);
        out << "; ";
        incrementordecrement->printC(out);
        out << ") {" << std::endl;
        branch->printC(out);
        out << "}";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 1; i--){
          out << "\t";
        }
        out << "while (";
        myPy.indent--;
        condition->printPy(out, myPy);
        out << "):" << std::endl;
        myPy.indent++;
        branch->printPy(out, myPy);
        myPy.indent++;
        out << std::endl;
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        incrementordecrement->printPy(out, myPy);
        out << std::endl;
        myPy.indent--;
    }
};

class While
    : public Base
{

protected:
    BasePtr condition;
    BasePtr branch;

public:
    While(BasePtr _condition, BasePtr _branch)
        : condition (_condition), branch (_branch)
    {}

    ~While(){
        delete condition;
        delete branch;
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "while(";
        condition->printC(out);
        out << ") {";
        branch->printC(out);
        out << "}";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        out << "while ";
        condition->printPy(out, myPy);
        out << ":" << std::endl;
        branch->printPy(out, myPy);
    }
};

class Do
    : public Base
{

protected:
    BasePtr condition;
    BasePtr branch;

public:
    Do(BasePtr _condition, BasePtr _branch)
        : condition (_condition), branch (_branch)
    {}

    ~Do(){
        delete condition;
        delete branch;
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "do {";
        branch->printC(out);
        out << "}";
        out << "while(";
        condition->printC(out);
        out << ")";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        out << "while True : \n";
        condition->printPy(out, myPy);
        out << "\n\t\tif (";
        branch->printPy(out, myPy);
        out << "):\n";
        out << "\t\t\tbreak";

    }
};

class BBreak
    : public Base
{

public:
    BBreak()
    {}

    ~BBreak(){}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "break\n";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        out << "break\n";
    }
};

class CContinue
    : public Base
{

public:
    CContinue()
    {}

    ~CContinue(){}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "continue\n";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        out << "continue\n";
    }
};

#endif
