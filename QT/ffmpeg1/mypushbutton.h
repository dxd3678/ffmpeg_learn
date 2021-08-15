#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MypushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MypushButton(QWidget *parent = nullptr);
        ~MypushButton();
signals:

};

#endif // MYPUSHBUTTON_H
