/**
  ******************************************************************************
  * @file      startup_stm32f4xx.s
  * @author    Coocox
  * @version   V1.0
  * @date      03/05/2012
  * @brief     STM32F4xx Devices vector table for RIDE7 toolchain. 
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Configure the clock system and the external SRAM mounted on 
  *                  STM324xG-EVAL board to be used as data memory (optional, 
  *                  to be enabled by user)
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M4 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  */

#include "stm32f7xx.h"

/*----------Stack Configuration-----------------------------------------------*/
extern uint32_t _estack;
//#define STACK_SIZE       0x00004000      /*!< Stack size (in Words)           */
//__attribute__ ((section(".co_stack"))) unsigned long pulStack[STACK_SIZE];


/*----------Macro definition--------------------------------------------------*/
#define WEAK __attribute__ ((weak))



/*----------Declaration of the default fault handlers-------------------------*/
/* System exception vector handler */
void WEAK  Reset_Handler(void);
void WEAK  NMI_Handler(void);
void WEAK  HardFault_Handler(void);
void WEAK  MemManage_Handler(void);
void WEAK  BusFault_Handler(void);
void WEAK  UsageFault_Handler(void);
void WEAK  SVC_Handler(void);
void WEAK  DebugMon_Handler(void);
void WEAK  PendSV_Handler(void);
void WEAK  SysTick_Handler(void);

void WEAK  WWDG_IRQHandler(void);
void WEAK  PVD_IRQHandler(void);
void WEAK  TAMP_STAMP_IRQHandler(void);
void WEAK  RTC_WKUP_IRQHandler(void);
void WEAK  FLASH_IRQHandler(void);
void WEAK  RCC_IRQHandler(void);
void WEAK  EXTI0_IRQHandler(void);
void WEAK  EXTI1_IRQHandler(void);
void WEAK  EXTI2_IRQHandler(void);
void WEAK  EXTI3_IRQHandler(void);
void WEAK  EXTI4_IRQHandler(void);
void WEAK  DMA1_Stream0_IRQHandler(void);
void WEAK  DMA1_Stream1_IRQHandler(void);
void WEAK  DMA1_Stream2_IRQHandler(void);
void WEAK  DMA1_Stream3_IRQHandler(void);
void WEAK  DMA1_Stream4_IRQHandler(void);
void WEAK  DMA1_Stream5_IRQHandler(void);
void WEAK  DMA1_Stream6_IRQHandler(void);
void WEAK  ADC_IRQHandler(void);
void WEAK  CAN1_TX_IRQHandler(void);
void WEAK  CAN1_RX0_IRQHandler(void);
void WEAK  CAN1_RX1_IRQHandler(void);
void WEAK  CAN1_SCE_IRQHandler(void);
void WEAK  EXTI9_5_IRQHandler(void);
void WEAK  TIM1_BRK_TIM9_IRQHandler(void);
void WEAK  TIM1_UP_TIM10_IRQHandler(void);
void WEAK  TIM1_TRG_COM_TIM11_IRQHandler(void);
void WEAK  TIM1_CC_IRQHandler(void);
void WEAK  TIM2_IRQHandler(void);
void WEAK  TIM3_IRQHandler(void);
void WEAK  TIM4_IRQHandler(void);
void WEAK  I2C1_EV_IRQHandler(void);
void WEAK  I2C1_ER_IRQHandler(void);
void WEAK  I2C2_EV_IRQHandler(void);
void WEAK  I2C2_ER_IRQHandler(void);
void WEAK  SPI1_IRQHandler(void);
void WEAK  SPI2_IRQHandler(void);
void WEAK  USART1_IRQHandler(void);
void WEAK  USART2_IRQHandler(void);
void WEAK  USART3_IRQHandler(void);
void WEAK  EXTI15_10_IRQHandler(void);
void WEAK  RTC_Alarm_IRQHandler(void);
void WEAK  OTG_FS_WKUP_IRQHandler(void);
void WEAK  TIM8_BRK_TIM12_IRQHandler(void);
void WEAK  TIM8_UP_TIM13_IRQHandler(void);
void WEAK  TIM8_TRG_COM_TIM14_IRQHandler(void);
void WEAK  TIM8_CC_IRQHandler(void);
void WEAK  DMA1_Stream7_IRQHandler(void);
//void WEAK  FSMC_IRQHandler(void);
//void WEAK  SDIO_IRQHandler(void);
void WEAK  TIM5_IRQHandler(void);
void WEAK  SPI3_IRQHandler(void);
void WEAK  UART4_IRQHandler(void);
void WEAK  UART5_IRQHandler(void);
void WEAK  TIM6_DAC_IRQHandler(void);
void WEAK  TIM7_IRQHandler(void);
void WEAK  DMA2_Stream0_IRQHandler(void);
void WEAK  DMA2_Stream1_IRQHandler(void);
void WEAK  DMA2_Stream2_IRQHandler(void);
void WEAK  DMA2_Stream3_IRQHandler(void);
void WEAK  DMA2_Stream4_IRQHandler(void);
void WEAK  ETH_IRQHandler(void);
void WEAK  ETH_WKUP_IRQHandler(void);
void WEAK  CAN2_TX_IRQHandler(void);
void WEAK  CAN2_RX0_IRQHandler(void);
void WEAK  CAN2_RX1_IRQHandler(void);
void WEAK  CAN2_SCE_IRQHandler(void);
void WEAK  OTG_FS_IRQHandler(void);
void WEAK  DMA2_Stream5_IRQHandler(void);
void WEAK  DMA2_Stream6_IRQHandler(void);
void WEAK  DMA2_Stream7_IRQHandler(void);
void WEAK  USART6_IRQHandler(void);
void WEAK  I2C3_EV_IRQHandler(void);
void WEAK  I2C3_ER_IRQHandler(void);
void WEAK  OTG_HS_EP1_OUT_IRQHandler(void);
void WEAK  OTG_HS_EP1_IN_IRQHandler(void);
void WEAK  OTG_HS_WKUP_IRQHandler(void);
void WEAK  OTG_HS_IRQHandler(void);
void WEAK  DCMI_IRQHandler(void);
//void WEAK  CRYP_IRQHandler(void);
//void WEAK  HASH_RNG_IRQHandler(void);
//void WEAK  FPU_IRQHandler(void);

