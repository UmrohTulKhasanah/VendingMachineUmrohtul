/*
 * myTask.h
 *
 *  Created on: Nov 24, 2019
 *      Author: Umroh Tul Khasanah
 */

#ifndef INC_MYTASK_H_
#define INC_MYTASK_H_

#include "main.h"
#define buzzer(state)		{ HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, (state)? GPIO_PIN_SET:GPIO_PIN_RESET); }

#define ledDrop(state)		{ HAL_GPIO_WritePin(LED_DROP_GPIO_Port, LED_DROP_Pin, (state)? GPIO_PIN_RESET:GPIO_PIN_SET);}
#define led500(state)		{ HAL_GPIO_WritePin(LED_500_GPIO_Port, LED_500_Pin, (state)? GPIO_PIN_RESET:GPIO_PIN_SET);}
#define led1000(state)		{ HAL_GPIO_WritePin(LED_1000_GPIO_Port, LED_1000_Pin, (state)? GPIO_PIN_RESET:GPIO_PIN_SET);}

void Task_init(void);
void Task_run(void);
_Bool PB_Process(void);
_Bool PB_Cancel(void);
_Bool PB_500(void);
_Bool PB_1000(void);


#endif /* INC_MYTASK_H_ */
