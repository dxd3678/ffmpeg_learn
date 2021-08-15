## 一、将 ffmpeg 的功能集成到 QT 项目当中去

首先提个问题：当我们使用命令行执行 ffmpeg 程序的时候，ffmpeg 二进制程序会调用哪些东西？

- ffmpeg 二进制程序会调用 **当前文件夹下**面的 **dll 文件当中的函数**。



为什么？

- 从文件大小，我们也可以分析出来，ffmpeg 二进制程序仅仅有 342 KB、而有的动态库有 57179KB。 （补图）

![image-20210815135917666](https://study-1258369184.cos.ap-beijing.myqcloud.com/Pictures/2021/image-20210815135917666.png)

继续分析文件对应关系：（补图）

- 一个动态库，对应一个**头文件夹**，对应一个 **静态库文件**

![image-20210815135956891](https://study-1258369184.cos.ap-beijing.myqcloud.com/Pictures/2021/image-20210815135956891.png)

***

在Windows中，我们 **最终是通过调用FFmpeg动态库**（dll）**中的函数**来操作音视频数据。

使用dll的其中一种方式是**需要用到3种文件**： 

（.h 头文件、.dll：动态链接库（Dynamic Link Library）、**.lib**或 **.dll.a**：（动态链接库的）导入库（Import Library））



- .h：头文件（Header File）
  - 包含了函数的声明
  - 通过*#include*去导入相应的头文件



- .dll：动态链接库（Dynamic Link Library）
  - 包含了函数的**具体实现代码**
  - Windows程序会在运行过程中，动态调用dll中的函数



- .lib或**.dll.a**：（动态链接库的）导入库（Import Library） （静态库文件）
  - **.lib**：用于MSVC编译器中
  - **.dll.a**：用于 MinGW编译器 中
  - 包含了dll中函数的入口，用于辅助找到并调用dll中的函数
  - 最终需要链接到Windows程序中（比如合并到exe文件中）

注意哦：

值得一提的是，在Windows中，静态链接库（Static Link Library）的扩展名也是.lib、.dll.a。静态链接库和导入库的区别是：

- 静态链接库：**包含了函数的具体实现代码**
- 导入库：**不包含函数的具体实现代码**（函数的具体实现代码存储在dll中）



***

怎么告诉我们自己写的源文件，调用的函数来自于 哪个动态库呢？

- dll 文件和 .exe 文件是分开的（dll 文件不存在于 .exe 文件），既然是**各自独立存在**的，那么 .exe 文件**怎么找到对应的函数体呢**？
- .exe 文件当中添加对应的静态库文件。



继续添加一个 静态库文件

- .dll.a 这个文件和 .a 文件作用是不相同的，（从名字也可以大概分析出来）
- .dll.a 这个文件是比较小的，并不像 .a 文件那么大。
- .dll.a 文件是专门为了 .dll 文件服务的，里面**只记录了 .exe 文件怎么在 dll 文件当中找到对应的函数**。
- 里面仅仅是一些 索引信息，里面仅仅是函数的**实现入口**。
- 如果是 MSVC（微软） 编译器的话，还需要添加对应 **.lib** 文件。

***

## 二、修改 QT 的项目文件

### 1、修改 profile 

- 此处 FFMPEG_HOME 这个环境变量，我是使用的是 **相对路径**，相当对于当前 exe 文件的路径。
- QT 当中**解引用变量**，使用 $${ }
- 记得添加换行符 \

```shell
win32{
    FFMPEG_HOME = ../../ffmpeg-4.3.2-2021-02-27-full_build-shared

    INCLUDEPATH += $${FFMPEG_HOME}/include

    LIBS += -L$${FFMPEG_HOME}/lib \
            -lavcodec \
            -lavdevice \
            -lavfilter \
            -lavformat \
            -lavutil \
            -lpostproc \
            -lswresample \
            -lswscale
}
```



注意：这时候我们 QT 项目**只能找到** **头文件和动态库的导入库**，并找不到对应的 **动态库文件**。

解决办法：

- 将 ffmpeg 8 个 dll 文件，拷贝到生成 .exe 文件的目录当中去。
- 将 ffmpeg 8 个 dll 文件的目录，添加到 windows 的 **PATH 环境变量当中去**。

***

### 2、添加头文件

因为 QT 的项目是使用 C++ 代码来进行编写，而我们 ffmpeg 是使用 C 语言来进行编写。所以我们要用到 extern C 关键字来包含头文件

```c++
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
```

- 使用 qDebug() 来打印信息
- 程序输出：4.3.2-2021-02-27-full_build-www.gyan.dev ， 集成成功

