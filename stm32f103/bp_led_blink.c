#include<stdint.h>
#include"stm32f103xx.h"
#include"stm32f103xx_gpio.h"

void wait_ms(uint16_t d)
{
	for(int i=0; i<(d*350); i++);
}

void wait(uint8_t d)
{
	wait_ms(d*1000);
}

int main()
{
	//GPIO PC13 Led Pin Settings
	GPIO_Handle led;
	
	//led
	led.pGPIOx                         = GPIOC;
	led.GPIOx_PinConfig.PinNo          = GPIO_PIN13;
	led.GPIOx_PinConfig.PinMode        = GPIO_MODE_OP;
	led.GPIOx_PinConfig.PinOutputSpeed = GPIO_OP_SPEED_10;
	led.GPIOx_PinConfig.PinConfigType  = GPIO_GP_OP_PP;
	
	//GPIO Init
	GPIO_Init(&led);
	
	
	while(1)
	{
		//Toggle PC13 Led Pin
		GPIO_OpToggle(led.pGPIOx, led.GPIOx_PinConfig.PinNo);
		wait(1);
	}
	
	return 0;
}