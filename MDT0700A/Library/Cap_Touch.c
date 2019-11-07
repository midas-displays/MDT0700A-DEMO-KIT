void begin_cap_touch(void)
{
	bcm2835_gpio_fsel(CPT_INT,BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(CPT_RESET,BCM2835_GPIO_FSEL_OUTP);
	
	CPT_RESET_HIGH;
	bcm2835_delay(50);
	CPT_RESET_LOW;
	bcm2835_delay(50);
	CPT_RESET_HIGH;
	bcm2835_delay(50);
	
	bcm2835_i2c_begin();
	bcm2835_i2c_set_baudrate(400000);
	bcm2835_i2c_setSlaveAddress(CPT_address);
	T1x=0;	T1y=0;
	T2x=0;	T2y=0;
	T3x=0;	T3y=0;
	T4x=0;	T4y=0;
	T5x=0;	T5y=0;

}

void get_cap_touch(void)
{
unsigned int touch_data[15];
char touch_bufW[2];   
   
   
   
   
   if(bcm2835_gpio_lev(CPT_INT)==0)
   {
	  while(bcm2835_gpio_lev(CPT_INT)==0);	//wait for CPT_INT to go high.
	  touch_bufW[0]=0;
	  bcm2835_i2c_write(touch_bufW,1);		//set register read address to zero.
	  bcm2835_i2c_read(touch_buf,31);//34);		//send read touch command
      
	  gest=touch_buf[1];
	  touches=touch_buf[2];
	  touch_data[0]=touch_buf[3]>>6;
	  touch_data[1]=((int)(touch_buf[3]&0x0f)<<8)+touch_buf[4];
	  touch_data[2]=((int)(touch_buf[5]&0x0f)<<8)+touch_buf[6];
		  
	  touch_data[3]=touch_buf[9]>>6;
	  touch_data[4]=((int)(touch_buf[9]&0x0f)<<8)+touch_buf[0x0a];
	  touch_data[5]=((int)(touch_buf[0x0b]&0x0f)<<8)+touch_buf[0x0c];
		  
	  touch_data[6]=touch_buf[0x0f]>>6;
	  touch_data[7]=((int)(touch_buf[0x0f]&0x0f)<<8)+touch_buf[0x10];
	  touch_data[8]=((int)(touch_buf[0x11]&0x0f)<<8)+touch_buf[0x12];
		  
	  touch_data[9]=touch_buf[0x15]>>6;
	  touch_data[10]=((int)(touch_buf[0x15]&0x0f)<<8)+touch_buf[0x16];
	  touch_data[11]=((int)(touch_buf[0x17]&0x0f)<<8)+touch_buf[0x18];
		  
	  touch_data[12]=touch_buf[0x1b]>>6;
	  touch_data[13]=((int)(touch_buf[0x1b]&0x0f)<<8)+touch_buf[0x1c];
	  touch_data[14]=((int)(touch_buf[0x1d]&0x0f)<<8)+touch_buf[0x1e];
		  
	
		if(touch_data[0]==2)
		{
		  T1_flag=touch_data[0];
		  T1x=(touch_data[1]*scale_to_width)/touch_width;
		  T1y=(touch_data[2]*scale_to_height)/touch_height;
		}
	    else
	    {
		  T1_flag=0;
          T1x=0;
          T1y=0;	
        }
         
		if(touch_data[3]==2)
		{ 
		  T2_flag=touch_data[3];
		  T2x=(touch_data[4]*scale_to_width)/touch_width;
		  T2y=(touch_data[5]*scale_to_height)/touch_height;
		}
		else
		{
		  T2_flag=0;
          T2x=0;
          T2y=0;
		}
		
		if(touch_data[6]==2)
		{ 
		  T3_flag=touch_data[6];
		  T3x=(touch_data[7]*scale_to_width)/touch_width;
		  T3y=(touch_data[8]*scale_to_height)/touch_height;
	    }
	    else
		{
		  T3_flag=0;
          T3x=0;
          T3y=0;
		}
		  
		if(touch_data[9]==2)
		{ 
		  T4_flag=touch_data[9];
		  T4x=(touch_data[10]*scale_to_width)/touch_width;
		  T4y=(touch_data[11]*scale_to_height)/touch_height;
	    }
	    else
		{
		  T4_flag=0;
          T4x=0;
          T4y=0;
		}
		
		if(touch_data[12]==2)
		{ 
		  T5_flag=touch_data[12];
		  T5x=(touch_data[13]*scale_to_width)/touch_width;
		  T5y=(touch_data[14]*scale_to_height)/touch_height;
	    }
	    else
		{
		  T5_flag=0;
          T5x=0;
          T5y=0;
		}
		
   }
	 
   else
   { 
	if(!bcm2835_i2c_begin())	//if i2c stops then restart it.
	 {
		bcm2835_i2c_begin();
		printf("I2C cap touch restart \n");
		CPT_RESET_LOW;
	    bcm2835_delay(10);
		CPT_RESET_HIGH;
		bcm2835_delay(10);
		bcm2835_i2c_set_baudrate(400000);
		bcm2835_i2c_setSlaveAddress(CPT_address);
	 } 
	

	  gest=0;
      touches=0;
      
      T1_flag=0;
      T1x=0;
      T1y=0;
      
      T2_flag=0;
      T2x=0;
      T2y=0;
      
      T3_flag=0;
      T3x=0;
      T3y=0;
      
      T4_flag=0;
      T4x=0;
      T4y=0;
      
      T5_flag=0;
      T5x=0;
      T5y=0;
 
   }
	
}


