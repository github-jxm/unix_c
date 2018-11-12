#########
线程
#########

************
一、基本概念
************


* 1.线程就是进程中代码的执行路线，即进程内部的控制序列。

::

    程序――磁盘文件，纸面上的旅行日程表
    进程――内存数据，头脑中的旅行计划
    线程――执行路径，按照计划旅行

* 2.线程只是一个执行路径，并不拥有独立的内存资源，

::

    共享进程的代码区、数据区、堆区、命令行参数和环境变量。

* 3.线程拥有自己独立的栈，因此用户自己独立的局部变量。
* 4.一个进程可以同时拥有多个线程，但是至少有一个主线程。

*********************
二、POSIX线程
*********************

IEEE POSIX 1003.1c指定了POSIX线程标准。

.. code-block:: c

    // pthread
    #include <pthread.h>

.. code-block:: sh

    # libpthread.so
    gcc ... -lpthread

************************
三、POSIX线程库的功能
************************

* 1.线程管理：创建、销毁、分离、汇合、获取或者设置属性。
* 2.线程同步：解决并发冲突问题。

************************
四、线程函数
************************

1.创建（工作）线程
======================

.. code-block:: c

    int pthread_create (
          pthread_t* tid,                 // 线程ID
          const pthread_attr_t* attr,     // 线程属性，置NULL表示缺省属性
          void* (*start_routine) (void*), // 线程过程函数
          void* arg                       // 传递给线程过程函数的参数
    );


    /* 内核：开辟一个新的线程，在该线程中调用
      start_routine (arg);
    */

    // 成功返回0，失败返回错误码。

2.汇合线程
==============

.. code-block:: c

    int pthread_join (
          pthread_t tid,   // 所要汇合的线程ID
          void**    retval // 线程过程函数的返回值
    );

    // 线程版的waitpid。
    // 该函数会一直阻塞，直到tid参数所标识的线程结束（线程过程函数返回），成功返回0，失败返回错误码。
    // 如果对线程过程函数的返回值不感兴趣，retval可以置NULL。

3.获取线程自身的ID
====================

.. code-block:: c

    pthread_t pthread_self (void);

    //成功返回调用线程的ID，不会失败。

4.比较线程ID
===============

.. code-block:: c

    int pthread_equal (pthread_t t1, pthread_t t2);

    // t1和t2相等返回非0，否则返回0。

5.终止线程（线程自杀）
==============================

.. code-block:: c

    void pthread_exit (void* retval);
    // 线程版的exit。
    /*
    void fun2 (void) {
      if (我实在受不了了)
        exit (-1);
    }

    void fun1 (void) {
      fun2 ();
    }

    int main (void) {
       fun1 ();
       return 0;
    }
    */

6.分离线程
================

默认情况下的线程都是可汇合线程，即可以通过pthread_join汇合的线程。
这样的线程即便终止，系统仍然会为其保留部分资源（其中包括线程过程函数的返回值），直到调用pthread_join函数，这部分资源才会被回收。

调用如下函数：

.. code-block:: c

    pthread_detach (pthread_t tid);
    // 将tid参数所标识的线程置为分离线程。这样的线程不可被pthread_join汇合，线程终止以后其全部资源被系统自动回收。

7.取消线程（线程他杀）
=======================


.. code-block:: c

    int pthread_cancel (pthread_t tid);
    // 成功返回0，失败返回错误码。

.. code-block:: c

    // 设置调用线程的取消状态：
    int pthread_setcancelstate (int state, int* oldstate);
    /* 
    state取值：
    PTHREAD_CANCEL_ENABLE  - 可以取消（默认）
    PTHREAD_CANCEL_DISABLE - 禁止取消
    */

.. code-block:: c

    // 设置调用线程的取消类型：
    int pthread_setcanceltype (int type, int* oldtype);
    /*
    type取值：
    PTHREAD_CANCEL_DEFERRED - 延迟取消（默认）
    PTHREAD_CANCEL_ASYNCHRONOUS - 立即取消
    */

------------------------------------------------------

************
网络通信补遗
************

.. code-block:: c

    #include <sys/socket.h>
    ssize_t recvfrom (int sockfd, 
                       void* buf, 
                       size_t len, 
                       int flags,
                      struct sockaddr* addr, 
                      socklen_t* addrlen);
    // 输入数addr和addrlen表示发送方的地址信息。

    ssize_t sendto ( int sockfd, 
                     void* buf, 
                     size_t len, 
                     int flags,
                     struct sockaddr const* addr, 
                     socklen_t addrlen);

    // 输入参数addr和addrlen表示接收方的地址信息。

