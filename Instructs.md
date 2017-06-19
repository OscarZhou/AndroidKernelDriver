## The file will instruct you how to set up the run time for Linux Kernel in Android.


#### How to download the source?

>【1】 下载Android Studio. 下载网址： [this](https://developer.android.com/studio/index.html)
>解释：下载完Android Studio之后，通常就会有一个默认 SDK 版本被下载下来。所以相当于下载好了SDK
>【2】 下载NDK，在Android Studio SDK Manager下可直接下载。
>【3】 下载goldfish.下载地址： [this](http://android.googlesource.com/kernel/goldfish) 
>解释，在下载goldfish之前，需要下载 git， 指令为 `sudo apt-get install git`。在下载git 之后，可以使用git指令下载goldfish源码，指令为`git clone https://android.googlesource.com/kernel/goldfish`，并且`checkout branch android-goldfish-3.4`。指令为 git checkout android-goldfish-3.4 。注意，这个指令需要在goldfish文件夹里输入
>【4】 创建AVD， AVD指的是Android Virtual Device， 是模拟Android硬件必须有的条件。AVD可以在Android Studio中的AVD Manager创建。
>解释：创建AVD，除了有SDK，还需要有System Image，直接在选项上下载就可以。下载好之后点完成，可能还会出现另外一个错误，提示“在创建过程中遇到错误，查看idea.log”，【help】-【Show log in files】可知是SD Card错误，如“Failed to create sdcard in the AVD folder.”
>解决方法：安装对应的32位库，重新打开一个terminal，指令为 `sudo apt-get install libgcc1:i386`
>【5】 在Operating System作业1中，需要用老师给的emulator去替换Sdk/emulator/emulator64-arm 



在安装完所有的东西后（保证了运行环境的存在），接下来：
在goldfish文件目录上导出 ：   **特别注意**，goldfish一定要在Document文件夹下，下面的编译命令才能有效
 
        export ARCH=arm
        export PATH=/Android/Sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin:$PATH
        export CROSS_COMPILE=arm-linux-androideabi-
        
        
包括输入下面指令
        make goldfish_armv7_defconfig   
        make -j 4   
完成以上命令，kernel程序被编译。   cd 


下一步是编程emulator， 进入Sdk/emulator路径下
 ./emulator64-arm -avd Nexus
运行之后会报如下错误：
./emulator64-arm: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5: version `Qt_5.7' not found (required by ./emulator64-arm)
./emulator64-arm: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5: version `Qt_5' not found (required by ./emulator64-arm)
./emulator64-arm: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5: version `Qt_5' not found (required by ./emulator64-arm)
./emulator64-arm: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5: version `Qt_5' not found (required by ./emulator64-arm)
./emulator64-arm: /usr/lib/x86_64-linux-gnu/libQt5Svg.so.5: version `Qt_5' not found (required by ./emulator64-arm)


解决方法：
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/oscar/Android/Sdk/emulator/lib64/qt/lib/:/home/oscar/Android/Sdk/emulator/lib64:/home/oscar/Android/Sdk/emulator/lib64/gles_swiftshade:/home/oscar/Android/Sdk/emulator/lib64/gles_mesa


再运行 ./emulator64-arm -avd Nexus
注意，Nexus为虚拟机的名字，所以在Android Studio里创建虚拟机的时候，需要起一个没有空格的AVD名称。

出现另一个错误：
Cannot open file ':/light/rotary_input_control', because: No such file or directory
[140458477311744]:WARNING:android/android-emu/android/featurecontrol/FeatureControlImpl.cpp:63:Loading advanced feature host default setting: ForceANGLE, expect on/off, get: null
[140458477311744]:WARNING:android/android-emu/android/featurecontrol/FeatureControlImpl.cpp:63:Loading advanced feature host default setting: ForceSwiftshader, expect on/off, get: null
[140458477311744]:WARNING:android/android-emu/android/featurecontrol/FeatureControlImpl.cpp:89:Loading advanced feature host default setting: Wifi, expect on/off, get: null
emulator: WARNING: Requested RAM size of 1536MB is too large for your environment, and is reduced to 1152MB.
-- Invalid CPU architecture: x86, valid values: arm

解决方法：在创建AVD的时候，Image不可以选择X86的，需要到Other Image选项上下载armeabi-v7a的Image


再运行./emulator64-arm -avd Nexus 
虚拟机启动！！！！  配置成功



关于如何在Linux环境下运行android studio：
/android-studio/bin/目录上有一个studio.sh文件。
./studio.sh 便可启动android studio



为了不用每次打开terminal都要做export，可以修改.bashrc文件，从而使每次环境变量导出自动执行。
方法：
在用户目录下（/home/oscar/)，命令为vi .bashrc
在文件最下方加入export的内容，保存。
如何想马上生效，则执行source /home/oscar/.bashrc ，否则需要重启之后才能生效。


启动avd方法，
在/emulator文件夹下执行：`./emulator64-arm -avd Nexus4 -kernel /home/oscar/Documents/goldfish/arch/arm/boot/zImage`（确保虚拟机的ram在2GB以上）
在/platform-tools/文件夹下执行：./adb shell     注意，如果是第一次使用，在这个指令前要先输入./adb root指令
即可连接上avd，尽管avd可能还没有完全初始化结束。



把goldfish_sensor.c 文件加入到 "~/Documents/goldfish/arch/arm/mach-goldfish" 路径下，
然后修改makefile文件
修改方法：
