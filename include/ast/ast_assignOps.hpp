#ifndef H_ASSIGNOPS
#define H_ASSIGNOPS

#include <iostream>
#include <sstream>
#include <string>
#include "ast_base.hpp"

class AssignOp
    : public Base
{
protected:
    std::string variable;

public:
    AssignOp(std::string _variable)
        : variable(_variable)
    {}

    virtual ~AssignOp()
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::stringstream &out, Py &myPy) const = 0;
};

class AssignEqualOperator
    : public AssignOp
{
protected:
    BasePtr val;
public:
    AssignEqualOperator(std::string &_variable, BasePtr _val)
        : AssignOp(_variable), val(_val)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        val->printMIPS(r1, out, help);
        out << "ADDU " << reg << ", $0, " << r1 << std::endl;
        if(help.localexists(variable)){
            out << "SW " << reg << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            std::string r2 = "$" + std::to_string(help.findreg());
            out << "LUI " << r2 << ", %hi(" << variable << ")" << std::endl;
            out << "ADDI " << r2 << ", " << r2 << ", %lo(" << variable << ")" << std::endl;
            out << "SW " << reg << ", 0(" << r2 << ")" << std::endl;
            help.regFlag[std::stoi(r2.substr(1))] = 0;
        }
        else{
            throw "Variable not declared. ";
        }
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << " = ";
        val->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable;
        out << " = ";
        val->printPy(out, myPy);
    }
};

class AssignEqualArray
    : public AssignOp
{
protected:
    BasePtr val;
    BasePtr index;
public:
    AssignEqualArray(std::string &_variable, BasePtr _val, BasePtr _index)
        : AssignOp(_variable), val(_val), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
      std::string r1 = "$" + std::to_string(help.findreg());
      val->printMIPS(r1, out, help);
      out << "ADDU " << reg << ", $0, " << r1 << std::endl;
      help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << "[" << index << "]=";
        val->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable;
        out << "[";
        index->printPy(out, myPy);
        out << "]=";
        val->printPy(out, myPy);
    }
};

class AddEqualOperator
    : public AssignOp
{
protected:
    BasePtr val;
public:
    AddEqualOperator(std::string &_variable, BasePtr _val)
        : AssignOp(_variable), val(_val)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        val->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(help.findreg());
        std::string r3 = "$" + std::to_string(help.findreg());

        if(help.localexists(variable)){
            out << "LW " << r2 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << "LUI " << r3 << ", %hi(" << variable << ")" << std::endl;
            out << "ADDI " << r2 << ", " << r2 << ", %lo(" << variable << ")" << std::endl;
            out << "LW " << r2 << ", 0(" << r3 << ")" << std::endl;
        }
        else{
          throw "Variable not declared. ";
        }
        out << "ADDU " << r2 << ", " << r2 << ", " << r1 << std::endl;
        out << "ADDU " << reg << ", $0, " << r2 << std::endl;

        if(help.localexists(variable)){
            out << "SW " << r2 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << "SW " << r2 << ", 0(" << r3 << ")" << std::endl;
            help.regFlag[std::stoi(r3.substr(1))] = 0;
        }
        else{
            throw "Variable not declared. ";
        }
        help.regFlag[std::stoi(r1.substr(1))] = 0;
        help.regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << " += ";
        val->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable;
        out << " += ";
        val->printPy(out, myPy);
    }
};

class AddEqualArray
    : public AssignOp
{
protected:
    BasePtr val;
    BasePtr index;
public:
    AddEqualArray(std::string &_variable, BasePtr _val, BasePtr _index)
        : AssignOp(_variable), val(_val), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        val->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(help.findreg());
        help.regFlag[std::stoi(r1.substr(1))] = 0;
        help.regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << "[" << index << "]+=";
        val->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable;
        out << "[";
        index->printPy(out, myPy);
        out << "]+=";
        val->printPy(out, myPy);
    }
};

