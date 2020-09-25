#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

typedef struct {
 int loglength;  //栈中元素数量
 int alloclength; //分配栈长度
 int elemsize;  //元素长度
 void * elems;  //栈空间
 void (* freefn)(void *); //释放内存函数
} Stack_t;

typedef Stack_t*   pStack;

void StackNew(Stack * s,int elemsize, void (* freefn)(void *));
void StackDispose(Stack * s);
void StackPush(Stack *s,void * elemaddr);
void StackPop(Stack *s,void * elemaddr);
void StackGrow(Stack *s);
void stringfree(void * elem);

int main(int argc, char* argv[])
{
 const char *friends[] = {"Alan","Bob","Carl","Frank","Mike"};
 Stack stringStack;
 
 //对字符串而言，压入栈的是字符串地址，因此元素长度为sizeof(char*)
 StackNew(&stringStack,sizeof(char*),stringfree);
 for(int i=0;i<5;i++)
 {
  char * copy = strdup(friends[i]); //在heap上分配内存
  StackPush(&stringStack,&copy); 
 }
 char *name;
 for(int i=0;i<5;i++)
 {
  StackPop(&stringStack,&name);
  printf("%s\n",name);
  free(name);  //因为这块内存是strdup分配的，使用完毕后必须free
 }
 StackDispose(&stringStack);
 const int intarr[] = {1,2,3,4,5,6};
 Stack intStack;
 //对int而言，压入栈的是int值本身，因此元素长度为sizeof(int)，且无需freefn
 StackNew(&intStack,sizeof(int),NULL);
 for(int i=0;i<6;i++)
 {
  StackPush(&intStack,(void *)&intarr[i]); 
 }
 int val;
 for(int i=0;i<6;i++)
 {
  StackPop(&intStack,&val);
  printf("%d\n",val);
 }
 StackDispose(&intStack);
 return 0;
}


/*
**初始化栈
*/
void StackNew(Stack * s,int elemsize, void (* freefn)(void *))
{
 s->alloclength = 4;
 s->loglength = 0;
 s->elemsize = elemsize;
 s->freefn = freefn;
 s->elems = malloc(4*elemsize);
 assert(s->elems != NULL);
}
/*
**释放栈
*/
void StackDispose(Stack * s)
{
 if(s->freefn != NULL) {
  for(int i=0;i<s->loglength;i++)
  {
   void * elem = (char *)s->elems + i * s->elemsize;
   s->freefn(elem);
  }
 }
 free(s->elems);
}
/*
**扩展栈
*/
void StackGrow(Stack *s)
{
 s->alloclength *= 2;
 s->elems = realloc(s->elems,s->alloclength*s->elemsize);
 assert(s->elems != NULL);
}
/*
**将元素压入栈
*/
void StackPush(Stack *s,void * elemaddr)
{
 if(s->loglength == s->alloclength)
 {
  StackGrow(s);
 }
 void * target = (char *)s->elems + s->loglength * s->elemsize;
 memcpy(target,elemaddr,s->elemsize);
 s->loglength ++;
}
/*
**弹出栈顶元素
**/
void StackPop(Stack *s,void * elemaddr)
{
 s->loglength --;
 void * source  = (char *)s->elems + s->loglength*s->elemsize;
 memcpy(elemaddr,source,s->elemsize);
}
/*
**自定义字符串free函数
*/
void stringfree(void * elem)
{
 free(*(char **)elem);
}
————————————————
版权声明：本文为CSDN博主「RuiyuanZHOU」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/zhoury/article/details/77899118