#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>


extern "C"{
// ffmpeg 与设备相关的 API
#include "libavdevice/avdevice.h"
// ffmpeg 与格式相关的 API 、（windows 下面的 dshow）
#include "libavformat/avformat.h"
// ffmpeg 的相关工具
#include "libavutil/avutil.h"
}

/*************************************************/
bool Record_Flag = false;


/*************************************************/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 第一步：注册设备 ：avdevice_register_all
    avdevice_register_all();

}

MainWindow::~MainWindow()
{
    delete ui;
}

#define FMT_NAME "dshow"
// ffmpeg -f dshow -list_devices true -i dummy (windows 下面查看 dshow 支持的设备)
// 注意前面一定要加上 audio=
#define DEVICE_NAME "audio=麦克风 (Conexant SmartAudio HD)"
#define FILENAME "D:/out.pcm"

void MainWindow::on_Record_audio_clicked()
{
    char errbuf[1024] = {0};

    Record_Flag = true;
    // 第二步：获取输出对象的格式：av_find_input_format
    AVInputFormat *fmt = av_find_input_format(FMT_NAME);
    if(!fmt)
    {
        qDebug() <<"获取对象格式失败" << FMT_NAME;
        return;
    }

    // 第三步：打开输入设备：avformat_open_input
    AVFormatContext *ctx = nullptr;
    int ret = avformat_open_input(&ctx,DEVICE_NAME,fmt,nullptr);
    if(ret < 0)
    {
        memset(errbuf,0,sizeof(errbuf));
        av_strerror(ret,errbuf,sizeof(errbuf));
        qDebug() << "打开输入设备失败" << errbuf;
        return;
    }

    // 第四步：开始录音 ：int av_read_frame(AVFormatContext *s, AVPacket *pkt);
    AVPacket pkt;
    ret = av_read_frame(ctx,&pkt);
    if(ret < 0)
    {
        memset(errbuf,0,sizeof(errbuf));
        av_strerror(ret,errbuf,sizeof(errbuf));
        qDebug() << "录音失败" << errbuf;
        return;
    }
    qDebug() << pkt.size << " " << pkt.buf;

    // 第五步：将录音得到的数据，写成一个文件
    QFile file(FILENAME);

    if( !file.open(QFile::WriteOnly) )
    {
        qDebug() << "文件打开失败";
        //关闭设备 ：avformat_close_input
        avformat_close_input(&ctx);
        return;
    }

    while(Record_Flag)
    {
        ret = av_read_frame(ctx,&pkt);
        if(ret == 0)
        {
            //读取成功，写为文件
            file.write((const char *)pkt.buf,pkt.size);

        }
    }
}
// 当程序运行时, 主窗口无响应，导致关闭录音的按钮无法点击。
void MainWindow::on_Record_audio_2_clicked()
{
    Record_Flag = false;
}
