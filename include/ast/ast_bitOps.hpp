#ifndef H_BITOPS
#define H_BITOPS

#include <iostream>
#include <sstream>

#include "ast_base.hpp"

class BitOp
    : public Base
{
protected:
    BasePtr left;
    BasePtr right;

    BitOp(BasePtr _left, BasePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~BitOp()
    {
        delete left;
        delete right;
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::stringstream &out, Py &myPy) const = 0;
};

class BitAnd
    : public BitOp
{

public:
    BitAnd(BasePtr _left, BasePtr _right)
        : BitOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.parameters+1);
        left->printMIPS(r1, out, help);
        right->printMIPS(reg, out, help);
        out << "AND " << reg << ", " << r1 << ", " << reg << std::endl;
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left->printC(out);
        out << " & ";
        right->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        left->printPy(out, myPy);
        out << " & ";
        right->printPy(out, myPy);
    }
};

class BitOr
    : public BitOp
{

public:
    BitOr(BasePtr _left, BasePtr _right)
        : BitOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.parameters+1);
        left->printMIPS(r1, out, help);
        right->printMIPS(reg, out, help);
        out << "OR " << reg << ", " << r1 << ", " << reg << std::endl;
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left->printC(out);
        out << " | ";
        right->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        left->printPy(out, myPy);
        out << " | ";
        right->printPy(out, myPy);
    }
};

class ExorOperator
    : public BitOp
{

public:
    ExorOperator(BasePtr _left, BasePtr _right)
        : BitOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.parameters+1);
        left->printMIPS(r1, out, help);
        right->printMIPS(reg, out, help);
        out << "XOR " << reg << ", " << r1 << ", " << reg << std::endl;
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left->printC(out);
        out << " ^ ";
        right->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        left->printPy(out, myPy);
        out << " ^ ";
        right->printPy(out, myPy);
    }
};

class LshiftOperator
    : public BitOp
{

public:
    LshiftOperator(BasePtr _left, BasePtr _right)
        : BitOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.parameters+1);
        left->printMIPS(r1, out, help);
        right->printMIPS(reg, out, help);
        out << "SLL " << reg << ", " << r1 << ", " << reg << std::endl;
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left->printC(out);
        out << " << ";
        right->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        left->printPy(out, myPy);
        out << " << ";
        right->printPy(out, myPy);
    }
};

class RshiftOperator
    : public BitOp
{

public:
    RshiftOperator(BasePtr _left, BasePtr _right)
        : BitOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.parameters+1);
        left->printMIPS(r1, out, help);
        right->printMIPS(reg, out, help);
        out << "SLR " << reg << ", " << r1 << ", " << reg << std::endl;
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left->printC(out);
        out << " >> ";
        right->printC(out);
    }
    virtual void printPy (std::stringstream &out, Py &myPy) const override{
        left->printPy(out, myPy);
        out << " >> ";
        right->printPy(out, myPy);
    }
};

#endif
