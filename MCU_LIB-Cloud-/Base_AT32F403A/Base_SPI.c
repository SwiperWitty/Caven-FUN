#include "Base_SPI.h"

#ifdef Exist_SPI

    #if (SPIx == 1)
        spi_type *Temp_SPI = SPI1;
        #define SPI_Tx_DMA_Channel     DMA1_CHANNEL3
    #elif (SPIx == 2)
        spi_type *Temp_SPI = SPI2;
        #define SPI_Tx_DMA_Channel     DMA1_CHANNEL5
    #endif
#endif

__IO uint16_t SPI_complete_flag = 1;

void SPI1_GPIO_Init(int Set)
{
#ifdef Exist_SPI
    gpio_init_type gpio_init_struct;
    gpio_default_para_init(&gpio_init_struct);
    if (Set)
    {
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK,TRUE);
        crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_pins = SPI1_SCK | SPI1_MOSI;
        gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
        gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_mode = SPI_MODE_OUT;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init(GPIO_SPI1, &gpio_init_struct);
        
        gpio_init_struct.gpio_pins = SPI1_NSS;
        gpio_init_struct.gpio_mode = SPI_MODE_NSS;                //NSS-���ģʽ�������
        gpio_init(GPIO_SPI1, &gpio_init_struct);
        
        gpio_init_struct.gpio_pins = SPI1_MISO;
        gpio_init_struct.gpio_mode = SPI_MODE_IN;
        gpio_init_struct.gpio_pull = GPIO_PULL_UP;
        gpio_init(GPIO_SPI1, &gpio_init_struct);

    }
    else
    {
        gpio_init_struct.gpio_pins = SPI1_NSS|SPI1_SCK|SPI1_MOSI|SPI1_MISO;
        gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init(GPIO_SPI1, &gpio_init_struct);
    }
#endif
}

void SPI2_GPIO_Init(int Set)
{
#ifdef Exist_SPI
    gpio_init_type gpio_init_struct;
    gpio_default_para_init(&gpio_init_struct);
    if (Set)
    {
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK,TRUE);
        crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
        
        gpio_init_struct.gpio_pins = SPI2_NSS;                  //NSS-���ģʽ�������
        gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
        gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_mode = SPI_MODE_NSS;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init(GPIO_SPI2, &gpio_init_struct);
        
        gpio_init_struct.gpio_pins = SPI2_SCK | SPI2_MOSI;      //SCK��MOSI���ģʽ�����ã�
        gpio_init_struct.gpio_mode = SPI_MODE_OUT;
        gpio_init(GPIO_SPI2, &gpio_init_struct);
        
        gpio_init_struct.gpio_pins = SPI2_MISO;
        gpio_init_struct.gpio_mode = SPI_MODE_IN;
        gpio_init_struct.gpio_pull = GPIO_PULL_UP;
        gpio_init(GPIO_SPI2, &gpio_init_struct);

    }
    else
    {
        gpio_init_struct.gpio_pins = SPI2_NSS|SPI2_SCK|SPI2_MOSI|SPI2_MISO;
        gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init(GPIO_SPI2, &gpio_init_struct);
    }
#endif
}

void SPI1_DMA_Config (const void *DMA_Buffer,int BufferSize)
{
#ifdef Exist_SPI
    dma_init_type dma_init_struct;
    dma_default_para_init(&dma_init_struct);        
    dma_init_struct.buffer_size = BufferSize;       //����
    dma_init_struct.memory_base_addr = (uint32_t)DMA_Buffer;
    dma_init_struct.peripheral_base_addr = (uint32_t)&SPI1->dt;
    dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;       //�ڴ浽����
    dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
    dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
    dma_init_struct.memory_inc_enable = TRUE;                       //�ڴ��ַ�Ƿ��Զ�����
    dma_init_struct.peripheral_inc_enable = FALSE;                  //�����ַ�Ƿ��Զ�����
    dma_init_struct.priority = DMA_PRIORITY_MEDIUM;                 //�������ȼ�--��
    dma_init_struct.loop_mode_enable = FALSE;                       //��ѭ��ģʽ
    dma_init(SPI_Tx_DMA_Channel, &dma_init_struct);
#endif

}
void SPI2_DMA_Config (const void *DMA_Buffer,int BufferSize)
{
#ifdef Exist_SPI
    dma_init_type dma_init_struct;
    dma_default_para_init(&dma_init_struct);        
    dma_init_struct.buffer_size = BufferSize;       //����
    dma_init_struct.memory_base_addr = (uint32_t)DMA_Buffer;
    dma_init_struct.peripheral_base_addr = (uint32_t)&SPI2->dt;
    dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;       //�ڴ浽����
    dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
    dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
    dma_init_struct.memory_inc_enable = TRUE;                       //�ڴ��ַ�Ƿ��Զ�����
    dma_init_struct.peripheral_inc_enable = FALSE;                  //�����ַ�Ƿ��Զ�����
    dma_init_struct.priority = DMA_PRIORITY_MEDIUM;                 //�������ȼ�--��
    dma_init_struct.loop_mode_enable = FALSE;                       //��ѭ��ģʽ
    dma_init(SPI_Tx_DMA_Channel, &dma_init_struct);
#endif

}

