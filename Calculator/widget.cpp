#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    text.clear();
    ui->setupUi(this);
    this->setWindowTitle("MyCalculator");
    connect(ui->pushButton_0,&QPushButton::clicked,ui->lineEdit,   //连接按键
            [=]()
            {
                char c='0';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_1,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='1';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_2,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='2';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_3,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='3';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_4,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='4';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_5,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='5';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_6,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='6';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_7,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='7';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_8,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='8';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_9,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='9';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_dot,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='.';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_plus,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='+';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_minus,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='-';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_times,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='*';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_divide,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='/';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_factorial,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='!';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_lp,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='(';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_rp,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c=')';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_mod,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='%';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_pow,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                char c='^';
                expr.enqueue(c);
                text+=c;
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_cl,&QPushButton::released,ui->lineEdit,
            [=]()
            {
                expr.remove(0,expr.size());
                text.clear();
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_back,&QPushButton::clicked,ui->lineEdit,
            [=]()
            {
                expr.remove(expr.size()-1);
                text.chop(1);
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_equal,&QPushButton::released,ui->lineEdit,
            [=]()
            {
                char c='\0';
                expr.enqueue(c);
                optr.push(c);
                char* S=expr.getPos(0);
                while(!optr.empty())
                {
                    if(isDigit(S))
                    {
                        opnd.push(readNumber(S));  //读入操作数
                        while(isDigit(S)) S++;
                    }
                    else
                    {
                        switch (orderBetween[transoptr(optr.top())][transoptr(*S)])  //在表中查找优先级关系
                        {
                            case '<': optr.push(*S); S++; break;  //入栈
                            case '=': optr.pop(); S++; break;  //括号或结束符，配对出栈
                            case '>':
                            {
                                char op=optr.pop();
                                if(op=='!')
                                    opnd.push((double)factorial(opnd.pop()));  //单目运算
                                else
                                {
                                    double opnd2=opnd.pop();
                                    double opnd1=opnd.pop();
                                    opnd.push(calculate(opnd1, op, opnd2));  //其他双目运算
                                }
                                break;

                            }
                            default: exit(-1);
                        }

                    }

                }
                double result=opnd.pop();
                text=text.number(result);  //字符串读入结果
                ui->lineEdit->setText(text);
            }
            );
    connect(ui->pushButton_RPN,&QPushButton::clicked,ui->lineEdit,   //逆波兰表达式
            [=]()
            {
                QString RPN;
                char c='\0';
                expr.enqueue(c);
                optr.push(c);
                char* S=expr.getPos(0);
                while(!optr.empty())
                {
                    if(isDigit(S))
                    {
                        opnd.push(readNumber(S));
                        RPN.append(RPN.number(opnd.top()));  //操作数接入RPN
                        while(isDigit(S)) S++;
                    }
                    else
                    {
                        switch (orderBetween[transoptr(optr.top())][transoptr(*S)])
                        {
                            case '<': optr.push(*S); S++; break;
                            case '=': optr.pop(); S++; break;
                            case '>': RPN.append(optr.pop()); break;  //操作符接入RPN
                            default: exit(-1);
                        }

                    }

                }
                ui->lineEdit->setText(RPN);
            }
            );
}

Widget::~Widget()
{
    delete ui;
}



