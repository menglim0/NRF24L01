/******************** (C) COPYRIGHT 2012 野火嵌入式开发工作室 ********************
 * 文件名  ：main.c
 * 描述    ：NRF24L01无线w传输测试实验        
 * 实验平台：野火STM32开发板	
 * 库版本  ：ST3.5.0
 *
 * 作者    ：fire  QQ: 313303034 
 * 博客    ：firestm32.blog.chinaunix.net
**********************************************************************************/
#include "stm32f10x.h"
#include "SPI_NRF.h"
#include "usart1.h"
#include "adc.h"
/* master branch1123*/

u8 status;	//用于判断接收/发送状态
u8 txbuf[8]={0,1,2,3,0,1,2,3};	 //发送缓冲
u8 rxbuf[8];			 //接收缓冲
int i=0;

// ADC1转换的电压值通过MDA方式传到flash
extern __IO u16 ADC_ConvertedValue[2];

// 局部变量，用于存从flash读到的电压值			 
__IO u16 ADC_ConvertedValueLocal[2];        


int main(void)
{
  
   SPI_NRF_Init();
   
  /* 串口1初始化 */
	USART1_Config();

	printf("\r\n 这是一个 NRF24L01 无线传输实验 \r\n");
   	printf("\r\n 这是无线传输 主机端 的反馈信息\r\n");
	printf("\r\n   正在检测NRF与MCU是否正常连接。。。\r\n");

	 /*检测NRF模块与MCU的连接*/
   	status = NRF_Check(); 

	/*判断连接状态*/  
   if(status == SUCCESS)	   
   		 printf("\r\n      NRF与MCU连接成功！\r\n");  
   else	  
   	     printf("\r\n  NRF与MCU连接失败，请重新检查接线。\r\n");

	ADC1_Init();
 while(1)
		{
	   	printf("\r\n 主机端 进入自应答发送模式\r\n"); 
	 	NRF_TX_Mode();
		 ADC_ConvertedValueLocal[0] = ADC_ConvertedValue[0]; // 读取转换的AD值 	
			 ADC_ConvertedValueLocal[1] = ADC_ConvertedValue[1]; // 读取转换的AD值 	
			txbuf[0]= ADC_ConvertedValueLocal[0]%0x100;
			txbuf[1]= ADC_ConvertedValueLocal[0]>>8;
			/*开始发送数据*/	
		status = NRF_Tx_Dat(txbuf);	  
		  
		  /*判断发送状态*/
		  switch(status)
		  	{
		  	  case MAX_RT:
			 	 	printf("\r\n 主机端 没接收到应答信号，发送次数超过限定值，发送失败。 \r\n");
				 break;
	
			  case ERROR:
			  	 	printf("\r\n 未知原因导致发送失败。 \r\n");
				 break;
	
			  case TX_DS:
			  		printf("\r\n 主机端 接收到 从机端 的应答信号，发送成功\r\n");	
							 					
				 break;  								
		  	}			   	
	   
	 	printf("\r\n 主机端 进入接收模式。 \r\n");	
					printf("\r\n ADC_ConvertedValueLocal = %d \r\n",ADC_ConvertedValueLocal[0]);	
		//NRF_RX_Mode();
		Delay(0x8ffff);
				
				
			/*等待接收数据*/
		//status = NRF_Rx_Dat(rxbuf);
	
			/*判断接收状态
			switch(status)
			{
			 case RX_DR:
			 	for(i=0;i<8;i++)
				{					
					printf("\r\n 主机端 接收到 从机端 发送的数据为：%d \r\n",rxbuf[i]);
					txbuf[i] =rxbuf[i];
				}
				  break;
	
			 case ERROR:
				  	printf("\r\n 主机端 接收出错。   \r\n");
				  break;  		
			}*/
		} 

}

/******************* (C) COPYRIGHT 2012 野火嵌入式开发工作室 *****END OF FILE****/