void SPI_Start_Init(int Set)
{
#ifdef Exist_SPI
    confirm_state set = FALSE;
    if (Set)
        set = TRUE;
    #if (SPIx == 1)
        SPI1_GPIO_Init(set);
    #elif (SPIx == 2)
        SPI2_GPIO_Init(set);
    #endif
    SPI_CS_Set(1,0);
    
    #ifndef SPI_Software
    spi_i2s_reset(Temp_SPI);
    spi_init_type spi_init_struct;
    spi_default_para_init(&spi_init_struct);
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_0);
        #if (SPIx == 1)
            crm_periph_clock_enable(CRM_SPI1_PERIPH_CLOCK, TRUE);
            nvic_irq_enable(SPI1_IRQn, 1, 0);                       //SPI�ж������� ����NSS��
        #elif (SPIx == 2)
            crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, set);
            nvic_irq_enable(SPI2_IRQn, 1, 0);
        #endif
    
        #ifdef HOST_MODE
        spi_init_struct.master_slave_mode =SPI_MODE_MASTER;
        #else
        spi_init_struct.master_slave_mode =SPI_MODE_SLAVE;
        #endif
        spi_init_struct.frame_bit_num = SPI_Size;
        spi_init_struct.mclk_freq_division = SPI_Speed;
        spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
        spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH;           //��ʱ SCK״̬
        spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;                //�������ôӻ���
        spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
        spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
        spi_init(Temp_SPI, &spi_init_struct);

        #ifdef SPI_DMA
        spi_i2s_dma_transmitter_enable (Temp_SPI, TRUE);        //���͵�DMA
        crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);

        dma_reset(SPI_Tx_DMA_Channel);                          //ȡ������
        // SPI2_DMA_Config (0,SPI_BufferSize);                     //��������
        dma_channel_enable(SPI_Tx_DMA_Channel,FALSE);
        #endif
        
        spi_i2s_interrupt_enable(Temp_SPI, SPI_I2S_TDBE_INT, FALSE);    //�ȱ� <FALSE>
        spi_enable(Temp_SPI, set);
        
    #else

    #endif
#endif
}

#ifdef Exist_SPI
static void SPI_Delay (int time)
{
    if (MCU_SYS_Freq >= 72000000)
    {
        volatile int temp;
        for (int i = 0; i < time; ++i)
        {
            temp = 100;            //SET
            while((temp--) > 0);
        }
    }
    else
        while((time--) > 0);
}
#endif

void SPI_CS_Set(char Serial,char State)
{
#ifdef Exist_SPI
    switch (Serial)
    {
        case 0:
            SPI_NSS_H();     //  High
        break;
        case 1:
            if (State) {
                SPI_NSS_L();      //  Low
            }
            else {
                SPI_NSS_H();     //  High
            }
            break;
        case 2:

            break;
        default:
            break;
    }
#endif

}

//��ͨ\��� ���ͣ�ֻ��SCLK��MOSI���� NSS
void SPI_Send_DATA(const uint16_t DATA)     
{
    /*
     * д��־λ
     * д����
     * ��æλ
     */
#ifdef Exist_SPI
    #ifdef SPI_Software
    char temp;
    for (int i = 0; i < 8; i++)
    {
        SPI_SCK_L();           //Ԥ��Down��
        temp = (DATA << i) & 0x80;
        if (temp)
            SPI_MOSI_H();      //����1
        else
            SPI_MOSI_L();      //����0
        SPI_SCK_H();           //���Down��
    }
    SPI_MOSI_H();
    //    SPI_SCK_H();              // 0 / 0����Ҫ����
    #else

//    spi_i2s_data_transmit(Temp_SPI, DATA);
//    while(spi_i2s_flag_get(Temp_SPI,SPI_I2S_BF_FLAG) != RESET);   //SPIæ�ͻ� = 1����æ����0
    
    while(spi_i2s_flag_get(Temp_SPI,SPI_I2S_TDBE_FLAG) == RESET);   //���ͻ���������
    spi_i2s_data_transmit(Temp_SPI, DATA);
    while(spi_i2s_flag_get(Temp_SPI,SPI_I2S_BF_FLAG) != RESET);   //SPIæ�ͻ� = 1����æ����0
    
    #endif
	
#endif
}


