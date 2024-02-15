/* 
 * File:   Application.c
 * Author: Alielden
 *
 * Created on September 9, 2023, 6:23 PM
 */

#include "Application.h"

#if (CPU_CFG == CPU1_CFG )

Std_ReturnType ret = STD_OK ;
uint8 keypad_val_str = 1 , keypad_val_num = 0 , confirm = 0  , temp = 1  , check = 0  , user = 0 , flag = 0 , money_l = 0 , money_h=0  ;
uint16 password = 0 , money = 0  ; 
uint8 *str[6] ;

keypad_t keypad =
{
  .rows_pins[0].port      = GPIO_PORTB  ,
  .rows_pins[0].pin       = GPIO_PIN0   ,
  .rows_pins[0].logic     = GPIO_LOW    ,
  .rows_pins[0].direction = GPIO_OUTPUT ,
  .rows_pins[1].port      = GPIO_PORTB  ,
  .rows_pins[1].pin       = GPIO_PIN1   ,
  .rows_pins[1].logic     = GPIO_LOW    ,
  .rows_pins[1].direction = GPIO_OUTPUT ,
  .rows_pins[2].port      = GPIO_PORTB  ,
  .rows_pins[2].pin       = GPIO_PIN2   ,
  .rows_pins[2].logic     = GPIO_LOW    ,
  .rows_pins[2].direction = GPIO_OUTPUT ,
  .rows_pins[3].port      = GPIO_PORTB  ,
  .rows_pins[3].pin       = GPIO_PIN3   ,
  .rows_pins[3].logic     = GPIO_LOW    ,
  .rows_pins[3].direction = GPIO_OUTPUT ,
  
  .columns_pins[0].port      = GPIO_PORTB  ,
  .columns_pins[0].pin       = GPIO_PIN4   ,
  .columns_pins[0].logic     = GPIO_LOW    ,
  .columns_pins[0].direction = GPIO_INPUT ,
  .columns_pins[1].port      = GPIO_PORTB  ,
  .columns_pins[1].pin       = GPIO_PIN5   ,
  .columns_pins[1].logic     = GPIO_LOW    ,
  .columns_pins[1].direction = GPIO_INPUT ,
  .columns_pins[2].port      = GPIO_PORTB  ,
  .columns_pins[2].pin       = GPIO_PIN6   ,
  .columns_pins[2].logic     = GPIO_LOW    ,
  .columns_pins[2].direction = GPIO_INPUT ,
  .columns_pins[3].port      = GPIO_PORTB  ,
  .columns_pins[3].pin       = GPIO_PIN7   ,
  .columns_pins[3].logic     = GPIO_LOW    ,
  .columns_pins[3].direction = GPIO_INPUT ,
};



lcd_8bit_t lcd = 
{
  .lcd_rs.port      = GPIO_PORTE ,
  .lcd_rs.pin       = GPIO_PIN1 ,
  .lcd_rs.logic     = GPIO_LOW ,
  .lcd_rs.direction = GPIO_OUTPUT ,
  
  .lcd_en.port      = GPIO_PORTE ,
  .lcd_en.pin       = GPIO_PIN0 ,
  .lcd_en.logic     = GPIO_LOW ,
  .lcd_en.direction = GPIO_OUTPUT ,
  
  .lcd_data[0].port      = GPIO_PORTD ,
  .lcd_data[0].pin       = GPIO_PIN0 ,
  .lcd_data[0].logic     = GPIO_LOW ,
  .lcd_data[0].direction = GPIO_OUTPUT ,
  
  .lcd_data[1].port      = GPIO_PORTD ,
  .lcd_data[1].pin       = GPIO_PIN1 ,
  .lcd_data[1].logic     = GPIO_LOW ,
  .lcd_data[1].direction = GPIO_OUTPUT ,
  
  .lcd_data[2].port      = GPIO_PORTD ,
  .lcd_data[2].pin       = GPIO_PIN2 ,
  .lcd_data[2].logic     = GPIO_LOW ,
  .lcd_data[2].direction = GPIO_OUTPUT ,
  
  .lcd_data[3].port      = GPIO_PORTD ,
  .lcd_data[3].pin       = GPIO_PIN3 ,
  .lcd_data[3].logic     = GPIO_LOW ,
  .lcd_data[3].direction = GPIO_OUTPUT ,
  
  .lcd_data[4].port      = GPIO_PORTD ,
  .lcd_data[4].pin       = GPIO_PIN4 ,
  .lcd_data[4].logic     = GPIO_LOW ,
  .lcd_data[4].direction = GPIO_OUTPUT ,
  
  .lcd_data[5].port      = GPIO_PORTD ,
  .lcd_data[5].pin       = GPIO_PIN5 ,
  .lcd_data[5].logic     = GPIO_LOW ,
  .lcd_data[5].direction = GPIO_OUTPUT ,
  
  .lcd_data[6].port      = GPIO_PORTD ,
  .lcd_data[6].pin       = GPIO_PIN6 ,
  .lcd_data[6].logic     = GPIO_LOW ,
  .lcd_data[6].direction = GPIO_OUTPUT ,
  
  .lcd_data[7].port      = GPIO_PORTD ,
  .lcd_data[7].pin       = GPIO_PIN7 ,
  .lcd_data[7].logic     = GPIO_LOW ,
  .lcd_data[7].direction = GPIO_OUTPUT ,
};


