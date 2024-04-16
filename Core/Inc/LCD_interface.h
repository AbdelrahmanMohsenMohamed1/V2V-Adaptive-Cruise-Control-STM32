/*
 * LCD_interface.h
 *
 * Created: 4/1/2024 11:52:44 PM
 *  Author: Ali Azzouz & Tarek Alaa
 * Description: Header file for LCD interface functions
 */ 

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/* 
 * Function: LCD_voidInit
 * -----------------------
 * Initializes the LCD module with 4-bit communication mode.
 * Sends initialization commands to set up the LCD.
 */
void LCD_voidInit(void);

/* 
 * Function: LCD_voidWriteCmd
 * ---------------------------
 * Writes a command to the LCD module.
 * Used internally by other functions to send control commands to the LCD.
 */
void LCD_voidWriteCommand(uint8_t copy_u8Command);

/* 
 * Function: LCD_voidWriteChar
 * ----------------------------
 * Writes a single character to the LCD at the current cursor position.
 * Used to display characters on the screen.
 */
void LCD_voidWriteData(uint8_t copy_u8data);
		
/* 
 * Function: LCD_voidClearScreen
 * ------------------------------
 * Clears the entire LCD screen by sending the appropriate command.
 */
void LCD_voidClear(void);

/* 
 * Function: LCD_voidSetCursor
 * ----------------------------
 * Sets the cursor position on the LCD screen.
 * Takes the row and column numbers as parameters to position the cursor accordingly.
 */
void LCD_voidSetCursor(uint8_t copy_u8Row,uint8_t copy_u8Col);

/* 
 * Function: LCD_voidWriteString
 * ------------------------------
 * Writes a null-terminated string to the LCD screen starting from the current cursor position.
 */
void LCD_voidWriteString(const uint8_t* copy_cu8pString);

/* 
 * Function: LCD_voidWriteNum
 * ---------------------------
 * Writes a decimal number to the LCD screen starting from the current cursor position.
 */
void LCD_voidWriteNum(uint32_t copy_u32Num);

/* 
 * Function: LCD_voidCreateChar
 * ------------------------------
 * Creates a custom character and stores it in the LCD's CGRAM (Character Generator RAM) at the specified address.
 * This custom character can then be displayed like any other character.
 */
void LCD_voidCreateChar(uint8_t copy_u8AddressData, uint8_t * copy_u8charArr);


#endif /* LCD_INTERFACE_H_ */
