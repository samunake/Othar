
#include "LCD_Functions.h"
#include "LCD_Config.h"

/*********************************************************************************************************
*
* File                : LCD_Config.c
* Hardware Environment:
* Build Environment   : CooCox CoIDE  Version: 1.7.8
* Version             : V1.0
* By                  : Tomás Ariza Crespo
*
*
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Chk_Busy
* Description    : Check whether the Memory Read/Write is busy
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Chk_Busy(void)
{
	uint8_t temp;
	do
	{
	  temp=LCD_StatusRead();
	}while((temp&0x80)==0x80);
}

/*******************************************************************************
* Function Name  : Chk_Busy_BTE
* Description    : Check whether the BTE is busy
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Chk_Busy_BTE(void)
{
	uint8_t temp;
	do
	{
          temp=LCD_StatusRead();
	}while((temp&0x40)==0x40);
}
/*******************************************************************************
* Function Name  : Chk_Busy_DIR_Access
* Description    : Check whether the DIR_Access is busy
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Chk_Busy_DIR_Access(void)
{
	uint8_t  temp;
	do
	{
          temp=LCD_StatusRead();
	}while((temp&0x01)==0x01);
}
/*******************************************************************************
* Function Name  : Chk_DMA_Busy
* Description    : Check whether the DMA is busy
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Chk_DMA_Busy(void)
{
	uint8_t temp;
	do
	{
	LCD_WriteCmd(0xbf);
	temp = LCD_ReadData();
	}while((temp&0x01)==0x01);
}

/*******************************************************************************
* Function Name  : Display_ON
* Description    : Display on
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Display_ON(void)
{
	LCD_WriteReg(0x01,0x80); //PWRR


}
/*******************************************************************************
* Function Name  : Display_OFF
* Description    : Display OFF
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Display_OFF(void)
{
	LCD_WriteReg(0x01,0x00); //PWRR

}
/*******************************************************************************
* Function Name  : Normal_Mode_exitSleep
* Description    : Normal mode
* Input          : None
* Output         : None
* Return         : None
* Attention		   : 1. There are 3 ways to wake up from sleep mode:
						Touch Panel wake up, Key Scan wake up ,Software wake up.
					 2. When using IIC interface, this function is not supported.
*******************************************************************************/
void Normal_Mode_exitSleep(void)
{
	LCD_WriteReg(0x01,0x00); //PWRR
}

