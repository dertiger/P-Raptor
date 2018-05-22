/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module using semaphores.
 */

/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module using semaphores.
 */

#include "Platform.h" /* interface to the platform */
#if PL_CONFIG_HAS_SEMAPHORE
#include "FRTOS1.h"
#include "Sem.h"
#include "LED.h"
#include "CLS1.h"

//static xSemaphoreHandle sem = NULL;
static TaskHandle_t taskHndl;

static void vSlaveTask(void *pvParameters) {
	xSemaphoreHandle sem = (xSemaphoreHandle)pvParameters;
	if (sem != NULL)
	{
		for(;;){
			if(xSemaphoreTake(sem, portMAX_DELAY) == pdPASS)
			{
				LED1_Neg();
			}
		}
	}
	else
	{
		for(;;)
		{
			CLS1_SendStr("Semaphore not installed",CLS1_GetStdio()->stdErr);
		}
	}
	/*! \todo Implement functionality */
}

static void vMasterTask(void *pvParameters) {
  /*! \todo send semaphore from master task to slave task */
	xSemaphoreHandle sem = NULL;
	(void) pvParameters;
	sem = xSemaphoreCreateBinary();
	if(sem == NULL)
	{
		CLS1_SendStr("Semaphore was not created",CLS1_GetStdio()->stdErr);
		for(;;){}
	}
	vQueueAddToRegistry(sem, "IPC_Sem");
	if(xTaskCreate(vSlaveTask, "Slave", 600/sizeof(StackType_t), sem, tskIDLE_PRIORITY+1, NULL)!=pdPASS){
		CLS1_SendStr("Not enough memory for slave",CLS1_GetStdio()->stdErr);
		for(;;){}	// ERROR handling for tasks to be implemented
	}
	for(;;)
	{
		(void)xSemaphoreGive(sem);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void SEM_Deinit(void) {
	vTaskDelete(taskHndl);
}

/*! \brief Initializes module */
void SEM_Init(void) {
	if(xTaskCreate(vMasterTask, "Master", 600/sizeof(StackType_t), (void*) NULL, tskIDLE_PRIORITY+1, &taskHndl)!=pdPASS){
		for(;;){}	// ERROR handling for tasks to be implemented
	}

}
#endif /* PL_CONFIG_HAS_SEMAPHORE */
