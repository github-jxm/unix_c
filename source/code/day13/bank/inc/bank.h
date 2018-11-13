#ifndef _BANK_H
#define _BANK_H
#include <sys/types.h>
#define KEY_REQUEST 0x12345678 // 请求队列
#define KEY_RESPOND 0x87654321 // 响应队列
#define TYPE_OPEN     8001 // 开户
#define TYPE_CLOSE    8002 // 清户
#define TYPE_SAVE     8003 // 存款
#define TYPE_WITHDRAW 8004 // 取款
#define TYPE_QUERY    8005 // 查询
#define TYPE_TRANSFER 8006 // 转账
// 账户
typedef struct tag_Account {
	int    id;        // 账号
	char   name[256]; // 户名
	char   passwd[9]; // 密码
	double balance;   // 余额
}	ACCOUNT;
// 开户请求
typedef struct tag_OpenRequest {
	long   type;      // 类型
	pid_t  pid;       // 进程ID
	char   name[256]; // 户名
	char   passwd[9]; // 密码
	double balance;   // 余额
}	OPEN_REQUEST;
// 开户响应
typedef struct tag_OpenRespond {
	long type;       // 类型
	char error[512]; // 错误
	int  id;         // 账号
}	OPEN_RESPOND;
// 查询请求
typedef struct tag_QueryRequest {
	long  type;      // 类型
	pid_t pid;       // 进程ID
	int   id;        // 账号
	char  name[256]; // 户名
	char  passwd[9]; // 密码
}	QUERY_REQUEST;
// 查询响应
typedef struct tag_QueryRespond {
	long   type;       // 类型
	char   error[512]; // 错误
	double balance;    // 余额
}	QUERY_RESPOND;
// ...
#endif // _BANK_H
