#ifndef __BOARD_H__
#define __BOARD_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/
extern SPI_HandleTypeDef hspi1;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);
void MX_Board_Init(void);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
