/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "vl53l5cx_api.h"
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
I2C_HandleTypeDef hi2c2;

/* USER CODE BEGIN PV */
VL53L5CX_Configuration 	Dev;
VL53L5CX_ResultsData 	Results;

#define DIST_THRESHOLD_MM 1000  // Le seuil de 1m dont tu parlais

// Définition des états de notre système
typedef enum {
    STATE_IDLE,
    STATE_WAIT_EXIT_RIGHT, // Objet venu de gauche (Col 3), attendu à droite (Col 7)
    STATE_WAIT_EXIT_LEFT   // Objet venu de droite (Col 4), attendu à gauche (Col 0)
} CountState_t;

CountState_t currentState = STATE_IDLE;
int32_t passageCounter = 0;
uint8_t flagTargetInExitCol = 0; // Marqueur pour savoir si l'objet a atteint la sortie
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
/* USER CODE BEGIN PFP */
uint32_t Get_Column_Average(VL53L5CX_ResultsData *pResults, uint8_t col_index);
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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
  // 1. Allumage matériel du capteur via la broche LPn (sur PA10)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); // Éteint
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);   // Allume
    HAL_Delay(100); // Laisse le temps au firmware du capteur de booter

    // 2. Initialisation de l'API (Platform I2C doit être implémenté dans le driver)
    // Assure-toi que Dev.platform pointe bien vers hi2c2 dans ton code d'interface
    uint8_t isAlive = 0;
    vl53l5cx_is_alive(&Dev, &isAlive);

    if (isAlive) {
        vl53l5cx_init(&Dev);
        vl53l5cx_set_resolution(&Dev, VL53L5CX_RESOLUTION_8X8);
        vl53l5cx_set_ranging_frequency_hz(&Dev, 15); // 15 Hz est un bon compromis pour 8x8
        vl53l5cx_start_ranging(&Dev);
    }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
      {
          uint8_t isReady = 0;
          // On vérifie si une nouvelle trame 8x8 est disponible
          vl53l5cx_check_data_ready(&Dev, &isReady);

          if (isReady) {
              // Lecture des données
              vl53l5cx_get_ranging_data(&Dev, &Results);

              // Calcul de la moyenne pour nos colonnes clés
              uint32_t avgCol0 = Get_Column_Average(&Results, 0);
              uint32_t avgCol3 = Get_Column_Average(&Results, 3);
              uint32_t avgCol4 = Get_Column_Average(&Results, 4);
              uint32_t avgCol7 = Get_Column_Average(&Results, 7);

              // Machine d'état pour le comptage bidirectionnel
              switch(currentState) {

                  case STATE_IDLE:
                      if (avgCol3 < DIST_THRESHOLD_MM) {
                          // Détection d'un objet venant de la gauche (franchissement col 3)
                          currentState = STATE_WAIT_EXIT_RIGHT;
                          flagTargetInExitCol = 0;
                      }
                      else if (avgCol4 < DIST_THRESHOLD_MM) {
                          // Détection d'un objet venant de la droite (franchissement col 4)
                          currentState = STATE_WAIT_EXIT_LEFT;
                          flagTargetInExitCol = 0;
                      }
                      break;

                  case STATE_WAIT_EXIT_RIGHT:
                      if (avgCol7 < DIST_THRESHOLD_MM) {
                          // L'objet a progressé jusqu'à la colonne 7 (la sortie à droite)
                          flagTargetInExitCol = 1;
                      }
                      else if (flagTargetInExitCol && avgCol7 >= DIST_THRESHOLD_MM) {
                          // L'objet était sur la colonne 7 et a maintenant quitté le champ de vision
                          passageCounter++;  // +1 au compteur
                          currentState = STATE_IDLE; // On se remet en attente d'un nouveau passage
                      }
                      // Si avgCol3 redevient > seuil sans que flagTargetInExitCol soit à 1,
                      // la personne a fait demi-tour. Tu pourrais ajouter un reset ici.
                      break;

                  case STATE_WAIT_EXIT_LEFT:
                      if (avgCol0 < DIST_THRESHOLD_MM) {
                          // L'objet a progressé jusqu'à la colonne 0 (la sortie à gauche)
                          flagTargetInExitCol = 1;
                      }
                      else if (flagTargetInExitCol && avgCol0 >= DIST_THRESHOLD_MM) {
                          // L'objet était sur la colonne 0 et a maintenant quitté le champ de vision
                          passageCounter--;  // -1 au compteur
                          currentState = STATE_IDLE;
                      }
                      break;
              }
          }
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 20;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
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

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x30D29DE4;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(VL53_LPn_GPIO_Port, VL53_LPn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : VL53_INT_Pin */
  GPIO_InitStruct.Pin = VL53_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(VL53_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : VL53_LPn_Pin */
  GPIO_InitStruct.Pin = VL53_LPn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(VL53_LPn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
uint32_t Get_Column_Average(VL53L5CX_ResultsData *pResults, uint8_t col_index) {
    uint32_t sum = 0;
    uint8_t valid_zones = 0;

    for (int row = 0; row < 8; row++) {
        uint8_t zone = (row * 8) + col_index; // Calcul de l'index 0 à 63

        // On vérifie que la mesure est valide (les statuts 5 et 9 sont généralement les "bons" statuts chez ST)
        if (pResults->target_status[VL53L5CX_NB_TARGET_PER_ZONE * zone] == 5 ||
            pResults->target_status[VL53L5CX_NB_TARGET_PER_ZONE * zone] == 9) {

            sum += pResults->distance_mm[VL53L5CX_NB_TARGET_PER_ZONE * zone];
            valid_zones++;
        }
    }

    if (valid_zones == 0) return 9999; // Valeur infinie si aucun objet détecté
    return (sum / valid_zones);
}
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
#ifdef USE_FULL_ASSERT
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
