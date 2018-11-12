// 单向线性链表
//
#include <stdlib.h>
#include "list.h"

// 创建节点
static LIST_NODE* create_node (void* data) {
	LIST_NODE* node = malloc (sizeof (LIST_NODE));
	node->data = data;
	node->next = NULL;
	return node;
}

// 销毁节点
static LIST_NODE* destroy_node (LIST_NODE* node) {
	LIST_NODE* next = node->next;
	free (node);
	return next;
}

// 创建
LIST* list_create (void) {
	LIST* list = malloc (sizeof (LIST));
	list->head = NULL;
	list->tail = NULL;
	return list;
}

// 销毁
void list_destroy (LIST* list) {
	list_clear (list);
	free (list);
}

// 压入
void list_push (LIST* list, void* data) {
	LIST_NODE* node = create_node (data);

	if (list->tail)
		list->tail->next = node;
	else
		list->head = node;

	list->tail = node;
}

// 弹出
void* list_pop (LIST* list) {
	void* data = list->head->data;
	if (! (list->head = destroy_node (list->head)))
		list->tail = NULL;
	return data;
}

// 删除
void list_remove (LIST* list, void* data) {
	if (! list_empty (list)) {
		LIST_NODE* node = list->head;
		while (node->next)
			if (node->next->data == data)
				node->next = destroy_node (node->next);
			else
				node = node->next;

		if (list->tail != node)
			list->tail = node;

		if (list->head->data == data)
			list_pop (list);
	}
}

// 清空
void list_clear (LIST* list) {
	while (list->head)
		list->head = destroy_node (list->head);
	list->tail = NULL;
}

// 判空
bool list_empty (LIST* list) {
	return ! list->head && ! list->tail;
}

// 开始
void list_begin (LIST* list) {
	list->iter = list->head;
}

// 继续
void** list_next (LIST* list) {
	void** data = &list->iter->data;
	list->iter = list->iter->next;
	return data;
}

// 终止
bool list_end (LIST* list) {
	return ! list->iter;
}