/*******************************************************************************
* Function Name  : Sleep_Mode
* Description    : Sleep mode.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : 1. There are 3 ways to wake up from sleep mode:
						Touch Panel wake up, Key Scan wake up ,Software wake up.
					 2. When using IIC interface, this function is not supported.
*******************************************************************************/
void Sleep_Mode(void)
{
	LCD_WriteReg(0x01,0x02); //PWRR

}
//REG[46h]~REG[49h]
void XY_Coordinate(uint16_t X,uint16_t Y)
{
	LCD_WriteReg(0x46,X);

    LCD_WriteReg(0x47,X>>8);

    LCD_WriteReg(0x48,Y);

    LCD_WriteReg(0x49,Y>>8);


}
/*******************************************************************************
* Function Name  : lcd_Reset
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void LCD_Reset(void)
{

	 //RA8875 RESET pin
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	Delay_ms(1);
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
	Delay_ms(10);
}

/*******************************************************************************
* Function Name  : Software_Reset
* Description    : Software Reset.
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Software_Reset(void)
{
	LCD_WriteReg(0x01,0x01); //PWRR
    LCD_WriteData(0x00);
    Delay_ms(1);
}

/*******************************************************************************
* Function Name  : PCLK_inversion (Pixel Clock Setting Register)
* Description    : PDAT is fetched at PCLK falling edge.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void PCLK_inversion(void)
{
    uint8_t temp;
    temp = LCD_ReadReg(0x04); //PCRS
    temp |= 0x80;
    LCD_WriteData(temp);
}

/*******************************************************************************
* Function Name  : PCLK_non_inversion (Pixel Clock Setting Register)
* Description    : PDAT is fetched at PCLK rising edge.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void PCLK_non_inversion(void)
{
    uint8_t temp;
    temp = LCD_ReadReg(0x04); //PCRS
    temp &= 0x7f;
    LCD_WriteData(temp);
}

/*******************************************************************************
* Function Name  : PCLK_width
* Description    : PCLK Period Setting  (Pixel clock (PCLK) period setting. )
* Input          : setx:
							00b: PCLK period = System Clock period.
							01b: PCLK period = 2 times of System Clock period.
							10b: PCLK period = 4 times of System Clock period.
							11b: PCLK period = 8 times of System Clock period.
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void PCLK_width(uint8_t setx) //uint8_t[1:0]
{
    uint8_t temp;
    temp = LCD_ReadReg(0x04); //PCRS
    temp &=0x80;
    temp |= setx;
    LCD_WriteData(temp);
}

/*******************************************************************************
* Function Name  : Serial_ROM_select0
* Description    : Serial Flash/ROM 0 I/F is selected.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Serial_ROM_select0(void)
{
    uint8_t temp;
    temp = LCD_ReadReg(0x05); //SROC
    temp &=0x7f;
    LCD_WriteData(temp);
}

/*******************************************************************************
* Function Name  : Serial_ROM_select1
* Description    : Serial Flash/ROM 0 or 1 I/F is selected.
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Serial_ROM_select1(void)
{
    uint8_t temp;
    temp = LCD_ReadReg(0x05); //SROC
    temp |=0x80;
    LCD_WriteData(temp);
}

void Background_color(uint16_t color)
{
	LCD_WriteReg(0x60,color>>11);

    LCD_WriteReg(0x61,color>>5);

    LCD_WriteReg(0x62,color);



}
/*******************************************************************************
* Function Name  : Active Window
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
//-------------------------------------------//
//REG[30h]~REG[37h]
void Active_Window(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB)
{
    //setting active window X

	LCD_WriteReg(0x30,XL & 0x00ff); //Horizontal Start Point 0 of Active Window (HSAW0)
	LCD_WriteReg(0x31,XL>>8); //Horizontal Start Point 1 of Active Window (HSAW1)
	LCD_WriteReg(0x34,XR & 0x00ff); //Horizontal End Point 0 of Active Window (HEAW0)
	LCD_WriteReg(0x35,XR>>8); //Horizontal End Point 1 of Active Window (HEAW1)


    //setting active window Y

	LCD_WriteReg(0x32,YT& 0x00ff); //Vertical Start Point 0 of Active Window (VSAW0)
	LCD_WriteReg(0x33,YT>>8); //Vertical Start Point 1 of Active Window (VSAW1)
	LCD_WriteReg(0x36,YB & 0x00ff); //Vertical End Point of Active Window 0 (VEAW0)
	LCD_WriteReg(0x37,YB>>8); //Vertical End Point of Active Window 1 (VEAW1)


}
/*******************************************************************************
* Function Name  : Graphic_Mode
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention	     : None
*******************************************************************************/
void Graphic_Mode(void)
{
  uint8_t temp;
  temp =LCD_ReadReg(0X40);//MWCR0
  temp &= 0x7f ;
  LCD_WriteData(temp);
}

/*******************************************************************************
* Function Name  : Text Color
* Description    : Set screen color
* Input          : Color: Screen Color
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Text_color(uint16_t color)
{

	LCD_WriteReg(0x63,((color&0xf800)>>11));
    LCD_WriteReg(0x64,((color&0x07e0)>>5));
    LCD_WriteReg(0x65,color&0x001f);

  #ifdef Color256
    LCD_CmdWrite(0x63);
    LCD_DataWrite((color&0xf800)>>13);

    LCD_CmdWrite(0x64);
    LCD_DataWrite((color&0x07e0)>>8);

    LCD_CmdWrite(0x65);
    LCD_DataWrite((color&0x001f)>>3);
 #endif
}
/*******************************************************************************
* Function Name  : Geometric_Coordinate
* Description    : Set screen color
* Input          : Color: Screen Color
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Geometric_Coordinate(uint16_t X,uint16_t Y,uint16_t X1  ,uint16_t Y1)
{
	LCD_WriteReg(0x91,X);
	LCD_WriteReg(0x92,X>>8);

	LCD_WriteReg(0x93,Y);
	LCD_WriteReg(0x94,Y>>8);

	LCD_WriteReg(0x95,X1);
	LCD_WriteReg(0x96,X1>>8);

	LCD_WriteReg(0x97,Y1);
	LCD_WriteReg(0x98,Y1>>8);

}
void Memory_Clear(void)
{
	LCD_WriteReg(0x8e,0x80);
	Chk_Busy();
}
void ActiveWindow_Clear(void)
{
	LCD_WriteReg(0x8e,0xC0);
	Chk_Busy();
}

/*******************************************************************************
* Function Name  : LcdClear
* Description    : Clear the screen
* Input          : Color: Screen Color
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void LCD_Clear(u16 color)
{
	Text_color(color); // Set the color
	Geometric_Coordinate(0,0,800,479);
	LCD_WriteReg(0x90,0xb0);

	Display_ON();
}
