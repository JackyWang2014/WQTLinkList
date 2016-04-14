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




// 遍历打印学生
void print_students(stu_t * head);
// 用名字查找学生, 打印学生信息
void search_students_name(stu_t * head, stu_t * p);

int main(int argc, const char * argv[]) {
  
    // 创建链表
    // 首先创建头结点, 头结点一般不存储数据, 只是作为链表的头部
    
    stu_t * head;
    head = create_node();
    
    while (1) {
        printf("请选择操作:1.添加学生 2.打印学生列表 3.清空所有学生 4 根据名字查找一名学生的信息\n");
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
