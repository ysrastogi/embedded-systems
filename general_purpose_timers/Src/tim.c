/*
 * tim.c
 *
 *  Created on: 25-Dec-2022
 *      Author: Yash Rastogi
 */

#include "stm32f4xx.h"

#define TIM2EN		(1U<<0)
#define CR1_CEN		(1U<<0)
#define GPIOAEN		(1U<<0)
#define AFR5_TIM	(1U<<20)

void tim2_1hz_init(void){
	/*Enable clock access to tim2*/
	RCC->APB1ENR |= TIM2EN;
	/*Set prescaler value*/
	TIM2->PSC = 1600 -1;
	/*Set auto-reload value*/
	TIM2->ARR = 1000-1;
	/*Clear counter*/
	TIM2->CNT = 0;
	/*Enable Timer*/
	TIM2->CR1 = CR1_CEN;
}

void tim2_output_compare(void){

	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA5 mode to alternate function*/
	GPIOA->MODER &=~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	/*Set PA5 alternate function type to TIM2_CH1*/
	GPIOA->AFR[0]	|= AFR5_TIM;

	/*Enable clock access to tim2*/
	RCC->APB1ENR |= TIM2EN;
	/*Set prescaler value*/
	TIM2->PSC = 1600 -1;
	/*Set auto-reload value*/
	TIM2->ARR = 10000-1;
	/*Set output compare toggle mode*/
	TIM2->CCMR1 = (1U<<4)| (1U<<5);
	/* Enable tim2 ch1 in compare mode*/
	TIM2->CCER |= (1U<<0);
	/*

	/*Clear counter*/
	TIM2->CNT = 0;
	/*Enable Timer*/
	TIM2->CR1 = CR1_CEN;
}


