#include "LCD_Interface.h"
#include "stm32f4xx.h"




/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    :
* Input          : - index:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
__inline void LCD_WriteCmd(uint16_t index)
{
	LCD_CMD	= index;
}
/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    :
* Input          : - index:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
__inline void LCD_WriteData(uint16_t data)
{

	LCD_DATA = data;
//	Delay_ms(1); //  Espacio de 5 clclos entre wr y wr (5.9*5 > 84ns) pag59 datasheet RA

}

/*******************************************************************************
* Function Name  : LCD_ReadData
* Description    :
* Input          : None
* Output         : None
* Return         :
* Attention		 : None
*******************************************************************************/
__inline uint16_t LCD_ReadData(void)
{
	return LCD_DATA;
}


/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
__inline void LCD_WriteReg(uint16_t LCD_Reg,uint16_t LCD_RegValue)
{
	/* Write 16-bit Index, then Write Reg */
	LCD_WriteCmd(LCD_Reg);
	Delay_ms(5);
	/* Write 16-bit Reg */
	LCD_WriteData(LCD_RegValue);
}

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
* Attention		 : None
*******************************************************************************/
__inline uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
	/* Write 16-bit Index (then Read Reg) */
	LCD_WriteCmd(LCD_Reg);

	/* Read 16-bit Reg */
	return LCD_ReadData();
}

__inline uint16_t LCD_StatusRead(void)
{

    return (LCD_CMD);
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
