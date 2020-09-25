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
    //�������߳� 
    do
    {
        //������ѯ ��� ϵͳ״̬
        int ret = read(alarm->vol_fd);
        //1 mean vol+ down   2 mean vol- down
        if(1 == ret)
        {
            //vol + ����
            alarm->status = ALARM_SYSTEM_NORMAL;
            break;
        }
        sleep(1);
    }
    while(1);
    //���� normal  ״̬ ��ѭ��
    alarm_system_open(alarm);
    //open ����ֻҪ���� �Ѿ���ζ�� ϵͳ�ر���
    alarm_system_destory(alarm);
    //�ͷſռ�
    free(alarm);
    alarm = NULL;
    TRACE("leave the alarm sysstem\n");
    return 0;
}
