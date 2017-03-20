
#include "SPI_By_IO.h"
//#include "usart.h"
#include "config.h"

void SPI_By_IO_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(SPI_GPIO_Port_RCC, ENABLE);	

    //SPI_CS
    GPIO_InitStructure.GPIO_Pin = SPI_CS_GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(SPI_CS_GPIO_Port, &GPIO_InitStructure);
    SPI_CS_1();											//cs³õÊ¼µçÆ½Îª¸ß

    //SPI_CLK	
    GPIO_InitStructure.GPIO_Pin = SPI_CLK_GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_Init(SPI_CLK_GPIO_Port, &GPIO_InitStructure);
    SPI_CLK_1();										//CLK³õÊ¼µçÆ½ÎªµÍ

    //SPI_MISO	
    GPIO_InitStructure.GPIO_Pin = SPI_MISO_GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SPI_MISO_GPIO_Port, &GPIO_InitStructure);

    //SPI_MOSI	
    GPIO_InitStructure.GPIO_Pin = SPI_MOSI_GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_Init(SPI_MOSI_GPIO_Port, &GPIO_InitStructure);
    SPI_MOSI_1();									//MOSI³õÊ¼µçÆ½Îª¸ß
		
		//AD_SYNC	
//    GPIO_InitStructure.GPIO_Pin = AD7175_SYNC_Pin;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_Init(AD7175_SYNC_Port, &GPIO_InitStructure);
//		//AD_SYNC_0();									//SYNCµÍµçÆ½²»Æô¶¯ÐÂµÄ×ª»»
//		AD_SYNC_1();		
}
void Reset64CLK(void)
{
		u8 i=0;
		for(i=0;i<65;i++)
	{
		SPI_CLK_0();					//³õÊ¼×´Ì¬Ê±ÖÓÎª¸ßµçÆ½
		SPI_CLK_Delay();
		SPI_CLK_1();					//³õÊ¼×´Ì¬Ê±ÖÓÎª¸ßµçÆ½
		SPI_CLK_Delay();
	}
}
void SPI_Send_One_Byte(u8 data)
{		u8 i=0;
    SPI_CS_0();
    SPI_CLK_Delay();
		for(i=0;i<8;i++)
		{
			SPI_CLK_1();					//³õÊ¼×´Ì¬Ê±ÖÓÎª¸ßµçÆ½
			SPI_CLK_Delay();
			
			SPI_CLK_0();					//CLKÏÂ½µÑØ£¬Êý¾ÝÏßÂ·¿É¸Ä±ä×´Ì¬
			if( data & 0x80 )			//MSB_First
				{	SPI_MOSI_1();}
			else {	SPI_MOSI_0();}
			SPI_CLK_Delay();

			SPI_CLK_1();					//ÉÏÉýÑØ£¬Êý¾Ý´«Êä¸ø´Ó»ú
			data=data<<1;					//´ý·¢ËÍÊý¾Ý×óÒÆ£¬ÒÔ·¢ËÍÏÂÒ»Î»Êý¾Ý
		}
    SPI_CLK_Delay();			//Ò»¸ö×Ö½ÚÊý¾Ý·¢ËÍÍê±Ï£¬×öÑÓÊ±
    SPI_CS_0();
    SPI_CLK_Delay();
}
//u8 SPI_Read_One_Byte(void)
//{
//		u8 i=0;
//		u8 dat=0;
//		SPI_CLK_1();	
//		SPI_CLK_Delay();
//	
//		for(i=0;i<8;i++)
//		{
//			SPI_CLK_0();
//			dat=dat<<1;						//Êý¾Ý»º³å±äÁ¿×óÒÆ£¬ÒÔ×¼±¸½ÓÊÜÏÂÒ»bitÊý¾Ý
//							//³õÊ¼×´Ì¬¾ùÎª¸ßµçÆ½
//			
//			
//								//CLKÏÂ½µÑØ£¬´Ó»ú¿ÉÒÔ¸Ä±äÊý¾ÝÏßÂ·µçÆ½
//			SPI_CLK_Delay();			//µÍµçÆ½±£³Ö
//			
//					//ÉÏÉýÑØ£¬Êý¾Ý´«Êä¸ø´Ó»ú
//		
//			if( Read_SPI_MISO()	)	//Èô¶ÁÈ¡µ½Êý¾ÝÎª1
//				{	dat= dat|0x01;}		//´æ´
//				SPI_CLK_1();	
//		}	
//			
//		
//		return	dat;						//·µ»Ø½ÓÊÕµ½µÄ½á¹ûÊý¾Ý
//}
u8 SPI_Read_One_Byte(void)
{
    SPI_CS_0();
    SPI_CLK_Delay();
		u8 i=0;
		u8 dat=0;

		for(i=0;i<8;i++)
		{
			dat=dat<<1;						//Êý¾Ý»º³å±äÁ¿×óÒÆ£¬ÒÔ×¼±¸½ÓÊÜÏÂÒ»bitÊý¾Ý
			SPI_CLK_1();					//³õÊ¼×´Ì¬¾ùÎª¸ßµçÆ½
			SPI_CLK_Delay();
			
			SPI_CLK_0();					//CLKÏÂ½µÑØ£¬´Ó»ú¿ÉÒÔ¸Ä±äÊý¾ÝÏßÂ·µçÆ½
			SPI_CLK_Delay();			//µÍµçÆ½±£³Ö
			
			SPI_CLK_1();					//ÉÏÉýÑØ£¬Êý¾Ý´«Êä¸ø´Ó»ú
			SPI_CLK_Delay();			//×öÑÓÊ±ºóÔÙ¶ÁÈ¡Êý¾Ý
			if( Read_SPI_MISO()	)	//Èô¶ÁÈ¡µ½Êý¾ÝÎª1
				{	dat= dat|0x01;}		//´æ´¢
		}
			SPI_CLK_Delay();
        SPI_CS_1();
		return	dat;						//·µ»Ø½ÓÊÕµ½µÄ½á¹ûÊý¾Ý
}


