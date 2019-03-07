/******************** (C) COPYRIGHT 2012 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���  ��main.c
 * ����    ��NRF24L01����w�������ʵ��        
 * ʵ��ƽ̨��Ұ��STM32������	
 * ��汾  ��ST3.5.0
 *
 * ����    ��fire  QQ: 313303034 
 * ����    ��firestm32.blog.chinaunix.net
**********************************************************************************/
#include "stm32f10x.h"
#include "SPI_NRF.h"
#include "usart1.h"
#include "adc.h"
/* master branch1123*/

u8 status;	//�����жϽ���/����״̬
u8 txbuf[8]={0,1,2,3,0,1,2,3};	 //���ͻ���
u8 rxbuf[8];			 //���ջ���
int i=0;

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����flash
extern __IO u16 ADC_ConvertedValue[2];

// �ֲ����������ڴ��flash�����ĵ�ѹֵ			 
__IO u16 ADC_ConvertedValueLocal[2];        


int main(void)
{
  
   SPI_NRF_Init();
   
  /* ����1��ʼ�� */
	USART1_Config();

	printf("\r\n ����һ�� NRF24L01 ���ߴ���ʵ�� \r\n");
   	printf("\r\n �������ߴ��� ������ �ķ�����Ϣ\r\n");
	printf("\r\n   ���ڼ��NRF��MCU�Ƿ��������ӡ�����\r\n");

	 /*���NRFģ����MCU������*/
   	status = NRF_Check(); 

	/*�ж�����״̬*/  
   if(status == SUCCESS)	   
   		 printf("\r\n      NRF��MCU���ӳɹ���\r\n");  
   else	  
   	     printf("\r\n  NRF��MCU����ʧ�ܣ������¼����ߡ�\r\n");

	ADC1_Init();
 while(1)
		{
	   	printf("\r\n ������ ������Ӧ����ģʽ\r\n"); 
	 	NRF_TX_Mode();
		 ADC_ConvertedValueLocal[0] = ADC_ConvertedValue[0]; // ��ȡת����ADֵ 	
			 ADC_ConvertedValueLocal[1] = ADC_ConvertedValue[1]; // ��ȡת����ADֵ 	
			txbuf[0]= ADC_ConvertedValueLocal[0]%0x100;
			txbuf[1]= ADC_ConvertedValueLocal[0]>>8;
			/*��ʼ��������*/	
		status = NRF_Tx_Dat(txbuf);	  
		  
		  /*�жϷ���״̬*/
		  switch(status)
		  	{
		  	  case MAX_RT:
			 	 	printf("\r\n ������ û���յ�Ӧ���źţ����ʹ��������޶�ֵ������ʧ�ܡ� \r\n");
				 break;
	
			  case ERROR:
			  	 	printf("\r\n δ֪ԭ���·���ʧ�ܡ� \r\n");
				 break;
	
			  case TX_DS:
			  		printf("\r\n ������ ���յ� �ӻ��� ��Ӧ���źţ����ͳɹ��|\r\n");	
							 					
				 break;  								
		  	}			   	
	   
	 	printf("\r\n ������ �������ģʽ�� \r\n");	
					printf("\r\n ADC_ConvertedValueLocal = %d \r\n",ADC_ConvertedValueLocal[0]);	
		//NRF_RX_Mode();
		Delay(0x8ffff);
				
				
			/*�ȴ���������*/
		//status = NRF_Rx_Dat(rxbuf);
	
			/*�жϽ���״̬
			switch(status)
			{
			 case RX_DR:
			 	for(i=0;i<8;i++)
				{					
					printf("\r\n ������ ���յ� �ӻ��� ���͵�����Ϊ��%d \r\n",rxbuf[i]);
					txbuf[i] =rxbuf[i];
				}
				  break;
	
			 case ERROR:
				  	printf("\r\n ������ ���ճ���   \r\n");
				  break;  		
			}*/
		} 

}

/******************* (C) COPYRIGHT 2012 Ұ��Ƕ��ʽ���������� *****END OF FILE****/