usart_t atm ={
  .baudrate = 9600 ,
  .baudrate_eqn = ASYN_8BIT_LOW_SPEED ,
  
  .tx_cfg.tx_enable = USART_TX_ENABLE ,
  .tx_cfg.tx_interrupt = EUSART_TX_INTERRUPT_ENABLE ,
  .tx_cfg.tx_9bit = USART_TX_9BIT_DATA_DISABLE ,
  
  .rx_cfg.rx_enable = USART_RX_ENABLE ,
  .rx_cfg.rx_interrupt = EUSART_RX_INTERRUPT_ENABLE ,
  .rx_cfg.rx_9bit = USART_RX_9BIT_DATA_DISABLE ,
  
  .USART_TX_CALLBACK = NULL ,
  .USART_RX_CALLBACK = RX_Callback ,
  .USART_RX_FRAMING_ERROR_CALLBACK = NULL ,
  .USART_RX_OVERRUN_ERROR_CALLBACK = NULL ,
  
};



 



int main() {
    
    APPLICATION_INTIALIZE();
    lcd_Enter_Pass();
    Check_Password();
    if( check == PASSWORD_CORRECT )
    {
        lcd_main();
        while(1)
        {
            
            confirm = FLOATING ;
            Take_Val_Keypad();
            if( confirm == NOT_CONFIRMED )
            {
                ret = lcd_8bit_send_char_data_pos(&lcd , 4 , 20 , keypad_val_str);
                __delay_ms(1000);
                
                switch(keypad_val_num)
                {
                    case CHECK_ACCOUNT :
                        ret = Usart_Async_WriteByte(CHECK_ACCOUNT) ;
                        while(1)
                        {
                            if( flag == 3 )
                            {
                                lcd_Check_Account();
                                ret = convert_short_to_string(money , str);
                                ret = lcd_8bit_send_string_data_pos(&lcd , 4 , 1 , str );
                                break;
                            }
                        }
                        break;
                        
                    case WITHDRAW :
                        lcd_Withdraw();
                         while(1)
                         {
                            Take_Val_Keypad();
        
                            if( confirm == NOT_CONFIRMED )
                            {
                                ret = lcd_8bit_send_char_data(&lcd , keypad_val_str);
                                money = keypad_val_num + money * 10 ;
                                confirm = FLOATING ;
                            }
                            else if( confirm == CONFIRMED )
                            {
                                ret = Usart_Async_WriteByte(WITHDRAW) ;
                                ret = Usart_Async_WriteByte(money) ;
                                ret = Usart_Async_WriteByte( money>>8 ) ;
                                break ;
                            }
                         }
                        while(1)
                        {
                            if( flag == 3 )
                            {
                                if( ((sint16)money) >= 0)
                                {
                                    lcd_Check_Account();
                                    ret = convert_short_to_string(money , str);
                                    ret = lcd_8bit_send_string_data_pos(&lcd , 4 , 1 , str );
                                }
                                else if( ((sint16)money) < 0 )
                                {
                                    lcd_Error();
                                }
                                break;
                            }
                        }
                        break;
                        
                    case DEPOSIT :
                        lcd_Deposite();
                         while(1)
                         {
                            Take_Val_Keypad();
        
                            if( confirm == NOT_CONFIRMED )
                            {
                                ret = lcd_8bit_send_char_data(&lcd , keypad_val_str);
                                money = keypad_val_num + money * 10 ;
                                confirm = FLOATING ;
                            }
                            else if( confirm == CONFIRMED )
                            {
                                ret = Usart_Async_WriteByte(DEPOSIT) ;
                                ret = Usart_Async_WriteByte(money) ;
                                ret = Usart_Async_WriteByte( money>>8 ) ;
                                break ;
                            }
                         }
                        while(1)
                        {
                            if( flag == 3 )
                            {
                                lcd_Check_Account();
                                ret = convert_short_to_string(money , str);
                                ret = lcd_8bit_send_string_data_pos(&lcd , 4 , 1 , str );
                                break;
                            }
                        }
                        break;
                
             
                }
            
            }
      
        }
        
    }
    return (EXIT_SUCCESS);
}


