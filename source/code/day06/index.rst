################
文件系统 - d06   
################

::

    闵卫
    minwei@tarena.com.cn
    标C     UC
    fopen open
    fclose close
    fread  read
    fwrite write
    一、系统I/O与标准I/O
    1.当系统调用函数被执行时，需要切换用户态和内核态，
    频繁调用会导致性能损失。
    2.标准库做了必要的优化，内部维护一个缓冲区，
    只有满足特定条件时才将缓冲区与系统内核同步，
    借此降低执行系统调用的频率，
    减少进程在用户态和内核态之间来回切换的次数，
    提高运行性能。
    二、lseek
    1.每个打开文件都有一个与之相关的“文件位置”。
    2.文件位置通常是一个非负的整数，
    用以度量从文件头开始计算的字节数。
    3.读写操作都是从当前文件位置开始，
    并且根据所读写的字节数，增加文件位置。
    4.打开一个文件，除非指定了O_APPEND，
    否则文件位置一律被设为0。
    5.lseek函数根据所提供的参数认为地设置文件位置，
    并不引发任何文件I/O动作。
    6.在超越文件尾的文件位置写入数据，
    将在文件中形成空洞。
    7.文件空洞并不占用磁盘空间，但是被算在文件大小内。
    #include <sys/types.h>
    #include <unistd.h>
    off_t lseek (
        int    fd,         // 文件描述符
        off_t offset,   // 偏移量
        int    whence // 起始位置
    );
    成功返回当前文件位置，失败返回-1。
    whence取值：
    SEEK_SET  - 从文件头
                      （文件的第一个字节）
    SEEK_CUR - 从当前位置
                      （上一次读写的最后一个字节的下一个位置）
    SEEK_END - 从文件尾
                      （文件的最后一个字节的下一个位置）
    获取当前文件位置：lseek (fd, 0, SEEK_CUR)
    获取文件大小：lseek (fd, 0, SEEK_END)
    复位到文件头：lseek (fd, 0, SEEK_SET)
    三、打开文件的内核数据结构
    1.每个进程在内存中都有一个进程表条目（Process Table Entry）
    与之对应。
    2.每个进程表条目中都有一个文件描述符表的结构体数组。
    3.文件描述符就是文件描述表条目在文件描述符表中的下标。
    4.每个文件描述符表条目中包含了一个文件表指针，
    指向一个特定的文件表结构（File Table）。
    5.文件表中包含了若个数据，如：文件状态标志、文件偏移、
    v节点指针等。
    6.v节点指针指向v节点结构体，v节点结构体中保存了i节点号。
    7.通过i节点号，对应磁盘上一个具体的i节点，
    通过i节点中记录的文件位置，
    就可以确定文件数据在磁盘上的存储位置。
    四、dup/dup2
    #include <unistd.h>
    int dup (int oldfd);
    将参数文件描述符oldfd所对应的文件描述符表条目复制到文件描述
    符表中的最小未用文件描述符的位置，返回该位置所对应的下标。
    如果失败，返回-1。
    int dup2 (int oldfd, int newfd);
    通过newfd指定文件描述符复制的目标。如果newfd对应的是一个
    正在打开的文件，该函数会先将该文件关闭，然后再复制。如果该
    函数成功返回第二参数，失败返回-1。
    无论dup还是dup2都只是复制文件描述符，文件表始终都只有一个。
    int fd1 = open ("a.txt", ...);
    int fd2 = dup (fd1);
    fd1 \
            > 文件表 -> v节点 -> i节点 -> 文件
    fd2 /
    两次open同一个文件，会得到两张文件表，对应同一个v节点。
    int fd1 = open ("a.txt", ...);
    int fd2 = open ("a.txt", ...);
    fd1 -> 文件表1 \
                             > v节点 -> i节点 -> 文件
    fd2 -> 文件表2 /
    五、sync/fsync/fdatasync
    1.大多数磁盘I/O都是通过缓冲区进行的，
    写入文件其实只是写入缓冲区，直到缓冲区满，
    才将其排入写队列，等待I/O子系统空闲时将其同步到设备。
    2.延迟写降低访问磁盘设备的频率，提高写操作的效率，
    但可能导致磁盘文件与缓冲区数据不同步。
    void sync (void);
    将调用进程所有被修改过的缓冲区排入写队列。
    int fsync (int fd);
    针对特定文件做写同步，只到被修改过的缓冲区确实被同步到设备上
    才返回。
    int fdatasync (int fd);
    功能和fsync一样，但只同步文件数据，不同步文件属性。
    应用程-fwrite->标准库缓冲-fflush->内核-sync----->磁盘
    序内存-------------write------------>缓冲 fsync        设备
                                                                  fdatasync
    六、fcntl
    #include <fcntl.h>
    int fcntl (
      int fd,    // 文件描述符
      int cmd, // 操作指令
      ...           // 可变参数，因操作指令而异
    );
    对fd文件执行cmd指令，某些指令需要提供参数。
    int fcntl (int fd, int cmd);
    int fcntl (int fd, int cmd, long arg);
    返回值因cmd而异，失败返回-1。
    cmd取值：
    F_DUPFD - 复制文件描述符fd为不小于arg的文件描述符
                      若arg文件描述符已用，
                      该函数会选择一个比arg大的最小的未用值，
                      而不是象dup2那样关闭之。
    F_GETFD - 获取文件描述符标志
    F_SETFD - 设置文件描述符标志
    截止目前文件描述符标志只包含一个位：FD_CLOEXEC
    0: 在通过exec函数所创建进程中，该文件描述符保持打开，缺省。
    1: 在通过exec函数所创建进程中，该文件描述符将被关闭。
    F_GETFL - 获取文件状态标志
                    不能获取O_CREAT/O_EXCL/O_TRUNC
    F_SETFL - 追加文件状态标志
                    只能追加O_APPEND/O_NONBLOCK
    int fd = open (...);
    int flags = fcntl (fd, F_GETFL);
    if (flags & O_WRONLY)
       只写文件
    fcntl (fd, F_SETFL, O_APPEND | O_NONBLOCK);
