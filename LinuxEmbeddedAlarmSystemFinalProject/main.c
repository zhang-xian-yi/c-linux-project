#include "AlarmSystem.h"

int main(int argc,char* argv[])
{
    TRACE("enter the aralm system\n");
    palarm alarm = (palarm)Malloc(sizeof(alarm_t));
    if(alarm_system_init(alarm) == FAILED)
    {
        TRACE("init the alarm system failed");
        return 0;
    }
    //阻赛主线程 
    do
    {
        //不断轮询 检查 系统状态
        int ret = read(alarm->vol_fd);
        //1 mean vol+ down   2 mean vol- down
        if(1 == ret)
        {
            //vol + 按下
            alarm->status = ALARM_SYSTEM_NORMAL;
            break;
        }
        sleep(1);
    }
    while(1);
    //进入 normal  状态 死循环
    alarm_system_open(alarm);
    //open 函数只要返回 已经意味着 系统关闭了
    alarm_system_destory(alarm);
    //释放空间
    free(alarm);
    alarm = NULL;
    TRACE("leave the alarm sysstem\n");
    return 0;
}