void APPLICATION_INTIALIZE(void)
{
    ret = lcd_8bit_intialize(&lcd);
    ret = keypad_intialize(&keypad);
    ret = Usart_Async_init(&atm);
}



void lcd_welcome(void)
{
    ret = lcd_8bit_send_string_data(&lcd , "Welcome");
    ret = lcd_8bit_send_char_data(&lcd , '.' ) ;
    __delay_ms(500) ;
    ret = lcd_8bit_send_char_data(&lcd , '.' ) ;
    __delay_ms(500) ;
    ret = lcd_8bit_send_char_data(&lcd , '.' ) ;
    __delay_ms(500) ;
    ret = lcd_8bit_send_char_data_pos(&lcd , 1 , 8 , ' ' );
    ret = lcd_8bit_send_char_data_pos(&lcd , 1 , 9 , ' ' );
    ret = lcd_8bit_send_char_data_pos(&lcd , 1 , 10 , ' ' );
     __delay_ms(500) ;
     ret = lcd_8bit_send_char_data_pos(&lcd , 1 , 8 , '.' ) ;
    __delay_ms(500) ;
     ret = lcd_8bit_send_char_data_pos(&lcd , 1 ,9 , '.' ) ;
    __delay_ms(500) ;
     ret = lcd_8bit_send_char_data_pos(&lcd , 1 , 10 , '.' ) ;
    __delay_ms(500) ;
    ret = lcd_8bit_send_command(&lcd , _LCD_CLEAR );

}


void lcd_main(void)
{
     ret = lcd_8bit_send_command(&lcd , _LCD_CLEAR );
     ret = lcd_8bit_send_string_data_pos(&lcd , 1 , 1 , "1.Check Account");
     ret = lcd_8bit_send_string_data_pos(&lcd , 2 , 1 , "2.Withdraw");
     ret = lcd_8bit_send_string_data_pos(&lcd , 3 , 1 , "3.Deposit");      
}

void lcd_Enter_Pass(void)
{
    ret = lcd_8bit_send_command(&lcd , _LCD_CLEAR );
    ret = lcd_8bit_send_string_data_pos(&lcd , 1 , 1 , "Enter The Password :");
}

void lcd_Password_Correct(void)
{
    ret = lcd_8bit_send_command(&lcd , _LCD_CLEAR );
    ret = lcd_8bit_send_string_data_pos(&lcd , 1 , 1 , "Password_Correct");
}
void lcd_Password_Incorrect(void)
{
    ret = lcd_8bit_send_command(&lcd , _LCD_CLEAR );
    ret = lcd_8bit_send_string_data_pos(&lcd , 1 , 1 , "Password_Incorrect");
}

void lcd_Check_Account(void)
{
    ret = lcd_8bit_send_command(&lcd , _LCD_CLEAR );
    ret = lcd_8bit_send_string_data_pos(&lcd , 1 , 1 , "Your Account has");
}

void lcd_Withdraw(void)
{
    ret = lcd_8bit_send_command(&lcd , _LCD_CLEAR );
    ret = lcd_8bit_send_string_data_pos(&lcd , 1 , 1 , "Enter the value you need :");
}

void lcd_Deposite(void)
{
    ret = lcd_8bit_send_command(&lcd , _LCD_CLEAR );
    ret = lcd_8bit_send_string_data_pos(&lcd , 1 , 1 , "Enter the value you add :");
}

void lcd_Error(void)
{
    ret = lcd_8bit_send_command(&lcd , _LCD_CLEAR );
    ret = lcd_8bit_send_string_data_pos(&lcd , 1 , 1 , "Sorry you dont have enough money");
}




