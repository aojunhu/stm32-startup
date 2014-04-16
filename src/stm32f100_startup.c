extern unsigned long _data_flash;
extern unsigned long _data_begin;
extern unsigned long _data_end;
extern unsigned long _bss_begin;
extern unsigned long _bss_end;
extern unsigned long _stack_end;

extern int main();

//Reset handler
USED void handler_Reset() {
	//clear BSS
	for (U32 *dest=&_bss_begin; dest<&_bss_end;) *(dest++) = 0;
	//copy initialized data
	for (U32 *dst=&_data_begin, *src=&_data_flash; dst<&_data_end;)	*(dst++) = *(src++);
	//call main
	main();
}

//Default/empty handlers
WEAK void handler_Default() { while (1); }
WEAK void handler_Empty()   {}

//Exceptions
void handler_NMI()                     ALIAS("handler_Default");
void handler_HardFault()               ALIAS("handler_Default");
void handler_MpuFault()                ALIAS("handler_Default");
void handler_BusFault()                ALIAS("handler_Default");
void handler_UsageFault()              ALIAS("handler_Default");
void handler_SVCall()                  ALIAS("handler_Default");
void handler_DebugMon()                ALIAS("handler_Default");
void handler_PendSV()                  ALIAS("handler_Default");
void handler_Systick()                 ALIAS("handler_Empty");

void handler_WWDG_IRQn()               ALIAS("handler_Empty");
void handler_PVD_IRQn()                ALIAS("handler_Empty");
void handler_TAMPER_IRQn()             ALIAS("handler_Empty");
void handler_RTC_IRQn()                ALIAS("handler_Empty");
void handler_FLASH_IRQn()              ALIAS("handler_Empty");
void handler_RCC_IRQn()                ALIAS("handler_Empty");

void handler_EXTI0_IRQn()              ALIAS("handler_Empty");
void handler_EXTI1_IRQn()              ALIAS("handler_Empty");
void handler_EXTI2_IRQn()              ALIAS("handler_Empty");
void handler_EXTI3_IRQn()              ALIAS("handler_Empty");
void handler_EXTI4_IRQn()              ALIAS("handler_Empty");

void handler_DMA1_Channel1_IRQn()      ALIAS("handler_Empty");
void handler_DMA1_Channel2_IRQn()      ALIAS("handler_Empty");
void handler_DMA1_Channel3_IRQn()      ALIAS("handler_Empty");
void handler_DMA1_Channel4_IRQn()      ALIAS("handler_Empty");
void handler_DMA1_Channel5_IRQn()      ALIAS("handler_Empty");
void handler_DMA1_Channel6_IRQn()      ALIAS("handler_Empty");
void handler_DMA1_Channel7_IRQn()      ALIAS("handler_Empty");

void handler_ADC1_IRQn()               ALIAS("handler_Empty");
void handler_EXTI9_5_IRQn()            ALIAS("handler_Empty");

void handler_TIM1_BRK_TIM15_IRQn()     ALIAS("handler_Empty");
void handler_TIM1_UP_TIM16_IRQn()      ALIAS("handler_Empty");
void handler_TIM1_TRG_COM_TIM17_IRQn() ALIAS("handler_Empty");
void handler_TIM1_CC_IRQn()            ALIAS("handler_Empty");
void handler_TIM2_IRQn()               ALIAS("handler_Empty");
void handler_TIM3_IRQn()               ALIAS("handler_Empty");

void handler_I2C1_EV_IRQn()            ALIAS("handler_Empty");
void handler_I2C1_ER_IRQn()            ALIAS("handler_Empty");

void handler_SPI1_IRQn()               ALIAS("handler_Empty");

void handler_USART1_IRQn()             ALIAS("handler_Empty");
void handler_USART2_IRQn()             ALIAS("handler_Empty");

void handler_EXTI15_10_IRQn()          ALIAS("handler_Empty");
void handler_RTCAlarm_IRQn()           ALIAS("handler_Empty");
void handler_CEC_IRQn()                ALIAS("handler_Empty");

void handler_TIM6_DAC_IRQn()           ALIAS("handler_Empty");
void handler_TIM7_IRQn()               ALIAS("handler_Empty");

// interrupt vectors
SECTION(".interrupt_vector")
void (* const table_interrupt_vector[])() = {
	(void *)&_stack_end, // -16 - stack

	handler_Reset,       // -15 - reset

	handler_NMI,         // -14 - nmi
	handler_HardFault,   // -13 - hard fault
	handler_MpuFault,    // -12 - memmanage
	handler_BusFault,    // -11 - busfault
	handler_UsageFault,  // -10 - usagefault
	handler_Default,     // -9  - reserved
	handler_Default,     // -8  - reserved
	handler_Default,     // -7  - reserved
	handler_Default,     // -6  - reserved
	handler_SVCall,      // -5  - svc
	handler_DebugMon,    // -4  - debugmon
	handler_Default,     // -3  - reserved
	handler_PendSV,      // -2  - pendsv
	handler_Systick,     // -1  - systick

	handler_WWDG_IRQn,   // 0
	handler_PVD_IRQn,    // 1
	handler_TAMPER_IRQn, // 2
	handler_RTC_IRQn ,   // 3
	handler_FLASH_IRQn,  // 4
	handler_RCC_IRQn,    // 5

	handler_EXTI0_IRQn,  // 6
	handler_EXTI1_IRQn,  // 7
	handler_EXTI2_IRQn,  // 8
	handler_EXTI3_IRQn,  // 9
	handler_EXTI4_IRQn,  // 10

	handler_DMA1_Channel1_IRQn, // 11
	handler_DMA1_Channel2_IRQn, // 12
	handler_DMA1_Channel3_IRQn, // 13
	handler_DMA1_Channel4_IRQn, // 14
	handler_DMA1_Channel5_IRQn, // 15
	handler_DMA1_Channel6_IRQn, // 16
	handler_DMA1_Channel7_IRQn, // 17

	handler_ADC1_IRQn,

	handler_Default, // 19
	handler_Default, // 20
	handler_Default, // 21
	handler_Default, // 22

	handler_EXTI9_5_IRQn,

	handler_TIM1_BRK_TIM15_IRQn,
	handler_TIM1_UP_TIM16_IRQn,
	handler_TIM1_TRG_COM_TIM17_IRQn,
	handler_TIM1_CC_IRQn,
	handler_TIM2_IRQn,
	handler_TIM3_IRQn,

	handler_Default,

	handler_I2C1_EV_IRQn,
	handler_I2C1_ER_IRQn,

	handler_Default,
	handler_Default,

	handler_SPI1_IRQn,

	handler_Default,

	handler_USART1_IRQn,
	handler_USART2_IRQn,

	handler_Default,

	handler_EXTI15_10_IRQn,
	handler_RTCAlarm_IRQn,
	handler_CEC_IRQn,

	handler_Default, // 43
	handler_Default, // 44
	handler_Default, // 45
	handler_Default, // 46
	handler_Default, // 47
	handler_Default, // 48
	handler_Default, // 49
	handler_Default, // 50
	handler_Default, // 51
	handler_Default, // 52
	handler_Default, // 53

	handler_TIM6_DAC_IRQn,
	handler_TIM7_IRQn,

	(void *)0xF108F85F
};
