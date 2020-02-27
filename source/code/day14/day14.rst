##################
网络通信 - d14
##################

************
一、基本概念
************


1.协议模型（OSI模型）
========================

::

    应用层 - 应用程序
    表示层 - 数据的组织
    会话层 - 数据的交换
    传输层 - 数据的封包
    网络层 - 网络的拓扑结构
    数据链路层 - 数字信号的电子化
    物理层 - 网络设备

2.TCP/IP协议族
==================

* 1)TCP(Transmission Control Protocol)，传输控制协议

::

    面向连接的协议。
    逻辑上模拟为电话业务。

* 2)UDP(User Datagram Protocol)，用户数据报文协议

::

    面向无连接的协议。
    逻辑上模拟为邮政业务。

* 3)IP(Internet Protocol)，互联网协议

::

    工作在TCP和UDP协议的底层。
    实现在互联网上传递信息的基本机制。

    ISO           TCP/IP
    应用层
    表示层        应用层      telnet/ftp/http
    会话层
    ------------------------
    传输层        传输层      TCP/UDP
    网络层        互联网层    IP
    ------------------------
    数据链路层    网络接口层  硬件/驱动
    物理层

3.消息流和协议栈
===================

有协议模型的不同层次构成了一个自下而上的协议栈，
所发送数据的数据沿着协议栈自上而下层层打包，
最终变成可以在物理介质上传输的电子信号。
接收数据时再将物理介质上的电子信号，沿着协议栈自下向上，
层层解包，最终变成应用可以处理的数据内容。

4.IP地址
=============

* 1)IP地址是Internet中唯一标识一台计算机的地址。

::

    A.IPv4：32位，IPv6：128位
    B.点分十进制字符串表示：0x01020304 -> 1.2.3.4

* 2)IP地址分级

::

    A级：0XXXXXXX | XXXXXXXX XXXXXXXX XXXXXXXX
             网络地址       本机地址
    B级：10XXXXXX XXXXXXXX | XXXXXXXX XXXXXXXX
             网络地址           本机地址
    C级：110XXXXX XXXXXXXX XXXXXXXX | XXXXXXXX
    网络地址                          本机地址
    172.40.0.10
    D级：1110XXXX XXXXXXXX XXXXXXXX XXXXXXXX
             多播地址

* 3)子网掩码

::

    IP地址 & 子网掩码 = 网络地址
    IP地址 & ~子网掩码 = 本机地址
    IP地址：192.168.182.48
    子网掩码：255.255.255.0
    网络地址：192.168.182.0
    本机地址：0.0.0.48

************************
二、套接字(Socket)
************************

1.接口
===========

::

    QQ      \
    LeapFTP  > socket -> TCP/UDP -> IP -> 网络驱动 -> 网络硬件
    IE      /

2.异构
=========

Java@UNIX@大型机<->socket<->C@Windows@PC机

3.模式
=============

* 1)点对点(Peer-to-Peer，P2P)，一对一通信。
* 2)客户机/服务器(Client/Server，C/S)，一对多通信。
* 3)浏览器/服务器(Browser/Server，B/S)，一个服务器为多个浏览器提供服务。

4.绑定
========

    将逻辑的套接字对象与物理的通信载体关联起来。

5.函数
===========

1)创建套接字

.. code-block:: c

    #include <sys/socket.h>
    int socket (int domain, int type, int protocol);

* domain - 域

::

                AF_UNIX/AF_LOCAL/AF_FILE，本地通信
                AF_INET，基于IPv4的网络通信, 对于BSD是AF_INET,对于POSIX是PF_INET. 两者本质一样。
                AF_INET6，基于IPv6的网络通信
                AF_PACKET，基于IP的底层协议进行网络通信

* type - 类型

::

           SOCKET_STREAM，流式套接字，基于TCP协议通信
           SOCKET_DGRAM，数据报套接字，基于UDP协议通信

* protocal - 特殊协议，目前置0即可

::

    成功返回套接字描述符，失败返回-1。
    套接字描述符类似于文件描述符，UNIX把网络当成文件看待。
    发送数据即写文件，接收数据即读文件，一切皆文件。

* 2)通信地址

A.基本地址结构

.. code-block:: c

    struct sockaddr {
      sa_family_t sa_family; // 地址族
      char sa_data[14];      // 地址值
    };

B.网络地址结构

.. code-block:: c

    #include <netinet/in.h>

    struct sockaddr_in {
      sa_family_t sin_family; /* 地址族，AF_INET/AF_INET6 */
      in_port_t    sin_port;  /* unsigned short，网络字节序的端口号
                                  逻辑上表示一个参与通信的进程，
                                  0-1024，公知端口，WWW-80
                                  FTP-21，TELNET-23，...
                                  自己编写的应用程序使用1024以上的端口号 */
      struct in_addr sin_addr; /* 网络字节序的IP地址 */
    };


