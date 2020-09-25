#include "./types/SList.h"

int main(int argc,char* argv[])
{
    pSList plist = slist_create(5);

    slist_destory(plist);
    return 0;
}