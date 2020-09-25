#include "./standard_types/StrStack.h"

int main(int argc, char* argv[])
{
    const char *friends[] = {"Alan","Bob","Carl","Frank","Mike"};
    StrStack_t stringStack;

    //for string to say£¬push string address£¬so the elem length  = sizeof(char*)
    strstack_create(&stringStack,sizeof(char*),string_free);
    for(int i=0;i<5;i++)
    {
        char * copy = strdup(friends[i]);  //malloc in heap
        strstack_push(&stringStack,&copy);
    }
    char *name;
    for(int i=0;i<5;i++)
    {
        strstack_pop(&stringStack,&name);
        D_TRACE("%s\n",name);
        free(name);    //strdup malloc memery  must free
    }
    strstack_destory(&stringStack);
    const int intarr[] = {1,2,3,4,5,6};
    StrStack_t intStack;
    //push in stack  elem is  int value`self  so  not need freefn
    strstack_create(&intStack,sizeof(int),NULL);
    for(int i=0;i<6;i++)
    {
        strstack_push(&intStack,(void *)&intarr[i]);
    }
    
    int val;
    for(int i=0;i<6;i++)
    {
        strstack_pop(&intStack,&val);
        D_TRACE("%d\n",val);
    }
    strstack_destory(&intStack);
    return 0;
}

