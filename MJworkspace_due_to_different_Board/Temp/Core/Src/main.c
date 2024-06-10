/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "menuHandler.h"
#include "shotHolder.h"
#include "liquidcrystal_i2c.h"
#include "servo.h"
#include "encoder.h"
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
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim9;

osThreadId defaultTaskHandle;
osThreadId diodeDetectorHandle;
osThreadId holeStateHandle;
osThreadId displayMenuHandle;
osThreadId servoPourHandle;
/* USER CODE BEGIN PV */
/* delete them later */
uint8_t holeState1 = 0;
uint8_t menuCursor = 0;
uint8_t subMenu = 0;

/**
 * @brief Assigns function names to each substructure and drink position structure
 *
 *  This allows to use "handleLeft", "handleRight" and "clickedReact" only for better clarity
 */
sub_t SUB1 = {.leftReact = leftReact1, .rightReact = rightReact1, .clickedReact=clickedReact1};
sub_t SUB2 = {.leftReact = leftReact2, .rightReact = rightReact2, .clickedReact=clickedReact2};
sub_t SUB3 = {.leftReact = leftReact3, .rightReact = rightReact3, .clickedReact=clickedReact3};
menu_t menu = {.handleLeft = handleLeft, .handleRight = handleRight, .clickedReact=handleClicked};
drinkpos_t drinkpos = {{0,0,0,0}, .drinkChange = drinkChange, .drinkReset = drinkReset};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM9_Init(void);
void StartDefaultTask(void const * argument);
void diodeDetector_Init(void const * argument);
void holeState_Init(void const * argument);
void displayMenu_Init(void const * argument);
void pourInit(void const * argument);