void WEAK  FMC_IRQHandler     (void);
void WEAK  SDMMC1_IRQHandler  (void);
void WEAK  RNG_IRQHandler     (void);
void WEAK  FPU_IRQHandler     (void);
void WEAK  UART7_IRQHandler   (void);
void WEAK  UART8_IRQHandler   (void);
void WEAK  SPI4_IRQHandler    (void);
void WEAK  SPI5_IRQHandler    (void);
void WEAK  SPI6_IRQHandler    (void);
void WEAK  SAI1_IRQHandler    (void);
void WEAK  DMA2D_IRQHandler   (void);
void WEAK  SAI2_IRQHandler    (void);
void WEAK  QUADSPI_IRQHandler (void);
void WEAK  LPTIM1_IRQHandler  (void);
void WEAK  CEC_IRQHandler     (void);
void WEAK  I2C4_EV_IRQHandler (void);
void WEAK  I2C4_ER_IRQHandler (void);
void WEAK  SPDIF_RX_IRQHandler(void);

/*----------Symbols defined in linker script----------------------------------*/
extern unsigned long _sidata;    /*!< Start address for the initialization
                                      values of the .data section.            */
extern unsigned long _sdata;     /*!< Start address for the .data section     */
extern unsigned long _edata;     /*!< End address for the .data section       */
extern unsigned long _sbss;      /*!< Start address for the .bss section      */
extern unsigned long _ebss;      /*!< End address for the .bss section        */
//extern void _eram;               /*!< End address for ram                     */


/*----------Function prototypes-----------------------------------------------*/
extern int main(void);           /*!< The entry point for the application.    */
//extern void SystemInit(void);    /*!< Setup the microcontroller system(CMSIS) */
void Default_Reset_Handler(void);   /*!< Default reset handler                */
static void Default_Handler(void) __attribute__( ( naked ) ) __attribute__ ((used));  /*!< Default exception handler            */


