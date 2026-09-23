/*
 * main.c
 *
 *  Created on: Sep 23, 2026
 *      Author: Filopatir Samir
 */
/*
 * main.c
 * Created on: Sep 23, 2026
 * Author: Filopatir Samir
 */

#include "LIB/STD_types.h"
#include "LIB/BitMath.h"
#include "MCAL/MADC/ADC.h"
#include "HAL/HLM35/LM35.h"


#define LED_PORT_REG   (*(volatile u8*)(0x32)) /* PORTD */
#define LED_DDR_REG    (*(volatile u8*)(0x31)) /* DDRD  */
#define RED_LED_PIN    7

#define TEMP_THRESHOLD 40

int main(void)
{
    /* 1. Initialize MADC with Prescaler 64 and VREF = AVCC */
    MADC_voidInit(ADC_PRESCALLER64, ADC_REF_AVCC);

    /* 2. Initialize LM35 */
    LM35_voidInit();

    /* 3. Set Red LED pin as Output */
    SET_BIT(LED_DDR_REG, RED_LED_PIN);

    u8 L_u8CurrentTemp = 0;

    while (1)
    {
        /* 4. Read current temperature from LM35 */
        L_u8CurrentTemp = LM35_u8GetTemperature();

        /* 5. Check Threshold for Temperature (DTC 0x52) */
        if (L_u8CurrentTemp > TEMP_THRESHOLD)
        {

            SET_BIT(LED_PORT_REG, RED_LED_PIN);
        }
        else
        {

            CLR_BIT(LED_PORT_REG, RED_LED_PIN);
        }
    }
}
