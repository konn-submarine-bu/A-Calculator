#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "vector.h"
#include "stack.h"
#include "queue.h"
#include<QString> 
#include<cmath>
static char orderBetween[10][10]=  //对优先级关系制表
{
    //         |-------------当前运算符----------------|
    //         +   -   *   /   ^   !   %   (   )  \0
    /*-- + */ {'>','>','<','<','<','<','<','<','>','>'},
    /* | - */ {'>','>','<','<','<','<','<','<','>','>'},
    /*栈 * */  {'>','>','>','>','<','<','>','<','>','>'},
    /*顶 / */  {'>','>','>','>','<','<','>','<','>','>'},
    /*运 ^ */  {'>','>','>','>','>','<','>','<','>','>'},
    /*算 ! */  {'>','>','>','>','<','<','>',' ','>','>'},
    /*符 % */  {'>','>','>','>','<','<','>','<','>','>'},
    /* | ( */ {'<','<','<','<','<','<','<','<','=',' '},
    /* | ) */ {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    /*--\0 */ {'<','<','<','<','<','<','<','<',' ','='}
};
static char allOptr[10]={'+','-','*','/','^','!','%','(',')','\0'};  //所有运算符

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    stack<double> opnd;  //操作数栈
    stack<char> optr;  //操作符栈
    queue<char> expr;  //写入的表达式
    QString text;  //用于显示输出
    bool isDigit(char *p)  //判别数据还是运算符
    {
        if(('0'<=*p&&*p<='9')||*p=='.') return 1;
        return 0;
    }
    int readInteger(char* ptr, int size)  //读入整数
    {
        if(size<=0) return 0;
        int RI=0;
        while(size>0)
        {
            RI+=((*ptr-'0')*pow(10,size-1));
            size--;
            ptr++;
        }
        return RI;
    }

    double readNumber(char* p)  //读入浮点数
    {
        stack<char> RN;
        while(isDigit(p))
        {
            RN.push(*p);
            p++;
        }
        int dot=RN.find('.');
        if(dot>=0)
        {
            int n1=readInteger(RN.getPos(0),dot);
            int n2=readInteger(RN.getPos(dot+1),RN.size()-dot-1);
            double f2=n2*pow(10,-(RN.size()-dot-1));
            return n1+f2;
        }
        else return readInteger(RN.getPos(0),RN.size());
    }
    double calculate(double opnd1, char optr, double opnd2)  //双目运算
    {
        switch (optr)
        {
            case '+': return opnd1+opnd2;
            case '-': return opnd1-opnd2;
            case '*': return opnd1*opnd2;
            case '/': return opnd1/opnd2;
            case '^': return pow(opnd1,opnd2);
            case '%': return int(opnd1)%int(opnd2);
            default: exit(-1);
        }

    }
    int factorial(int opnd)  //阶乘运算
    {
        int x=1;
        while(0<opnd)
        {
            x*=opnd;
            opnd--;
        }
        return x;
    }
    int  transoptr(char optr)  //将运算符转化为数组下标
    {
        int i=0;
        while(allOptr[i]!=optr) i++;
        return i;
    }


private:
    Ui::Widget *ui;
};



#endif // WIDGET_H

