#include "mypushbutton.h"
#include "QDebug"
MypushButton::MypushButton(QWidget *parent) : QPushButton(parent)
{

}

MypushButton::~MypushButton()
{
    qDebug()<<"MypushButton::~MypushButton()";
}
