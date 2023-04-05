#include "Mode.h"
#include "API.h"
#include "pic.h"

/*
            软件文件夹->AT32文件夹->Keil工程
项目文件->  
            云端库文件夹...
*/
#define Photo1 gImage_shashashu
//#define Photo2 gImage_mmao

int temp = 0;
//char *temp_po;
//U16 *temp_list;

//float temp_f;
int i;
char User_IO3_flag = 1;

void Main_Init(void);
int main (void)
{
    Main_Init();
    
    while(1)
    {
        Mode_User.Sys_Clock.Get_TIME();
		if(Mode_User.KEY.KEY_State(1) == 0)
		{
			if(Mode_User.KEY.KEY_State(1) == 0)
			{
				i++;
				if(i > 100)
				{i = 1;}
				printf("Key num : %d",i);
			}
			do{
				Mode_User.Delay.Delay_ms(5);
				
			}while(Mode_User.KEY.KEY_State(1) == 0);
		}
		if(CV_UART[3]->Rxd_Received)
		{
			if(CV_UART[3]->DATA.Poit_U8[1] == 'L')
			{
				if(CV_UART[3]->DATA.Poit_U8[6] == 'N')
				{
					Mode_User.LED.LED_SET(1,DISABLE);
				}
				else
				{
					Mode_User.LED.LED_SET(1,ENABLE);
				}
			}
			Destroy(CV_UART[3],sizeof(*CV_UART[3]));
			printf("size uart- %d \r\n",sizeof(*CV_UART[3]));
		}
		if(User_IO3_flag != User_IO3_R())
		{
			User_IO3_flag = User_IO3_R();
			if(User_IO3_flag == 0)
			{
				HORIZONTAL = 1;
			}
			else
			{
				HORIZONTAL = 0;
			}
			Mode_Init.LCD(ENABLE);
			Mode_User.Delay.Delay_ms(10);
			Mode_User.LCD.Show_Picture(0,0,240,240,Photo1);     //Photo
		}
		
		
//		
//		TIM4_PWMx_SetValue(1,14);
//		Mode_User.Delay.Delay_ms(10);
//		
//		TIM4_PWMx_SetValue(1,0);
//		Mode_User.Delay.Delay_ms(100);

    }
}

void Main_Init(void)
{
    system_clock_config();
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
    Mode_Index();
    API_Index();
    
    Mode_Init.Sys_Clock(ENABLE);
    Mode_Init.LCD(ENABLE);
	Mode_Init.UART(DEBUG_OUT,115200,ENABLE);
	Mode_Init.UART(2,115200,ENABLE);
	Mode_Init.LED(ENABLE);
    Mode_Init.KEY(1,ENABLE);
    Mode_Init.User_ADC(ENABLE);
	
	User_GPIO_Init(ENABLE);
	
	Mode_User.LED.LED_SET(1,ENABLE);
	Mode_User.LCD.Show_Picture(0,0,240,240,Photo1);     //Photo
    printf("system_core_clock: %d \r\n",SystemCoreClock);

//    temp_list = Mode_User.USER_ADC.DATA_List;

}
