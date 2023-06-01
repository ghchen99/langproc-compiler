#ifndef H_UNARY
#define H_UNARY

#include <string>
#include <iostream>
#include <sstream>

#include "ast_base.hpp"

class Unary
    : public Base
{
protected:
    BasePtr expr;

    Unary(const BasePtr _expr)
        : expr(_expr)
    {}
public:
    virtual ~Unary()
    {
        delete expr;
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::stringstream &out, Py &myPy) const = 0;
};


// -
class NegOperator
    : public Unary
{
public:
    NegOperator(const BasePtr _expr)
        : Unary(_expr)
    {}


    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        expr->printMIPS(r1, out, help);
        out << "SUBU " << reg << ", $0, " << r1 << std::endl;
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "-";
        expr->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << "-(";
        expr->printPy(out, myPy);
        out << ")";
    }
};

// +
class PlusOperator
    : public Unary
{
public:
    PlusOperator(const BasePtr _expr)
        : Unary(_expr)
    {}


    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        expr->printMIPS(r1, out, help);
        out << "ADDU " << reg << ", $0, " << r1 << std::endl;
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "+";
        expr->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << "+(";
        expr->printPy(out, myPy);
        out << ")";
    }

};



//! logical negation
class LogicNotOperator
    : public Unary
{
public:
    LogicNotOperator(const BasePtr _expr)
        : Unary(_expr)
    {}


    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << "!";
        expr->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << " not ";
        expr->printPy(out, myPy);
    }
};

//~ bitwise negation
class BitNotOperator
    : public Unary
{
public:
    BitNotOperator(const BasePtr _expr)
        : Unary(_expr)
    {}


    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        expr->printMIPS(r1, out, help);
        out << "NOT " << reg << ", " << r1 << std::endl;
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "~";
        expr->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        out << "~";
        expr->printPy(out, myPy);
    }
};

#endif
