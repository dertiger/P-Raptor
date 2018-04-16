/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_CONFIG_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "Application.h"
#include "LED.h";

void RTOS_Init(void) {
 /*! \todo Create tasks here */
	xTaskHandle taskHndl;
	if(xTaskCreate(BlingTask, "Blingy1", configMINIMAL_STACK_SIZE, (void*) NULL, tskIDLE_PRIORITY, &taskHndl)!=pdPASS){
		for(;;){}	// ERROR handling for tasks to be implemented
	}
	if(xTaskCreate(BlingTask, "Blingy2", configMINIMAL_STACK_SIZE, (void*) NULL, tskIDLE_PRIORITY, &taskHndl)!=pdPASS){
		for(;;){}	// ERROR handling for tasks to be implemented
	}
	if(xTaskCreate(Busy, "Busy", configMINIMAL_STACK_SIZE, (void*) NULL, tskIDLE_PRIORITY, &taskHndl)!=pdPASS){
		for(;;){}	// ERROR handling for tasks to be implemented
	}
}

void RTOS_Deinit(void) {
  /* nothing needed for now */
}

static void BlingTask (void *pvParameters)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for(;;){
		LED1_Neg();
		vTaskDelayUntil(&xLastWakeTime, 100/portTICK_PERIOD_MS);
	}
}

static void Busy (void *param)
{
	for(;;){
		LED1_Neg();
		vTaskDelay(pdMS_TO_TICKS(150));
	}
}

#endif /* PL_CONFIG_HAS_RTOS */