::

    小低低：小端字节序，低位低地址
    int i = 0x12345678;
    小端机器：低地址-------->高地址
                    78      56     34      12  -> 0x78563412
    大端机器：低地址-------->高地址
                    12      34     56      78

    主机字节序->网络字节序->发送
    接收->网络字节序->主机字节序
    网络字节序就是大端字节序
    欲从小端机器发送0x12345678：L 78 56 34 12 H
    现将其转换为网络字节序：L 12 34 56 78 H
    发送到大端机器上：L 12 34 56 78 H
    从网络字节序转到大端字节序：L 12 34 56 78 H -> 0x12345678

.. code-block:: c

    struct in_addr {
      in_addr_t s_addr;
    };
    typedef uint32_t in_addr_t;
    typedef unsigned int uint32_t;

* 3)将套接字和通信地址绑定


.. code-block:: c

    int bind (int sockfd, const string sockaddr* addr, socklen_t addrlen);

    // 成功返回0，失败返回-1。


* 4)将套接字和对方通信地址连接

.. code-block:: c

    int connect (int sockfd, const string sockaddr* addr, socklen_t addrlen);

    // 成功返回0，失败返回-1。

* 5)用读写文件的方式通信：read/write
* 6)关闭套接字：close
* 7)字节序转换

.. code-block:: c

    #include <arpa/inet.h>

    // 主机字节序->网络字节序
    uint32_t htonl (uint32_t hostlong);
    uint16_t htons (uint16_t hostshort);

    // 网络字节序->主机字节序
    uint32_t ntohl (uint32_t netlong);
    uint16_t ntohs (uint16_t netshort);

* 8)IP地址转换

.. code-block:: c

    //点分十进制字符串->网络字节序整数形式的IP地址
    in_addr_t inet_addr (const char* cp);

    //网络字节序整数形式的IP地址->点分十进制字符串
    char* inet_ntoa (struct in_addr in);

6.编程
========

:: 

    服务器：创建套接字 -> 准备地址结构并绑定 -> 接收数据 -> 关闭套接字
    客户机：创建套接字 -> 准备地址结构并连接 -> 发送数据 -> 关闭套接字

************************************************
三、基于TCP协议的客户机/服务器模型
************************************************



1.TCP协议的基本特征
======================

* 1)面向连接：虚拟电路，建立可靠的连接，稳定地传输数据，人为断开连接。
* 2)传输可靠：发送数据、等待确认、丢包重传。

::

    ABCDEF
    A->              -+
    B->               |
    C->               | 时间窗口
    D->               | 
    E-> <-A OK -+
    F-> <-B OK
           <-C OK
           <-D OK
           <-E OK
           <-F OK

    每个发送都有应答，若在一定的时间窗口内没有收到应答，
    重新再发。

* 3)保证顺序：有序发送，有序接收，丢弃重复。
* 4)流量控制：接收端实时通知发送端接收窗口大小，防止溢出。
* 5)传输速度慢。

2.编程模型
===============

:: 

    服务器                             客户机
    =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    创建套接字 socket           创建套接字 socket
    准备地址   sockaddr_in      准备地址   sockaddr_in
    绑定地址   bind
    监听套接字 listen
    接受连接   accept           建立连接   connect
    接收数据   read/recv        发送数据   write/send
    发送数据   write/send       接收数据   read/recv
    关闭套接字 close            关闭套接字 close

3.常用函数
==============

.. code-block:: c

    #include <sys/socket.h>
    int listen (
        int sockfd,   // 套接字描述符
        int backlog   // 未决连接请求队列的最大长度，1024
    );
    //成功返回0，失败返回-1。

    int accept (int sockfd, struct sockaddr* addr, socklen_t* addrlen);
    /*
    从sockfd参数所标识套接字的未决连接请求队列中，
    提取第一个连接请求，同时创建一个新的套接字，
    用于在该连接中通信，返回该套接字描述符。
    同时通过后两个参数向调用者输出客户机的地址信息。
    失败返回-1。
    */

    ssize_t recv (int sockfd, void* buf, size_t len, int flags);
    // 返回实际接收到的字节数。
    // 如果在该函数执行过程中，对方关闭了连接，返回0。
    // 失败返回-1。

    ssize_t send (int sockfd, void const* buf, size_t len, int flags);
    //返回kk实际发送的字节数。失败返回-1。


**********
example   
**********


.. literalinclude:: ./day14/netcli.c
    :language: c
    :encoding: utf-8

.. literalinclude:: ./day14/netcli.c
    :language: c
    :encoding: utf-8

.. literalinclude:: ./day14/tcpsvr.c
    :language: c
    :encoding: utf-8

.. literalinclude:: ./day14/csem.c
    :language: c
    :encoding: utf-8

.. literalinclude:: ./day14/gsem.c
    :language: c
    :encoding: utf-8