//    ���ò�      //

//�������ͣ�Soft/Hard
void SPI_Send_String(const void * DATA,int num)                 //������һ��ָ�룬�ڷ�������;�У���Ҫ��Ŀ��ָ��ı䣡
{
#ifdef Exist_SPI
    #ifdef  SPI_DMA 
    while(spi_i2s_flag_get(Temp_SPI,SPI_I2S_BF_FLAG) == 1);         //���Կ�ʼ����
    while(SPI_complete_flag == 0);                                  //��SPI�ж�
    SPI_complete_flag = 0;
    
    dma_channel_enable(SPI_Tx_DMA_Channel,FALSE);
    SPI_CS_Set(1,TRUE);                 //��ʼƬѡ
        #if (SPIx == 1)
        // dma_flag_clear(DMA1_FDT3_FLAG);
        SPI1_DMA_Config (DATA,num);                                 //��������
        #elif (SPIx == 2)
        // dma_flag_clear(DMA1_FDT5_FLAG);
        SPI2_DMA_Config (DATA,num);                                 //��������
        #endif 
                                                         
        dma_channel_enable(SPI_Tx_DMA_Channel,TRUE);                        //��ʼDMA
        spi_i2s_interrupt_enable(Temp_SPI, SPI_I2S_TDBE_INT, TRUE);         //��SPI�ж�
    
    #else
    SPI_CS_Set(1,TRUE);                 //��ʼƬѡ
    for (int i = 0; i < num; i++)
    {
        SPI_Send_DATA(*((uint8_t *)DATA + i));
    }
        #ifdef SPI_Software
    SPI_CS_Set(1,0);                    //��
        #else
    spi_i2s_interrupt_enable(Temp_SPI, SPI_I2S_TDBE_INT, TRUE);        //���жϣ������Լ�����Ƭѡ
        #endif
    #endif
    
#endif
}

void SPI_SET_Addr_SendData(char Serial,uint16_t Addr,uint16_t DATA)
{
// Addr &= 0xBFFF;
#ifdef Exist_SPI
    SPI_CS_Set(Serial,1);      //SPI��ʼ��Ƭѡ��
    SPI_Delay (1);

    SPI_Send_DATA(Addr);
//    SPI_Delay (1);
    SPI_Send_DATA(DATA);

    SPI_Delay (1);
    
#endif
}

uint16_t SPI_SET_Addr_ReadData(char Serial,uint16_t Addr)
{
    /*
     * ���ܶ�
     * ��
     */
    uint16_t temp = 0;
    // Addr &= 0xBFFF;
#ifdef Exist_SPI
    #ifdef SPI_Software

    #else
    spi_type *Temp_SPI;
        #if (SPIx == 1)
        Temp_SPI = SPI1;
        #elif (SPIx == 2)
        Temp_SPI = SPI2;
        #endif

    SPI_CS_Set(Serial,TRUE);      //SPI��ʼ��Ƭѡ��
    SPI_Delay (1);
    
    SPI_Send_DATA(Addr);

    spi_i2s_data_receive(Temp_SPI);             //1
    SPI_Send_DATA(0);
    while(spi_i2s_flag_get(Temp_SPI,SPI_I2S_RDBF_FLAG) == RESET);
    temp = spi_i2s_data_receive(Temp_SPI);      //2

    SPI_Send_DATA(0);
    while(spi_i2s_flag_get(Temp_SPI,SPI_I2S_RDBF_FLAG) == RESET);
    temp = spi_i2s_data_receive(Temp_SPI);      //3

    SPI_Delay (1);
    
    #endif
#endif
    return temp;
}

#ifdef Exist_SPI
void SPI1_IRQHandler(void)
{
    if (spi_i2s_flag_get(SPI1, SPI_I2S_TDBE_FLAG) == 1)
    {
        if(spi_i2s_flag_get(SPI1,SPI_I2S_BF_FLAG) == 0)     //busy
        {
            spi_i2s_interrupt_enable(SPI1, SPI_I2S_TDBE_INT, FALSE);
            SPI_CS_Set(1,FALSE);          //ȡ��Ƭѡ
            SPI_complete_flag = 1;
//            printf("SPI ok \r\n");
        }
    }
}

 void SPI2_IRQHandler(void)
{
    if (spi_i2s_flag_get(SPI2, SPI_I2S_TDBE_FLAG) == 1)
    {
        if(spi_i2s_flag_get(SPI2,SPI_I2S_BF_FLAG) == 0)
        {
//            spi_i2s_interrupt_enable(SPI2, SPI_I2S_TDBE_INT, FALSE);    //���ж�
//            SPI_CS_Set(1,FALSE);          //ȡ��Ƭѡ
//            SPI_complete_flag = 1;
        }
    }
}
#endif