/**
  *@brief The minimal vector table for a Cortex M3.  Note that the proper constructs
  *       must be placed on this to ensure that it ends up at physical address
  *       0x00000000.
  */
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
	(void *)&_estack,
	Reset_Handler,

	NMI_Handler,
	HardFault_Handler,
	MemManage_Handler,
	BusFault_Handler,
	UsageFault_Handler,
	0,
	0,
	0,
	0,
	SVC_Handler,
	DebugMon_Handler,
	0,
	PendSV_Handler,
	SysTick_Handler,
  
  /* External Interrupts */
	WWDG_IRQHandler,                   /* Window WatchDog              */
	PVD_IRQHandler,                    /* PVD through EXTI Line detection */
	TAMP_STAMP_IRQHandler,             /* Tamper and TimeStamps through the EXTI line */
	RTC_WKUP_IRQHandler,               /* RTC Wakeup through the EXTI line */
	FLASH_IRQHandler,                  /* FLASH                        */
	RCC_IRQHandler,                    /* RCC                          */
	EXTI0_IRQHandler,                  /* EXTI Line0                   */
	EXTI1_IRQHandler,                  /* EXTI Line1                   */
	EXTI2_IRQHandler,                  /* EXTI Line2                   */
	EXTI3_IRQHandler,                  /* EXTI Line3                   */
	EXTI4_IRQHandler,                  /* EXTI Line4                   */
	DMA1_Stream0_IRQHandler,           /* DMA1 Stream 0                */
	DMA1_Stream1_IRQHandler,           /* DMA1 Stream 1                */
	DMA1_Stream2_IRQHandler,           /* DMA1 Stream 2                */
	DMA1_Stream3_IRQHandler,           /* DMA1 Stream 3                */
	DMA1_Stream4_IRQHandler,           /* DMA1 Stream 4                */
	DMA1_Stream5_IRQHandler,           /* DMA1 Stream 5                */
	DMA1_Stream6_IRQHandler,           /* DMA1 Stream 6                */
	ADC_IRQHandler,                    /* ADC1, ADC2 and ADC3s         */
	CAN1_TX_IRQHandler,                /* CAN1 TX                      */
	CAN1_RX0_IRQHandler,               /* CAN1 RX0                     */
	CAN1_RX1_IRQHandler,               /* CAN1 RX1                     */
	CAN1_SCE_IRQHandler,               /* CAN1 SCE                     */
	EXTI9_5_IRQHandler,                /* External Line[9:5]s          */
	TIM1_BRK_TIM9_IRQHandler,          /* TIM1 Break and TIM9          */
	TIM1_UP_TIM10_IRQHandler,          /* TIM1 Update and TIM10        */
	TIM1_TRG_COM_TIM11_IRQHandler,     /* TIM1 Trigger and Commutation and TIM11 */
	TIM1_CC_IRQHandler,                /* TIM1 Capture Compare         */
	TIM2_IRQHandler,                   /* TIM2                         */
	TIM3_IRQHandler,                   /* TIM3                         */
	TIM4_IRQHandler,                   /* TIM4                         */
	I2C1_EV_IRQHandler,                /* I2C1 Event                   */
	I2C1_ER_IRQHandler,                /* I2C1 Error                   */
	I2C2_EV_IRQHandler,                /* I2C2 Event                   */
	I2C2_ER_IRQHandler,                /* I2C2 Error                   */
	SPI1_IRQHandler,                   /* SPI1                         */
	SPI2_IRQHandler,                   /* SPI2                         */
	USART1_IRQHandler,                 /* USART1                       */
	USART2_IRQHandler,                 /* USART2                       */
	USART3_IRQHandler,                 /* USART3                       */
	EXTI15_10_IRQHandler,              /* External Line[15:10]s        */
	RTC_Alarm_IRQHandler,              /* RTC Alarm (A and B) through EXTI Line */
	OTG_FS_WKUP_IRQHandler,            /* USB OTG FS Wakeup through EXTI line */
	TIM8_BRK_TIM12_IRQHandler,         /* TIM8 Break and TIM12         */
	TIM8_UP_TIM13_IRQHandler,          /* TIM8 Update and TIM13        */
	TIM8_TRG_COM_TIM14_IRQHandler,     /* TIM8 Trigger and Commutation and TIM14 */
	TIM8_CC_IRQHandler,                /* TIM8 Capture Compare         */
	DMA1_Stream7_IRQHandler,           /* DMA1 Stream7                 */
	FMC_IRQHandler,                    /* FMC                          */
	SDMMC1_IRQHandler,                 /* SDMMC1                       */
	TIM5_IRQHandler,                   /* TIM5                         */
	SPI3_IRQHandler,                   /* SPI3                         */
	UART4_IRQHandler,                  /* UART4                        */
	UART5_IRQHandler,                  /* UART5                        */
	TIM6_DAC_IRQHandler,               /* TIM6 and DAC1&2 underrun errors */
	TIM7_IRQHandler,                   /* TIM7                         */
	DMA2_Stream0_IRQHandler,           /* DMA2 Stream 0                */
	DMA2_Stream1_IRQHandler,           /* DMA2 Stream 1                */
	DMA2_Stream2_IRQHandler,           /* DMA2 Stream 2                */
	DMA2_Stream3_IRQHandler,           /* DMA2 Stream 3                */
	DMA2_Stream4_IRQHandler,           /* DMA2 Stream 4                */
	ETH_IRQHandler,                    /* Ethernet                     */
	ETH_WKUP_IRQHandler,               /* Ethernet Wakeup through EXTI line */
	CAN2_TX_IRQHandler,                /* CAN2 TX                      */
	CAN2_RX0_IRQHandler,               /* CAN2 RX0                     */
	CAN2_RX1_IRQHandler,               /* CAN2 RX1                     */
	CAN2_SCE_IRQHandler,               /* CAN2 SCE                     */
	OTG_FS_IRQHandler,                 /* USB OTG FS                   */
	DMA2_Stream5_IRQHandler,           /* DMA2 Stream 5                */
	DMA2_Stream6_IRQHandler,           /* DMA2 Stream 6                */
	DMA2_Stream7_IRQHandler,           /* DMA2 Stream 7                */
	USART6_IRQHandler,                 /* USART6                       */
	I2C3_EV_IRQHandler,                /* I2C3 event                   */
	I2C3_ER_IRQHandler,                /* I2C3 error                   */
	OTG_HS_EP1_OUT_IRQHandler,         /* USB OTG HS End Point 1 Out   */
	OTG_HS_EP1_IN_IRQHandler,          /* USB OTG HS End Point 1 In    */
	OTG_HS_WKUP_IRQHandler,            /* USB OTG HS Wakeup through EXTI */
	OTG_HS_IRQHandler,                 /* USB OTG HS                   */
	DCMI_IRQHandler,                   /* DCMI                         */
	0,                                 /* Reserved                     */
	RNG_IRQHandler,                   /* Rng                          */
	FPU_IRQHandler,                    /* FPU                          */
	UART7_IRQHandler,                  /* UART7                        */
	UART8_IRQHandler,                  /* UART8                        */
	SPI4_IRQHandler,                   /* SPI4                         */
	SPI5_IRQHandler,                   /* SPI5                           */
	SPI6_IRQHandler,                   /* SPI6                         */
	SAI1_IRQHandler,                   /* SAI1                          */
	0,                                 /* Reserved                     */
	0,                                 /* Reserved                     */
	DMA2D_IRQHandler,                  /* DMA2D                          */
	SAI2_IRQHandler,                   /* SAI2                         */
	QUADSPI_IRQHandler,                /* QUADSPI                      */
	LPTIM1_IRQHandler,                 /* LPTIM1                       */
	CEC_IRQHandler,                    /* HDMI_CEC                     */
	I2C4_EV_IRQHandler,                /* I2C4 Event                   */
	I2C4_ER_IRQHandler,                /* I2C4 Error                   */
	SPDIF_RX_IRQHandler,               /* SPDIF_RX                     */
  
};


