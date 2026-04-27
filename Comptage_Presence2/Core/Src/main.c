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
#include "vl53l5cx_api.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
 // Le fichier principal du driver ST

#define THRESHOLD_MM 1000 // Ton seuil de 1 mètre

// États de la machine à états pour le tracking
typedef enum {
    STATE_IDLE,
    STATE_ENTERING_LR, // Objet détecté col 3, attend col 7
    STATE_LEAVING_LR,  // Objet détecté col 7, attend sortie col 7
    STATE_ENTERING_RL, // Objet détecté col 4, attend col 0
    STATE_LEAVING_RL   // Objet détecté col 0, attend sortie col 0
} PassageState_t;

PassageState_t current_state = STATE_IDLE;
int compteur_passages = 0;

VL53L5CX_Configuration 	Dev;
VL53L5CX_ResultsData 	Results;

// Fonction utilitaire pour calculer la moyenne d'une colonne (0 à 7)
uint16_t get_column_average(VL53L5CX_ResultsData *pResults, uint8_t col) {
    uint32_t sum = 0;
    uint8_t valid_zones = 0;

    for (int row = 0; row < 8; row++) {
        uint8_t zone_index = (row * 8) + col;

        // On vérifie si la mesure de la zone est valide (le status 5 ou 9 indique généralement une bonne mesure)
        if (pResults->target_status[VL53L5CX_NB_TARGET_PER_ZONE * zone_index] == 5 ||
            pResults->target_status[VL53L5CX_NB_TARGET_PER_ZONE * zone_index] == 9) {

            sum += pResults->distance_mm[VL53L5CX_NB_TARGET_PER_ZONE * zone_index];
            valid_zones++;
        }
    }

    // Si aucune zone de la colonne ne renvoie une distance valide, on renvoie une valeur très haute
    if (valid_zones == 0) return 9999;

    return (uint16_t)(sum / valid_zones);
}
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
  /* USER CODE BEGIN SysInit */

    // --- FORÇAGE MANUEL DE PA15 EN I2C2_SDA ---
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;      // Open Drain
    GPIO_InitStruct.Pull = GPIO_PULLUP;          // Pull-up
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;   // AF4 pour I2C2
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_I2C2_Init(); // Maintenant, quand cette fonction s'exécute, PA15 est déjà prête.
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
  // 1. Initialisation des broches du capteur
    HAL_GPIO_WritePin(LPn_GPIO_Port, LPn_Pin, GPIO_PIN_SET); // Activation I2C
    HAL_GPIO_WritePin(I2C_RST_GPIO_Port, I2C_RST_Pin, GPIO_PIN_RESET); // Pas de reset matériel
    HAL_Delay(100);

    // 2. Initialisation du capteur VL53L5CX via le driver
    Dev.platform.address = 0x52; // Adresse I2C par défaut
    Dev.platform.i2c_handle = &hi2c_sensor; // Remplace par ton instance I2C (ex: &hi2c2)

    uint8_t isAlive = 0;
    vl53l5cx_is_alive(&Dev, &isAlive);
    if(isAlive) {
        vl53l5cx_init(&Dev);
        vl53l5cx_set_resolution(&Dev, VL53L5CX_RESOLUTION_8X8); // Matrice 8x8
        vl53l5cx_set_ranging_frequency_hz(&Dev, 15); // 15 Hz est le max officiel en 8x8 continu
        vl53l5cx_start_ranging(&Dev);
    } else {
        // Gérer l'erreur si le capteur ne répond pas
        while(1);
    }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
    uint8_t isReady = 0;
        vl53l5cx_check_data_ready(&Dev, &isReady);

        if(isReady) {
            vl53l5cx_get_ranging_data(&Dev, &Results);

            // Récupération de la moyenne des colonnes d'intérêt
            uint16_t avg_col_0 = get_column_average(&Results, 0);
            uint16_t avg_col_3 = get_column_average(&Results, 3);
            uint16_t avg_col_4 = get_column_average(&Results, 4);
            uint16_t avg_col_7 = get_column_average(&Results, 7);

            // Machine à états selon ta logique exacte
            switch(current_state) {
                case STATE_IDLE:
                    if (avg_col_3 < THRESHOLD_MM) {
                        current_state = STATE_ENTERING_LR;
                    } else if (avg_col_4 < THRESHOLD_MM) {
                        current_state = STATE_ENTERING_RL;
                    }
                    break;

                // --- GESTION GAUCHE VERS DROITE (+1) ---
                case STATE_ENTERING_LR:
                    if (avg_col_7 < THRESHOLD_MM) {
                        // L'objet a atteint la colonne de sortie droite
                        current_state = STATE_LEAVING_LR;
                    } else if (avg_col_3 > THRESHOLD_MM && avg_col_4 > THRESHOLD_MM) {
                        // L'objet a reculé / Faux positif
                        current_state = STATE_IDLE;
                    }
                    break;

                case STATE_LEAVING_LR:
                    if (avg_col_7 > THRESHOLD_MM) {
                        // L'objet est totalement sorti
                        compteur_passages++;
                        current_state = STATE_IDLE;
                        HAL_GPIO_TogglePin(LED_Status_GPIO_Port, LED_Status_Pin); // Petit clignotement de ta LED !
                        printf("Passage G->D | Compteur : %d\r\n", compteur_passages);
                    }
                    break;

                // --- GESTION DROITE VERS GAUCHE (-1) ---
                case STATE_ENTERING_RL:
                    if (avg_col_0 < THRESHOLD_MM) {
                        // L'objet a atteint la colonne de sortie gauche
                        current_state = STATE_LEAVING_RL;
                    } else if (avg_col_4 > THRESHOLD_MM && avg_col_3 > THRESHOLD_MM) {
                        // L'objet a reculé / Faux positif
                        current_state = STATE_IDLE;
                    }
                    break;

                case STATE_LEAVING_RL:
                    if (avg_col_0 > THRESHOLD_MM) {
                        // L'objet est totalement sorti
                        compteur_passages--;
                        current_state = STATE_IDLE;
                        HAL_GPIO_TogglePin(LED_Status_GPIO_Port, LED_Status_Pin);
                        printf("Passage D->G | Compteur : %d\r\n", compteur_passages);
                    }
                    break;
            }
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  hi2c2.Init.Timing = 0x00503D58;
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
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
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
