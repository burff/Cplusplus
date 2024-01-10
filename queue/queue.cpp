#include <stdio.h>
#include <stdlib.h>

/*当使用C语言时，Node的使用需要添加struct，如struct Node* prev;*/
/*当使用C++语言时，只需要使用Node就可以，说明了C++在struct上省略了*/
typedef struct Node
{
    int data;
    Node* prev;  
    Node* next;
} Node;

struct LinkQueue
{
    Node* head;
    Node* end;
};

void InitQueue(LinkQueue *&q)
{
    q = (LinkQueue*)malloc(sizeof(LinkQueue));
    q->head = q->end = NULL;
}



