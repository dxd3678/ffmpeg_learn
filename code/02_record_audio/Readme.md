## 一、ffmpeg 命令行体验















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

