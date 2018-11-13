########################
文件系统 - d07   
########################

::

    六、fcntl
    ...
    文件锁
    int fcntl (int fd, int cmd, struct flock* lock);
    其中：
    struct flock {
      short int l_type;       // 锁的类型
                                      // F_RDLCK/F_WRLCK/F_UNLCK
                                      // 读锁/写锁/无锁
      short int l_whence; // 偏移起点
                                      // SEEK_SET/SEEK_CUR/SEEK_END
                                      // 文件头/当前位置/文件尾
      off_t       l_start;      // 锁区偏移，相对于l_whence计算
      off_t       l_len;        // 锁区长度，0表示锁到文件尾
      pid_t      l_pid;        // 加锁进程，-1表示自动设置
    };
    文件fd, 从相对于文件头10个字节处开始，对20个字节加写锁。
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 10;
    lock.l_len = 20;
    lock.l_pid = -1;
    fcntl (fd, F_SETLK, &lock);
    cmd取值：
    F_GETLK   - 测试锁
                       测试lock所表示的锁是否可加，
                       若可加则将lock.l_type置为F_UNLCK,
                       否则通过lock返回当前锁的信息
    F_SETLK    - 设置锁，成功返回0，失败返回-1
                       若因为其它进程持有锁而导致的失败，
                       errno = EACCESS/EAGAIN
    F_SETLKW - 以阻塞模式设置锁，成功返回0，失败返回-1
                        若有其它进程持有锁，该函数会阻塞，直到获得锁为止
    把刚才20个字节中的前5个字节解锁。
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 10;
    lock.l_len = 5;
    lock.l_pid = -1;
    fcntl (fd, F_SETLK, &lock);
    此时，另一个进程试图：
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 10;
    lock.l_len = 6;
    lock.l_pid = -1;
    fcntl (fd, F_SETLKW, &lock);
    这个进程会怎么样？阻塞...
    这时第一个进程
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 15;
    lock.l_len = 1;
    lock.l_pid = -1;
    fcntl (fd, F_SETLK, &lock);
    第二个进程立即获得所要求锁，同时从fcntl中返回。
    七、stat/fstat/lstat
    #include <sys/stat.h>
    int stat (
      char const* path, // 文件路径
      struct stat* buf    // 文件属性
    );
    int fstat (
      int               fd,   // 文件描述符
      struct stat* buf  // 文件属性
    );
    int lstat (                // 不跟踪软链接
      char const* path, // 文件路径
      struct stat* buf    // 文件属性
    );
    文件：a.txt [我要吃饭]
    软链接：b.txt [a.txt]
    软链接：c.txt [b.txt]
    stat ("b.txt", ...); // 获取a.txt的属性
    stat ("c.txt", ...); // 获取a.txt的属性
    lstat ("b.txt", ...); // 获取b.txt软链接文件本身的属性
    lstat ("c.txt", ...); // 获取c.txt软链接文件本身的属性
    成功返回0，失败返回-1。
    struct stat {
      dev_t st_dev; // 设备ID
      ino_t st_ino; // i节点号
      mode_t st_mode; // 文件类型和权限
      nlink_t st_nlink; // 硬链接数
      uid_t st_uid; // 用户ID
      gid_t st_gid; // 组ID
      dev_t st_rdev; // 特殊设备ID
      off_t st_size; // 总字节数
      blksize_t st_blksize; // I/O块字节数
      blkcnt_t st_blocks; // 占用块(512字节)数
      time_t st_atime; // 最后访问时间
      time_t st_mtime; // 最后修改时间
      time_t st_ctime; // 最后状态改变时间
    };
    文件元数据/文件属性/文件状态
    用八进制标书st_mode成员：TTSUGO
    TT - 文件类型
    S_IFDIR - 目录
    S_IFREG - 普通文件
    S_IFLNK - 软链接
    S_IFBLK - 块设备
    S_IFCHR - 字符设备
    S_IFSOCK - UNIX域套接字
    S_IFIFO - 有名管道
    S - 设置与粘滞位
    S_ISUID - 设置用户ID
    S_ISGID - 设置组ID
    S_ISVTX - 粘滞
    -r--r----- ... tarena soft ...
    mw
    a.out suid tarena
    /usr/bin/passwd：可执行程序，改口令
    /etc/passwd：数据文件，存口令
    执行具有S_ISUID/S_ISGID位的可执行文件所产生的进程，
    其有效用户ID/有效组ID，
    并不取自由其父进程（比如登录shell）所决定的，
    实际用户ID/实际组ID，
    而是取自该可执行文件的用户ID/组ID。
    S_ISUID位对于目录而言没有任何意义。
    具有S_ISGID的目录，
    在该目录下所创建的文件，继承该目录的组ID，
    而非其创建者进程的有效组ID。
    具有S_IVTX位的可执行文件，
    在其首次执行并结束后，
    其代码区被连续地保存在磁盘交换区中，
    因此，下次执行该程序可以获得较快的载入速度。
    具有S_IVTX位的目录，
    该目录下的文件或子目录，
    只有其拥有者或者超级用户才能更名或删除。
    U - 用户权限
    S_IRUSR - 用户可读
    S_IWUSR - 用户可写
    S_IXUSR - 用户可执行
    G - 同组权限
    S_IRGRP - 同组可读
    S_IWGRP - 同组可写
    S_IXGRP - 同组可执行
    O - 其它用户权限
    S_IROTH - 其它用户可读
    S_IWOTH - 其它用户可写
    S_IXOTH - 其它用户可执行
