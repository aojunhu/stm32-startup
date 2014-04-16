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
void handler_IRQ_RTC()             ALIAS("handler_Empty");
void handler_IRQ_FLASH()           ALIAS("handler_Empty");
void handler_IRQ_RCC()             ALIAS("handler_Empty");

void handler_IRQ_EXTI0_1()         ALIAS("handler_Empty");
void handler_IRQ_EXTI2_3()         ALIAS("handler_Empty");
void handler_IRQ_EXTI4_15()        ALIAS("handler_Empty");

void handler_IRQ_DMA1_Channel1()   ALIAS("handler_Empty");
void handler_IRQ_DMA1_Channel2_3() ALIAS("handler_Empty");
void handler_IRQ_DMA1_Channel4_5() ALIAS("handler_Empty");

void handler_IRQ_ADC1_COMP()       ALIAS("handler_Empty");

void handler_IRQ_TIM1_BRK_UP_TRG() ALIAS("handler_Empty");
void handler_IRQ_TIM1_CC()         ALIAS("handler_Empty");
void handler_IRQ_TIM3()            ALIAS("handler_Empty");
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

//Vectors table
SECTION(".interrupt_vector")
void (* const table_interrupt_vector[])() = {

	(void *)&_stack_end,   // stack top
	handler_Reset,         // Reset
	handler_NMI,           // NMI
	handler_HardFault,     // Hard fault
	handler_Default,       //   Reserved
	handler_Default,       //   Reserved
	handler_Default,       //   Reserved
	handler_Default,       //   Reserved
	handler_Default,       //   Reserved
	handler_Default,       //   Reserved
	handler_Default,       //   Reserved
	handler_SVCall,        // SVCall
	handler_Default,       //   Reserved
	handler_Default,       //   Reserved
	handler_PendSV,        // PendSV
	handler_Systick,       // SysTick

	handler_IRQ_WWDG,      // IRQ0
	handler_Default,       //   Reserved
	handler_IRQ_RTC,       // RTC
	handler_IRQ_FLASH,     // FLASH
	handler_IRQ_RCC,       // RCC

	handler_IRQ_EXTI0_1,   // EXTI0..1
	handler_IRQ_EXTI2_3,   // EXTI2..3
	handler_IRQ_EXTI4_15,  // EXTI4..15

	handler_Default,       //   Reserved

	handler_IRQ_DMA1_Channel1,   // DMA1.1
	handler_IRQ_DMA1_Channel2_3, // DMA2.3
	handler_IRQ_DMA1_Channel4_5, // DMA4.5

	handler_IRQ_ADC1_COMP,       // ADC

	handler_IRQ_TIM1_BRK_UP_TRG, // TIM1  break, update, trigger and commutation
	handler_IRQ_TIM1_CC,         // TIM1 capture compare
	handler_Default,       //   Reserved
	handler_IRQ_TIM3,      // TIM3 global
	handler_Default,       //   Reserved
	handler_Default,       //   Reserved
	handler_IRQ_TIM14,     // TIM14 global
	handler_IRQ_TIM15,     // TIM15 global
	handler_IRQ_TIM16,     // TIM16 global
	handler_IRQ_TIM17,     // TIM17 global

	handler_IRQ_I2C1,      // I2C1 global
	handler_IRQ_I2C2,      // I2C2 global

	handler_IRQ_SPI1,      // SPI1 global
	handler_IRQ_SPI2,      // SPI2 global

	handler_IRQ_USART1,    // USART1 global
	handler_IRQ_USART2,    // USART2 global

	handler_Default,       //   Reserved
	handler_Default,       //   Reserved
	handler_Default,       //   Reserved

	(void *)0xF108F85F
};

