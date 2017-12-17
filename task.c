/*
 * task.c
 *
 *  Created on: Apr 10, 2016
 *      Author: hendri
 */
#include "task.h"
#include "stm32f4xx.h"
#include "device.h"
#include "uart.h"
#include "lcd.h"

//Private constant-----------------------
#define LAMA_MERAH	5
#define LAMA_KUNING	2
#define LAMA_HIJAU	4
#define lama_detik 4
#define lama_advance 8
#define lama_backlight 12
//#define lama_normal 4

#define MerahON   HAL_GPIO_WritePin(ld4_GPIO_Port,ld4_Pin,GPIO_PIN_SET)
#define MerahOFF  HAL_GPIO_WritePin(ld4_GPIO_Port,ld4_Pin,GPIO_PIN_RESET)

#define KuningON  HAL_GPIO_WritePin(ld5_GPIO_Port,ld5_Pin,GPIO_PIN_SET)
#define KuningOFF HAL_GPIO_WritePin(ld5_GPIO_Port,ld5_Pin,GPIO_PIN_RESET)

#define HijauON	   HAL_GPIO_WritePin(ld6_GPIO_Port,ld6_Pin,GPIO_PIN_SET)
#define HijauOFF  HAL_GPIO_WritePin(ld6_GPIO_Port,ld6_Pin,GPIO_PIN_RESET)

#define BacklightON	   HAL_GPIO_WritePin(reserve_out1_GPIO_Port,reserve_out1_Pin,GPIO_PIN_SET)
#define BacklightOFF  HAL_GPIO_WritePin(reserve_out1_GPIO_Port,reserve_out1_Pin,GPIO_PIN_RESET)

//Private variable-----------------------
enum state {merah, kuning, hijau,light } stateku;
//enum state {ubah_jam, ubah_menit, tampil } stateku;
unsigned int Time_in_state=0,j1=0,j2=0,m1=0,m2=0,d1=0,d2=0,Time_read_state=0,Time_backlight_state=0;
char tampung[100];

/* -------------------------------------- *
	Traffic_Light_Init()
	Set kondisi pertama ke merah
-* -------------------------------------- */

void Task_Init(void){
	stateku=merah;
//	stateku=tampil;
}