__attribute__ ((section(".isr_vector_minimal")))
void (* const StartVectors_minimal[])(void) =
{
  (void *)&_estack,
  Reset_Handler,
};

__attribute__ ((section(".isr_vector_RAM")))
void (* StartVectors_RAM_actual[128])(void) = {0};


//void SystemCoreClockUpdate();
void SystemInit(void);
//void kiss_startup_init();

extern uint32_t _itcm_copy;
extern uint32_t _itcm_image_from;
extern uint32_t _itcm_image_to;

__attribute__ ((naked, long_call))
void Default_Reset_Handler_itcm(void);

__attribute__ ((naked, section(".itcm_code_loader")))
void Reset_Handler(void)
{
	uint32_t *itcm_src = &_itcm_copy;
	uint32_t *itcm_dst = &_itcm_image_from;
	while (itcm_dst < &_itcm_image_to)
		*(itcm_dst++) = *(itcm_src++);

	Default_Reset_Handler_itcm();
}

/**
  * @brief  This is the code that gets called when the processor first
  *         starts execution following a reset event. Only the absolutely
  *         necessary set is performed, after which the application
  *         supplied main() routine is called.
  * @param  None
  * @retval None
  */
__attribute__ ((naked, long_call))
void Default_Reset_Handler_itcm(void)
//void Default_Reset_Handler(void)
{
	//RCC->AHB1ENR |= RCC_AHB1ENR_CCMDATARAMEN;
//	heap_mark();
//	stack_mark();

  /* Initialize data and bss */
  unsigned long *pulSrc, *pulDest;

  /* Copy the data segment initializers from flash to SRAM*/
  pulSrc = &_sidata;

  for(pulDest = &_sdata; pulDest < &_edata; )
  {
    *(pulDest++) = *(pulSrc++);
  }
  
  /* Zero fill the bss segment.  This is done with inline assembly since this
     will clear the value of pulDest if it is not kept in a register. */
  __asm("  ldr     r0, =_sbss\n"
        "  ldr     r1, =_ebss\n"
        "  mov     r2, #0\n"
        "  .thumb_func\n"
        "zero_loop:\n"
        "    cmp     r0, r1\n"
        "    it      lt\n"
        "    strlt   r2, [r0], #4\n"
        "    blt     zero_loop");
//#ifdef __FPU_USED
//  /* Enable FPU.*/
//  __asm("  LDR.W R0, =0xE000ED88\n"
//        "  LDR R1, [R0]\n"
//        "  ORR R1, R1, #(0xF << 20)\n"
//        "  STR R1, [R0]");
//#endif

  /* Call the application's entry point.*/
  SystemInit();


  //StartVectors_RAM_actual[0xD4 / 4] = USART1_IRQHandler;
  //SCB->VTOR = (uint32_t)StartVectors_RAM_actual;

//  SCB->VTOR = (uint32_t)g_pfnVectors;
  //SystemCoreClockUpdate();
  //kiss_startup_init();
  main();
}