void Take_Val_Keypad(void)
{
    ret = keypad_get_value(&keypad , &keypad_val_str) ;
    
    if( temp != keypad_val_str )
    {
        if( (keypad_val_str != '/' ) && (keypad_val_str != '+' ) && (keypad_val_str != '-' ) && (keypad_val_str != '=' ) && (keypad_val_str != '*' ) && (keypad_val_str != '#' ) )
        {
            //if( keypad_val_str != 0 )
            {
                keypad_val_num = atoi(&keypad_val_str) ;
                if( keypad_val_num > 10 )
                {
                    keypad_val_num /= 10 ;
                }
                confirm = NOT_CONFIRMED ;
                temp = keypad_val_str ;
            }
        }
        else if( keypad_val_str == '#' )
        {
            confirm = CONFIRMED ;
            temp = keypad_val_str ;
        }
    }
    else
    {
        confirm = FLOATING ;
    }
}


void Check_Password(void)
{
    confirm = FLOATING ;
    while(1)
    {
        Take_Val_Keypad();
        
        if( confirm == NOT_CONFIRMED )
        {
            ret = lcd_8bit_send_char_data(&lcd , keypad_val_str);
            password = keypad_val_num + password * 10 ;
            confirm = FLOATING ;
        }
        else if( confirm == CONFIRMED )
        {
            ret = Usart_Async_WriteByte((uint8)password);
            ret = Usart_Async_WriteByte((uint8)( password >> 8 ));
        }
        
        
        if( flag == 1 )
        {
            if( check == PASSWORD_CORRECT )
            {
                lcd_Password_Correct();
                __delay_ms(2000);
            }
            else if( check == PASSWORD_INCORRECT )
            {
                lcd_Password_Incorrect();
                __delay_ms(2000);
            }
            break;
        }
      
            
    }
}



void RX_Callback(void)
{
    if( flag == 0 )
    {
        ret = Usart_Async_ReadByte(&check);
        flag = 1 ;
    }
    else if ( flag == 1 )
    {
        ret = Usart_Async_ReadByte(&money_l);
        flag = 2 ;
    }
    else if( flag == 2 )
    {
        ret = Usart_Async_ReadByte(&money_h);
        money = money_l + (money_h << 8) ;
        flag = 3 ;
    }
}


#endif


#if (CPU_CFG == CPU2_CFG)


Std_ReturnType ret = STD_OK ;
uint8 pass_l = 0 , pass_h = 0 , money_l = 0 , money_h = 0 , flag = 0  , EEPROM_data_l = 0  , EEPROM_data_h = 0 , check = 0  , user = 0 , mode = 5 ;
uint16 password = 0 , money = 0 , EEPROM_data = 0 , temp = 0  ;

usart_t bank ={
  .baudrate = 9600 ,
  .baudrate_eqn = ASYN_8BIT_LOW_SPEED ,
  
  .tx_cfg.tx_enable = USART_TX_ENABLE ,
  .tx_cfg.tx_interrupt = EUSART_TX_INTERRUPT_ENABLE ,
  .tx_cfg.tx_9bit = USART_TX_9BIT_DATA_DISABLE ,
  
  .rx_cfg.rx_enable = USART_RX_ENABLE ,
  .rx_cfg.rx_interrupt = EUSART_RX_INTERRUPT_ENABLE ,
  .rx_cfg.rx_9bit = USART_RX_9BIT_DATA_DISABLE ,
  
  .USART_TX_CALLBACK = NULL ,
  .USART_RX_CALLBACK = RX_Callback ,
  .USART_RX_FRAMING_ERROR_CALLBACK = NULL ,
  .USART_RX_OVERRUN_ERROR_CALLBACK = NULL ,
  
};


