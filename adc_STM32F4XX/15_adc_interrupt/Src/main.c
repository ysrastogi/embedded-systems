#include<stdint.h>
#include<stdio.h>
#include"stm32f4xx.h"
#include"adc.h"

// Where USART_TX is connected?
// Port A
// Pin2



char key;
uint32_t sensor_value;

int main(void)
{
	pa1_adc_interrupt_init();

	while(1){

	}
}

static void adc_callback(void){
	sensor_value = ADC1->DR;
	printf("Sensor value: %d \n\r",sensor_value);

}
void ADC_IRQHandler(void){
	/*Check for EOC in SR*/
	if((ADC1->SR & SR_EOC) != 0){
		/*Clear EOC*/
		ADC1->SR &=~ SR_EOC;

		//Do Something
		adc_callback();
	}
}