class SubEqualOperator
    : public AssignOp
{
protected:
    BasePtr val;
public:
    SubEqualOperator(std::string &_variable, BasePtr _val)
        : AssignOp(_variable), val(_val)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        val->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(help.findreg());
        std::string r3 = "$" + std::to_string(help.findreg());

        if(help.localexists(variable)){
            out << "LW " << r2 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << "LUI " << r3 << ", %hi(" << variable << ")" << std::endl;
            out << "ADDI " << r2 << ", " << r2 << ", %lo(" << variable << ")" << std::endl;
            out << "LW " << r2 << ", 0(" << r3 << ")" << std::endl;
        }
        else{
            throw "Variable not declared. ";
        }
        out << "SUBU " << r2 << ", " << r2 << ", " << r1 << std::endl;
        out << "ADDU " << reg << ", $0, " << r2 << std::endl;
        if(help.localexists(variable)){
            out << "SW " << r2 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << "SW " << r2 << ", 0(" << r3 << ")" << std::endl;
            help.regFlag[std::stoi(r3.substr(1))] = 0;
        }
        else{
            throw "Variable not declared. ";
        }
        help.regFlag[std::stoi(r1.substr(1))] = 0;
        help.regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << " -= ";
        val->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable;
        out << " -= ";
        val->printPy(out, myPy);
    }
};

class SubEqualArray
    : public AssignOp
{
protected:
    BasePtr val;
    BasePtr index;
public:
    SubEqualArray(std::string &_variable, BasePtr _val, BasePtr _index)
        : AssignOp(_variable), val(_val), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        val->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(help.findreg());

        out << "SUBU " << r2 << ", " << r2 << ", " << r1 << std::endl;
        out << "ADDU " << reg << ", $0, " << r2 << std::endl;

        help.regFlag[std::stoi(r1.substr(1))] = 0;
        help.regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << "[";
        index->printC(out);
        out << "]-=";
        val->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable;
        out << "[" ;
        index->printPy(out, myPy);
        out << "]-=";
        val->printPy(out, myPy);
    }
};

class MultEqualOperator
    : public AssignOp
{
protected:
    BasePtr val;
public:
    MultEqualOperator(std::string &_variable, BasePtr _val)
        : AssignOp(_variable), val(_val)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        val->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(help.findreg());
        std::string r3 = "$" + std::to_string(help.findreg());

        if(help.localexists(variable)){
            out << "LW " << r2 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << "LUI " << r3 << ", %hi(" << variable << ")" << std::endl;
            out << "ADDI " << r2 << ", " << r2 << ", %lo(" << variable << ")" << std::endl;
            out << "LW " << r2 << ", 0(" << r3 << ")" << std::endl;
        }
        else{
            throw "Variable not declared. ";
        }
        out << "MUL " << reg << ", " << r2 << ", " << r1 << std::endl;
        if(help.localexists(variable)){
            out << "SW " << r2 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << "SW " << r2 << ", 0(" << r3 << ")" << std::endl;
            help.regFlag[std::stoi(r3.substr(1))] = 0;
        }
        else{
            throw "Variable not declared. ";
        }
        help.regFlag[std::stoi(r1.substr(1))] = 0;
        help.regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << " *= ";
        val->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable;
        out << " *= ";
        val->printPy(out, myPy);
    }
};

class MultEqualArray
    : public AssignOp
{
protected:
    BasePtr val;
    BasePtr index;
public:
    MultEqualArray(std::string &_variable, BasePtr _val, BasePtr _index)
        : AssignOp(_variable), val(_val), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        val->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(help.findreg());

        out << "MUL " << reg << ", " << r2 << ", " << r1 << std::endl;

        help.regFlag[std::stoi(r1.substr(1))] = 0;
        help.regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << "[";
        index->printC(out);
        out << "]*=";
        val->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable;
        out << "[" ;
        index->printPy(out, myPy);
        out << "]*=";
        val->printPy(out, myPy);
    }
};

class DivEqualOperator
    : public AssignOp
{
protected:
    BasePtr val;
public:
    DivEqualOperator(std::string &_variable, BasePtr _val)
        : AssignOp(_variable), val(_val)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        val->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(help.findreg());
        std::string r3 = "$" + std::to_string(help.findreg());

        if(help.localexists(variable)){
            out << "LW " << r2 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << "LUI " << r3 << ", %hi(" << variable << ")" << std::endl;
            out << "ADDI " << r2 << ", " << r2 << ", %lo(" << variable << ")" << std::endl;
            out << "LW " << r2 << ", 0(" << r3 << ")" << std::endl;
        }
        else{
            throw "Variable not declared. ";
        }
        out << "DIV " << r2 << ", " << r1 << std::endl;
        out << "MFLO " << r2 << std::endl;
        out << "ADDU " << reg << ", $0, " << r2 << std::endl;
        if(help.localexists(variable)){
            out << "SW " << r2 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << "SW " << r2 << ", 0(" << r3 << ")" << std::endl;
            help.regFlag[std::stoi(r3.substr(1))] = 0;
        }
        else{
            throw "Variable not declared. ";
        }
        help.regFlag[std::stoi(r1.substr(1))] = 0;
        help.regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << " /= ";
        val->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable;
        out << " /= ";
        val->printPy(out, myPy);
    }
};

