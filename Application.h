/* 
 * File:   Application.h
 * Author: Alielden
 *
 * Created on September 9, 2023, 7:04 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section :  Includes */
#include "Mca_Layer/GPIO/hal_gpio.h"
#include "Ecua_Layer/LED/ecu_led.h"
#include "Ecua_Layer/BUTTON/ecu_button.h"
#include "Ecua_Layer/RELAY/ecu_relay.h"
#include "Ecua_Layer/DC_MOTOR/ecu_dc_motor.h"
#include "Ecua_Layer/7_SEGMENT/ecu_seven_seg.h"
#include "Ecua_Layer/KEYPAD/ecu_keypad.h"
#include "Ecua_Layer/LCD/ecu_lcd.h"
#include "Mca_Layer/INTERRUPT/hal_external_interrupt.h"
#include "Mca_Layer/INTERRUPT/hal_internal_interrupt.h"
#include "Mca_Layer/INTERRUPT/hal_interrupt_manager.h"
#include "Mca_Layer/INTERRUPT/hal_interrupt_config.h"
#include "Mca_Layer/EEPROM/hal_eeprom.h"
#include "Mca_Layer/ADC/hal_adc.h"
#include "Mca_Layer/TIMER0/hal_timer0.h"
#include "Mca_Layer/TIMER1/hal_timer_1.h"
#include "Mca_Layer/TIMER2/hal_timer2.h"
#include "Mca_Layer/TIMER3/hal_timer3.h"
#include "Mca_Layer/CCP1/hal_ccp.h"
#include "Mca_Layer/usart/hal_usart.h"
#include <xc.h>


 /* Section : Macros */



/* Section : Macros Functions */

#define FLOATING      2
#define CONFIRMED     1
#define NOT_CONFIRMED 0


#define PASSWORD_CORRECT   1
#define PASSWORD_INCORRECT 0

#define CHECK_ACCOUNT  1
#define WITHDRAW       2
#define DEPOSIT        3

#define CPU1_CFG      1
#define CPU2_CFG      2

#define CPU_CFG       (CPU1_CFG)  

/* Section : Data type Declaration */


/* Section : Functions Declaration */

void APPLICATION_INTIALIZE(void);

#if (CPU_CFG == CPU1_CFG )
void lcd_welcome(void);
void lcd_main(void);
void lcd_Enter_Pass(void);
void lcd_Password_Correct(void);
void lcd_Password_Incorrect(void);
void lcd_Check_Account(void);
void lcd_Withdraw(void);
void lcd_Deposite(void);
void lcd_Error(void);
void Take_Val_Keypad(void);
void Check_Password(void);
void RX_Callback(void);
#endif


#if (CPU_CFG == CPU2_CFG )
void RX_Callback(void);
void Check_Pass(void);
#endif


#endif	/* APPLICATION_H */

