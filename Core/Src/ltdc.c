/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ltdc.c
  * @brief   This file provides code for the configuration
  *          of the LTDC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "ltdc.h"

/* USER CODE BEGIN 0 */
LTDC_HandleTypeDef  LTDC_Handler;	    //LTDC
#define LCD_FRAME_BUF_ADDR			0XC0000000
u32 *ltdc_framebuf[2];					//LTDC LCD帧缓存数组指�?,必须指向对应大小的内存区�?
_ltdc_dev lcdltdc;						//管理LCD LTDC的重要参�?

/* USER CODE END 0 */

LTDC_HandleTypeDef hltdc;

/* LTDC init function */
void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 19;
  hltdc.Init.VerticalSync = 2;
  hltdc.Init.AccumulatedHBP = 159;
  hltdc.Init.AccumulatedVBP = 22;
  hltdc.Init.AccumulatedActiveW = 1183;
  hltdc.Init.AccumulatedActiveH = 622;
  hltdc.Init.TotalWidth = 1343;
  hltdc.Init.TotalHeigh = 634;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = PIXELS_W;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = PIXELS_H;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0xc0000000;
  pLayerCfg.ImageWidth = 1024;
  pLayerCfg.ImageHeight = 600;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspInit 0 */

  /* USER CODE END LTDC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLL3.PLL3M = 1;
    PeriphClkInitStruct.PLL3.PLL3N = 9;
    PeriphClkInitStruct.PLL3.PLL3P = 2;
    PeriphClkInitStruct.PLL3.PLL3Q = 2;
    PeriphClkInitStruct.PLL3.PLL3R = 5;
    PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_3;
    PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
    PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* LTDC clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    /**LTDC GPIO Configuration
    PI9     ------> LTDC_VSYNC
    PI10     ------> LTDC_HSYNC
    PF10     ------> LTDC_DE
    PH9     ------> LTDC_R3
    PH10     ------> LTDC_R4
    PH11     ------> LTDC_R5
    PH12     ------> LTDC_R6
    PG6     ------> LTDC_R7
    PG7     ------> LTDC_CLK
    PH13     ------> LTDC_G2
    PH14     ------> LTDC_G3
    PH15     ------> LTDC_G4
    PI0     ------> LTDC_G5
    PI1     ------> LTDC_G6
    PI2     ------> LTDC_G7
    PG11     ------> LTDC_B3
    PI4     ------> LTDC_B4
    PI5     ------> LTDC_B5
    PI6     ------> LTDC_B6
    PI7     ------> LTDC_B7
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1
                          |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* USER CODE BEGIN LTDC_MspInit 1 */

  /* USER CODE END LTDC_MspInit 1 */
  }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /**LTDC GPIO Configuration
    PI9     ------> LTDC_VSYNC
    PI10     ------> LTDC_HSYNC
    PF10     ------> LTDC_DE
    PH9     ------> LTDC_R3
    PH10     ------> LTDC_R4
    PH11     ------> LTDC_R5
    PH12     ------> LTDC_R6
    PG6     ------> LTDC_R7
    PG7     ------> LTDC_CLK
    PH13     ------> LTDC_G2
    PH14     ------> LTDC_G3
    PH15     ------> LTDC_G4
    PI0     ------> LTDC_G5
    PI1     ------> LTDC_G6
    PI2     ------> LTDC_G7
    PG11     ------> LTDC_B3
    PI4     ------> LTDC_B4
    PI5     ------> LTDC_B5
    PI6     ------> LTDC_B6
    PI7     ------> LTDC_B7
    */
    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1
                          |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11);

  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

LTDC_HandleTypeDef  LTDC_Handler;	    //LTDC���

//���ݲ�ͬ����ɫ��ʽ,����֡��������
#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888
u32 ltdc_lcd_framebuf[1280][800] __attribute__((at(LCD_FRAME_BUF_ADDR)));	//����������ֱ���ʱ,LCD�����֡���������С
#else
u16 ltdc_lcd_framebuf[1024][600] __attribute__((section(".lcd_frame_buf_addr")));	//����������ֱ���ʱ,LCD�����֡���������С
#endif