class DivEqualArray
    : public AssignOp
{
protected:
    BasePtr val;
    BasePtr index;
public:
    DivEqualArray(std::string &_variable, BasePtr _val, BasePtr _index)
        : AssignOp(_variable), val(_val), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        val->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(help.findreg());

        out << "DIV " << r2 << ", " << r1 << std::endl;
        out << "MFLO " << r2 << std::endl;
        out << "ADDU " << reg << ", $0, " << r2 << std::endl;

        help.regFlag[std::stoi(r1.substr(1))] = 0;
        help.regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << "[";
        index->printC(out);
        out << "]/=";
        val->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable;
        out << "[" ;
        index->printPy(out, myPy);
        out << "]/=";
        val->printPy(out, myPy);
    }
};

class ModEqualOperator
    : public AssignOp
{
protected:
    BasePtr val;
public:
    ModEqualOperator(std::string &_variable, BasePtr _val)
        : AssignOp(_variable), val(_val)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        val->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(help.findreg());
        std::string r3 = "$" + std::to_string(help.findreg());

        if(help.localexists(variable)){
            out << "LW " << r2 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << "LUI " << r3 << ", %hi(" << variable << ")" << std::endl;
            out << "ADDI " << r2 << ", " << r2 << ", %lo(" << variable << ")" << std::endl;
            out << "LW " << r2 << ", 0(" << r3 << ")" << std::endl;
        }
        else{
            throw "Variable not declared. ";
        }
        out << "DIV " << r2 << ", " << r1 << std::endl;
        out << "MFHI " << r2 << std::endl;
        out << "ADDU " << reg << ", $0, " << r2 << std::endl;
        if(help.localexists(variable)){
            out << "SW " << r2 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << "SW " << r2 << ", 0(" << r3 << ")" << std::endl;
            help.regFlag[std::stoi(r3.substr(1))] = 0;
        }
        else{
            throw "Variable not declared. ";
        }
        help.regFlag[std::stoi(r1.substr(1))] = 0;
        help.regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << " %= ";
        val->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable;
        out << " %= ";
        val->printPy(out, myPy);
    }
};

class ModEqualArray
    : public AssignOp
{
protected:
    BasePtr val;
    BasePtr index;
public:
    ModEqualArray(std::string &_variable, BasePtr _val, BasePtr _index)
        : AssignOp(_variable), val(_val), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        val->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(help.findreg());

        out << "DIV " << r2 << ", " << r1 << std::endl;
        out << "MFHI " << r2 << std::endl;
        out << "ADDU " << reg << ", $0, " << r2 << std::endl;

        help.regFlag[std::stoi(r1.substr(1))] = 0;
        help.regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << "[";
        index->printC(out);
        out << "]%=";
        val->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable;
        out << "[" ;
        index->printPy(out, myPy);
        out << "]%=";
        val->printPy(out, myPy);
    }
};

class PreIncrement
    : public AssignOp
{

public:
    PreIncrement(std::string &_variable)
        : AssignOp(_variable)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        if(help.localexists(variable)){
            out << "LW " << r1 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        std::string address = "$" + std::to_string(help.findreg());
        if(help.globalexists(variable)){
            out << "LUI" << address << ", %hi(" << variable << ")" << std::endl;
            out << "ADDI" << address << ", " << address << ", %lo(" << variable << ")" << std::endl;
            out << "LW" << r1 << ", 0(" << address << ")" << std::endl;
        }
        else{
            throw "variable not declared.";
        }

        out << "ADDI " << r1 << ", " << r1 << ", 1" << std::endl;
        out << "ADDU " << reg << ", " << r1 << ", $0" << std::endl;

        if(help.localexists(variable)){
            out << "SW " << r1 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << r1 << ", 0(" << address << ")" << std::endl;
            help.regFlag[std::stoi(address.substr(1))] = 0;
        }
        else{
            throw "variable not declared.";
        }
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "++" << variable;

    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << "++" << variable;
    }
};

class PreIncrementArray
    : public AssignOp
{

protected:
    BasePtr index;

public:
    PreIncrementArray(std::string &_variable, BasePtr _index)
        : AssignOp(_variable), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        //out << "++" << variable << "[" << index << "]" << std::endl;

    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << "++" << variable << "[";
        index->printPy(out, myPy);
        out << "]" << std::endl;
    }
};

