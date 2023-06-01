#ifndef H_BASE
#define H_BASE

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

#include <memory>

class Base;
class Py;
class MIPZ;

typedef const Base *BasePtr;

class Base {
public:
    virtual ~Base(){}
    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::stringstream &out, Py &myPy) const = 0;
};

class Py {
public:
    int indent;
    std::vector<std::string> globalv;
    std::vector<std::string> switchVar;
    std::vector<int> caseIndex;
    std::vector<std::string> pointers;
    std::vector<std::string> references;
    int flag;

    Py(): indent(0), flag(0)
    {
        //TODO:constructor
    }
    Py(Py &prevPy){
        //TODO:copy constructor
        indent = prevPy.indent;
        flag = prevPy.flag;
    }

    ~Py(){

    }

        //TODO: any functions needed for indent?
};

class MIPZ {

public:
    std::map <std::string, int> localVars;
    std::vector<std::string> globalVars;
    std::vector <int> regFlag {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // can't use $0-$7, $8-$25 free
    int scopecount;
    int frameptr;
    int globalptr;
    int parameters;
    int arrayelement;
    std::string arrayname;

    MIPZ(){
        //TODO:initial constructor
        scopecount = 0;
        frameptr = 0;
        globalptr = 0;
        parameters = 0;
        for(int i = 8; i < 26; i++){
          regFlag[i] = 0;
        }
    }

    MIPZ(MIPZ &help){
        //TODO:copy constructor
        localVars = help.localVars;
        globalVars = help.globalVars;
        scopecount = help.scopecount;
        frameptr = help.frameptr;
        parameters = help.parameters;
        arrayelement = help.arrayelement;
        arrayname = help.arrayname;
        for(int i = 8; i < 26; i++){
          regFlag[i] = help.regFlag[i];
        }
    }

    ~MIPZ(){

    }

    int findreg(){
        int i = 8;
        while(regFlag[i] != 0){
        i++;
        }
        regFlag[i] = 1;
        return i;
    }

    void newfunc(){
        localVars.clear();
        frameptr = 0;
    }

    int lcount = 0;
    std::string makelabl(){
        return "L_" + std::to_string(lcount++);
    }

    void newscope(){
        scopecount++;
    }

    int createlocal(std::string str){
      localVars[str] = frameptr;
      frameptr += 4;
      return (frameptr + 4);
    }

    int findlocal(std::string str){
        return localVars[str];
    }

    bool localexists(std::string str){
        if(localVars[str] > 0){
            return true;
        }
        else{
            return false;
        }
    }

    void createglobal(std::string str){
        globalVars.push_back(str);
    }

    bool globalexists(std::string str){
        for (size_t i = 0; i < globalVars.size(); i++) {
            if(globalVars[i] == str){
                return true;
            }
        }
        return false;
    }

    int createarray(std::string str, int n){
        localVars[str] = frameptr;
        frameptr -= 4*n;
        return (frameptr + 4*n);
    }

    int findarrayelement(std::string str, double n){
        return (localVars[str] - 4*n);
    }
};


#endif