void Task_Run(void){

	//	USARTPutStr("."); //current state
		switch(stateku)
		{
//		case tampil:
//		{
//			sprintf(tampung,"%d",detik);
//			if(++Time_in_state==lama_detik)
//			{
//				detik++;
//				Time_in_state=0;
//			}
//			break;
//		}
			case merah: //tampil
		        {
//					printf("Merah ON \n\r");
		        	if(HAL_GPIO_ReadPin(Mode_GPIO_Port,Mode_Pin)==GPIO_PIN_RESET)
		        	{
		        		stateku=kuning;
		        	}
		        	if (++Time_in_state==lama_detik)
		        	{
//		        		stateku=kuning;
		        		d2++;
		        		Time_in_state=0;
		        		if(d2==10)
		        		{
		        			d1++;
		        			d2=0;
		        			if(d1==6)
		        			{
		        				m2++;
		        				d1=0;
		        				if(m2==10)
		        				{
		        					m1++;
		        					m2=0;
		        				}
		        				if(m1==6)
		        				{
		        					j2++;
		        					m1=0;
		        				}
		        				if(j2==4&&j1==2)
		        				{
		        					j1=0;j2=0;m1=0;m2=0;d1=0;d2=0;
		        				}
		        				else if(j2==10)
		        				{
		        					j1++;
		        					j2=0;
		        				}
		        			}
		        		}
		        		sprintf(tampung,"%d%d:%d%d:%d%d",j1,j2,m1,m2,d1,d2);
		        	}

		        	break;
		        }

			case kuning: //ubah_jam
		        {
//        			sprintf(tampung,"%d%d:%d%d:%d%d",j1,j2,m1,m2,d1,d2);

//		        	MerahOFF;
//		        	KuningON;
//		        	HijauOFF;
//		        	printf("Kuning ON \n\r");
		        	if(++Time_in_state==lama_detik)
		        	{
		        		d2++;
		        		Time_in_state=0;
		        		if(d2==10)
		        		{
		        			d1++;
		        			d2=0;
		        			if(d1==6)
		        			{
		        				d1=0;d2=0;
		        			}
		        		}
		        		sprintf(tampung,"%d%d:%d%d:%d%d",j1,j2,m1,m2,d1,d2);
//		        		sprintf(tampung,"  :%d%d:%d%d",j1,j2,m1,m2,d1,d2);
		        	}

		        	if(HAL_GPIO_ReadPin(Mode_GPIO_Port,Mode_Pin)==GPIO_PIN_RESET)
		        	{
		        		stateku=hijau;
		        	}
		        	if(HAL_GPIO_ReadPin(Advance_GPIO_Port,Advance_Pin)==GPIO_PIN_RESET)
		        	{
		        		if(++Time_read_state>=lama_advance)
		        		{
		        			j2++;

		        			if(j2==4&&j1==2)
		        			{
		        				j1=0;j2=0;m1=0;m2=0;d1=0;d2=0;
		        			}
		        			else if(j2==10)
		        			{
		        				j1++;
		        				j2=0;
		        			}
		        			sprintf(tampung,"%d%d:%d%d:%d%d",j1,j2,m1,m2,d1,d2);
//		        			sprintf(tampung,"  :%d%d:%d%d",j1,j2,m1,m2,d1,d2);
		        		}
		        		else
		        		{
		        			j2++;

		        			if(j2==4&&j1==2)
		        			{
		        				j1=0;j2=0;m1=0;m2=0;d1=0;d2=0;
		        			}
		        			else if(j2==10)
		        			{
		        				j1++;
		        				j2=0;
		        			}
		        			sprintf(tampung,"%d%d:%d%d:%d%d",j1,j2,m1,m2,d1,d2);
//		        			sprintf(tampung,"  :%d%d:%d%d",j1,j2,m1,m2,d1,d2);
		        		}
		        	}
//		        	if (++Time_in_state==LAMA_KUNING)
//		        	{
//		        		stateku=hijau;
//		        		Time_in_state=0;
//		        	}

		        	break;
		        }

			case hijau: //ubah_menit
		        {
//	        		sprintf(tampung,"%d%d:%d%d:%d%d",j1,j2,m1,m2,d1,d2);

//		        	BacklightOFF;
//	                MerahOFF;
//	                KuningOFF;
//	                HijauON;
//	                printf("Hijau ON \n\r");
		        	if(++Time_in_state==lama_detik)
		        	{
		        		d2++;
		        		Time_in_state=0;
		        		if(d2==10)
		        		{
		        			d1++;
		        			d2=0;
		        			if(d1==6)
		        			{
		        				d1=0;d2=0;
		        			}
		        		}
		        		sprintf(tampung,"%d%d:%d%d:%d%d",j1,j2,m1,m2,d1,d2);
//		        		sprintf(tampung,"%d%d:  :%d%d",j1,j2,m1,m2,d1,d2);

		        	}

		        	if(HAL_GPIO_ReadPin(Mode_GPIO_Port,Mode_Pin)==GPIO_PIN_RESET)
		        	{
		        		stateku=merah;
		        	}
		        	if(HAL_GPIO_ReadPin(Advance_GPIO_Port,Advance_Pin)==GPIO_PIN_RESET)
		        	{
		        		if(++Time_read_state>=lama_advance)
		        		{
		        			m2++;

		        			if(m2==10)
		        			{
		        				m1++;
		        				m2=0;
		        				if(m1==6)
		        				{
		        					m1=0;m2=0;
		        				}
		        			}
		        			sprintf(tampung,"%d%d:%d%d:%d%d",j1,j2,m1,m2,d1,d2);
//		        			sprintf(tampung,"%d%d:  :%d%d",j1,j2,m1,m2,d1,d2);
		        		}
		        		else
		        		{
		        			m2++;

		        			if(m2==10)
		        			{
		        				m1++;
		        				m2=0;
		        				if(m1==6)
		        				{
		        					m1=0;m2=0;
		        				}
		        			}
		        			sprintf(tampung,"%d%d:%d%d:%d%d",j1,j2,m1,m2,d1,d2);
//		        			sprintf(tampung,"%d%d:  :%d%d",j1,j2,m1,m2,d1,d2);
		        		}
		        	}
//		        	if (++Time_in_state==LAMA_HIJAU)
//		        	{
//		        		stateku=merah;
//		        		Time_in_state=0;
//		        	}

		        	break;
		        }
		}

}

