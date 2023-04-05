#ifndef _BASE_SPI_H__
#define _BASE_SPI_H__

#ifdef DEFAULT
#include "items.h"              //Ĭ�Ϲ���
#endif

#ifndef DEFAULT
#include "User_items.h"         //�������ù��ܣ�һ������ڱ����ļ���User��
#endif

/****************/

/*
            SCK    ->  
                        /----\
            MISO   ->   |SPI1|    <-    NSS/NSS2/NSS3  (Serial) 
                        \----/
            MOSI   ->
    
    ��ΪӲ��SPI/���SPI
    ���SPI��������������ָ������IO��(Ŀǰֻ������)��
    ����ʹ SPI_GPIO ��ͬһ��GPIO�ϣ�A/B/C/D��
    SPI������ͨ�ţ����ӣ����������շ��߼�����Ҫ�жϣ����Ǵӻ���Ҫ��ɵ�˰ɣ����ǲ�ȫ��ģ���
    DMA����ͨģʽ�ǿ���һ���õ�
																					2022.02.26
    SPI��ΨһҪ�󡪡�����Խ��Խ�ã�Ŀǰ���ģ�� 461kHz(8bit)��Ӳ��SPI�ο�-SPI_Speed-���塣
    ���ģʽ -- 4Mhz
    Ӳ����ͨģʽ -- 36Mhz
    Ӳ��DMAģʽ  -- 36Mhz
                                                                                    2022.07.26
    SPI�����ģ�ⷽʽΪsize-8bit,Ӳ��SPI������size-8bit/size-16bit
    SPI�����ģ�ⷽʽΪ�����ض�(0,0)
    SPIһ��ֻ��ʹ��һ����SPI1��������Ӳ�����ܱ�ռ������ѡ��SPI2���Ƽ�ֻʹ��һ��SPI��
                                                                                    2022.08.15
    SPI��Ӳ��NSS����һֱ���͡��������á�
                                                                                    2022.08.19  
    SPI�������������Ӳ��������DMA����ɣ�û��DMA����
                                                                                    2022.10.14                                                                                                                                                                

*/

// ѡ�����ģʽ
#ifdef Exist_SPI
    #define SPI_Software	        //���ξ���Ӳ��ģʽ
    #ifndef SPI_Software
        #define SPI_DMA			    //���ξ�����ͨģʽ
    #endif
    #define HOST_MODE
    #define SPIx   2
#endif


#ifdef SPI_Software                                 //���SPI
#define SPI_MODE_IN    GPIO_MODE_INPUT
#define SPI_MODE_OUT   GPIO_MODE_OUTPUT
#else                                               //Ӳ��SPI
#define SPI_MODE_IN    GPIO_MODE_INPUT
#define SPI_MODE_OUT   GPIO_MODE_MUX
#define SPI_Speed   SPI_MCLK_DIV_8        //16-9MHZ   8-18MHZ     4-36MHZ     2-72MHZ
#define SPI_Size    SPI_FRAME_8BIT                  //8b   16b
#endif
#define SPI_MODE_NSS    GPIO_MODE_OUTPUT

//SPI1
#define SPI1_NSS        GPIO_PINS_4     //(CS)
#define SPI1_SCK        GPIO_PINS_5
#define SPI1_MISO       GPIO_PINS_6
#define SPI1_MOSI       GPIO_PINS_7
#define GPIO_SPI1       GPIOA

//SPI2
#define SPI2_NSS        GPIO_PINS_12    //(CS)
#define SPI2_SCK        GPIO_PINS_13
#define SPI2_MISO       GPIO_PINS_14
#define SPI2_MOSI       GPIO_PINS_15
#define GPIO_SPI2       GPIOB

void SPI_Start_Init(int Set);

//    ������      //

void SPI_CS_Set(char Serial,char State);

void SPI_Send_DATA(const uint16_t DATA);

//    ���ò�      //

void SPI_SET_Addr_SendData(char Serial,uint16_t Addr,uint16_t DATA);
uint16_t SPI_SET_Addr_ReadData(char Serial,uint16_t Addr);

void SPI_Send_String(const void * DATA,int num);



#if (SPIx == 1)
#define SPI_NSS_H()  GPIO_SPI1->scr = SPI1_NSS		//�øߵ�ƽ
#define SPI_NSS_L()  GPIO_SPI1->clr = SPI1_NSS 		//�õ͵�ƽ
#define SPI_SCK_H()  GPIO_SPI1->scr = SPI1_SCK
#define SPI_SCK_L()  GPIO_SPI1->clr = SPI1_SCK 
#define SPI_MOSI_H() GPIO_SPI1->scr = SPI1_MOSI
#define SPI_MOSI_L() GPIO_SPI1->clr = SPI1_MOSI

#define SPI_MISO_R() gpio_input_data_bit_read(GPIO_SPI1,SPI1_MISO)      //��ȡ���ŵ�ƽ

#elif (SPIx == 2)
#define SPI_NSS_H()  GPIO_SPI2->scr = SPI2_NSS		//�øߵ�ƽ
#define SPI_NSS_L()  GPIO_SPI2->clr = SPI2_NSS 		//�õ͵�ƽ
#define SPI_SCK_H()  GPIO_SPI2->scr = SPI2_SCK
#define SPI_SCK_L()  GPIO_SPI2->clr = SPI2_SCK 
#define SPI_MOSI_H() GPIO_SPI2->scr = SPI2_MOSI
#define SPI_MOSI_L() GPIO_SPI2->clr = SPI2_MOSI

#define SPI_MISO_R() gpio_input_data_bit_read(GPIO_SPI2,SPI2_MISO)      //��ȡ���ŵ�ƽ

#endif

#endif
