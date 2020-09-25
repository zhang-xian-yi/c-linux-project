#include "./types/SList.h"

int main(int argc,char* argv[])
{
    D_TRACE("start main\n");
    pSList plist = slist_create(5);
    D_TRACE("create plist succ\n");
    slist_destory(plist);
    D_TRACE("destory plist suncc\n");
    return 0;
}