#ifndef _CHATROOM_H
#define _CHATROOM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "list.h"

#define MAX_NCK  256                // 最大昵称
#define MAX_TAG (4+MAX_NCK)         // 最大标志
#define MAX_TXT 1024                // 最大文本
#define MAX_MSG (MAX_NCK+MAX_TXT+1) // 最大消息
#define MAX_ACK  256                // 最大应答

#endif // _CHATROOM_H
