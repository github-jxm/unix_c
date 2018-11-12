// 单向线性链表
//
#ifndef _LIST_H
#define _LIST_H

#include <sys/types.h>
#include <stdbool.h>

// 节点
typedef struct ListNode {
	void*            data; // 数据
	struct ListNode* next; // 后指针
}	LIST_NODE;

// 链表
typedef struct List {
	LIST_NODE* head; // 头指针
	LIST_NODE* tail; // 尾指针
	LIST_NODE* iter; // 迭代器
}	LIST;

// 创建
LIST* list_create (void);

// 销毁
void list_destroy (LIST* list);

// 压入
void list_push (LIST* list, void* data);

// 弹出
void* list_pop (LIST* list);

// 删除
void list_remove (LIST* list, void* data);

// 清空
void list_clear (LIST* list);

// 判空
bool list_empty (LIST* list);

// 开始
void list_begin (LIST* list);

// 继续
void** list_next (LIST* list);

// 终止
bool list_end (LIST* list);

#endif // _LIST_H
