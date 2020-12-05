#ifndef PROGRAM_H_
#define PROGRAM_H_
#include <fstream>
#include "output.h"
#include "varible.h"
#include "function.h"

class Program
{
private:
    unsigned int magic;
    unsigned int version;
    VaribleTable globals;
    FunctionTable functions;
public:
    Program(unsigned int magic=0x72303b3e,unsigned int version = 0x1): 
        magic(magic),version(version) {  }
    ~Program() = default;

    unsigned int getMagic() const { return magic; }
    unsigned int getVersion() const { return version; }
    VaribleTable & getGlobals() { return globals; }
    FunctionTable & getFunctions() { return functions; }

    Function & getFunction(const std::string & name,const Position & pos) { 
        return functions.get(name,pos);
    }
    const Varible & getGlobal(const std::string & name,const Position & pos) { return globals.get(name,pos);}
    void addFunction(Function & fn,const Position & pos) { functions.insert(fn,pos); }
    void addGlobal(Varible & var, const Position & pos) { globals.insert(var,pos); } 

    /////////////
    /// \brief 将_start函数添加到函数列表当中
    /////////////
    void init() 
    {
        if(!functions.isDeclared("_start"))
        {
            Function _start("_start",Type::VOID);
            functions.insert(_start,Position(0,0));
        }
    }
    
    friend std::ostream & operator<<(std::ostream & os, const Program & pg)
    {
        write(os,(void *)&pg.magic,sizeof(pg.magic));
        write(os,(void *)&pg.version,sizeof(pg.version));
        os << pg.globals;
        os << pg.functions;
        return os;
    }
};


#endif // PROGRAM_H_