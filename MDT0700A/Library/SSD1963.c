void begin_display(void)
{
	bcm2835_gpio_fsel(D0,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(D1,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(D2,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(D3,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(D4,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(D5,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(D6,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(D7,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(D8,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RESET,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RS,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(WR,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RD,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(CS,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(BLE,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(DISP,BCM2835_GPIO_FSEL_OUTP);
	
	
	RESET_HIGH;
	
	BLE_LOW;
	DISP_LOW;
	bcm2835_delay(50);
	RESET_LOW;
	
	bcm2835_delay(50);
	RESET_HIGH;
	
	bcm2835_delay(50);
	
	DISP_HIGH;
	
	SSD1963_Init_9bit();
	clear_screen(0x00);
	
	
}


void write_bus(unsigned int data)
{
unsigned char d0,d1,d2,d3,d4,d5,d6,d7,d8;	//temp values for bits in data.

	
	if((data&0x01)==0x01) d0=1; else d0=0;
	if((data&0x02)==0x02) d1=1; else d1=0;
	if((data&0x04)==0x04) d2=1; else d2=0;
	if((data&0x08)==0x08) d3=1; else d3=0;
	if((data&0x10)==0x10) d4=1; else d4=0;
	if((data&0x20)==0x20) d5=1; else d5=0;
	if((data&0x40)==0x40) d6=1; else d6=0;
	if((data&0x80)==0x80) d7=1; else d7=0;
	if((data&0x100)==0x100) d8=1; else d8=0;
	bcm2835_gpio_write_mask((0<<WR)|(d0<<D0)|(d1<<D1)|(d2<<D2)|(d3<<D3)|(d4<<D4)|(d5<<D5)|(d6<<D6)|(d7<<D7)|(d8<<D8),(1<<WR)|(1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7)|(1<<D8)); //set WR low as well
	
	bcm2835_gpio_write(WR,HIGH);
	
}

void set_data_write()
{
	bcm2835_gpio_write(RS,HIGH);
	bcm2835_gpio_write(RD,HIGH);
	bcm2835_gpio_write(CS,LOW);
}

void set_cmd_write()
{
	bcm2835_gpio_write(RS,LOW);
	bcm2835_gpio_write(RD,HIGH);
	bcm2835_gpio_write(CS,LOW);
}

	
	//
//SSD1963 Set_Index
//
void Set_Index(int x)
{
  set_cmd_write();
  //delay(1);
  write_bus(x);
  //delay(1);
}

//
//SSD1963 Set_Reg
//
void Set_Reg(int x, int y)
{
  Set_Index(x);
  Write_Data(y);
}

void Write_Data(int x)
{
  set_data_write();
  //delay(1);
  write_bus(x);
  //delay(1);
}



//
// SSD1963 inits
//
void SSD1963_Init_9bit(void)
{

  Set_Index(0x01);        //Software Reset
  delay(5);               // Delay >= 5ms

  Set_Index(0x01);        //Software Reset
  delay(5);               // Delay >= 5ms

  Set_Index(0x01);        //Software Reset
  delay(5);               // Delay >= 5ms

  Set_Reg(0xE0, 0x01);    // START PLL
  delay(1);
  Set_Reg(0xE0, 0x03);    // LOCK PLL

  Set_Index(0xE2);        // SET PLL freq=113.33MHz assuming xtal of 10mhz
  Write_Data(0x21);
  Write_Data(0x02);
  Write_Data(0x54);

  Set_Index(0xE6);        // SET PCLK freq=25MHz, pixel clk freq
  Write_Data(0x04);    //0x04=7"  0x03=5.6"  0x01=3.5"  Just guessing here may not be correct
  Write_Data(0x8a);
  Write_Data(0x31);


  Set_Index(0xB0);        // SET LCD MODE SET TFT 18Bits MODE

  Write_Data(0x38);    // SET TFT MODE & hsync+Vsync+DEN MODE
  Write_Data(0x00);    // SET TFT MODE & hsync+Vsync+DEN MODE
  Write_Data((disp_width-1)>>8);  // SET horizontal size=640-1 HightByte
  Write_Data(disp_width-1);       // SET horizontal size=640-1 LowByte
  Write_Data((disp_height-1)>>8); // SET vertical size=480-1 HightByte
  Write_Data(disp_height-1);      // SET vertical size=480-1 LowByte

  Write_Data(0x00);    // SET even/odd line RGB seq.00=RGB

  //Set_Reg(0x3a, 0x60);    // Set 18bits/pixel this command is no longer valid.

  Set_Index(0xB4);        // SET HBP
  Write_Data((disp_width+75)>>8);
  Write_Data(disp_width+75);
  Write_Data(0x00);    // SET HBP
  Write_Data(0x2e);//44);	//7=2e 5=44
  Write_Data(0x07);    // SET HPW=8-1
  Write_Data(0x00);
  Write_Data(0x00);    // SET Hsync pulse start position
  Write_Data(0x00);    // SET Hsync pulse subpixel start position

  Set_Index(0xB6);        // SET VBP
  Write_Data((disp_height+22)>>8);
  Write_Data(disp_height+22);
  Write_Data(0x00);    // SET VBP+VPW = 18-1
  Write_Data(0x17);//11);
  Write_Data(0x02);    // SET Vsync pulse width =3-1
  Write_Data(0x00);    // SET Vsync pulse start position
  Write_Data(0x00);

  Set_Index(0x2A);        // SET column address
  Write_Data(0x00);    // SET start column address=0
  Write_Data(0x00);
  Write_Data((disp_width-1)>>8);  // SET horizontal size=640-1 HightByte
  Write_Data(disp_width-1);       // SET horizontal size=640-1 LowByte

  Set_Index(0x2B);        // SET page address
  Write_Data(0x00);    // SET start page address=0
  Write_Data(0x00);
  Write_Data((memory_height-1)>>8); // SET vertical size=480-1 HightByte
  Write_Data(memory_height-1);      // SET vertical size=480-1 LowByte

  Set_Index(0x37);        // SET scroll start
  Write_Data(0);       //high byte
  Write_Data(0);       //low byte
  
  Set_Index(0xb8);        // gpio to enable 7 inch
  Write_Data(0x0f);  
  Write_Data(0x01);  
  Set_Reg(0xba,0x01);

  Set_Reg(0x36, 0x08);    // 7.0&3.5=0x88  5.6=0x8a SET address mode bit3  0=rgb 1=bgr  bit7 0=top to bottom 1=bottom to top bit1=1 for horz flip
                          //set to bgr and bottom to top for bmp compatibility.
  Set_Reg(0xF0, 0x06);    // SET pixel data I/F 0x06=format=9bit 0x00=8bit interface.

  
  Set_Index(0x29);        // SET display on


}



void clear_screen(long colour)
{
 int x,y,RG,GB,p,red,green,blue;
  red=colour>>16;
  green=colour>>8;
  blue=colour;
  
  RG = ((red&0xfc)<<1);
  p=green&0xfc;
  RG += (p>>5);
  GB = ((p&0x1c)<<4)+((blue&0xfc)>>2);
  Set_Index(0x2A);        				// SET column address
  Write_Data(0x00);    				// SET start column address=0
  Write_Data(0x00);
  Write_Data((disp_width-1)>>8);     // SET end column address=width-1
  Write_Data(disp_width-1);

  Set_Index(0x2B);        				// SET page address
  Write_Data(0x00);    				// SET start page address=0
  Write_Data(0x00);
  Write_Data((memory_height-1)>>8);  // SET end page address=height-1
  Write_Data(memory_height-1);
  Set_Index(0x2c);        				//Write memory start
  set_data_write();
  for(y=0;y<memory_height;y++)
  {
    for(x=0;x<disp_width;x++)
    {
      write_bus(RG);
      
      write_bus(GB);
      
     
      
    }
  }

}





//Draw an image storred in a ram int array 1 pixel=two ints. 0000 000R RRRR RGGG 0000 000G GGBB BBBB	
void draw_image(int pos_x1, int pos_y1, int width, int height, unsigned int *array)
{
long i;	
	
	Set_Index(0x2A);        					// SET column address
	Write_Data(pos_x1>>8);    				// SET start column address=0
	Write_Data(pos_x1&0x00ff);
	Write_Data((pos_x1+width-1)>>8);     	// SET end column address=width-1
	Write_Data((pos_x1+width-1)&0x00ff);

	Set_Index(0x2B);        					// SET page address
	Write_Data(pos_y1>>8);    				// SET start page address=0
	Write_Data(pos_y1&0x00ff);
	Write_Data((pos_y1+height-1)>>8);  	// SET end page address=height-1
	Write_Data((pos_y1+height-1)&0x00ff);
	Set_Index(0x2c);        					//Write memory start
	set_data_write();
	
	for(i=0;i<width*height*2;i++)
	  write_bus(array[i]);
	
}

//loads a 24 bit bitmap to an int array for 9 bit = two bytes at 18bpp		0000 000R RRRR RGGG 0000 000G GGBB BBBB	
//0,0 = top left
void load_bitmap(int width, int height, char *filename, unsigned int *array, int index)
{		
int p;
long x,y;
	
	height=height*index;
	FILE *bmpFile = fopen(filename,"rb");
	
	fseek(bmpFile,0x36,SEEK_SET);            //Goto start of image data.
			
	for(y=height-1;y>=0;y--)
	{
		for(x=0;x<width;x++)
		{
		    
		  	array[(y*width*2)+(x*2)] = ((fgetc(bmpFile)&0xfc)<<1);
		  	p=fgetc(bmpFile)&0xfc;
		  	array[(y*width*2)+(x*2)] += (p>>5);
		  	array[(y*width*2)+(x*2)+1] = ((p&0x1c)<<4)+((fgetc(bmpFile)&0xfc)>>2);
		  	
		 } 	
		 switch(width%4)					//strip out packing bytes from end of bitmap line
		 {
			 case	3:	fgetc(bmpFile);	
			 case	2:	fgetc(bmpFile);
			 case	1:	fgetc(bmpFile);
			 case	0:	break;
			 default:	break;
		 }
		
	}
		fclose(bmpFile);
}

// moded for 9 bit = two bytes at 18bpp		0000 000R RRRR RGGG 0000 000G GGBB BBBB	
//0,0 = top left.
void draw_number(int pos_x1, int pos_y1, int width, int height, unsigned int *array, unsigned int *back_array, int del_colour, long value, unsigned char no_of_digets)
{
	unsigned int x,numbers[10];
	
	numbers[9]=value/1000000000;
	numbers[8]=(value/100000000)%10;
	numbers[7]=(value/10000000)%10;
	numbers[6]=(value/1000000)%10;
	numbers[5]=(value/100000)%10;
	numbers[4]=(value/10000)%10;
	numbers[3]=(value/1000)%10;
	numbers[2]=(value/100)%10;
	numbers[1]=(value/10)%10;
	numbers[0]=value%10;
	
	for(x=0;x<no_of_digets;x++)
	{
		draw_indexed_graphic(pos_x1+(width*x),pos_y1,width,height,array,back_array,numbers[no_of_digets-x-1],del_colour);
	}
  
}
			

// moded for 9 bit = two bytes at 18bpp		0000 000R RRRR RGGG 0000 000G GGBB BBBB		
void draw_indexed_graphic(int pos_x1, int pos_y1, int width, int height, unsigned int *array, unsigned int *back_array, unsigned char value, int del_colour)
{

  unsigned int x,offset,RG,GB;
  offset=value*width*height*2;
  Set_Index(0x2A);        					// SET column address
  Write_Data(pos_x1>>8);    				// SET start column address=0
  Write_Data(pos_x1&0x00ff);
  Write_Data((pos_x1+width-1)>>8);     	// SET end column address=width-1
  Write_Data((pos_x1+width-1)&0x00ff);

  Set_Index(0x2B);        					// SET page address
  Write_Data(pos_y1>>8);    				// SET start page address=0
  Write_Data(pos_y1&0x00ff);
  Write_Data((pos_y1+height-1)>>8);  	// SET end page address=height-1
  Write_Data((pos_y1+height-1)&0x00ff);
  Set_Index(0x2c);        					//Write memory start
  set_data_write();
  for(x=0;x<(width*height);x++)
   {
      RG=array[x*2+offset];
      GB=array[x*2+1+offset];
      if((RG==del_colour)&(GB==del_colour))
        {
		 //printf("%d,%d\n",x,pos_x1*2 + pos_y1*1600 + (x/34)*(1600-68) + x*2);
         write_bus(back_array[(pos_x1*2) + (pos_y1*disp_width*2) + ((x/width)*((disp_width*2)-(width*2))) + (x*2)]);
         write_bus(back_array[(pos_x1*2) + (pos_y1*disp_width*2) + ((x/width)*((disp_width*2)-(width*2))) + (x*2) + 1]);
		}
	  else
	    {
		 write_bus(RG);
         write_bus(GB);
		}
      
      
      
    }
  


}
			
// moded for 9 bit = two bytes at 18bpp		0000 000R RRRR RGGG 0000 000G GGBB BBBB		
void draw_square (int pos_x1, int pos_y1, int width, int height, long colour)
{

  int x,y,RG,GB,p,red,green,blue;
  red=colour>>16;
  green=colour>>8;
  blue=colour;
  
  RG = ((red&0xfc)<<1);
  p=green&0xfc;
  RG += (p>>5);
  GB = ((p&0x1c)<<4)+((blue&0xfc)>>2);

  Set_Index(0x2A);        					// SET column address
  Write_Data(pos_x1>>8);    				// SET start column address=0
  Write_Data(pos_x1&0x00ff);
  Write_Data((pos_x1+width-1)>>8);     	// SET end column address=width-1
  Write_Data((pos_x1+width-1)&0x00ff);

  Set_Index(0x2B);        					// SET page address
  Write_Data(pos_y1>>8);    				// SET start page address=0
  Write_Data(pos_y1&0x00ff);
  Write_Data((pos_y1+height-1)>>8);  	// SET end page address=height-1
  Write_Data((pos_y1+height-1)&0x00ff);
  Set_Index(0x2c);        					//Write memory start
  set_data_write();
  for(y=0;y<height;y++)
 {
    for(x=0;x<width;x++)
   {
      write_bus(RG);
      
      write_bus(GB);
      
      
      
    }
  }


}

