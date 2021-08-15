#include "mainwindow.h"

#include <QApplication>

extern "C"{
#include "libavcodec/avcodec.h"
}

#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << av_version_info();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
