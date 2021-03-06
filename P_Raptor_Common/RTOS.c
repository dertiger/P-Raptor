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
#include "LED.h"
#include "Reflectance.h"
#include "Motor.h"

void RTOS_Init(void) {
 /*! \todo Create tasks here */
	xTaskHandle taskHndl;
#if 0

	if(xTaskCreate(ReflectanceTask, "Reflectance", configMINIMAL_STACK_SIZE, (void*) NULL, tskIDLE_PRIORITY, &taskHndl)!=pdPASS){
		for(;;){}
	}

	if(xTaskCreate(BlingTask, "Blingy2", configMINIMAL_STACK_SIZE, (void*) NULL, tskIDLE_PRIORITY, &taskHndl)!=pdPASS){
		for(;;){}	// ERROR handling for tasks to be implemented
	}
	if(xTaskCreate(Busy, "Busy", configMINIMAL_STACK_SIZE, (void*) NULL, tskIDLE_PRIORITY, &taskHndl)!=pdPASS){
			for(;;){}	// ERROR handling for tasks to be implemented
		}

	if(xTaskCreate(KeyHandler, "KeyHandler", configMINIMAL_STACK_SIZE, (void*) NULL, tskIDLE_PRIORITY, &taskHndl)!=pdPASS){
				for(;;){}	// ERROR handling for tasks to be implemented
			}

	#endif
	if(xTaskCreate(BlingTask, "Tastendruck", 600/sizeof(StackType_t), (void*) NULL, tskIDLE_PRIORITY, &taskHndl)!=pdPASS){
			for(;;){}	// ERROR handling for tasks to be implemented
		}
}

void RTOS_Deinit(void) {
  /* nothing needed for now */
}

#if 0
static void ReflectanceTask (void *pvParameters){
	/*if(REF_GetLineKind()==1){
		MOT_SetSpeedPercent(MOT_MOTOR_LEFT, 10);
		MOT_SetSpeedPercent(MOT_MOTOR_RIGHT, 10);
	}
	else{
		MOT_SetSpeedPercent(MOT_MOTOR_LEFT, 0);
		MOT_SetSpeedPercent(MOT_MOTOR_RIGHT, 0);
	}*/
}

static void Busy (void *param)
{
	int counter = 0;
	for(;;){
		TACHO_Sample();
		counter++;
		if(counter>=10){
			TACHO_CalcSpeed();
			counter = 0;
		}
		//EVNT_HandleEvent(APP_EventHandler,TRUE);
		//KEY_Scan();
		/*if(REF_GetLineKind() != REF_LINE_STRAIGHT){
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
		}*/
		//KEYDBNC_Process();

		vTaskDelay(pdMS_TO_TICKS(10));
	}
}
#endif

static void BlingTask (void *pvParameters)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for(;;){
		//LED1_Neg();
		EVNT_HandleEvent(APP_EventHandler,TRUE);
		//KEY_Scan();
		KEYDBNC_Process();
		vTaskDelayUntil(&xLastWakeTime, 100/portTICK_PERIOD_MS);
	}
}

static void KeyHandler(void *param)
{
	  EVNT_HandleEvent(APP_EventHandler,TRUE);
	  //KEY_Scan();
	  KEYDBNC_Process();
	  vTaskDelay(pdMS_TO_TICKS(5));
}

#endif /* PL_CONFIG_HAS_RTOS */
