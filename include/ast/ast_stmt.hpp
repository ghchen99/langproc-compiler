//TODO: BREAK, CONTINUE, RETURN, EXPGRESSION STMT, DECLARE STMT,
#include <string>
#include <iostream>
#include <sstream>

#include "ast_base.hpp"

class DecGlobal
    : public Base
{
protected:
    std::string id;
    BasePtr expr;
public:
    DecGlobal(std::string _id, BasePtr _expr)
        : id(_id), expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        help.createglobal(id);
        out << ".globl " << id << std::endl;
        out << ".data" << std::endl;
        out << ".align 2" << std::endl;
        out << id << ":" << std::endl;
        if(expr != NULL){
            out << ".word ";
            expr->printMIPS(reg, out, help);
        }
        else{
            out << ".word 0" << std::endl;
        }
    }
    virtual void printC (std::ostream &out) const override{
        out << id << "=";
        expr->printC(out);
        out << ";";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        myPy.globalv.push_back(id);
        out << id;
        if(expr != NULL){
            out << " = ";
            expr->printPy(out, myPy);
        }
        else{
            out << " = 0";
        }
    }
};

class GDeclareArray
    : public Base
{
protected:
    std::string id;
    BasePtr expr;
public:
    GDeclareArray(std::string _id, BasePtr _expr)
        : id(_id), expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        //int address = help.createarray(id, )
    }
    virtual void printC (std::ostream &out) const override{}

    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        myPy.globalv.push_back(id);
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        if(expr!=NULL){
            out << id << " = [";
            expr->printPy(out, myPy);
            out << "]";
        }
        else{
          out << id << " = []";
        }
    }
};

class Empty_stmt
    : public Base
{

public:
    Empty_stmt()
    {}

    ~Empty_stmt(){}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << ";";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        out << ";";
    }
};

class Expr_stmt
    : public Base
{
protected:
    BasePtr expr;
public:
    Expr_stmt(BasePtr _expr)
        : expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        if(expr != NULL){
            expr->printMIPS(reg, out, help);
        }
    }
    virtual void printC (std::ostream &out) const override{
        expr->printC(out);
        out << ";";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        expr->printPy(out, myPy);
    }
};

class Return_stmt
    : public Base
{
protected:
    BasePtr retval;
public:
    Return_stmt(BasePtr _retval)
        : retval(_retval)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        reg = "$2";
        retval->printMIPS(reg, out, help);
        //this goes to number primitive
    }
    virtual void printC (std::ostream &out) const override{
        out << "return ";
        retval->printC(out);
        out << ";";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        out << "return ";
        retval->printPy(out, myPy);
    }
};

class Decl_stmt
    : public Base
{
protected:
    std::string type;
    BasePtr list;
public:
    Decl_stmt(std::string _type, BasePtr _list)
        : type(_type), list(_list)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        if(list != NULL){
            list->printMIPS(reg, out, help);
        }
    }
    virtual void printC (std::ostream &out) const override{
        out << type << " ";
        list->printC(out);
        out << ";";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        list->printPy(out, myPy);
    }
};

class Declare
    : public Base
{
protected:
    std::string id;
    BasePtr expr;
public:
    Declare(std::string _id, BasePtr _expr)
        : id(_id), expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        help.createlocal(id);
        if(expr != NULL){
            expr->printMIPS(reg, out, help);
        }
        else{
            out << "ADDI " << r1 << ", $0, 0" << std::endl;
        }
        out << "SW $2, " << (help.createlocal(id)) << "($fp)" << std::endl;
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << id << "=";
        expr->printC(out);
        out << ";";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        if(expr != NULL){
            out << id << "=";
            expr->printPy(out, myPy);
        }
        else{
            out << id << " = 0";
        }
    }
};

class DeclareArray
    : public Base
{
protected:
    std::string id;
    BasePtr expr;
public:
    DeclareArray(std::string _id, BasePtr _expr)
        : id(_id), expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        //int address = help.createarray(id, )
    }
    virtual void printC (std::ostream &out) const override{}

    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        if(expr!=NULL){
            out << id << " = [";
            expr->printPy(out, myPy);
            out << "]";
        }
        else{
          out << id << " = []";
        }
    }
};


class StructDecl
    : public Base
{
protected:
    std::string id;
    std::string id2;
public:
    StructDecl(std::string _id, std::string _id2)
        : id(_id), id2(_id2)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{

    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        out << id2 << " = " << id << "()";
    }
};
