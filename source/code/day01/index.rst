##########
编程基础 
##########

::

    第一课   编程基础
    第二课   内存管理
    第三课   文件系统
    第四课   进程管理
    第五课   信号处理
    第六课   进程通信
    第七课   网络通信
    第八课   线程管理
    第九课   线程同步
    第十课   综合案例


::

    1、 unix下c开发，和前边学习的C编程数据结构有什么区别
        C学习，C编程语法、C标准库函数 ：printf malloc 
                                         strcpy strcmp
                                         memcpy fgets
                                         fopen fclose
                                         fread fwrite
        数据结构是把学会C语法（遣词造句），如何表达我们的思想（算法）
        uc学习的内容？
            开放给应用编程者的函数（系统调用）如何使用
         200~300个系统调用
    2、UC课程学什么？
       学习系统调用
           开发环境
           内存管理
           文件操作
           进程管理/进程间通信
           网络通信
           线程管理
           线程同步
       操作系统原理的内容

    《linux程序设计》   陈健
     《unix环境高级编程》
    3、怎么学？
       注意听原理
       man手册 + 编程练习   + 网络搜索
      关于某些函数man不到如何解决？ 
         man-patch.tar.gz
        步骤：tar xf man-patch.tar.gz
              rm manpages-zh_1.5.2-1_all.deb 
              sudo dpkg -i *.deb
    4、unix/linux发展历程
       1970年出现的unix系统
       C语言 用C语言改写了unix
       1975 unix第6版发布了，已经具有现代操作系统的几乎所有特征，最后一版免费版本的unix。
       后续商业版本的unix, AIX(IBM) 银行
                           Solaris(sun) 电信
                           HPUX
        1991 在unix发展起来的linux 0.0.1版  开源
        fedora ubuntu redhat debain  红旗...
        POSIX: 统一的系统编程接口规范
        GNU计划： 开源共享
    5、重新审视gcc工具
       gcc hello.c >a.out
       1) 预编译 ：处理所有的伪指令（以#开头）
          gcc hello.c -E -o hello.i
       2）编译: 把hello.i中的C语言变成汇编语言
          gcc hello.i -S -o hello.s     
       3）汇编:由汇编变成目标代码（二进制）
          gcc hello.s -c -o hello.o
       4）链接 : 将多个.o生成一个可执行文件
          gcc hello.o -o hello 
        把前三歩统称为编译阶段，最后一步称为链接阶段，
    编译阶段检查的是语法错误。  
       gcc的一些重要参数
          -c: 只编译不链接
          -o: 目标文件名称
          -E：预编译
          -S：产生汇编文件
          -Wall: 产生尽可能多的警告信息（建议加上该选项）
          -g: 生成的目标文件中包含调试信息
          -v: 显示编译阶段的过程以及编译器的版本号
          -O0/1/2/3：目标代码的优化级别
    6、重新审视.c和.h文件
      6.1 编译多个文件生成一个可执行文件
        gcc xxx.c yyy.c -o 
      6.2 头文件的作用？什么内容放入头文件？
        本模块对外的清单，各中声明都应该放在头文件中。
        1）声明外部的函数、变量
        2）自定义类型 strcut 宏定义
        3）包含其他的头文件
        注意：防止头文件的重复包含机制   
      6.3 头文件的使用注意事项
         1） #include <>:在系统目录下找文件  
             #include "":先在当前目录找指定的头文件， 如果找不到再到系统目录下找
         问题1： 系统目录是哪个目录？
              gcc hello.c -v 
              /usr/include
             /usr/include/i386-linux-gnu
         问题2：自己写一个.h文件，写一个.c文件，该文件中包含该.h ,如果.h和.c不在同一个目录怎么办？
          解决方案一：#include 时指定头文件所在的路径
                             相对路径（推荐）
                             绝对路径
          解决方案二： 把xxx.h扔到系统目录下去（不推荐）
          解决方案三： 使用gcc -I指定附加的头文件搜索路径
        6.4 预编译指示符
           #error
             各种版本控制工具： SVN CVS git
              error.c
           #line
           #pragma
              #pragma pack(1) (重点)
             pack.c
            对齐：每个成员，必须放在自己大小整数倍的位置
                    （该成员大于4字节按4字节计算）
            补齐：每个结构体的大小应该是最大成员大小的整数倍（最大成员超过4个字节按4字节算）	
              #pragma GCC poison
                 poison.c
          6.5 预定义宏 
              __FILE__
              __LINE__
              __FUNCTION__
            predef.c
              一般用于程序调试阶段
    7、重新审视a.out
       问题一：为什么./a.out可以执行 而a.out 不可以执行
              ls clear统统可以执行？
        答案：环境变量中的PATH在起作用
              环境变量一般是操作系统中用来指定操作系统运行环境的一些参数，比如说临时文件夹的位置。
              环境变量有很多，对应了不同的用途。
          命令 env,可以用来显示当前用户的环境变量
              其中PATH用来指定可执行程序的搜索路径。
    PATH=/home/tarena/workdir/Android2.3/android-source/jdk1.6.0_16/bin:/bin:/usr/bin:/usr/X11R6/bin:/usr/local/bin:/home/tarena/workdir/linux-x86/sdk/android-sdk_eng.root_linux-x86/tools
         问题二： printf()函数的实现代码在哪？
            ldd a.out: 显示可执行程序需要的共享库文件
            printf()函数的实现代码位于libc.so共享库文件中
    7.1 静态库文件
        就是一些目标文件的集合，通常以.a结尾。静态库在程序链接的时候使用，连接器会将程序中使用到的函数的代码从库文件中拷贝到应用程序中。一旦链接完成，在执行应用程序时就不再需要静态库文件。
        由于每个使用静态库的应用程序都需要拷贝所用函数的代码，所以静态链接的文件会比较大。
       7.1.1创建静态库文件
           1）编辑源程序
           2）编译生成目标文件 gcc -c xxx.c -o  xxx.o
              gcc -c calc.c
              gcc show.c -c 
           3）打包生成静态库文件 ar -r libzzz.a xxx.o yyy.o
              ar -r libmath.a calc.o show.o
              ar [选项]  静态库文件名称 目标文件列表
                 选项：
                     -r, 将目标文件插入到静态库中（重点）
                     -d, 从静态库中删除目标文件
                     -t, 以列表方式显示静态库中的目标文件
        7.1.2 静态库如何使用
            1） 直接法
               gcc main.c libmath.a 
            2）环境变量法
               export LIBRARY_PATH=$LIBRARY_PATH:./
               gcc main.c -lmath
            3）参数法 （推荐使用）
              gcc main.c -lmath -L./
    作业：写两个函数， 分别打印空/实心菱形，把这两个函数封装成静态库，通过main.c调用这两个库函数

    数据结构作业：在内存中建立一个班上同学的电话簿
           struct 
            {
               name
               age
               number
               vip
            }
       增删改查
       输入姓名找到电话，姓名重复的，把连个重复姓名的电话都列出来。


    7.2 共享库文件
