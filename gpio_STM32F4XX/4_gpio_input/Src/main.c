#include"stm32f4xx.h"
// Where is user push button is connected?
//PC13
//pin 2



#define GPIOAEN			(1U<<0)
#define GPIOCEN			(1U<<2)
#define PIN5			(1U<<5)
#define PIN13			(1U<<13)

#define LED_PIN			PIN5
#define BTN_PIN			PIN13


int main(void)
{
	/*Enable clock access to GPIOA and GPIOC*/
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	/*Set PA5 as output pin*/
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

	/*Set PA 13 as input pin*/
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);
	while(1){
		/*Check if button is pressed*/
		if(GPIOC->IDR & BTN_PIN){
		GPIOA->BSRR = LED_PIN;
		}
		else{
		GPIOA->BSRR = (1U<<21);
		}
	}
}
