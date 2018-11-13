################
文件系统 - d08   
################


::

    八、access
    #include <unistd.h>
    int access (
      char const* pathname, // 文件路径
      int               mode         // 访问模式
    );
    根据调用进程的用户ID和组ID进行指定访问模式测试。
    测试通过返回0，否则返回-1。
    mode取值：
    R_OK - 读
    W_OK - 写
    X_OK - 执行
    F_OK - 存在
    access ("a.txt", F_OK) -> 0 : 存在，-1 : 不存在
    access ("a.txt", R_OK) -> 0 : 可读，-1 : 不可读
    九、umask
    #include <sys/stat.h>
    mode_t umask (mode_t cmask);
    为调用进程设置文件权限屏蔽字，并返回以前的值。
    所谓文件权限屏蔽字，就是此进程所创建的文件都不会包含屏蔽字中
    的权限。
    当前屏蔽字：U               0002
    设置权限字：M              0666 & ~0002 = 0664
                                         110110110  000000010
                                         111111101
                                         110110100
                                             6    6    4
    实际文件权限：M&~U   0664
    十、chmod/fchmod
    修改文件的权限。
    #include <sys/stat.h>
    int chmod (
      char* const pathname, // 文件路径
      mode_t        mode        // 文件权限
    );
    int fchmod (
      int        fd,       // 文件描述符号
      mode_t mode // 文件权限
    );
    成功返回0，失败返回-1。
    十一、chown/fchown/lchown
    修改文件的用户和组。
    #include <unistd.h>
    int chown (
      char const* pathname, // 文件路径
      uid_t            owner,      // 用户ID
      gid_t            group       // 组ID
    );
    int fchown (
      int    fd,        // 文件描述符
      uid_t owner, // 用户ID
      gid_t group  // 组ID
    );
    int lchown (                     // 不跟踪软链接
      char const* pathname, // 文件路径
      uid_t            owner,      // 用户ID
      gid_t            group       // 组ID
    );
    成功返回0，失败返回-1。
    某个文件a，原来是tarena(1000):soft(2000)，
    1) 希望改成csd1408(1001):beijing(2001)
    chown ("a", 1001, 2001);
    2) 希望改成csd1408(1001):soft(2000)
    chown ("a", 1001, -1);
    3) 希望改成tarena(1000):beijing(2001)
    chown ("a", -1, 2001);
    注意：只有超级用户(root)才可以任意修改文件的用户和组，
    普通用户只能修改原来属于自己的文件的用户和组。
    相当于执行命令：$ chown cs1408:beijing a
    十二、truncate/ftruncate
    从文件尾部截短或增长，增加的部分用0填充。
    #include <unistd.h>
    int truncate (
      char const* pathname, // 文件路径
      off_t            length        // 文件长度
    );
    int ftruncate (
      int    fd,       // 文件描述符
      off_t length // 文件长度
    );
    成功返回0，失败返回-1。
    注意：对于文件映射，
    私有映射(MAP_PRIVATE)
    只是将虚拟内存映射到文件缓冲区而非文件中。
    对于内存映射，私有映射(MAP_PRIVATE)和
    公有映射(MAP_SHARED)，没有任何区别。
    十三、link/unlink/remove/rename
    #include <unistd.h>
    1.创建硬链接
    int link (
      char const* path1, // 文件路径
      char const* path2  // 链接路径
    );
    成功返回0，失败返回-1。
    已有文件/usr/home/tarena/a.txt，
    希望为其建立硬链接/usr/home/soft/b.txt。
    link ("/usr/home/tarena/a.txt",
      "/usr/home/soft/b.txt");
    硬链接的本质就是目录文件中的一个条目：
    <文件路径>    <i节点号>
    a.txt <- b.txt
            <- c.txt
    目录文件中：
    a.txt 1234
    b.txt 1234
    c.txt 1234
    2.删除硬链接
    int unlink (
      char const* path // 路径
    );
    成功返回0，失败返回-1。
    如果与一个文件相对应的所有的硬链接都被删除了，
    那么该文件在磁盘上的存储区域即被释放。
    unlink ("a.txt"); -> 2
    unlink ("b.txt"); -> 1
    unlink ("c.txt"); -> 0 -> 释放磁盘空间
    如果此刻文件正在被打开，
    并不会立即释放磁盘空间，而是对该文件做标记，
    当该文件的最后一个描述符被关闭时，
    检查此标记，若为删除状态，则释放磁盘空间。
    3.删除文件及空目录
    int remove (
      char const* path // 路径
    );
    成功返回0，失败返回-1。
    4.移动或更名
    int rename (
      char const* old,  // 原路径
      char const* new // 新路径
    );
    成功返回0，失败返回-1。
    在/usr/home/tarena目录下有文件abc.txt，
    希望将其改名为123.txt。
    rename ("/usr/home/tarena/abc.txt",
      "/usr/home/tarena/123.txt");
    在/usr/home/tarena目录下有文件abc.txt，
    希望将该文件移动到/usr/home/soft目录下。
    rename ("/usr/home/tarena/abc.txt",
      "/usr/home/soft/abc.txt");
    在/usr/home/tarena目录下有文件abc.txt，
    希望将该文件移动到/usr/home/soft目录下，
    同时更名为123.txt。
    rename ("/usr/home/tarena/abc.txt",
      "/usr/home/soft/123.txt");
    十四、symlink/readlink
    #include <unistd.h>
    1.建立符号链接(软链接)
    int symlink (
      char const* oldpath,  // 文件路径（可以不存在）
      char const* newpath // 链接路径
    );
    成功返回0，失败返回-1。
    已有文件a.txt，建立该文件的符号链接b.txt。
    symlink ("a.txt", "b.txt");
    2.读取符号链接文件
    ssize_t readlink (
      char const* path,     // 符号链接文件路径
      char*           buf,       // 缓冲区
      size_t           bufsize  // 缓冲区大小
    );
    成功返回实际拷入buf缓冲区中符号链接文件内容的字节数，
    失败返回-1。
    注意，该函数不追加结尾空字符。
    十五、mkdir/rmdir
    #include <sys/stat.h>
    1.创建目录
    int mkdir (
      char const* path,  // 目录路径
      mode_t       mode // 访问权限
    );
    成功返回0，失败返回-1。
    2.删除空目录
    int rmdir (
      char const* path,  // 目录路径
    );
    成功返回0，失败返回-1。
    十六、chdir/fchdir/getcwd
    当前目录<==>工作目录
    #include <unistd.h>
    1.获取工作目录
    char* getcwd (
      char* buf, // 缓冲区
      size_t size // 缓冲区大小
    );
    将当前工作目录拷贝入buf缓冲区，同时返回其首地址。
    失败返回NULL。
    该函数会追加空字符。
    #include <limits.h>
    char buf[PATH_MAX+1];
    getcwd (buf, sizeof (buf));
    2.改变工作目录
    int chdir (char const* path);
    int fchdir (int fd);
    成功返回0，失败返回-1。
    十七、opendir/fopendir/closedir/readdir/
              rewinddir/telldir/seekdir
    #include <sys/types.h>
    #include <dirent.h>
    1.打开目录流
    DIR* opendir (
      char const* pathname // 目录路径
    );
    成功返回目录流指针，失败返回NULL。
    DIR* fopendir (
      int fd // 目录的文件描述符（open返回）
    );
    成功返回目录流指针，失败返回NULL。
    2.关闭目录流
    int closedir (DIR* dirp);
    成功返回0，失败返回-1。
    3.读取目录流
    struct dirent* readdir (DIR* dirp);
    struct dirent {
      ino_t                  d_ino;             // i节点号
      off_t                  d_off;              // 下一个条目在目录流中的位置
      unsigned short d_reclen;         // 目录条目记录长度
      unsigned char   d_type;           // 目录/文件类型
      char                   d_name[256]; // 目录/文件名字
    };
    d_type取值：
    DT_DIR - 目录
    DT_REG - 普通文件
    DT_LNK - 符号链接
    DT_BLK - 块设备文件
    DT_CHR - 字符设备文件
    DT_SOCK - UNIX域套接字文件
    DT_FIFO - 有名管道文件
    DT_UNKNOWN - 不知道是什么文件
    成功返回下一个目录条目结构体的指针，
    到达目录尾(不设置errno)或者失败(设置errno)返回NULL。
    4.设置目录流位置
    void seekdir (
      DIR* dirp,   // 目录流指针
      long offset // 目录流位置（相对于目录头）
    );
    5.获取目录流位置
    long telldir (DIR* dirp);
    6.复位目录流
    void rewinddir (DIR* dirp);
    作业：根据命令行指定的路径，打印一棵目录树。