int main() {
    
    APPLICATION_INTIALIZE();
   
   /* ret = EEPROM_WriteData(0x00 , 123);
    ret = EEPROM_WriteData(0x01 , 234);
    ret = EEPROM_WriteData(0x02 , 198);
    
    ret = EEPROM_WriteData(0x10 , 232);
    ret = EEPROM_WriteData(0x11 , 3);
    ret = EEPROM_WriteData(0x12 , 208);
    ret = EEPROM_WriteData(0x13 , 7);
    ret = EEPROM_WriteData(0x14 , 184);
    ret = EEPROM_WriteData(0x15 , 11);
    * */
    while(1)
    {
        Check_Pass();
        
        if( flag == 4 )         
        {
             switch(mode)
                {
                    case CHECK_ACCOUNT :
                        ret = EEPROM_ReadData( ( 0x10 + (2* user ) - 2 ) , &money_l ) ;
                        ret = EEPROM_ReadData( ( 0x10 + (2* user ) - 1  ) , &money_h ) ;
                        ret = Usart_Async_WriteByte(money_l);
                        ret = Usart_Async_WriteByte(money_h);
                        flag = 0 ;
                        break;
                        
                    case WITHDRAW :
                        while(1)
                        {
                            if( flag == 6 )
                            {
                                ret = EEPROM_ReadData( ( 0x10 + (2* user ) - 2 ) , &EEPROM_data_l ) ;
                                ret = EEPROM_ReadData( ( 0x10 + (2* user ) - 1  ) , &EEPROM_data_h ) ;
                                EEPROM_data = EEPROM_data_l + (EEPROM_data_h<<8) ;
                                temp = EEPROM_data ;
                                EEPROM_data = EEPROM_data - money ;
                                ret = Usart_Async_WriteByte(EEPROM_data);
                                ret = Usart_Async_WriteByte(EEPROM_data>>8);
                                ret = EEPROM_WriteData( ( 0x10 + (2* user ) - 2 ) , EEPROM_data);
                                ret = EEPROM_WriteData( ( 0x10 + (2* user ) - 1 ) , EEPROM_data>>8);
                                if( ((sint16)EEPROM_data) < 0 )
                                {
                                    EEPROM_data = temp ;
                                    ret = EEPROM_WriteData( ( 0x10 + (2* user ) - 2 ) , EEPROM_data);
                                    ret = EEPROM_WriteData( ( 0x10 + (2* user ) - 1 ) , EEPROM_data>>8);
                                }
                                flag = 0 ;
                                break;
                            }
                        }
                        break;
                        
                    case DEPOSIT :
                        while(1)
                        {
                            if( flag == 6 )
                            {
                                ret = EEPROM_ReadData( ( 0x10 + (2* user ) - 2 ) , &EEPROM_data_l ) ;
                                ret = EEPROM_ReadData( ( 0x10 + (2* user ) - 1  ) , &EEPROM_data_h ) ;
                                EEPROM_data = EEPROM_data_l + (EEPROM_data_h<<8) ;
                                EEPROM_data = EEPROM_data + money ;
                                ret = Usart_Async_WriteByte(EEPROM_data);
                                ret = Usart_Async_WriteByte(EEPROM_data>>8);
                                ret = EEPROM_WriteData( ( 0x10 + (2* user ) - 2 ) , EEPROM_data);
                                ret = EEPROM_WriteData( ( 0x10 + (2* user ) - 1 ) , EEPROM_data>>8);
                                flag = 0 ;
                                break;
                            }
                        }
                        break;
                
             
                }
        }
    }
    
    
}




void APPLICATION_INTIALIZE(void)
{
    ret = Usart_Async_init(&bank);
}

void RX_Callback(void)
{
    if( flag == 0 )
    {
        ret = Usart_Async_ReadByte(&pass_l);
        flag = 1 ;
    }
    
    else if( flag == 1 )
    {
       ret = Usart_Async_ReadByte(&pass_h);
       flag = 2 ;
    }
    else if( flag == 3 )
    {
        ret = Usart_Async_ReadByte(&mode);
        flag = 4 ;
    }
    else if( flag == 4 )
    {
       ret = Usart_Async_ReadByte(&money_l);
       flag = 5 ;
    }
    else if( flag == 5 )
    {
       ret = Usart_Async_ReadByte(&money_h);
       money = money_l + (money_h << 8) ;
       flag = 6 ;
    }
  
}


void Check_Pass(void)
{
    if( flag == 2 )
    {
        password = pass_l + ( pass_h << 8 ) ;
        for( user = 1 ; user < 4 ; user++ )
        {
            ret = EEPROM_ReadData( (0x00 + user - 1) , &EEPROM_data ) ;
            if( EEPROM_data == password )
            {
                check = PASSWORD_CORRECT ;
                ret = Usart_Async_WriteByte(check);
                flag = 3 ;
                break;
            }
            if( user == 3 )
            {
                check = PASSWORD_INCORRECT ;
                ret = Usart_Async_WriteByte(check);
                flag = 3; 
            }
        }

        
    }
    
}





#endif
