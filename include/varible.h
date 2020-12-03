#ifndef VARIBLE_H_
#define VARIBLE_H_
#include <string>
#include <vector>
#include "position.h"
#include "output.h"

////////////////
/// \brief 变量具体的类型
////////////////
enum class Type
{
    // 整形
    INT,
    // void型
    VOID,
    // 浮点型
    DOUBLE
};
///////////////
/// \brief 符号表的条目类型，
///////////////
enum class Kind
{
    // 参数
    PARAM,
    // 函数，可以不要，将函数放在另一张表当中
    FUNC,
    // 变量
    VAR,
    // 全局变量
    GLOBAL
};

//////////////
/// \brief 变量
//////////////
class Varible
{
private :
    /////////////
    /// \brief 是否常量
    /////////////
    bool is_const;

    /////////////////
    /// \brief 变量名
    /////////////////
    std::string name;

    ///////////
    /// 参数还是普通变量
    ///////////
    Kind kind;

    //////////
    /// \brief 数据类型
    //////////
    Type type;

    //////////
    /// \brief 数据的size
    //////////
    int size;

    ///////////////////////////
    /// \brief 地址,如果是全部变量，则表示是第几个全局变量
    ///        如果是函数参数，则表示是该函数的第几个参数
    ///        如果是局部变量，则表示第几个局部变量
    ///        可能需要加入符号表中才分配
    ///////////////////////////
    unsigned long long address;
public:
    Varible() = default;
    Varible(const Varible &) = default;
    Varible(Varible &&) = default;
    Varible & operator=(const Varible &) = default;
    Varible & operator=(Varible &&) = default;
    ~Varible() = default;

    Varible(const std::string & name,const Kind kind, const Type type,unsigned long long address=0,bool is_const = false) 
    {
        this->type = type;
        this->name = name;
        this->address = address;
        this->is_const = is_const;
        this->kind = kind;
        if(type == Type::VOID) size = 0;
        else size = 8;
    }

    bool isConst() const { return is_const; }
    const std::string & getName() const { return name; }
    Type getType() const { return type; }
    int getSize() const { return size; }
    unsigned long long getAddress() const { return address; }

    friend std::ostream & operator<<(std::ostream & os,const Varible & var)
    {
        char c = var.is_const ? 1:0;
        // 是否是常量
        write(os,(void *)&c,sizeof(c));
        // 变量的size
        write(os,(void *)&var.size,sizeof(var.size));
        long long t = 0;
        // 用0填充，在_start函数里面去完成赋值
        write(os,(void *)&t,var.size);
        return os;
    }
};

//////////////////
/// \brief 变量的符号表
//////////////////
class VaribleTable
{
private:
    VaribleTable * parent;
    std::vector<Varible> table;
    // 可以假想存在两个栈，返回值和参数放在一个栈中，局部变量放在另一个
    int param_offset; // 下一个参数的偏移
    int loca_offset; // 下一个局部变量的偏移
public:
    VaribleTable(VaribleTable * parent = nullptr,int param_offset=0,int loca_offset=0) 
        : parent(parent),param_offset(param_offset),loca_offset(loca_offset) {}
    bool isDeclared(const std::string & var_name);
    void insert(const Varible & var,const Position & pos);
    const Varible & get(const std::string & var_name,const Position & pos);

    friend std::ostream & operator<<(std::ostream & os,const VaribleTable & vr)
    {
        int n = vr.table.size();
        write(os,(void *)&n,sizeof(n));
        for(const auto & var:vr.table)
            os << var;
        return os;
    }
};
#endif // VARIBLE_H_