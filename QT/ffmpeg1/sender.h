#ifndef SENDER_H
#define SENDER_H

#include <QObject>

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = nullptr);

    // 自定义的信号，必须要放到 signals 里面
signals:
    void exit();
};

#endif // SENDER_H
