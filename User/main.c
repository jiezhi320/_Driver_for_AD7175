
#include "main.h"

#include "config.h"
#include "blink.h"


void  Initialize_Device(void)
{
    Uart1Init(115200);
    SPI_By_IO_GPIO_Init();
}

int main(void)
{
    uint8_t counter = 0;
    int32_t temp      = 0;
    long timeout  = 0x00FFFFFF;
    int32_t sample   = 0;
    float voltage = 0;

    SystemInit (); //系统初始化 调用官方库
    SysTick_Config(72000);//Set SysTick to 1ms   SystemCoreClock=8MHZ,72000000/1000=72000  调用官方库

    GPIO_Configuration();
    NVIC_Configuration();
    Delayms(5);
    Initialize_Device();    
    
    temp = AD7175_SetChannels_DefaultMode();
    if(temp < 0)
    {
        printf("AD7175 Error.\r\n");
    }
    else
    {
        printf("\r\n");
        printf("AD7175 Init to Default Model Succeed.\r\n");
        Delayms(100);
   
        AD7175_ReadRegister(&AD7175_regs[ID_st_reg]);       //??ADC_ID
        printf("ADC7175_ID = %04X\r\n",AD7175_regs[ID_st_reg].value);        
    }  
    while(1)
    {
        //UART1_Operation_function();
        blink();
        counter++;
        if(counter == 5)
        {
            temp = AD7175_WaitForReady(timeout);
            if(temp < 0)
            {
                printf("AD7175 Read Register Error, counter 1.\r\n");
            }
            temp = AD7175_ReadRegister(&AD7175_regs[Data_Register]);        //read Data register
            if(temp < 0)
            {
                printf("AD7175 Read Register Error, counter 2.\r\n");
            }
            printf("CH_1 RegValue is: %04X\t", AD7175_regs[CH_Map_1].value);
            printf("CH_1 Value is: %d,\t",AD7175_regs[Data_Register].value);

            sample = AD7175_regs[Data_Register].value;
            voltage = ((float)sample * 2.5) / ((long)1 << 24);
            printf("Channel1 Voltage is: %2.6f V\r\n", voltage);

            //voltage = (float)(2.5*AD7175_regs[Data_Register].value)/16777216.0;
            
            //printf("CH_Map_2 Register Value is: %04X\r\n", AD7175_regs[CH_Map_2].value);
        }
        
    }  
}
