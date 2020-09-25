#include "./standard_types/Stack.h"

int main(int argc, char* argv[])
{
    const char *friends[] = {"Alan","Bob","Carl","Frank","Mike"};
    Stack_t stringStack;

    //for string to say£¬push string address£¬so the elem length  = sizeof(char*)
    stack_create(&stringStack,sizeof(char*),string_free);
    for(int i=0;i<5;i++)
    {
        char * copy = strdup(friends[i]);  //malloc in heap
        stack_push(&stringStack,&copy);
    }
    char *name;
    for(int i=0;i<5;i++)
    {
        stack_pop(&stringStack,&name);
        D_TRACE("%s\n",name);
        free(name);    //strdup malloc memery  must free
    }
    stack_destory(&stringStack);
    const int intarr[] = {1,2,3,4,5,6};
    Stack_t intStack;
    //push in stack  elem is  int value`self  so  not need freefn
    stack_create(&intStack,sizeof(int),NULL);
    for(int i=0;i<6;i++)
    {
        stack_push(&intStack,(void *)&intarr[i]);
    }
    
    int val;
    for(int i=0;i<6;i++)
    {
        stack_pop(&intStack,&val);
        D_TRACE("%d\n",val);
    }
    stack_destory(&intStack);
    return 0;
}