/* USER CODE BEGIN PFP */
/*

*/
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
  menu.currentMenu = &SUB1;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_TIM9_Init();
  /* USER CODE BEGIN 2 */
  encoderInit();
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
  initServo();
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityAboveNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of diodeDetector */
  osThreadDef(diodeDetector, diodeDetector_Init, osPriorityIdle, 0, 128);
  diodeDetectorHandle = osThreadCreate(osThread(diodeDetector), NULL);

  /* definition and creation of holeState */
  osThreadDef(holeState, holeState_Init, osPriorityNormal, 0, 128);
  holeStateHandle = osThreadCreate(osThread(holeState), NULL);

  /* definition and creation of displayMenu */
  osThreadDef(displayMenu, displayMenu_Init, osPriorityIdle, 0, 128);
  displayMenuHandle = osThreadCreate(osThread(displayMenu), NULL);

  /* definition and creation of servoPour */
  osThreadDef(servoPour, pourInit, osPriorityHigh, 0, 128);
  servoPourHandle = osThreadCreate(osThread(servoPour), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 25000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 60000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM9 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM9_Init(void)
{

  /* USER CODE BEGIN TIM9_Init 0 */

  /* USER CODE END TIM9_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM9_Init 1 */

  /* USER CODE END TIM9_Init 1 */
  htim9.Instance = TIM9;
  htim9.Init.Prescaler = 266;
  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim9.Init.Period = 3600;
  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_PWM_Init(&htim9) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 249;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM9_Init 2 */

  /* USER CODE END TIM9_Init 2 */
  HAL_TIM_MspPostInit(&htim9);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|pump_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, diode1_Pin|diode2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, diode3_Pin|diode4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PE2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : CS_I2C_SPI_Pin pump_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|pump_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PE4 PE5 MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : OTG_FS_PowerSwitchOn_Pin diode1_Pin diode2_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin|diode1_Pin|diode2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : holeStatePin1_Pin holeStatePin2_Pin */
  GPIO_InitStruct.Pin = holeStatePin1_Pin|holeStatePin2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PDM_OUT_Pin */
  GPIO_InitStruct.Pin = PDM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : I2S3_WS_Pin */
  GPIO_InitStruct.Pin = I2S3_WS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(I2S3_WS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI1_SCK_Pin SPI1_MISO_Pin SPI1_MOSI_Pin */
  GPIO_InitStruct.Pin = SPI1_SCK_Pin|SPI1_MISO_Pin|SPI1_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : diode3_Pin diode4_Pin */
  GPIO_InitStruct.Pin = diode3_Pin|diode4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : holeStatePin3_Pin */
  GPIO_InitStruct.Pin = holeStatePin3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(holeStatePin3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : holeStatePin4_Pin */
  GPIO_InitStruct.Pin = holeStatePin4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(holeStatePin4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CLK_IN_Pin PB12 */
  GPIO_InitStruct.Pin = CLK_IN_Pin|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
                           Audio_RST_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : I2S3_MCK_Pin I2S3_SCK_Pin I2S3_SD_Pin */
  GPIO_InitStruct.Pin = I2S3_MCK_Pin|I2S3_SCK_Pin|I2S3_SD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : VBUS_FS_Pin */
  GPIO_InitStruct.Pin = VBUS_FS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VBUS_FS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : OTG_FS_ID_Pin OTG_FS_DM_Pin OTG_FS_DP_Pin */
  GPIO_InitStruct.Pin = OTG_FS_ID_Pin|OTG_FS_DM_Pin|OTG_FS_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : enc_CLICK_Pin enc_DATA_Pin enc_CLK_Pin */
  GPIO_InitStruct.Pin = enc_CLICK_Pin|enc_DATA_Pin|enc_CLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */

  /* Infinite loop */
  for(;;)
  {

	  osDelay(10000);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_diodeDetector_Init */
/**
* @brief Function implementing the diodeDetector thread.
*
* This thread is responsible for LED lightning when a shot glass is detected on holders positions
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_diodeDetector_Init */
void diodeDetector_Init(void const * argument)
{
  /* USER CODE BEGIN diodeDetector_Init */
  /* Infinite loop */
  for(;;)
  {

	if (drinkpos.postitionOfDrinks[0] == 1){
		HAL_GPIO_WritePin(diode1_GPIO_Port, diode1_Pin, 1);
	}
	else{
		HAL_GPIO_WritePin(diode1_GPIO_Port, diode1_Pin, 0);
	}
	if (drinkpos.postitionOfDrinks[1] == 1){
		HAL_GPIO_WritePin(diode2_GPIO_Port, diode2_Pin, 1);
	}
	else{
		HAL_GPIO_WritePin(diode2_GPIO_Port, diode2_Pin, 0);
	}
	if (drinkpos.postitionOfDrinks[2] == 1){
		HAL_GPIO_WritePin(diode3_GPIO_Port, diode3_Pin, 1);
	}
	else{
		HAL_GPIO_WritePin(diode3_GPIO_Port, diode3_Pin, 0);
	}
	if (drinkpos.postitionOfDrinks[3] == 1){
		HAL_GPIO_WritePin(diode4_GPIO_Port, diode4_Pin, 1);
	}
	else{
		HAL_GPIO_WritePin(diode4_GPIO_Port, diode4_Pin, 0);
	}

	osDelay(100);
  }
  /* USER CODE END diodeDetector_Init */
}

/* USER CODE BEGIN Header_holeState_Init */
/**
* @brief Function implementing the holeState thread.
*
* This thread is responsible for checking whether the glass is in position or has been removed from it
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_holeState_Init */
void holeState_Init(void const * argument)
{
  /* USER CODE BEGIN holeState_Init */
  /* Infinite loop */
  for(;;)
  {

	if (HAL_GPIO_ReadPin(holeStatePin1_GPIO_Port, holeStatePin1_Pin) == 0){
		drinkpos.drinkChange(&drinkpos, 1);
	}
	else{
		drinkpos.drinkChange(&drinkpos, 11);
	}

	if (HAL_GPIO_ReadPin(holeStatePin2_GPIO_Port, holeStatePin2_Pin) == 0){
		drinkpos.drinkChange(&drinkpos, 2);
	}
	else{
		drinkpos.drinkChange(&drinkpos, 22);
	}
	if (HAL_GPIO_ReadPin(holeStatePin3_GPIO_Port, holeStatePin3_Pin) == 0){
		drinkpos.drinkChange(&drinkpos, 3);
	}
	else{
		drinkpos.drinkChange(&drinkpos, 33);
	}
	if (HAL_GPIO_ReadPin(holeStatePin4_GPIO_Port, holeStatePin4_Pin) == 0){
		drinkpos.drinkChange(&drinkpos, 4);
	}
	else{
		drinkpos.drinkChange(&drinkpos, 44);
	}

    osDelay(100);
  }
  /* USER CODE END holeState_Init */
}

/* USER CODE BEGIN Header_displayMenu_Init */
/**
* @brief Function implementing the displayMenu thread.
*
* This thread is responsible for permanently displaying current menu and current cursor position
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_displayMenu_Init */
void displayMenu_Init(void const * argument)
{
  /* USER CODE BEGIN displayMenu_Init */
  HD44780_Init(2);
  drinkCounterReset();
  menu.subMenuFlag = 1;
  menu.cursorPos = 0;
  menu.menuChanged = 1;
  menu.mililiters = 10;
  /* Infinite loop */
  for(;;)
  {
	  switch(menu.subMenuFlag){
	  	  case 1:
	  		  menu.currentMenu = &SUB1;
	  		  break;
	  	  case 2:
	          menu.currentMenu = &SUB2;
	          break;
	  	  case 3:
	  		  menu.currentMenu = &SUB3;
	  		  break;
	  }
	  if(menu.menuChanged==1){
		  if (menu.currentMenu==&SUB1){
			  defaultMenu();
			  switch(menu.cursorPos){
			  	  case 0:
			  		  defaultMenuCursorPos1();
			  		  break;
			  	  case 1:
			  		  defaultMenuCursorPos2();
			  		  break;
			  	  case 2:
			  		  defaultMenuCursorPos3();
			  		  break;
			  }
		  }
		  if (menu.currentMenu==&SUB2){
			  sub2Menu(&menu);
			  switch(menu.cursorPos){
			  	  case 0:
			  		  sub2MenuCursorPos1();
			  		  break;
			  	  case 1:
			  		  sub2MenuCursorPos2();
			  		  break;
			  }
		  }
		  if (menu.currentMenu==&SUB3){
			  sub3Menu();
			  switch(menu.cursorPos){
			  	  case 0:
			  		  sub3MenuCursorPos1();
			  		  break;
			  	  case 1:
			  		  sub3MenuCursorPos2();
			  		  break;
			  }
		  }
	  menu.menuChanged = 0;
	  }
	osDelay(30);
  }
  /* USER CODE END displayMenu_Init */
}

/* USER CODE BEGIN Header_pourInit */

void pump(int timeOn){
	osDelay(2000);
	HAL_GPIO_WritePin(pump_GPIO_Port, pump_Pin, 1);
	osDelay(timeOn);
	HAL_GPIO_WritePin(pump_GPIO_Port, pump_Pin, 0);
	osDelay(2000);
}
/**
* @brief Function implementing the servoPour thread.
*
* This thread s responsible for adjusting servo to proper positions and pouring correct amount of drink
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_pourInit */
void pourInit(void const * argument)
{
  /* USER CODE BEGIN pourInit */
	menu.pourChanged = 0;
	HAL_GPIO_WritePin(pump_GPIO_Port, pump_Pin, 0);
  /* Infinite loop */
  for(;;)
  {
	if (menu.pourChanged == 1){
		setRotation(10);
		osDelay(1500);
		if (drinkpos.postitionOfDrinks[0] == 1){
			setRotation(58);
			pump(menu.mililiters*200);
			drinkAddCounter1();
		}
		if (drinkpos.postitionOfDrinks[1] == 1){
			setRotation(84);
			pump(menu.mililiters*200);
			drinkAddCounter2();
		}
		if (drinkpos.postitionOfDrinks[2] == 1){
			setRotation(112);
			pump(menu.mililiters*200);
			drinkAddCounter3();
		}
		if (drinkpos.postitionOfDrinks[3] == 1){
			setRotation(141);
			pump(menu.mililiters*200);
			drinkAddCounter4();
		}
		osDelay(500);
		setRotation(180);
		menu.pourChanged = 0;
	}
    osDelay(30);
  }
  /* USER CODE END pourInit */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