/**
  *@brief Provide weak aliases for each Exception handler to the Default_Handler.
  *       As they are weak aliases, any function with the same name will override
  *       this definition.
  */
//#pragma weak Reset_Handler = Default_Reset_Handler
#pragma weak NMI_Handler = Default_Handler
#pragma weak HardFault_Handler = Default_Handler
#pragma weak MemManage_Handler = Default_Handler
#pragma weak BusFault_Handler = Default_Handler
#pragma weak UsageFault_Handler = Default_Handler
#pragma weak SVC_Handler = Default_Handler
#pragma weak DebugMon_Handler = Default_Handler
#pragma weak PendSV_Handler = Default_Handler
#pragma weak SysTick_Handler = Default_Handler

#pragma weak WWDG_IRQHandler = Default_Handler
#pragma weak PVD_IRQHandler = Default_Handler
#pragma weak TAMP_STAMP_IRQHandler = Default_Handler
#pragma weak RTC_WKUP_IRQHandler = Default_Handler
#pragma weak FLASH_IRQHandler = Default_Handler
#pragma weak RCC_IRQHandler = Default_Handler
#pragma weak EXTI0_IRQHandler = Default_Handler
#pragma weak EXTI1_IRQHandler = Default_Handler
#pragma weak EXTI2_IRQHandler = Default_Handler
#pragma weak EXTI3_IRQHandler = Default_Handler
#pragma weak EXTI4_IRQHandler = Default_Handler
#pragma weak DMA1_Stream0_IRQHandler = Default_Handler
#pragma weak DMA1_Stream1_IRQHandler = Default_Handler
#pragma weak DMA1_Stream2_IRQHandler = Default_Handler
#pragma weak DMA1_Stream3_IRQHandler = Default_Handler
#pragma weak DMA1_Stream4_IRQHandler = Default_Handler
#pragma weak DMA1_Stream5_IRQHandler = Default_Handler
#pragma weak DMA1_Stream6_IRQHandler = Default_Handler
#pragma weak ADC_IRQHandler = Default_Handler
#pragma weak CAN1_TX_IRQHandler = Default_Handler
#pragma weak CAN1_RX0_IRQHandler = Default_Handler
#pragma weak CAN1_RX1_IRQHandler = Default_Handler
#pragma weak CAN1_SCE_IRQHandler = Default_Handler
#pragma weak EXTI9_5_IRQHandler = Default_Handler
#pragma weak TIM1_BRK_TIM9_IRQHandler = Default_Handler
#pragma weak TIM1_UP_TIM10_IRQHandler = Default_Handler
#pragma weak TIM1_TRG_COM_TIM11_IRQHandler = Default_Handler
#pragma weak TIM1_CC_IRQHandler = Default_Handler
#pragma weak TIM2_IRQHandler = Default_Handler
#pragma weak TIM3_IRQHandler = Default_Handler
#pragma weak TIM4_IRQHandler = Default_Handler
#pragma weak I2C1_EV_IRQHandler = Default_Handler
#pragma weak I2C1_ER_IRQHandler = Default_Handler
#pragma weak I2C2_EV_IRQHandler = Default_Handler
#pragma weak I2C2_ER_IRQHandler = Default_Handler
#pragma weak SPI1_IRQHandler = Default_Handler
#pragma weak SPI2_IRQHandler = Default_Handler
#pragma weak USART1_IRQHandler = Default_Handler
#pragma weak USART2_IRQHandler = Default_Handler
#pragma weak USART3_IRQHandler = Default_Handler
#pragma weak EXTI15_10_IRQHandler = Default_Handler
#pragma weak RTC_Alarm_IRQHandler = Default_Handler
#pragma weak OTG_FS_WKUP_IRQHandler = Default_Handler
#pragma weak TIM8_BRK_TIM12_IRQHandler = Default_Handler
#pragma weak TIM8_UP_TIM13_IRQHandler = Default_Handler
#pragma weak TIM8_TRG_COM_TIM14_IRQHandler = Default_Handler
#pragma weak TIM8_CC_IRQHandler = Default_Handler
#pragma weak DMA1_Stream7_IRQHandler = Default_Handler
#pragma weak FSMC_IRQHandler = Default_Handler
#pragma weak SDIO_IRQHandler = Default_Handler
#pragma weak TIM5_IRQHandler = Default_Handler
#pragma weak SPI3_IRQHandler = Default_Handler
#pragma weak UART4_IRQHandler = Default_Handler
#pragma weak UART5_IRQHandler = Default_Handler
#pragma weak TIM6_DAC_IRQHandler = Default_Handler
#pragma weak TIM7_IRQHandler = Default_Handler
#pragma weak DMA2_Stream0_IRQHandler = Default_Handler
#pragma weak DMA2_Stream1_IRQHandler = Default_Handler
#pragma weak DMA2_Stream2_IRQHandler = Default_Handler
#pragma weak DMA2_Stream3_IRQHandler = Default_Handler
#pragma weak DMA2_Stream4_IRQHandler = Default_Handler
#pragma weak ETH_IRQHandler = Default_Handler
#pragma weak ETH_WKUP_IRQHandler = Default_Handler
#pragma weak CAN2_TX_IRQHandler = Default_Handler
#pragma weak CAN2_RX0_IRQHandler = Default_Handler
#pragma weak CAN2_RX1_IRQHandler = Default_Handler
#pragma weak CAN2_SCE_IRQHandler = Default_Handler
#pragma weak OTG_FS_IRQHandler = Default_Handler
#pragma weak DMA2_Stream5_IRQHandler = Default_Handler
#pragma weak DMA2_Stream6_IRQHandler = Default_Handler
#pragma weak DMA2_Stream7_IRQHandler = Default_Handler
#pragma weak USART6_IRQHandler = Default_Handler
#pragma weak I2C3_EV_IRQHandler = Default_Handler
#pragma weak I2C3_ER_IRQHandler = Default_Handler
#pragma weak OTG_HS_EP1_OUT_IRQHandler = Default_Handler
#pragma weak OTG_HS_EP1_IN_IRQHandler = Default_Handler
#pragma weak OTG_HS_WKUP_IRQHandler = Default_Handler
#pragma weak OTG_HS_IRQHandler = Default_Handler
#pragma weak DCMI_IRQHandler = Default_Handler
#pragma weak CRYP_IRQHandler = Default_Handler
#pragma weak HASH_RNG_IRQHandler = Default_Handler

