#include "ledctl.h"
#include "AlarmSystem.h"
#include "alarmctl.h"
#include "adcctl.h"

#include <fcntl.h>

/*****************************************************************************
*   Prototype    : alarm_system_init
*   Description  : init the struct alarm system 
*   Input        : palarm temp
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/12/19
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
int alarm_system_init( palarm temp)
{
    temp->led_fd = getLedCtlFd();
    temp->adc_fd = getADCfd();
    temp->alarm_fd = getAlarmFd();
    temp->status = ALARM_SYSTEM_COLSE;
    temp->uart_fd = getuartfd();
    
    set_opt(temp->uart_fd,115200,8,'N',1);
    //vol �豸
    char *vol_node = "/dev/zxy_vol_ctl";
    if((temp->vol_fd = open(vol_node, O_RDWR|O_NOCTTY))<0){
		TRACE("open %s is failed",vol_node);
        return FAILED;
	}
    return SUCCESS;
}

/*****************************************************************************
*   Prototype    : alarm_system_destory
*   Description  : destory the alarm_system
*   Input        : palarm temp
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/12/19
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
int alarm_system_destory( palarm temp )
{
    close(temp->led_fd);
    close(temp->alarm_fd);
    close(temp->uart_fd);
    close(temp->vol_fd);
    close(temp->adc_fd);
    temp->status = ALARM_SYSTEM_COLSE;
}

/*****************************************************************************
*   Prototype    : alarm_system_open
*   Description  : open the alarm system
*   Input        : palarm temp  
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2019/12/19
*           Author       : zhangxianyi
*           Modification : Created function
*
*****************************************************************************/
int alarm_system_open(palarm temp)
{
    while(1)
    {
        //�� vol  ���������Ƶ���Ӧ ������ֱ��ָ���� CLOSE 
        if(2 ==read(temp->vol_fd))
        {
            led2_off(temp->led_fd);
            led3_off(temp->led_fd);
            BEEP_ctl(temp->alarm_fd, ALARM_CLOSE);
            temp->status = ALARM_SYSTEM_COLSE;
            write_UART1(temp->uart_fd, "����ϵͳ�Ѿ��ر�\n", 1);
            break;
        }
        //if temp alarm system == normal
        led2_shine(temp->led_fd);
        led3_shine(temp->led_fd);
        BEEP_ctl(temp->alarm_fd, ALARM_CLOSE);
        while ( ALARM_SYSTEM_NORMAL == temp->status )
        {
            // normal ״̬ �ſ��Թر�
            if(2 ==read(temp->vol_fd))
            {
                led2_off(temp->led_fd);
                led3_off(temp->led_fd);
                BEEP_ctl(temp->alarm_fd, ALARM_CLOSE);
                temp->status = ALARM_SYSTEM_COLSE;
                write_UART1(temp->uart_fd, "����ϵͳ�Ѿ��ر�\n", 1);
                return 0;
            }   
        
            int adc_value = getADCValue(temp->adc_fd);
            //adc value 
            TRACE("normal  adc_value = %d\n",adc_value);
            if(adc_value > 6000)
            {
                //change the status
                temp->status = ALARM_SYSTEM_EXCEPTION;
                break;
            }
            sleep(1);
        }
        //if the alarm system == exception
        //����������
        write_UART1(temp->uart_fd, "���� ����\n", 1);
        BEEP_ctl(temp->alarm_fd, ALARM_OPEN);
        while(ALARM_SYSTEM_EXCEPTION == temp->status)
        {
            //ѭ����˸
            cycleShineLed(temp->led_fd);
            //��ȡadc ��ֵ
            int adc_value = getADCValue(temp->adc_fd);
            //adc value 
            TRACE("exception adc_value = %d\n",adc_value);
            if(adc_value < 6000)
            {
                temp->status = ALARM_SYSTEM_NORMAL;
                break;
            }
        }
        write_UART1(temp->uart_fd, "������� �������\n", 3);
    }
}

    














