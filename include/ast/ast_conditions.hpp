#ifndef H_CONDITIONS
#define H_CONDITIONS

#include <iostream>
#include <sstream>

#include "ast_base.hpp"

class Conditions
    : public Base
{
protected:
    BasePtr condition;
    BasePtr branch;


public:
    Conditions(BasePtr _condition, BasePtr _branch)
        : condition(_condition)
        , branch(_branch)
    {}

    virtual ~Conditions()
    {
        delete condition;
        delete branch;
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::stringstream &out, Py &myPy) const = 0;
};

class If
    : public Conditions
{

public:
    If(BasePtr _condition, BasePtr _branch)
        : Conditions(_condition, _branch)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        condition->printMIPS(r1, out, help);
        std::string label = help.makelabl();
        out << "BEQ " << r1 << ", $0, " << label << std::endl;
        branch->printMIPS(reg, out, help);
        out << label << ":" << std::endl;
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "if (";
        condition->printC(out);
        out << ") \n";
        out << "{";
        branch->printC(out);
        out << " }";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
          out << "\t";
        }
        out << "if (";
        condition->printPy(out, myPy);
        out << ") :\n";
        branch->printPy(out, myPy);
    }
};

class IfElse
    : public Conditions
{
protected:
    BasePtr elseBranch;
public:
    IfElse(BasePtr _condition, BasePtr _branch, BasePtr _elseBranch)
        : Conditions(_condition, _branch), elseBranch(_elseBranch)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        condition->printMIPS(r1, out, help);
        std::string label1 = help.makelabl();
        std::string label2 = help.makelabl();

        out << "BEQ " << r1 << ", $0, " << label1 << std::endl;
        branch->printMIPS(reg, out, help);
        out << "J " << label2 << std::endl;
        out << label1 << std::endl;
        elseBranch->printMIPS(reg, out, help);
        out << label2 << ":" << std::endl;
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "if (";
        condition->printC(out);
        out << ") \n";
        out << "{";
        branch->printC(out);
        out << " } else {\n";
        elseBranch->printC(out);
        out << std::endl;
        out << "}";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
          out << "\t";
        }
        out << "if (";
        condition->printPy(out, myPy);
        out << ") :\n";
        branch->printPy(out, myPy);
        out << std::endl;
        for(int i = myPy.indent; i > 0; i--){
          out << "\t";
        }
        out << "else :\n";
        elseBranch->printPy(out, myPy);
    }
};

class Switch
    : public Base
{
protected:
    std::string condition;
    BasePtr branch;
public:
    Switch(std::string _condition, BasePtr _branch)
        : condition(_condition), branch(_branch)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        out << "switch " << std::endl;
    }
    virtual void printC (std::ostream &out) const override{
        /*out << "switch (";
        condition->printC(out);
        out << ") \n";
        out << "{";
        branch->printC(out);
        out << " }";*/
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        myPy.switchVar.push_back(condition);
        branch->printPy(out, myPy);
    }
};


class Case
    : public Base
{
protected:
    int index;
    BasePtr stmt;
    BasePtr nextStmt;
    std::string ifBreak;

public:
    Case(int _index, BasePtr _stmt, BasePtr _nextStmt, std::string _ifBreak)
    : index(_index), stmt(_stmt), nextStmt(_nextStmt), ifBreak(_ifBreak)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        out << "case " << std::endl;
    }
    virtual void printC (std::ostream &out) const override{
        /*out << "switch (";
        condition->printC(out);
        out << ") \n";
        out << "{";
        branch->printC(out);
        out << " }";*/
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        if(index != 1000){
            out << "if ( " << myPy.switchVar[myPy.switchVar.size() - 1] << " = " << index;
            for(int i = 0; i < myPy.caseIndex.size(); i++){
                out << " || " << myPy.switchVar[myPy.switchVar.size() - 1] << " = " << myPy.caseIndex[i] ;
            }
            myPy.caseIndex.push_back(index);
            if(ifBreak != ""){
                myPy.caseIndex.clear();
            }
            out << " ) : \n";
            myPy.indent++;
            stmt->printPy(out, myPy);
            myPy.indent--;
            out << std::endl;
        }
        if(nextStmt != NULL){
            nextStmt-> printPy(out, myPy);
        }
        if(index == 1000 && nextStmt == NULL){
            out << "else :\n";
            myPy.indent++;
            stmt->printPy(out, myPy);
            myPy.indent--;
            out << std::endl;
        }

    }
};
#endif
