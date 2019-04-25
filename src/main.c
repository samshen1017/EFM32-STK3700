#include "em_chip.h"
#include "leuart.h"

int main(void)
{
	CHIP_Init();
	leuart_init();
	
	while(1){
		leuart_write("Hello\r\n", sizeof("Hello\r\n"));
	}
}


