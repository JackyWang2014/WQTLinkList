//
//  main.c
//  WQTLinklist
//
//  Created by 王亓泰 on 16/4/14.
//  Copyright © 2016年 WangQitai. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    NO,
    YES
} BOOL;

typedef struct stu{
    char name[64];
    
    int age;
    int score;
    struct stu * next;
}stu_t;

// 创建结点
stu_t * create_node(void);
// 添加结点
void add_node(stu_t * head, stu_t * new_node);
// 遍历链表
void traverse_list(stu_t * head,  void (*func)(stu_t *));
// 销毁链表
void clear_list(stu_t *);
// 搜索链表
void search_list(stu_t *, stu_t *, BOOL (*)(stu_t *, stu_t *),void (*func)(stu_t *));
// 逆序链表
void reverse_list(stu_t * head);
// 冒泡排序 单链表
void sort_list_bubble(stu_t * head);


// 遍历打印学生
void print_students(stu_t * head);
// 用名字查找学生, 打印学生信息
void search_students_name(stu_t * head, stu_t * p);
// 用年龄查找学生, 打印学生信息
void search_students_age(stu_t * head, stu_t * p);


int main(int argc, const char * argv[]) {
  
    // 创建链表
    // 首先创建头结点, 头结点一般不存储数据, 只是作为链表的头部
    
    stu_t * head;
    head = create_node();
    
    while (1) {
        printf("请选择操作:1.添加学生 2.打印学生列表 3.清空所有学生 4.根据名字查找一名学生的信息 5.根据年龄查找学生信息 6.逆序所有学生 7.冒泡法根据年龄排序\n");
        int ctr;
        scanf("%d",&ctr);
        if (ctr == 1) {
            // 创建一个新的结点, 存储学生信息, 添加到链表上
            stu_t * new_node = create_node();
            scanf("%s%d%d",new_node->name,&new_node->age,&new_node->score);
            // 添加到链表上
            add_node(head, new_node);
        } else if (ctr == 2) {
            // 遍历链表, 打印每个结点的信息
            print_students(head);
        } else if (ctr == 3) {
            // 清空链表, 删除并释放每个结点
            clear_list(head);
        } else if (ctr == 4) {
            // 搜索学生的信息
            // 根据姓名搜索
            stu_t * p = create_node();
            scanf("%s", p->name);
            // 搜索对应结点
            search_students_name(head, p);
            free(p);
        } else if (ctr == 5) {
            stu_t * p = create_node();
            scanf("%d", &p->age);
            search_students_age(head, p);
            free(p);
        } else if (ctr == 6) {
            // 逆序链表的每个结点
            reverse_list(head);
        } else if (ctr == 7) {
            sort_list_bubble(head);
        }
    }
    
    
    return 0;
}

stu_t * create_node(void)
{
    stu_t * stu = (stu_t *)malloc(sizeof(stu_t));
    if (!stu) {
        perror("malloc");
        exit(-1);
    }
    stu->next = NULL;
    return stu;
}

void add_node(stu_t * head, stu_t * new_node)
{
    //head->next = new_node;
    while (head->next) {
        head = head->next;
    }
    // head 指向尾结点
    head->next = new_node;
    new_node->next = NULL;
    
}

// 打印一个结点
void print_node(stu_t * stu)
{
    printf("姓名: %s 年龄: %d 成绩: %d\n",stu->name, stu->age, stu->score);
}


// 遍历链表
void traverse_list(stu_t * head, void (*func)(stu_t *))
{
    // 让指针依次指向每个结点
    while ((head = head->next)) {
        func(head);
    }
}

// 销毁链表
void clear_list(stu_t * head)
{
    stu_t * p = head->next;
    while (p) {
        stu_t * temp = p->next;
        free(p);
        p = temp;
        
    }
    head->next = NULL;
}

// 遍历打印学生
void print_students(stu_t * head)
{
    traverse_list(head, print_node);
}



// 用名字比较两个结点
BOOL cmp_node_name(stu_t * p1, stu_t * p2)
{
    if (strcmp(p1->name, p2->name) == 0) {
        return YES;
    }
    return NO;
}

// 用年龄比较两个结点
BOOL cmp_node_age(stu_t * p1, stu_t * p2)
{
    return p1->age == p2->age;
}

// 搜索链表
void search_list(stu_t * head, stu_t * p, BOOL (*cmp)(stu_t *, stu_t *), void (*func)(stu_t *))
{
    // p是参照结点
    while ((head = head->next)) {
        if (cmp(head, p) == YES) {
            func(head);
        }
    }
}

// 用名字查找学生, 打印学生信息
void search_students_name(stu_t * head, stu_t * p)
{
    search_list(head, p, cmp_node_name, print_node);
    
}
// 用年龄查找学生, 打印学生信息
void search_students_age(stu_t * head, stu_t * p)
{
    search_list(head, p, cmp_node_age, print_node);
}
// 插入某节点到 index位置
// index 从0开始
void insert_node(stu_t * head, stu_t * new_node, int index)
{
    for (int i = 0; i < index; i++) {
        if (head->next) {
            head = head->next;
        } else {
            return;
        }
    }
    new_node->next = head->next;
    head->next = new_node;
}

// 逆序链表结点
void reverse_list(stu_t * head)
{
    stu_t * p = head->next;
    head->next = NULL;
    while (p) {
        stu_t * tmp = p->next;
        insert_node(head, p, 0);
        p = tmp;
    }
    
}


//// 逆序链表结点
//void reverse_list(stu_t * head)
//{
//    stu_t * p = head->next;
//    head->next = NULL;
//    while (p) {
//        stu_t * tmp = p->next;
//        p->next = head->next;
//        head->next = p;
//        p = tmp;
//    }
//    
//}


void sort_list_bubble(stu_t * head)
{
    stu_t * temp1, * temp2, *p, *q;
    
    for (q = head; q->next != NULL; q = q->next) {
        for (p = q->next; p->next != NULL; p = p->next) {
            // 实际是比较的q->next 和 p->next的大小 如果不符合条件就交换q->next 和 p->next
            
            if (p->next->age > q->next->age) {
                //如果q->next == p 的话 交换q->next 和p->next 就是交换p和p->next
                // 此时 p的位置已经交换 到 原来的 p->next处, 需要交换结束后 让p指向交换钱的位置
                
                if (q->next == p) {
                    temp1 = p->next;
                    p->next = p->next->next;
                    temp1->next = q->next;
                    q->next = temp1;
                    p = temp1;
                } else {
                    // q->next != p->next 的话, 只需要交换q->next结点 和 p->next结点就可以了 p和 q的位置都不会改变
                    temp1 = p->next;
                    temp2 = q->next;
                    p->next = p->next->next;
                    q->next = q->next->next;
                    temp1->next = q->next;
                    q->next = temp1;
                    temp2->next = p->next;
                    p->next = temp2;
                }
            }
        }
    }
    
    print_students(head);
}

