#ifndef H_PRIMATIVES
#define H_PRIMATIVES

#include <string>
#include <iostream>
#include <sstream>

#include "ast_base.hpp"

class Variable
    : public Base
{
protected:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
        if(help.globalexists(id)){
            std::string r1 = "$" + std::to_string(help.findreg());
            out << "LUI " << r1 << ", %hi(" << id << ")" << std::endl;
            out << "ADDI " << r1 << ", " << r1 << ", %lo(" << id << ")" << std::endl;
            out << "LW " << reg << ", 0(" << r1 << ")" << std::endl;
            help.regFlag[std::stoi(r1.substr(1))] = 0;
        }
        else if(help.localexists(id)){
            out << "LW " << reg << ", " << 4+help.findlocal(id) << "($fp)" << std::endl;
        }
        else{
            throw "variable not declared.";
        }
    }
    virtual void printC (std::ostream &out) const{
        out << id;
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const{
        out << id;
    }


};

class Number
    : public Base
{
protected:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
        out << "ADDI " << reg << ", $0, " << value << std::endl;
    }
    virtual void printC (std::ostream &out) const{
        out << value;
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const{
        out << value;
    }

};

class Array
    : public Base
{
protected:
    std::string var;
    BasePtr expr;
public:
    Array(std::string _var, BasePtr _expr)
        : var(_var), expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
        if(help.localexists(var)){
            //out << "LW "<< reg<<", "<<help.findarrayelement(id, element)<<"($fp)"<<std::endl;
        }
        else if(help.globalexists(var)){
            std::string r1 = "$" + std::to_string(help.findreg());
            out << "LUI " << r1 << ", %hi(" << var << ")" << std::endl;
            out << "ADDI " << r1 << ", " << r1 << ", %lo(" << var << ")" << std::endl;
            out << "LW " << reg << ", ";
            expr->printMIPS(reg, out, help); // times 4
            out << "(" << r1 << ")" << std::endl;
            help.regFlag[std::stoi(r1.substr(1))] = 0;
        }
        else{
            throw "Variable not declared. ";
        }
    }
    virtual void printC (std::ostream &out) const{
       // out << name << "[" << index << "]";
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const{
        out << var << "[";
        expr->printPy(out, myPy);
        out << "]";
    }

};

class Struct
    : public Base
{
protected:
    std::string var;
    BasePtr inside;

public:
    Struct (std::string _var, BasePtr _inside)
    : var(_var), inside(_inside)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
    }
    virtual void printC (std::ostream &out) const{
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << "class " << var << "(object):\n";
        myPy.indent++;
        for(int i = 0; i < myPy.globalv.size(); i++){
            for(int j = myPy.indent; j > 0; j--){
                out << "\t";
            }
            out << "global " << myPy.globalv[i] << std::endl;
        }
        for(int j = myPy.indent; j > 0; j--){
                out << "\t";
        }
        out << "__slots__ = ('";
        inside->printPy(out, myPy);
        out << "')\n";
        myPy.indent--;
    }

};

class StructVar
    : public Base
{
protected:
    std::string type;
    std::string var;

public:
    StructVar(std::string _type, std::string _var)
    : type(_type), var(_var)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
    }
    virtual void printC (std::ostream &out) const{
    }
     virtual void printPy (std::stringstream &out, Py &myPy) const override{
         out << var;
    }
};

class StructVarList
    : public Base
{
protected:
    BasePtr var;
    BasePtr nextVar;

public:
    StructVarList(BasePtr _var, BasePtr _nextVar)
    : var(_var), nextVar(_nextVar)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
    }
    virtual void printC (std::ostream &out) const{
    }
     virtual void printPy (std::stringstream &out, Py &myPy) const override{
         if(nextVar != NULL){
             nextVar->printPy(out, myPy);
             out << "', '";
         }
         var->printPy(out, myPy);
    }
};

class Pointer
    : public Base
{
protected:
    std::string var;
public:
    Pointer(std::string _var)
    : var(_var)
    {}
    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
    }
    virtual void printC (std::ostream &out) const{
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const{
        myPy.flag = 1;
        myPy.pointers.push_back(var);
        out << var;
    }

};

class Reference
    : public Base
{
protected:
    std::string var;
public:
    Reference(std::string _var)
    : var(_var)
    {}
    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
    }
    virtual void printC (std::ostream &out) const{
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const{
        myPy.flag = 1;
        myPy.references.push_back(var);
        out << var;
    }
};


class PointRef
    : public Base
{
protected:
    BasePtr Point;
    BasePtr Ref;
public:
    PointRef(BasePtr _Point, BasePtr _Ref)
    : Point(_Point), Ref(_Ref)
    {}
    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
    }
    virtual void printC (std::ostream &out) const{
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const{
        myPy.flag = 1;
        out << "\tdef _";
        Ref->printPy(out, myPy);
        out << "_ref_fn(*_set):\n";
        out << "\t\tnonlocal ";
        Ref->printPy(out, myPy);
        out << "\n";
        out << "\t\tif len(_set) > 0\n";
        out << "\t\t\t";
        Ref->printPy(out, myPy);
        out << " = _set[0]\n";
        out << "\t\treturn ";
        Ref->printPy(out, myPy);
        out << "\n\t";
        Point->printPy(out, myPy);
        out << " = Pointer(_";
        Ref->printPy(out, myPy);
        out << "_ref_fn)\n";
    }

};

class DecPoint
    : public Base
{
protected:
    BasePtr var;
public:
    DecPoint(BasePtr _var)
    : var(_var)
    {}
    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
    }
    virtual void printC (std::ostream &out) const{
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const{
        myPy.flag = 1;
        for(int j = myPy.indent; j > 0; j--){
            out << "\t";
        }
        var->printPy(out, myPy);
        out << " = None";
    }

};

class PArg
    : public Base
{
protected:
    BasePtr var;
    BasePtr nextVar;
public:
    PArg(BasePtr _var, BasePtr _nextVar)
    : var(_var), nextVar(_nextVar)
    {}
    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
    }
    virtual void printC (std::ostream &out) const{
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const{
        if(nextVar!=NULL){
            nextVar->printPy(out, myPy);
            out << ", ";
        }
        var->printPy(out, myPy);
    }

};

class AssignPoint
    : public Base
{
protected:
    BasePtr Point;
    BasePtr Ref;
public:
    AssignPoint(BasePtr _Point, BasePtr _Ref)
    : Point(_Point), Ref(_Ref)
    {}
    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
    }
    virtual void printC (std::ostream &out) const{
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const{
        myPy.flag = 1;
        for(int j = myPy.indent; j > 0; j--){
            out << "\t";
        }
        Point->printPy(out, myPy);
        out << ".deref(";
        Point->printPy(out, myPy);
        out << ", ";
        Ref->printPy(out, myPy);
        out << ")";
    }

};

class PReturn
    : public Base
{
protected:
    BasePtr Point;
public:
    PReturn(BasePtr _Point)
    : Point(_Point)
    {}
    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
    }
    virtual void printC (std::ostream &out) const{
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const{
        myPy.flag = 1;
        for(int j = myPy.indent; j > 0; j--){
            out << "\t";
        }
        out << "return ";
        Point->printPy(out, myPy);
        out << ".deref()\n";
    }

};

#endif
