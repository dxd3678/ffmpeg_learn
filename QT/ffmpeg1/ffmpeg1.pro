#-------------------------------------------------
#
# Project created by QtCreator 2021-08-13T23:44:40
#
#-------------------------------------------------

#该项目包含的两个模块
QT       += core gui

# QT 版本大于 4 ，就包含了 widgets。（之前的版本的 widgets 在上面两个模块当中）
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ffmpeg1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#需要编译的源代码
SOURCES += \
        main.cpp \
        mainwindow.cpp \
        mypushbutton.cpp \
        sender.cpp

#项目中用到的头文件
HEADERS += \
        mainwindow.h \
        mypushbutton.h \
        sender.h



win32: {
    FFMPEG_HOME=D:\SF\ffmpeg\MJ\ffmpeg-4.3.2-2021-02-27-full_build-shared
    #设置 ffmpeg 的头文件
    INCLUDEPATH += $$FFMPEG_HOME/include

    #设置导入库的目录一边程序可以找到导入库
    # -L ：指定导入库的目录
    # -l ：指定要导入的 库名称
    LIBS +=  -L$$FFMPEG_HOME/lib \
             -lavcodec \
             -lavdevice \
             -lavfilter \
            -lavformat \
            -lavutil \
            -lpostproc \
            -lswresample \
            -lswscale
}

# $${ } ：可以解引用 当前文件的变量
# $$( ) ：可以解引用 系统的环境变量
message($${FFMPEG_HOME});
