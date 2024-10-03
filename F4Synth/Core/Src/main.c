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
#include "dac.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SYNTH.h"
#include "MIDI.H"
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
//波表合成器
//ch表示MIDI通道序号
u32 Synth_GM(const u32 MIDI[], u8 ch
	, struct MIDI_CTRL midi_ctrl[], struct VCO VCO1[], struct ADSR ADSR1[])
{
    MIDI_Control(&midi_ctrl[ch], MIDI, &ADSR1[ch].ADSR_in);
    VCO1[ch].VCO_freq = midi_ctrl[ch].mid_freq;
    VCO_gen(&VCO1[ch]);
    ADSR(&ADSR1[ch]);
    u32 amp = midi_ctrl[ch].mid_vec * ADSR1[ch].ADSR_out / 10000;
    return amp * (VCO1[ch].VCO_Out)  / 256;
}

//采样播放器
//midi_ch表示MIDI通道序号
//sample_ch表示采样通道序号
u32 Synth_SA(const u32 MIDI[], u8 midi_ch, struct MIDI_CTRL midi_ctrl[], 
				 struct SampleCTRL SaCt1[], u8 sample_ch, const s8 Sample_Audio[], u32 Sample_len)
{
	SaCt1[sample_ch].max_len = Sample_len;
	
    MIDI_Control(&midi_ctrl[midi_ch], MIDI, &SaCt1[sample_ch].trig);
    return Sample(Sample_Audio, &SaCt1[sample_ch]);
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern const signed char SnareTable[6000];
extern const signed char CrashTable[17500];
extern const signed char TomsTable[10000];
extern const signed char TambourineTable[10000];
extern const signed char Tambourine2Table[15000];
extern const unsigned int MIDI_1[];
extern const unsigned int MIDI_2[];
extern const unsigned int MIDI_3[];
extern const unsigned int MIDI_4[];
extern const unsigned int MIDI_5[];
extern const unsigned int MIDI_6[];
extern const unsigned int MIDI_7[];

unsigned int i = 0;
struct SampleCTRL SaCt1[4];
struct MIDI_CTRL midi_ctrl[8];
struct VCO VCO_1[4];
struct ADSR ADSR_1[4];
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
    MX_DAC_Init();
    MX_TIM3_Init();
    /* USER CODE BEGIN 2 */
    HAL_DAC_MspInit(&hdac);
    HAL_TIM_Base_MspInit(&htim3);
    HAL_TIM_Base_Start_IT(&htim3);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    SaCtInit(SaCt1, 4);

    MIDI_CTRL_INIT(midi_ctrl, 8);

    VCO_1[0].idx = 0;
    VCO_1[0].phase = 1;
    VCO_1[0].VCO_wavetype = 4;
    VCO_1[1].idx = 0;
    VCO_1[1].phase = 1;
    VCO_1[1].VCO_wavetype = 0;
	VCO_1[2].idx = 0;
    VCO_1[2].phase = 1;
    VCO_1[2].VCO_wavetype = 0;
    VCO_1[3].idx = 0;
    VCO_1[3].phase = 1;
    VCO_1[3].VCO_wavetype = 3;

    {
        ADSR_1[0].ADSR_enable = 1;
        ADSR_1[0].ADSR_statu = 0;
        ADSR_1[0].ADSR_count = 0;
        ADSR_1[0].A_time = 5;
        ADSR_1[0].A_speed = 2000;
        ADSR_1[0].D_time = 3000;
        ADSR_1[0].D_speed = 3;
        ADSR_1[0].R_time = 0;
        ADSR_1[0].R_speed = 0;
        ADSR_1[0].velocity = 255;
        ADSR_1[1].ADSR_enable = 1;
        ADSR_1[1].ADSR_statu = 0;
        ADSR_1[1].ADSR_count = 0;
        ADSR_1[1].A_time = 5;
        ADSR_1[1].A_speed = 2000;
        ADSR_1[1].D_time = 3000;
        ADSR_1[1].D_speed = 0;
        ADSR_1[1].R_time = 0;
        ADSR_1[1].R_speed = 0;
        ADSR_1[1].velocity = 255;
		ADSR_1[2].ADSR_enable = 1;
        ADSR_1[2].ADSR_statu = 0;
        ADSR_1[2].ADSR_count = 0;
        ADSR_1[2].A_time = 5;
        ADSR_1[2].A_speed = 2000;
        ADSR_1[2].D_time = 3000;
        ADSR_1[2].D_speed = 0;
        ADSR_1[2].R_time = 0;
        ADSR_1[2].R_speed = 0;
        ADSR_1[2].velocity = 255;
		ADSR_1[3].ADSR_enable = 1;
        ADSR_1[3].ADSR_statu = 0;
        ADSR_1[3].ADSR_count = 0;
        ADSR_1[3].A_time = 5;
        ADSR_1[3].A_speed = 2000;
        ADSR_1[3].D_time = 3000;
        ADSR_1[3].D_speed = 0;
        ADSR_1[3].R_time = 0;
        ADSR_1[3].R_speed = 0;
        ADSR_1[3].velocity = 255;
    }

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
    RCC_OscInitStruct.PLL.PLLN = 160;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
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
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	u32 SampleLen = 0;
	
    if(htim == &htim3)	//TIM3 MIDI音序触发定时
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);

        u32 out1 = Synth_GM(MIDI_1, 0, midi_ctrl, VCO_1, ADSR_1);
        u32 out2 = Synth_GM(MIDI_2, 1, midi_ctrl, VCO_1, ADSR_1);
		u32 out3 = Synth_GM(MIDI_3, 2, midi_ctrl, VCO_1, ADSR_1);
        u32 out4 = Synth_GM(MIDI_4, 3, midi_ctrl, VCO_1, ADSR_1);

		SampleLen = sizeof(SnareTable);
        u32 out5 = Synth_SA(MIDI_5, 4, midi_ctrl, SaCt1, 0, SnareTable, SampleLen);
		SampleLen = sizeof(TomsTable);
        u32 out6 = Synth_SA(MIDI_6, 5, midi_ctrl, SaCt1, 1, TomsTable, SampleLen);
		SampleLen = sizeof(CrashTable);
		u32 out7 = Synth_SA(MIDI_7, 6, midi_ctrl, SaCt1, 2, CrashTable, SampleLen);

		
        u32 output = 4096 / 2 + (out1 + out4) * 10 + (out5 + out6 + out7 + out2 + out3) * 5;

        HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, output);
        HAL_DAC_Start(&hdac, DAC_CHANNEL_1);

        //u32 output = 4096 / 2 + (midi_ctrl.mid_vec * Sample(SnareTable, &SaCt1[0]) / 127);
    }
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
