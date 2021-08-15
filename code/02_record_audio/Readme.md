## 一、ffmpeg 命令行体验

### 1、查看多媒体系统库

使用命令行查看当前平台的可用设备：

```sh
ffmpeg -devices
```

Windows的输出结果如下所示：

```shell
Devices:
 D. = Demuxing supported
 .E = Muxing supported
 --
  E caca            caca (color ASCII art) output device
 D  dshow           DirectShow capture
 D  gdigrab         GDI API Windows frame grabber
 D  lavfi           Libavfilter virtual input device
 D  libcdio
  E sdl,sdl2        SDL2 output device
 D  vfwcap          VfW video capture
```

- 列表中有个[dshow](https://ffmpeg.org/ffmpeg-all.html#dshow)，全名叫DirectShow，是Windows平台的多媒体系统库
- 我们可以使用 dshow 去**操作多媒体输入设备**（比如录音设备）

***

### 2、查看 dshow 支持的设备

```bash
# 查看dshow支持的设备
ffmpeg -f dshow -list_devices true -i dummy

# 或者
# ffmpeg -list_devices true -f dshow -i ''
# ffmpeg -list_devices true -f dshow -i ""
```

- *-f dshow*
  - dshow支持的
- *-list_devices true*
  - 打印出所有的设备
- *-i dummy* 或 *-i ''* 或 *-i ""*
  - 立即退出

执行的结果：

```bash
DirectShow video devices (some may be both video and audio devices)
"USB2.0 VGA UVC WebCam"

DirectShow audio devices
"麦克风 (Conexant SmartAudio HD)"

```

- dshow支持的 **视频设备**
  - USB2.0 VGA UVC WebCam：笔记本自带的摄像头
- dshow支持的 **音频设备**
  - 麦克风 (Conexant SmartAudio HD)：笔记本自带的麦克风

***

### 3、指定设备进行录音

```bash
# 使用笔记本自带的麦克风进行录音，最后生成一个wav文件
ffmpeg -f dshow -i audio="麦克风 (Conexant SmartAudio HD)" out.wav
```

- 可以使用快捷键Ctrl + C终止录音
- 我这边的测试结果显示，音频参数是：
  - Windows：44100Hz采样率、16位深度、2声道、1411Kbps比特率







***

## 二、ffmpeg API 编程

### （1）修改 profile 文件

```shell
win32{
    FFMPEG_HOME = ../../ffmpeg-4.3.2-2021-02-27-full_build-shared

    INCLUDEPATH += $${FFMPEG_HOME}/include

    LIBS += -L$${FFMPEG_HOME}/lib \
            -lavdevice \
            -lavformat \
            -lavutil
}
```

各个库对应的头文件，以及各个库的意义：

```c++
extern "C"{
// ffmpeg 与设备相关的 API
#include "libavdevice/avdevice.h"
// ffmpeg 与格式相关的 API 、（windows 下面的 dshow）
#include "libavformat/avformat.h"
// ffmpeg 的相关工具
#include "libavutil/avutil.h"
}
```



***

### 2、整体流程图