u32 *ltdc_framebuf[2];					//LTDC LCD֡��������ָ��,����ָ���Ӧ��С���ڴ�����
_ltdc_dev lcdltdc;						//����LCD LTDC����Ҫ����

//��LCD����
//lcd_switch:1 ��,0���ر�
void LTDC_Switch(u8 sw)
{
    if(sw==1) __HAL_LTDC_ENABLE(&LTDC_Handler);
    else if(sw==0)__HAL_LTDC_DISABLE(&LTDC_Handler);
}

//ѡ���
//layerx:���;0,��һ��;1,�ڶ���;
void LTDC_Select_Layer(u8 layerx)
{
    lcdltdc.activelayer=layerx;
}

//����LCD��ʾ����
//dir:0,������1,����
void LTDC_Display_Dir(u8 dir)
{
    lcdltdc.dir=dir; 	//��ʾ����
    if(dir==0)			//����
    {
        lcdltdc.width=lcdltdc.pheight;
        lcdltdc.height=lcdltdc.pwidth;
    }else if(dir==1)	//����
    {
        lcdltdc.width=lcdltdc.pwidth;
        lcdltdc.height=lcdltdc.pheight;
    }
}

//���㺯��
//x,y:����
//color:��ɫֵ
void LTDC_Draw_Point(u16 x,u16 y,u32 color)
{
#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888
    if(lcdltdc.dir)	//����
	{
        *(u32*)((u32)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*y+x))=color;
	}else 			//����
	{
        *(u32*)((u32)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*(lcdltdc.pheight-x-1)+y))=color;
	}
#else
    if(lcdltdc.dir)	//����
    {
        *(u16*)((u32)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*y+x))=color;
    }else 			//����
    {
        *(u16*)((u32)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*(lcdltdc.pheight-x-1)+y))=color;
    }
#endif
}

//���㺯��
//����ֵ:��ɫֵ
u32 LTDC_Read_Point(u16 x,u16 y)
{
#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888
    if(lcdltdc.dir)	//����
	{
		return *(u32*)((u32)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*y+x));
	}else 			//����
	{
		return *(u32*)((u32)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*(lcdltdc.pheight-x-1)+y));
	}
#else
    if(lcdltdc.dir)	//����
    {
        return *(u16*)((u32)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*y+x));
    }else 			//����
    {
        return *(u16*)((u32)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*(lcdltdc.pheight-x-1)+y));
    }
#endif
}

