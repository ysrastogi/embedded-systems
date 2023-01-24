/*
 * uart_txrx.c
 *
 *  Created on: 22-Dec-2022
 *      Author: Yash Rastogi
 */

#include"uart_txrx.h"

#define GPIOAEN			(1U<<0)
#define UART2EN			(1U<<17)

#define CR1_UE			(1U<<13)
#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)
#define SR_TXE			(1U<<7)
#define SR_RXNE			(1U<<5)

#define SYS_FREQ		16000000
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE	57600


static uint16_t compute_uart_bd(uint32_t PreiphClk, uint32_t BaudRate);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(int ch);
char uart2_read(void);

void uart2_txrx_init(void){
	/******Configure uart gpio pin******/

	/*Enable clock access to gpioa*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA2 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |=(1U<<5);

	/*Set PA2 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	/*Set PA3 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	/*Set PA3 alternate function type to UART_RX (AF07)*/
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);



	/***************CONFIGURE UART MODULE******************/
	/*Enable clock access to UART2*/
	RCC->APB1ENR |= UART2EN;
	/*Configure baudrate*/
	uart_set_baudrate(USART2,APB1_CLK,57600);
	/*Configure the transfer direction*/
	USART2->CR1 = (CR1_TE | CR1_RE);
	/*Enable UART module*/
	USART2->CR1 |= CR1_UE;

}
char uart2_read(void){
	/* Make sure the receive data register is not empty */
	while(!(USART2->SR & SR_RXNE)){
		/*Read Data*/
		return USART2->DR;
	}
}

void uart2_write(int ch){
	/*Make sure the transmit data register is empty*/
	while(!(USART2->SR & SR_TXE)){}
	/*Write to transmit data register*/
	USART2->DR = (ch & 0xFF);
}
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate){
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	return((PeriphClk +(BaudRate/2U))/BaudRate);
}



