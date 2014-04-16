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
	for (U32 *dst=&_data_begin, *src=&_data_flash; dst<&_data_end;) *(dst++) = *(src++);
	//call main
	main();
}

//Default/empty handlers
WEAK void handler_Default() { while (1); }
WEAK void handler_Empty() {}

//Exceptions
void handler_NMI()                 ALIAS("handler_Default");
void handler_HardFault()           ALIAS("handler_Default");
void handler_SVCall()              ALIAS("handler_Default");
void handler_PendSV()              ALIAS("handler_Default");
void handler_Systick()             ALIAS("handler_Empty");

//IRQs
void handler_IRQ_WWDG()            ALIAS("handler_Empty");
void handler_IRQ_PVD()             ALIAS("handler_Empty");
void handler_IRQ_RTC()             ALIAS("handler_Empty");
void handler_IRQ_FLASH()           ALIAS("handler_Empty");
void handler_IRQ_RCC()             ALIAS("handler_Empty");
void handler_IRQ_EXTI0_1()         ALIAS("handler_Empty");
void handler_IRQ_EXTI2_3()         ALIAS("handler_Empty");
void handler_IRQ_EXTI4_15()        ALIAS("handler_Empty");
void handler_IRQ_TS()              ALIAS("handler_Empty");
void handler_IRQ_DMA1_Channel1()   ALIAS("handler_Empty");
void handler_IRQ_DMA1_Channel2_3() ALIAS("handler_Empty");
void handler_IRQ_DMA1_Channel4_5() ALIAS("handler_Empty");
void handler_IRQ_ADC1_COMP()       ALIAS("handler_Empty");
void handler_IRQ_TIM1_BRK_UP_TRG() ALIAS("handler_Empty");
void handler_IRQ_TIM1_CC()         ALIAS("handler_Empty");
void handler_IRQ_TIM2()            ALIAS("handler_Empty");
void handler_IRQ_TIM3()            ALIAS("handler_Empty");
void handler_IRQ_TIM6_DAC()        ALIAS("handler_Empty");
void handler_IRQ_TIM14()           ALIAS("handler_Empty");
void handler_IRQ_TIM15()           ALIAS("handler_Empty");
void handler_IRQ_TIM16()           ALIAS("handler_Empty");
void handler_IRQ_TIM17()           ALIAS("handler_Empty");
void handler_IRQ_I2C1()            ALIAS("handler_Empty");
void handler_IRQ_I2C2()            ALIAS("handler_Empty");
void handler_IRQ_SPI1()            ALIAS("handler_Empty");
void handler_IRQ_SPI2()            ALIAS("handler_Empty");
void handler_IRQ_USART1()          ALIAS("handler_Empty");
void handler_IRQ_USART2()          ALIAS("handler_Empty");
void handler_IRQ_CEC()             ALIAS("handler_Empty");

//Vectors table
SECTION(".interrupt_vector")
void (* const table_interrupt_vector[])() = {

	(void *)&_stack_end,   // stack top
	handler_Reset,         // Reset

	handler_NMI,           // -14 NMI
	handler_HardFault,     // -13 Hard fault
	handler_Default,       // -12 Reserved
	handler_Default,       // -11 Reserved
	handler_Default,       // -10 Reserved
	handler_Default,       // -9  Reserved
	handler_Default,       // -8  Reserved
	handler_Default,       // -7  Reserved
	handler_Default,       // -6  Reserved
	handler_SVCall,        // -5  SVCall
	handler_Default,       // -4  Reserved
	handler_Default,       // -3  Reserved
	handler_PendSV,        // -2  PendSV
	handler_Systick,       // -1  SysTick

	handler_IRQ_WWDG,      // IRQ0
	handler_IRQ_PVD,       // 1
	handler_IRQ_RTC,       // 2
	handler_IRQ_FLASH,     // 3
	handler_IRQ_RCC,       // 4

	handler_IRQ_EXTI0_1,   // 5
	handler_IRQ_EXTI2_3,   // 6
	handler_IRQ_EXTI4_15,  // 7

	handler_IRQ_TS,        // 8

	handler_IRQ_DMA1_Channel1,   // 9
	handler_IRQ_DMA1_Channel2_3, // 10
	handler_IRQ_DMA1_Channel4_5, // 11

	handler_IRQ_ADC1_COMP,       // 12

	handler_IRQ_TIM1_BRK_UP_TRG, // 13
	handler_IRQ_TIM1_CC,         // 14
	handler_IRQ_TIM2,      // 15
	handler_IRQ_TIM3,      // 16
	handler_IRQ_TIM6_DAC,  // 17
	handler_Empty,         // 18 Reserved
	handler_IRQ_TIM14,     // 19
	handler_IRQ_TIM15,     // 20
	handler_IRQ_TIM16,     // 21
	handler_IRQ_TIM17,     // 22

	handler_IRQ_I2C1,      // 23
	handler_IRQ_I2C2,      // 24

	handler_IRQ_SPI1,      // 25
	handler_IRQ_SPI2,      // 26

	handler_IRQ_USART1,    // 27
	handler_IRQ_USART2,    // 28

	handler_Empty,         // 29 Reserved

	handler_IRQ_CEC,       // 30

	handler_Empty,         // 31 Reserved

	(void *)0xF108F85F
};