//LTDC������,DMA2D���
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)
//ע��:sx,ex,���ܴ���lcddev.width-1;sy,ey,���ܴ���lcddev.height-1!!!
//color:Ҫ������ɫ
void LTDC_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u32 color)
{
    u32 psx,psy,pex,pey;	//��LCD���Ϊ��׼������ϵ,����������仯���仯
    u32 timeout=0;
    u16 offline;
    u32 addr;
    //����ϵת��

    if(lcdltdc.dir)	//����
    {
        psx=sx;psy=sy;
        pex=ex;pey=ey;
    }else			//����
    {
        psx=sy;psy=lcdltdc.pheight-ex-1;
        pex=ey;pey=lcdltdc.pheight-sx-1;
    }
    offline=lcdltdc.pwidth-(pex-psx+1);
    addr=((u32)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*psy+psx));
    RCC->AHB1ENR|=1<<23;			//ʹ��DM2Dʱ��
    DMA2D->CR=3<<16;				//�Ĵ������洢��ģʽ
    DMA2D->OPFCCR=LCD_PIXFORMAT;	//������ɫ��ʽ
    DMA2D->OOR=offline;				//������ƫ��
    DMA2D->CR&=~(1<<0);				//��ֹͣDMA2D
    DMA2D->OMAR=addr;				//����洢����ַ
    DMA2D->NLR=(pey-psy+1)|((pex-psx+1)<<16);	//�趨�����Ĵ���
    DMA2D->OCOLR=color;				//�趨�����ɫ�Ĵ���
    DMA2D->CR|=1<<0;				//����DMA2D
    while((DMA2D->ISR&(1<<1))==0)	//�ȴ��������
    {
        timeout++;
        if(timeout>0X1FFFFF)break;	//��ʱ�˳�
    }
    DMA2D->IFCR|=1<<1;				//���������ɱ�־
}
void LTDC_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{
    u32 psx,psy,pex,pey;	//��LCD���Ϊ��׼������ϵ,����������仯���仯
    u32 timeout=0;
    u16 offline;
    u32 addr;
    //����ϵת��
    if(lcdltdc.dir)	//����
    {
        psx=sx;psy=sy;
        pex=ex;pey=ey;
    }else			//����
    {
        psx=sy;psy=lcdltdc.pheight-ex-1;
        pex=ey;pey=lcdltdc.pheight-sx-1;
    }
    offline=lcdltdc.pwidth-(pex-psx+1);
    addr=((u32)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*psy+psx));
    RCC->AHB1ENR|=1<<23;			//ʹ��DM2Dʱ��
    DMA2D->CR=0<<16;				//�洢�����洢��ģʽ
    DMA2D->FGPFCCR=LCD_PIXFORMAT;	//������ɫ��ʽ
    DMA2D->FGOR=0;					//ǰ������ƫ��Ϊ0
    DMA2D->OOR=offline;				//������ƫ��
    DMA2D->CR&=~(1<<0);				//��ֹͣDMA2D
    DMA2D->FGMAR=(u32)color;		//Դ��ַ
    DMA2D->OMAR=addr;				//����洢����ַ
    DMA2D->NLR=(pey-psy+1)|((pex-psx+1)<<16);	//�趨�����Ĵ���
    DMA2D->CR|=1<<0;				//����DMA2D
    while((DMA2D->ISR&(1<<1))==0)	//�ȴ��������
    {
        timeout++;
        if(timeout>0X1FFFFF)break;	//��ʱ�˳�
    }
    DMA2D->IFCR|=1<<1;				//���������ɱ�־
}

//LCD����
//color:��ɫֵ
void LTDC_Clear(u32 color)
{
    LTDC_Fill(0,0,lcdltdc.width-1,lcdltdc.height-1,color);
}



//LCD��ʼ������
void LTDC_Init(void)
{
    u16 lcdid=0;
    lcdid=0x7016;			//��ȡLCD���ID
    if(lcdid==0X7016)
    {
        lcdltdc.pwidth=1024;			//�����,��λ:����
        lcdltdc.pheight=600;			//���߶�,��λ:����
        lcdltdc.hsw=20;				    //ˮƽͬ�����
        lcdltdc.vsw=3;				    //��ֱͬ�����
        lcdltdc.hbp=140;			    //ˮƽ����
        lcdltdc.vbp=20;				    //��ֱ����
        lcdltdc.hfp=160;			    //ˮƽǰ��
        lcdltdc.vfp=12;				    //��ֱǰ��
        //������������.
    }else
        printf("Not 7016 Device.\r\n");

//    lcddev.width=lcdltdc.pwidth;
//    lcddev.height=lcdltdc.pheight;

#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888
    ltdc_framebuf[0]=(u32*)&ltdc_lcd_framebuf;
	lcdltdc.pixsize=4;				//ÿ������ռ4���ֽ�
#else
    lcdltdc.pixsize=2;				//ÿ������ռ2���ֽ�
    ltdc_framebuf[0]=(u32*)&ltdc_lcd_framebuf;
#endif

    LTDC_Display_Dir(1);			//����
    LTDC_Select_Layer(0); 			//ѡ���1��
    LCD_LED(1);         		    //��������
    LTDC_Clear(0XFFFFFFFF);			//����
}

/* USER CODE END 1 */