#pragma weak FMC_IRQHandler      = Default_Handler
#pragma weak SDMMC1_IRQHandler   = Default_Handler
#pragma weak RNG_IRQHandler      = Default_Handler
#pragma weak FPU_IRQHandler      = Default_Handler
#pragma weak UART7_IRQHandler    = Default_Handler
#pragma weak UART8_IRQHandler    = Default_Handler
#pragma weak SPI4_IRQHandler     = Default_Handler
#pragma weak SPI5_IRQHandler     = Default_Handler
#pragma weak SPI6_IRQHandler     = Default_Handler
#pragma weak SAI1_IRQHandler     = Default_Handler
#pragma weak DMA2D_IRQHandler    = Default_Handler
#pragma weak SAI2_IRQHandler     = Default_Handler
#pragma weak QUADSPI_IRQHandler  = Default_Handler
#pragma weak LPTIM1_IRQHandler   = Default_Handler
#pragma weak CEC_IRQHandler      = Default_Handler
#pragma weak I2C4_EV_IRQHandler  = Default_Handler
#pragma weak I2C4_ER_IRQHandler  = Default_Handler
#pragma weak SPDIF_RX_IRQHandler = Default_Handler
/**
  * @brief  This is the code that gets called when the processor receives an
  *         unexpected interrupt.  This simply enters an infinite loop,
  *         preserving the system state for examination by a debugger.
  * @param  None
  * @retval None
  */
