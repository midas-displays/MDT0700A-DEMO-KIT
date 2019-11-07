


#define CPT_RESET RPI_V2_GPIO_P1_13
#define CPT_INT RPI_V2_GPIO_P1_22
#define	CPT_address	0x38
#define CPT_RESET_HIGH	bcm2835_gpio_write(CPT_RESET,HIGH)
#define CPT_RESET_LOW	bcm2835_gpio_write(CPT_RESET,LOW)

#define touch_width		1792
#define touch_height	1092
#define scale_to_width	800		//the touch screen will be scaled to this resolution
#define	scale_to_height	480

unsigned int gest,touches,T1_flag,T1x,T1y,T2_flag,T2x,T2y,T3_flag,T3x,T3y,T4_flag,T4x,T4y,T5_flag,T5x,T5y;
char touch_buf[40];

void begin_cap_touch(void);
void get_cap_touch(void);

#include "Cap_Touch.c"
