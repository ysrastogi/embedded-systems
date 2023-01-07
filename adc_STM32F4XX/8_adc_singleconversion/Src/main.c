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
	pa1_adc_init();

	while(1){
		start_conversion();
		key = uart2_read();
		sensor_value = adc_read();
		printf("Sensor value: %d \n\r",sensor_value);
	}
}