/* The prototype shows it is a naked function - in effect this is just an
assembly function. */

//#define DEBUG_PRINTF

#ifndef DEBUG_PRINTF
static void Default_Handler(void)
{
	while (1)
		;
}

void *dummy = Default_Handler;

#else
/* The fault handler implementation calls a function called
prvGetRegistersFromStack(). */
static void Default_Handler(void)
{
    __asm volatile
    (
        " tst lr, #4                                                \n"
        " ite eq                                                    \n"
        " mrseq r0, msp                                             \n"
        " mrsne r0, psp                                             \n"
        " ldr r1, [r0, #24]                                         \n"
        " ldr r2, handler2_address_const                            \n"
        " bx r2                                                     \n"
        " handler2_address_const: .word prvGetRegistersFromStack    \n"
    );
}

#include "stm32kiss.h"
#pragma GCC diagnostic ignored "-Wformat"

void prvGetRegistersFromStack( uint32_t *pulFaultStackAddress )
{
/* These are volatile to try and prevent the compiler/linker optimising them
away as the variables never actually get used.  If the debugger won't show the
values of the variables, make them global my moving their declaration outside
of this function. */
volatile uint32_t r0;
volatile uint32_t r1;
volatile uint32_t r2;
volatile uint32_t r3;
volatile uint32_t r12;
volatile uint32_t lr; /* Link register. */
volatile uint32_t pc; /* Program counter. */
volatile uint32_t psr;/* Program status register. */

    r0 = pulFaultStackAddress[0];
    r1 = pulFaultStackAddress[1];
    r2 = pulFaultStackAddress[2];
    r3 = pulFaultStackAddress[3];

    r12 = pulFaultStackAddress[4];
    lr = pulFaultStackAddress[5];
    pc = pulFaultStackAddress[6];
    psr = pulFaultStackAddress[7];

    printf ("\r\rERROR: [Hard fault handler - all numbers in hex]\r");
    printf ("R0  = %08X\r", r0);
    printf ("R1  = %08X\r", r1);
    printf ("R2  = %08X\r", r2);
    printf ("R3  = %08X\r", r3);
    printf ("R12 = %08X\r", r12);
    printf ("LR  = %08X\r", lr);
    printf ("PC  = %08X\r", pc);
    printf ("PSR = %08X\r", psr);
    printf ("SCB->CCR   = %08X\r", SCB->CCR);
    printf ("SCB->CFSR  = %08X\r", SCB->CFSR);
    printf ("SCB->HFSR  = %08X\r", SCB->HFSR);
    printf ("SCB->BFAR  = %08X\r", SCB->BFAR);
    printf ("SCB->SHCSR = %08X\r", SCB->SHCSR);
    printf ("SCB->MMFAR = %08X\r", SCB->MMFAR);

    /* When the following line is hit, the variables contain the register values. */
    for( ;; );
}
#endif
/*********************** (C) COPYRIGHT 2009 Coocox ************END OF FILE*****/