class PreDecrement
    : public AssignOp
{

public:
    PreDecrement(std::string &_variable)
        : AssignOp(_variable)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        if(help.localexists(variable)){
            out << "LW " << r1 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        std::string address = "$" + std::to_string(help.findreg());
        if(help.globalexists(variable)){
            out << "LUI" << address << ", %hi(" << variable << ")" << std::endl;
            out << "ADDI" << address << ", " << address << ", %lo(" << variable << ")" << std::endl;
            out << "LW" << r1 << ", 0(" << address << ")" << std::endl;
        }
        else{
            throw "variable not declared.";
        }

        out << "ADDIU " << r1 << ", " << r1 << ", 1" << std::endl;
        out << "ADDU " << reg << ", " << r1 << ", $0" << std::endl;

        if(help.localexists(variable)){
            out << "SW " << r1 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << r1 << ", 0(" << address << ")" << std::endl;
            help.regFlag[std::stoi(address.substr(1))] = 0;
        }
        else{
            throw "variable not declared.";
        }
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "--" << variable;
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << "--" << variable;
    }
};

class PreDecrementArray
    : public AssignOp
{

protected:
    BasePtr index;

public:
    PreDecrementArray(std::string &_variable, BasePtr _index)
        : AssignOp(_variable), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        //out << "--" << variable << "[" << index << "]" << std::endl;

    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << "--" << variable << "[";
        index->printPy(out, myPy);
        out << "]" << std::endl;
    }
};

class PostIncrement
    : public AssignOp
{

public:
    PostIncrement(std::string &_variable)
        : AssignOp(_variable)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        if(help.localexists(variable)){
            out << "LW " << r1 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        std::string address = "$" + std::to_string(help.findreg());
        if(help.globalexists(variable)){
            out << "LUI" << address << ", %hi(" << variable << ")" << std::endl;
            out << "ADDI" << address << ", " << address << ", %lo(" << variable << ")" << std::endl;
            out << "LW" << r1 << ", 0(" << address << ")" << std::endl;
        }
        else{
            throw "variable not declared.";
        }

        out << "ADDU " << reg << ", " << r1 << ", $0" << std::endl;
        out << "ADDI " << r1 << ", " << r1 << ", 1" << std::endl;

        if(help.localexists(variable)){
            out << "SW " << r1 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << r1 << ", 0(" << address << ")" << std::endl;
            help.regFlag[std::stoi(address.substr(1))] = 0;
        }
        else{
            throw "variable not declared.";
        }
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable << "++";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable << "++";
    }
};

class PostIncrementArray
    : public AssignOp
{

protected:
    BasePtr index;

public:
    PostIncrementArray(std::string &_variable, BasePtr _index)
        : AssignOp(_variable), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        //out << variable << "[" << index << "]++" << std::endl;

    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable << "[";
        index->printPy(out, myPy);
        out << "]++" << std::endl;
    }
};

class PostDecrement
    : public AssignOp
{

public:
    PostDecrement(std::string &_variable)
        : AssignOp(_variable)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        if(help.localexists(variable)){
            out << "LW " << r1 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        std::string address = "$" + std::to_string(help.findreg());
        if(help.globalexists(variable)){
            out << "LUI" << address << ", %hi(" << variable << ")" << std::endl;
            out << "ADDI" << address << ", " << address << ", %lo(" << variable << ")" << std::endl;
            out << "LW" << r1 << ", 0(" << address << ")" << std::endl;
        }
        else{
            throw "variable not declared.";
        }

        out << "ADDU " << reg << ", " << r1 << ", $0" << std::endl;
        out << "ADDIU " << r1 << ", " << r1 << ", -1" << std::endl;

        if(help.localexists(variable)){
            out << "SW " << r1 << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            out << r1 << ", 0(" << address << ")" << std::endl;
            help.regFlag[std::stoi(address.substr(1))] = 0;
        }
        else{
            throw "variable not declared.";
        }
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable << "--";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable << "--";
    }
};

class PostDecrementArray
    : public AssignOp
{

protected:
    BasePtr index;

public:
    PostDecrementArray(std::string &_variable, BasePtr _index)
        : AssignOp(_variable), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        //out << variable << "[" << index << "]--" << std::endl;

    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << variable << "[";
        index->printPy(out, myPy);
        out << "]--" << std::endl;
    }
};

class DotAssign
    : public Base
{
private:
    BasePtr expr;
public:
    DotAssign(BasePtr _expr)
    : expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{

    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << " = ";
        expr->printPy(out, myPy);
    }
};

#endif
