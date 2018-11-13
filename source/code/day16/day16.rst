################
线程同步 - d16
################

*******************
一、并发冲突问题
*******************

:: 

    g_pool = 0;
    线程1                                    线程1
    从内存中把0读取CPU寄存器
    把CPU寄存器中的0累加为1
    把CPU寄存器中1写回到内存   
                                                从内存中把1读取CPU寄存器
                                                把CPU寄存器中的1累减为0
                                                把CPU寄存器中0写回到内存
    -------------------------------------------------------------
    从内存中把0读取CPU寄存器
                                                从内存中把0读取CPU寄存器
    把CPU寄存器中的0累加为1
                                                把CPU寄存器中的0累减为-1
                                                把CPU寄存器中-1写回到内存
    把CPU寄存器中1写回到内存   
    当多个线程同时访问共享资源时，
    由于对共享资源的非原子化操作，
    可以引发数据不一致的问题。
    这种现象被称为并发冲突。

*******************
二、互斥量
*******************

:: 

    多线程 X
    并发访问共享资源 X
    非原子化操作 V
    将一组非原子化的指令变成原子化
    ――任何时候都只会有一个线程执行一组特定的指令。
    线程1 {
      锁定互斥量;
      ...... \
      ......  > 原子化操作
      ...... /
      解锁互斥量;
    }
    线程2 {
      锁定互斥量;
      ...... \
      ......  > 原子化操作
      ...... /
      解锁互斥量;
    }
 
.. code-block:: c
 
    // 初始化互斥量：
    int pthread_mutex_init (pthread_mutex_t* mutex,
          const pthread_mutexattr_t* mutexattr);
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    // 锁定互斥量：
    int pthread_mutex_lock (pthread_mutex_t* mutex);

    // 解锁互斥量：
    int pthread_mutex_unlock (pthread_mutex_t* mutex);

    // 销毁互斥量：
    int pthread_mutex_destroy (pthread_mutex_t* mutex);
    // 针对通过pthread_mutex_init初始化的互斥量。


************************
三、资源分享问题
************************

当多个线程竞争有限资源时，会出现某些线程得不到资源的情况。 
这时得不到资源的线程应该等待那些获得资源的线程，在使用资源以后，主动放弃资源。

************************
四、信号量
************************

信号量是一个资源计数器，用于控制访问有限资源的线程数。

.. code-block:: c

    #include <semaphore.h>

    /* 1.创建信号量 */
    int sem_init (
      sem_t* sem,        // 输出，信号量ID
      int pshared,       // 0表示线程信号量，非零表示进程信号量
      unsigned int value // 信号量初值
    );
    // 成功返回0，失败返回-1。

    /* 2.等待信号量 */
    int sem_wait (sem_t* sem);
    // 如果信号量sem的计数值足够减1，立即返回0，
    // 同时将信号量sem的计数值减1，不够减则阻塞，直到够减为止。

    int sem_trywait (sem_t* sem);
    // 如果信号量sem的计数值不够减，不阻塞而是立即返回-1，
    // 同时将errno置为EAGAIN。

    int sem_timedwait (sem_t* sem,
          const struct timespec* abs_timeout /* 等待超时 */);

    struct timespec {
          time_t tv_sec; // 秒
          long tv_nsec; // 纳秒(10^-9秒)
    };
    // 如果信号量sem的计数值不够减即阻塞，直到够减或超时返回，
    // 如果因为超时返回，errno为ETIMEOUT。

    /* 3.释放信号量 */
    int sem_post (sem_t* sem);
    // 将信号量sem的计数值加1。

    /* 4.销毁信号量 */
    int sem_destroy (sem_t* sem);
    // 释放信号量对象本身的内核资源。

************************
五、死锁问题
************************

:: 

    线程1    线程2
       |       |
    获取A    获取B
       |       |
    获取B    获取A <- 死锁
       | \  /  |
    释放B X  释放A
       | / \   |
    释放A    释放B

.. literalinclude:: ./day16/bus.c
    :language: c
    :encoding: utf-8

.. literalinclude:: ./day16/dead.c
    :language: c
    :encoding: utf-8

.. literalinclude:: ./day16/pool.c
    :language: c
    :encoding: utf-8

.. literalinclude:: ./day16/Makefile
    :language: makefile
    :encoding: utf-8


***********************
六、条件变量（DMS项目）
***********************

