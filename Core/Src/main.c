/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "define.h"
#include "PL_timer.h"
#include "PL_lcd.h"
#include "PL_sensor.h"
#include "PL_speaker.h"
#include "PL_motor.h"
#include "Control_motor.h"
#include "Control_sensor.h"
#include "PID_wall.h"
#include "mode_selection.h"
#include "turning_parameter.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
 // setbuf(stdout, NULL);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM6_Init();
  MX_I2C1_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM15_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  init_WallControl();
  pl_motor_init();
  pl_speaker_init();
  pl_timer_init();
  pl_lcd_init();
  motor_init();
  record_reset();
  input_parameter();

  pl_lcd_puts("Hello");
  pl_lcd_pos(1, 0);
  pl_lcd_puts("   STM32");
  HAL_Delay(500);
  pl_lcd_clear();

  if(pl_getbatt() < LIPO_LIMIT){
	  pl_lcd_clear();
	  pl_lcd_pos(0, 0);
	  pl_lcd_puts("LIPO");
	  pl_lcd_pos(1, 0);
	  pl_lcd_puts("error");
	  HAL_Delay(1000);
  }

  uint16_t cnt = 0;
  unsigned char mode1,mode2;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	  mode1=mode_decision(0,mode1);
	  wait_ms(1000);
	  mode2=mode_decision(1,mode2);
	  mode_execution(mode1,mode2);
// test LED1
//	  HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,GPIO_PIN_SET);
//	  HAL_Delay(1000);
//	  HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,GPIO_PIN_RESET);
//	  HAL_Delay(1000);
// test LED2
//	  HAL_GPIO_WritePin(INTERFACELED_GPIO_Port,INTERFACELED_Pin,GPIO_PIN_SET);
//	  HAL_Delay(500);
//	  HAL_GPIO_WritePin(INTERFACELED_GPIO_Port,INTERFACELED_Pin,GPIO_PIN_RESET);
//	  HAL_Delay(500);
// test SWITCH_1,2
//	 if (HAL_GPIO_ReadPin(SWITCH_1_GPIO_Port,SWITCH_1_Pin)==0){
//		 HAL_GPIO_WritePin(INTERFACELED_GPIO_Port,INTERFACELED_Pin,GPIO_PIN_SET);
//		 HAL_Delay(100);
//	 }
//	 if (HAL_GPIO_ReadPin(SWITCH_2_GPIO_Port,SWITCH_2_Pin)==0){
//		 HAL_GPIO_WritePin(INTERFACELED_GPIO_Port,INTERFACELED_Pin,GPIO_PIN_RESET);
//		 HAL_Delay(100);
//	 }
// test USART1
//	 uint8_t hello[] = "Hello World\n\r";
//	 HAL_UART_Transmit(&huart2, hello, sizeof(hello), 1000);
// test USART2
//	  setbuf(stdout, NULL);
//     uint8_t hello[] = "Hello World\n\r";
//     printf("hello=%s", hello);
//     uint8_t hoge = 3;
//     float PI=3.14;
//     printf("hoge=%d\n", hoge);
//     printf("M_PI=%f\n", PI); // @suppress("Float formatting support")
// test timer
//     HAL_GPIO_WritePin(INTERFACELED_GPIO_Port,INTERFACELED_Pin,GPIO_PIN_SET);
//     wait_ms(500);
//     HAL_GPIO_WritePin(INTERFACELED_GPIO_Port,INTERFACELED_Pin,GPIO_PIN_RESET);
//     wait_ms(500);
// test speaker
//   if (HAL_GPIO_ReadPin(SWITCH_1_GPIO_Port,SWITCH_1_Pin)==0){
//    	HAL_GPIO_WritePin(INTERFACELED_GPIO_Port,INTERFACELED_Pin,GPIO_PIN_SET);
//     	HAL_Delay(1000);
//		HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);
//		while(HAL_GPIO_ReadPin(SWITCH_1_GPIO_Port,SWITCH_1_Pin)==1){
//		}
//		HAL_Delay(100);
//	 	HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_2);
//   }
// test LCD
//	 char strBuffer[17] = {0};
//	 sprintf(strBuffer, "CNT=%04d", cnt);
//	 cnt++;
//	 pl_lcd_pos(1, 0);
//	 pl_lcd_puts(strBuffer);
// sensor test
//     HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer,sizeof(g_ADCBuffer) / sizeof(uint16_t));
//	 printf("BATT=%f\n",g_V_batt);
//     printf("SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d\n", g_sensor[0][0],g_sensor[1][0],g_sensor[2][0],g_sensor[3][0]);
//     wait_ms(500);
// motor test
//	  if (HAL_GPIO_ReadPin(SWITCH_1_GPIO_Port,SWITCH_1_Pin)==0){
//    	HAL_GPIO_WritePin(INTERFACELED_GPIO_Port,INTERFACELED_Pin,GPIO_PIN_SET);
//     	HAL_Delay(1000);
//		HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_Port,MOTOR_ENABLE_Pin,GPIO_PIN_SET);
//		g_TargetStraight.velocity=100;
//		HAL_GPIO_WritePin(MD_RESET_GPIO_Port,MD_RESET_Pin,GPIO_PIN_SET);
//		HAL_Delay(3);
//		HAL_GPIO_WritePin(MD_RESET_GPIO_Port,MD_RESET_Pin,GPIO_PIN_RESET);
//		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
//		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
//		HAL_Delay(5000);
//	 	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
//	 	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
//	 	HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_Port,MOTOR_ENABLE_Pin,GPIO_PIN_RESET);
//	 	HAL_Delay(1000);
//		HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_Port,MOTOR_ENABLE_Pin,GPIO_PIN_SET);
//		g_TargetStraight.velocity=-100;
//		HAL_GPIO_WritePin(MD_RESET_GPIO_Port,MD_RESET_Pin,GPIO_PIN_SET);
//		HAL_Delay(3);
//		HAL_GPIO_WritePin(MD_RESET_GPIO_Port,MD_RESET_Pin,GPIO_PIN_RESET);
//		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
//		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
//		HAL_Delay(5000);
//	 	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
//	 	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
//	 	HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_Port,MOTOR_ENABLE_Pin,GPIO_PIN_RESET);
//	 	HAL_Delay(1000);
//	  }

//	  if (HAL_GPIO_ReadPin(SWITCH_1_GPIO_Port,SWITCH_1_Pin)==0){
// test_speaker_music
    //pl_test_speaker();
// test_motor
//     pl_test_motor();
//      control_test_motor(1);
//	  }



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
