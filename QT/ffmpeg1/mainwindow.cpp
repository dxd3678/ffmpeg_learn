#include "mainwindow.h"
#include "QPushButton"

#include "mypushbutton.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("主窗口");
    setFixedSize(400,400);

    //调用构造函数的时候，没有传入父类，所以屏幕的坐标就是基准
    move(100,100);

    // 添加第一个按钮：
    QPushButton *btn = new QPushButton;
    btn->setText("关闭");
    btn->setFixedSize(100,100);
    // 设置按钮的父控件
    btn->setParent(this);
    // 移动按钮的位置：
    btn->move(300,0);

    // 使用 connect 函数
    connect(btn,&QPushButton::clicked,this,&MainWindow::close);
}



//MainWindow::MainWindow(QWidget *parent)
//    : QMainWindow(parent)
//{
//    setWindowTitle("主窗口");
//    resize(300,300);
//    setFixedSize(400,400);

//    //调用构造函数的时候，没有传入父类，所以屏幕的坐标就是基准
//    move(100,100);

//    // 添加第一个按钮：
//    QPushButton *btn = new QPushButton;
//    btn->setText("登陆");
//    btn->setFixedSize(100,100);

//    // 设置按钮的父控件
//    btn->setParent(this);
//    // 移动按钮的位置：
//    btn->move(350,350);

//    // 添加第二个按钮：
//    new QPushButton("注册",this);

//    // 验证一下父控件销毁的时候，子控件会自动销毁
//    MypushButton * Mybtn = new MypushButton;
//    Mybtn->setText("账号");
//    Mybtn->setParent(this);
//    Mybtn->move(200,200);
//    Mybtn->setFixedSize(50,50);

//}

MainWindow::~MainWindow()
{

}
