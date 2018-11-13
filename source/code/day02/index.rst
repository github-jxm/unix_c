#######
day02  
#######

::

    回顾：
        unix/linux发展历史：
            1970 unix 第一版
            1975 unix 第六版  以后版本不再免费
                  HPUX AIX solaris
            GNU计划： 自由软件  操作系统 之上的应用软件
            1991 linux 0.0.1 GNU/linux
                  fedora ubuntu redhat debain suse 红旗
            POSIX：统一的用户编程接口规范

    1、重新认识编译器
       .c ---> a.out
       1) 预编译
       2）编译
       3）汇编
       4）链接
       gcc 编译器的参数： -o -g -c -E -S -I -v -l -L -Wall

    2、.c .h文件
       预处理指令 pragma pack
                  pragma GCC poison
       预定义宏   __LINE__ __FILE__ __FUNCTION__ (调试)
       头文件的使用：本模块对外的清单
                 #include <>    
                 #include ""区别
            如果头文件和.c不在同一个目录的解决方案
                1）#include "相对路径/xxx.h"
                2) #include "xxx.h" 
                   gcc -I "相对路径"    
    3、重新审视a.out
       环境变量： 系统运行时需要的一系列参数
           PATH: 当去执行某个可执行程序未指定路径，在PATH中的路径挨个寻找是否存在要执行的可执行程序
           如何定义 赋值 环境变量
              export PATH=$PATH:. (不推荐将当前目录添加)
           env: 当前用户的所有环境变量
    4、静态库
      1）静态库的制作
          gcc -c xxx.c yyy.c
          ar -r libxxxxx.a   xxx.o yyy.o
      2) 使用方式
         gcc main.c -lxxxxx -L./
      3) 运行./a.out
    5、共享库
       在程序链接时并不像静态库那样拷贝库中函数的代码，而是做标记。然后在程序启动运行的时候，动态加载所需要的模块。
       所以，应用程序在执行时仍需要共享库的支持。
       使用共享库生成的可执行文件要比使用静态库生成的可执行文件小的多。
      1）共享库的制作
         a) 编辑.c .h文件
         b) 编译生成目标文件  gcc -c -fpic xxx.c
             fpic作用：生成位置无关码 
            gcc -c -fpic calc.c
            gcc -c -fpic show.c
         c) 链接成共享库文件 gcc -shared xxx.o... libxxx.so
            gcc -shared calc.o show.o -o libmy.so
          b、c步骤可以合并为
           gcc -shared -fpic calc.c show.c -o libmy.so
      2）使用方式
         a) 直接法
            gcc main.c libmy.so
         blibc.) 环境变量法
            export LIBRARY_PATH=$LIBRARY_PATH:.
            gcc main.c -lmy
         c)参数法 （推荐使用）
            gcc main.c -lmy -L./ ---》a.out
      3）运行
         LD_LIBRARY_PATH: 加载共享库的路径
         export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
         ./a.out
    总结：静态库和动态库的优缺点
         使用静态库占用空间非常大， 执行效率高，如果静态库函数修改，a.out需要重新编译
         使用动态库占用空间比较小， 执行效率偏低，如果动态库中的函数进行了修改，只需要重新编译生成库文件，不需要重新编译a.out文件。
       
        4)共享库的加载方式
          a)隐式加载
            ./a.out 所需要的共享库由加载器加载到内存中去
          b)显式加载
            编程者通过程序手工加载所需要的库文件。
            dlopen
            dlsym
            dlerror
            dlclose
          load.c
      
    6、工具
       ldd: 可以用来察看可执行文件和共享库文件的动态依赖
           ldd a.out
           ldd libmy.so
       nm: 察看目标文件、可执行文件、静态库、共享库文件的
           符号列表
           所谓的符号：函数名称 全局变量名称
       objdump: 反汇编 ， 将二进制翻译成汇编程序
    7、C语言的出错处理
      错误处理解决不了所有的问题，只是可控的范围内，对错误的情况进行编码处理。
       错误的处理对所有的语言都是必须的，后期学习的C++都使用异常机制进行错误处理。
       C语言中通过返回值的方式来描述出错原因，判断返回值进行出错处理。
    7.1 通过函数的返回值来表示错误
       1）返回合法值表示成功，返回非法值表示失败。
       2）返回有效指针表示成功，返回空指针表示失败
       3）返回0表示成功，返回-1表示失败
       4）永远成功. 如： bzero
      练习：
          写4个函数，分别是：
      取1~10的随机值，并返回该值， 假如随机到5代表出错
      字符串拷贝，拷贝成功返回目标字符串地址，失败返回null
        strcopy(char *dest, char *src, int len)
      传入一个字符串，如果该字符串为"error",返回出错，否则返回0 
       求两个整数的平均值，
        void func(int a, int b , int *av)
    7.2 标C库函数 系统调用如何判断是否执行成功
        errno.c
       在标C中，对出错情况提供了一个全局变量和3个函数
         errno-----外部的全局变量，用于存储错误的编号
         strerror/perror/printf:把错误的编号转换成对应出错原因字符串信息
         strerror
         perror
         printf("%m") :打印当前的出错原因（自动查找errno）
     问题：为什么sudo ./a.out 读写打开/etc/passwd文件成功，
           而./a.out读写打开失败？
        答：当a.out 开始执行时会获取一张环境变量表，这张表记录了当前是哪个用户（权限）来执行的a.out

    8、环境变量的操作
       env命令
       在C语言中环境变量存在于环境变量表中。环境表就是一个字符串的数组（字符指针数组）。
       通过外部的全局变量 environ --->环境表的地址
                        char **environ
       编程：打印所有的环境变量的值
          env.c
       练习：将”LANG=zh_CN.UTF-8“中的 ”zh_CN.UTF-8“过滤出来，并保存到buf[],最后打印buf
        思路：通过environ变量取得环境变量表中的每个环境变量字符串 ，通过strncmp(字符串 ， ”LANG=“， ...)
        如果相等字符串中就含有字串”zh_CN.UTF-8“，
        将该字串拷贝到buf[],并打印 
       
    操作环境变量的函数：getenv setenv unsetenv clearenv
                         putenv
    内存管理   malloc/brk/sbrk/mmap

      makefile 三要素
        目标：依赖
            （ＴＡＢ） 命令
      工具《跟我一起写makefile》
       
