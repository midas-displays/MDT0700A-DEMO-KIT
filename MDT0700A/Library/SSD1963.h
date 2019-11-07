
#define D0 RPI_V2_GPIO_P1_36
#define D1 RPI_V2_GPIO_P1_11
#define D2 RPI_V2_GPIO_P1_12
#define D3 RPI_V2_GPIO_P1_35
#define D4 RPI_V2_GPIO_P1_38
#define D5 RPI_V2_GPIO_P1_40
#define D6 RPI_V2_GPIO_P1_15
#define D7 RPI_V2_GPIO_P1_16
#define D8 RPI_V2_GPIO_P1_26

#define RESET RPI_V2_GPIO_P1_29
#define RS RPI_V2_GPIO_P1_31
#define WR RPI_V2_GPIO_P1_33
#define RD RPI_V2_GPIO_P1_37
#define CS RPI_V2_GPIO_P1_32
#define BLE RPI_V2_GPIO_P1_07
#define DISP RPI_V2_GPIO_P1_18


#define RESET_HIGH	bcm2835_gpio_write(RESET,HIGH)
#define RESET_LOW	bcm2835_gpio_write(RESET,LOW)
#define BLE_HIGH	bcm2835_gpio_write(BLE,HIGH)
#define BLE_LOW		bcm2835_gpio_write(BLE,LOW)
#define DISP_HIGH	bcm2835_gpio_write(DISP,HIGH)
#define DISP_LOW		bcm2835_gpio_write(DISP,LOW)

#define  disp_width   800
#define  disp_height  480
#define  memory_height  480
//You may still need to adjust the clock frequency.

void begin_display(void);
void write_bus(unsigned int data);
void set_data_write();
void set_cmd_write();
void Set_Index(int x);
void Set_Reg(int x, int y);
void Write_Data(int x);
void SSD1963_Init_9bit(void);
void clear_screen(long colour);
void draw_indexed_graphic(int pos_x1, int pos_y1, int width, int height, unsigned int *array, unsigned int *back_array, unsigned char value, int del_colour);
void draw_number(int pos_x1, int pos_y1, int width, int height, unsigned int *array, unsigned int *back_array, int del_colour, long value, unsigned char no_of_digets);
void load_bitmap(int width, int height, char *filename, unsigned int *array, int index);
void draw_image(int pos_x1, int pos_y1, int width, int height, unsigned int *array);
void draw_square();
#include "SSD1963.c"
