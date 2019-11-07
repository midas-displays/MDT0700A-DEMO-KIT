/*
 *
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <bcm2835.h>
//#include <math.h>		//needed for pow() function also put -lm in build paramiters
//#include <stdlib.h>		//needed for abs() function
#include "./Library/Cap_Touch.h"
#include "./Library/SSD1963.h"

void boot_screen(void);
void curtain();
void music();
void voice();
void screen1();

int main(int argc, char **argv)
{


	

	if(!bcm2835_init())
	  return 1;
	
	begin_cap_touch();
	begin_display();
	
	
	boot_screen();

	
		 while(1)
		 {

		  
		    get_cap_touch();  
		 
		  
		    if((T1x>1) && (T1x<246) && (T1y>1) && (T1y<208))
		      screen1();
		    
		    if((T1x>555) && (T1x<750) && (T1y>60) && (T1y<208))
		      voice();
		      	
			if((T1x>1) && (T1x<246) && (T1y>270) && (T1y<440))
		      music();
		      		
			if((T1x>550) && (T1x<790) && (T1y>270) && (T1y<440))
		      curtain();
		 }
		 

	return 0;
}  //main

void boot_screen(void)
{
	unsigned int display_array1[384000*2];

	load_bitmap(800,480,"./img/Specs.bmp",display_array1,1);
	draw_image(0,0,800,480,display_array1);
	BLE_HIGH;	//turn on backlight
	bcm2835_delay(8000);
	load_bitmap(800,480,"./img/Main.bmp",display_array1,1);
	draw_image(0,0,800,480,display_array1);

}


#define SCREEN	384000*2
#define NUMBER	27500*2		//50 x 55 x 10
#define SLIDER	27*71*2
#define	BEAM	120*180*2
#define	LIGHT	101*86*2

void screen1(void)
{

unsigned int display_array2[SCREEN];
unsigned int num_array2[NUMBER];
unsigned int slider1_array[SLIDER];
unsigned int beam1_array[BEAM];
unsigned int beam2_array[BEAM];
unsigned int beam3_array[BEAM];
unsigned int beam4_array[BEAM];
unsigned int beam5_array[BEAM];
unsigned int beam6_array[BEAM];
unsigned int light_array[LIGHT];
	
		
	
int ax=35+22,ay=220,bx=695+22,by=220,beam,old_beam,beam2,old_beam2;

	
	
	   	load_bitmap(800,480,"./img/slider_back2.bmp",display_array2,1);
		
		load_bitmap(50,55,"./img/0to9_50x55.bmp",num_array2,10);
		
		load_bitmap(27,71,"./img/slider1_27x71.bmp",slider1_array,1);
		
		load_bitmap(120,180,"./img/beam1_120x180.bmp",beam1_array,1);
		
		load_bitmap(120,180,"./img/beam2_120x180.bmp",beam2_array,1);
		
		load_bitmap(120,180,"./img/beam3_120x180.bmp",beam3_array,1);
		
		load_bitmap(120,180,"./img/beam4_120x180.bmp",beam4_array,1);
		
		load_bitmap(120,180,"./img/beam5_120x180.bmp",beam5_array,1);
		
		load_bitmap(120,180,"./img/beam6_120x180.bmp",beam6_array,1);
		
		load_bitmap(101,86,"./img/light_101x86.bmp",light_array,1);
	
		draw_image(0,0,800,480,display_array2);
		  
		   
		//draw_indexed_graphic(ax,ay-60,69,120,slider1_array,display_array2,0,0x7);		 
		//draw_indexed_graphic(bx,by-60,69,120,slider1_array,display_array2,0,0x7);	
		
		draw_indexed_graphic(ax,ay-35,27,71,slider1_array,display_array2,0,0x0);		 
		draw_indexed_graphic(bx,by-35,27,71,slider1_array,display_array2,0,0x0);	
		  
		draw_indexed_graphic(228,130,101,86,light_array,display_array2,0,0x1ff);		
		draw_indexed_graphic(220,212,120,180,beam3_array,display_array2,0,0x1ff);	
		draw_number(250,70,50,55,num_array2,display_array2,0x00,4,1);		
		  
		draw_indexed_graphic(468,130,101,86,light_array,display_array2,0,0x1ff);		
		draw_indexed_graphic(460,212,120,180,beam3_array,display_array2,0,0x1ff);	
		draw_number(490,70,50,55,num_array2,display_array2,0x00,4,1);		
		  
		//bcm2835_delay(500);
		 
		 
		  while((T1x<770)||(T1y>30))
		  {
			
		   
		   get_cap_touch();
		   //printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d XXX\n",touch_mode,touches,T1x,T1y,T2x,T2y,T3x,T3y,T4x,T4y,T5x,T5y);
		   if((T1x>20)&&(T1x<120)&&(T1y>80)&&(T1y<400))
		   {
			   while((ay/5)!=(T1y/5))
			   {  
			    if(ay<T1y)
				  ay+=5;
			    if(ay>T1y)
				  ay-=5;
			    //draw_indexed_graphic(ax,ay-60,69,120,slider1_array,display_array2,0,0x7);
			    draw_indexed_graphic(ax,ay-35,27,71,slider1_array,display_array2,0,0x0);
			    beam=(ay-100)/40;
			    if(beam != old_beam)
			    {
				   switch(beam)
				   {
					case	1:	draw_indexed_graphic(220,212,120,180,beam1_array,display_array2,0,0x1ff);
								draw_number(250,70,50,55,num_array2,display_array2,0x00,6,1);
								break;
					case	2:	draw_indexed_graphic(220,212,120,180,beam2_array,display_array2,0,0x1ff);
								draw_number(250,70,50,55,num_array2,display_array2,0x00,5,1);
								break;
					case	3:	draw_indexed_graphic(220,212,120,180,beam3_array,display_array2,0,0x1ff);
								draw_number(250,70,50,55,num_array2,display_array2,0x00,4,1);
								break;
					case	4:	draw_indexed_graphic(220,212,120,180,beam4_array,display_array2,0,0x1ff);
								draw_number(250,70,50,55,num_array2,display_array2,0x00,3,1);
								break;
					case	5:	draw_indexed_graphic(220,212,120,180,beam5_array,display_array2,0,0x1ff);
								draw_number(250,70,50,55,num_array2,display_array2,0x00,2,1);
								break;
					case	6:	draw_indexed_graphic(220,212,120,180,beam6_array,display_array2,0,0x1ff);
								draw_number(250,70,50,55,num_array2,display_array2,0x00,1,1);
								break;
					default:	break;
				   }		
			    }
		       old_beam=beam;
			   }	 
		   } 
		   if((T2x>20)&&(T2x<120)&&(T2y>80)&&(T2y<400))
		   {
			   while((ay/5)!=(T2y/5))
			   {  
			    if(ay<T2y)
				  ay+=5;
			    if(ay>T2y)
				  ay-=5;
			    //draw_indexed_graphic(ax,ay-60,69,120,slider1_array,display_array2,0,0x7);
			    draw_indexed_graphic(ax,ay-35,27,71,slider1_array,display_array2,0,0x0);
			    beam=(ay-100)/40;
			    if(beam != old_beam)
			    {
				   switch(beam)
				   {
					case	1:	draw_indexed_graphic(220,212,120,180,beam1_array,display_array2,0,0x1ff);
								draw_number(250,70,50,55,num_array2,display_array2,0x00,6,1);
								break;
					case	2:	draw_indexed_graphic(220,212,120,180,beam2_array,display_array2,0,0x1ff);
								draw_number(250,70,50,55,num_array2,display_array2,0x00,5,1);
								break;
					case	3:	draw_indexed_graphic(220,212,120,180,beam3_array,display_array2,0,0x1ff);
								draw_number(250,70,50,55,num_array2,display_array2,0x00,4,1);
								break;
					case	4:	draw_indexed_graphic(220,212,120,180,beam4_array,display_array2,0,0x1ff);
								draw_number(250,70,50,55,num_array2,display_array2,0x00,3,1);
								break;
					case	5:	draw_indexed_graphic(220,212,120,180,beam5_array,display_array2,0,0x1ff);
								draw_number(250,70,50,55,num_array2,display_array2,0x00,2,1);
								break;
					case	6:	draw_indexed_graphic(220,212,120,180,beam6_array,display_array2,0,0x1ff);
								draw_number(250,70,50,55,num_array2,display_array2,0x00,1,1);
								break;
					default:	break;
				   }		
			    }
		       old_beam=beam;
			   }	 
			    
		   } 
		   if((T1x>675)&&(T1x<785)&&(T1y>80)&&(T1y<400))
		   {
			   while((by/5)!=(T1y/5))
			   {  
			    if(by<T1y)
				  by+=5;
			    if(by>T1y)
				  by-=5;
			    //draw_indexed_graphic(bx,by-60,69,120,slider1_array,display_array2,0,0x7);
			    draw_indexed_graphic(bx,by-35,27,71,slider1_array,display_array2,0,0x0);
			    beam2=(by-100)/40;
			    if(beam2 != old_beam2)
			    {
				   switch(beam2)
				   {
					case	1:	draw_indexed_graphic(460,212,120,180,beam1_array,display_array2,0,0x1ff);
								draw_number(490,70,50,55,num_array2,display_array2,0x00,6,1);
								break;
					case	2:	draw_indexed_graphic(460,212,120,180,beam2_array,display_array2,0,0x1ff);
								draw_number(490,70,50,55,num_array2,display_array2,0x00,5,1);
								break;
					case	3:	draw_indexed_graphic(460,212,120,180,beam3_array,display_array2,0,0x1ff);
								draw_number(490,70,50,55,num_array2,display_array2,0x00,4,1);
								break;
					case	4:	draw_indexed_graphic(460,212,120,180,beam4_array,display_array2,0,0x1ff);
								draw_number(490,70,50,55,num_array2,display_array2,0x00,3,1);
								break;
					case	5:	draw_indexed_graphic(460,212,120,180,beam5_array,display_array2,0,0x1ff);
								draw_number(490,70,50,55,num_array2,display_array2,0x00,2,1);
								break;
					case	6:	draw_indexed_graphic(460,212,120,180,beam6_array,display_array2,0,0x1ff);
								draw_number(490,70,50,55,num_array2,display_array2,0x00,1,1);
								break;
					default:	break;
				   }		
			    }
			    old_beam2=beam2;
		   
			   }	 
		   } 
		   if((T2x>675)&&(T2x<785)&&(T2y>80)&&(T2y<400))
		   {
			   while((by/5)!=(T2y/5))
			   {  
			    if(by<T2y)
				  by+=5;
			    if(by>T2y)
				  by-=5;
		        //draw_indexed_graphic(bx,by-60,69,120,slider1_array,display_array2,0,0x7);
		        draw_indexed_graphic(bx,by-35,27,71,slider1_array,display_array2,0,0x0);
		        beam2=(by-100)/40;
			    if(beam2 != old_beam2)
			    {
				   switch(beam2)
				   {
					case	1:	draw_indexed_graphic(460,212,120,180,beam1_array,display_array2,0,0x1ff);
								draw_number(490,70,50,55,num_array2,display_array2,0x00,6,1);
								break;
					case	2:	draw_indexed_graphic(460,212,120,180,beam2_array,display_array2,0,0x1ff);
								draw_number(490,70,50,55,num_array2,display_array2,0x00,5,1);
								break;
					case	3:	draw_indexed_graphic(460,212,120,180,beam3_array,display_array2,0,0x1ff);
								draw_number(490,70,50,55,num_array2,display_array2,0x00,4,1);
								break;
					case	4:	draw_indexed_graphic(460,212,120,180,beam4_array,display_array2,0,0x1ff);
								draw_number(490,70,50,55,num_array2,display_array2,0x00,3,1);
								break;
					case	5:	draw_indexed_graphic(460,212,120,180,beam5_array,display_array2,0,0x1ff);
								draw_number(490,70,50,55,num_array2,display_array2,0x00,2,1);
								break;
					case	6:	draw_indexed_graphic(460,212,120,180,beam6_array,display_array2,0,0x1ff);
								draw_number(490,70,50,55,num_array2,display_array2,0x00,1,1);
								break;
					default:	break;
				   }		
			    }
			    old_beam2=beam2;
		   
			   }	 
		   }
		  }
		//  unsigned int display_array2[384000*2];
		  load_bitmap(800,480,"./img/Main.bmp",display_array2,1);
		  draw_image(0,0,800,480,display_array2);
		  T1x=1;
		  
		  	
}



void curtain()
{
	

unsigned int display_array1[384000*2];

unsigned int butm1[250*100*2];
unsigned int butm2[250*100*2];
unsigned int butm3[250*100*2];
unsigned int butm4[250*100*2];

int d;	

d=1;	
load_bitmap(800,480,"./img/Background3.bmp",display_array1,1);					 
draw_image(0,0,800,480,display_array1);
			

		load_bitmap(250,100,"./img/M1.bmp",butm1,1);
		load_bitmap(250,100,"./img/M2.bmp",butm2,1);
		load_bitmap(250,100,"./img/M3.bmp",butm3,1);
		load_bitmap(250,100,"./img/M4.bmp",butm4,1);

		
			 
		draw_indexed_graphic(20,100,250,100,butm1,display_array1,0,0x0);
		draw_indexed_graphic(530,100,250,100,butm2,display_array1,0,0x0);
		draw_indexed_graphic(20,300,250,100,butm3,display_array1,0,0x0);
		draw_indexed_graphic(530,300,250,100,butm4,display_array1,0,0x0);

	    bcm2835_delay(500);
		  
	
		  while(d==1)
		  {
		 
		  
		   get_cap_touch();  
		   //printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d XXX\n",touches,T1x,T1y,T2x,T2y,T3x,T3y,T4x,T4y,T5x,T5y); 
		   
		   if((T1x>30) & (T1x<230) & (T1y>100) & (T1y<180))
		   {
		     unsigned int butm1a[250*100*2];
		     unsigned int w1[190*268*2];
		     
		    
		     load_bitmap(250,100,"./img/M1a.bmp",butm1a,1);
		     load_bitmap(190,268,"./img/W1.bmp",w1,1);
		     
		     draw_indexed_graphic(20,100,250,100,butm1a,display_array1,0,0x0);
		     draw_indexed_graphic(303,120,190,268,w1,display_array1,0,0x0);
		     
			  draw_indexed_graphic(530,100,250,100,butm2,display_array1,0,0x0);
			  draw_indexed_graphic(20,300,250,100,butm3,display_array1,0,0x0);
			  draw_indexed_graphic(530,300,250,100,butm4,display_array1,0,0x0);	
		     
		     //get_cap_touch(); 
		       
		   }
		     
		   if((T1x>540) & (T1x<760) & (T1y>100) & (T1y<180))
		   {
		     unsigned int butm2a[250*100*2];
		     unsigned int w2[190*268*2];
		     
		     
		     load_bitmap(250,100,"./img/M2a.bmp",butm2a,1);
		     load_bitmap(190,268,"./img/W2.bmp",w2,1);
		     
		     draw_indexed_graphic(530,100,250,100,butm2a,display_array1,0,0x0);
		     draw_indexed_graphic(303,120,190,268,w2,display_array1,0,0x0);
		     
			 
			  draw_indexed_graphic(20,100,250,100,butm1,display_array1,0,0x0);
			  draw_indexed_graphic(20,300,250,100,butm3,display_array1,0,0x0);
			  draw_indexed_graphic(530,300,250,100,butm4,display_array1,0,0x0);	
		     
		     //get_cap_touch(); 
		     }
		     
		       
		   if((T1x>30) & (T1x<260) & (T1y>300) & (T1y<380))
		   {
		     unsigned int butm3a[250*100*2];
		     unsigned int w3[190*268*2];
		     
		     
		     load_bitmap(250,100,"./img/M3a.bmp",butm3a,1);
		     load_bitmap(190,268,"./img/W3.bmp",w3,1);
		     
		     draw_indexed_graphic(20,300,250,100,butm3a,display_array1,0,0x0);
		     draw_indexed_graphic(303,120,190,268,w3,display_array1,0,0x0);
		     
			  draw_indexed_graphic(20,100,250,100,butm1,display_array1,0,0x0);
			  draw_indexed_graphic(530,100,250,100,butm2,display_array1,0,0x0);
			  draw_indexed_graphic(530,300,250,100,butm4,display_array1,0,0x0);

		     
		     //get_cap_touch(); 
		 }
		   
		     
		   if((T1x>540) & (T1x<760) & (T1y>300) & (T1y<380))
		   {
		     unsigned int butm4a[250*100*2];
		     unsigned int w4[190*268*2];
		     
		     
		     load_bitmap(250,100,"./img/M4a.bmp",butm4a,1);
		     load_bitmap(190,268,"./img/W4.bmp",w4,1);
		     
		     draw_indexed_graphic(530,300,250,100,butm4a,display_array1,0,0x0);
		     draw_indexed_graphic(303,120,190,268,w4,display_array1,0,0x0);
		     
			  draw_indexed_graphic(530,100,250,100,butm2,display_array1,0,0x0);
			  draw_indexed_graphic(20,100,250,100,butm1,display_array1,0,0x0);
			  draw_indexed_graphic(20,300,250,100,butm3,display_array1,0,0x0);
		
		     
		     //get_cap_touch(); 
		   
		   }
		   
		   if((T1x>750) && (T1y>1) & (T1y<60))
		   {
			   
			
			load_bitmap(800,480,"./img/Main.bmp",display_array1,1);
			draw_image(0,0,800,480,display_array1);
			d=0;   
			   
		   }
		   

	   
   } //while  	
	
	
	
}


void music()
{
	




unsigned int display_array1[384000*2];
unsigned int buts[250*100*2];
unsigned int butb[250*100*2];
unsigned int butk[250*100*2];
unsigned int butd[250*100*2];
unsigned int butbat[250*100*2];
unsigned int butg[250*100*2];
	

//long i;
unsigned int p,c;
//const unsigned char mask1[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
//const unsigned char mask2[8]={1,2,4,8,16,32,64,128};
	
c=1;	
	
load_bitmap(800,480,"./img/Background2.bmp",display_array1,1);
draw_image(0,0,800,480,display_array1);
	
	////working
	


		//load_bitmap(114,165,"lamp.bmp",lamp,1);	
		load_bitmap(250,100,"./img/Butbs.bmp",buts,1);
		load_bitmap(250,100,"./img/Butbb.bmp",butb,1);
		load_bitmap(250,100,"./img/Butk.bmp",butk,1);
		load_bitmap(250,100,"./img/Butd.bmp",butd,1);
		load_bitmap(250,100,"./img/Butbat.bmp",butbat,1);
		load_bitmap(250,100,"./img/Butg.bmp",butg,1);		

		
		//  draw_indexed_graphic(30,50,114,165,lamp,display_array1,0,0x0);
		 // draw_indexed_graphic(350,190,100,100,button1_array,display_array1,0,0x0);		 
		  draw_indexed_graphic(20,100,250,100,buts,display_array1,0,0x0);
		  draw_indexed_graphic(530,100,250,100,butb,display_array1,0,0x0);
		  draw_indexed_graphic(20,200,250,100,butk,display_array1,0,0x0);
		  draw_indexed_graphic(530,200,250,100,butbat,display_array1,0,0x0);
		  draw_indexed_graphic(20,300,250,100,butd,display_array1,0,0x0);
		  draw_indexed_graphic(530,300,250,100,butg,display_array1,0,0x0);		 	 
		 
		 
		  bcm2835_delay(500);
		  

		  p=0;
		  while(c==1)
		  {

		   p++;
		   
		   get_cap_touch();  
		    
		   
		   if((T1x>30) & (T1x<260) & (T1y>130) & (T1y<160))
		   {
		     unsigned int buts2[250*100*2];
		     unsigned int bed1[200*200*2];
		     
		     
		     load_bitmap(250,100,"./img/Butbs2.bmp",buts2,1);
		     load_bitmap(200,200,"./img/bed1.bmp",bed1,1);
		     
		     draw_indexed_graphic(20,100,250,100,buts2,display_array1,0,0x0);
		     draw_indexed_graphic(305,150,200,200,bed1,display_array1,0,0x0);
		     
			  draw_indexed_graphic(530,100,250,100,butb,display_array1,0,0x0);
			  draw_indexed_graphic(20,200,250,100,butk,display_array1,0,0x0);
			  draw_indexed_graphic(530,200,250,100,butbat,display_array1,0,0x0);
			  draw_indexed_graphic(20,300,250,100,butd,display_array1,0,0x0);
			  draw_indexed_graphic(530,300,250,100,butg,display_array1,0,0x0);	
		     
		     get_cap_touch(); 
		    
	            
		   }  
	
		    if((T1x>500) & (T1x<740) & (T1y>130) & (T1y<160))
		    {
		     unsigned int butb2[250*100*2];
		     unsigned int bed2[200*200*2];
		     
		     
		     load_bitmap(250,100,"./img/Butbb2.bmp",butb2,1);
		     load_bitmap(200,200,"./img/bed2.bmp",bed2,1);
		     
		     draw_indexed_graphic(530,100,250,100,butb2,display_array1,0,0x0);
		     draw_indexed_graphic(305,150,200,200,bed2,display_array1,0,0x0);
		     
		  draw_indexed_graphic(20,100,250,100,buts,display_array1,0,0x0);
		  draw_indexed_graphic(20,200,250,100,butk,display_array1,0,0x0);
		  draw_indexed_graphic(530,200,250,100,butbat,display_array1,0,0x0);
		  draw_indexed_graphic(20,300,250,100,butd,display_array1,0,0x0);
		  draw_indexed_graphic(530,300,250,100,butg,display_array1,0,0x0);	 
		     
		     get_cap_touch(); 
		     }
		    
		     
		    if((T1x>30) & (T1x<260) & (T1y>227) & (T1y<260))
		    {
		     unsigned int butk2[250*100*2];
		     unsigned int bed2[200*200*2];
		     
		     
		     load_bitmap(250,100,"./img/Butk2.bmp",butk2,1);
		     load_bitmap(200,200,"./img/frisge.bmp",bed2,1);
		     
		     draw_indexed_graphic(20,200,250,100,butk2,display_array1,0,0x0);
		     draw_indexed_graphic(305,150,200,200,bed2,display_array1,0,0x0);
		     
		  draw_indexed_graphic(530,100,250,100,butb,display_array1,0,0x0);
		  draw_indexed_graphic(20,100,250,100,buts,display_array1,0,0x0);
		  draw_indexed_graphic(530,200,250,100,butbat,display_array1,0,0x0);
		  draw_indexed_graphic(20,300,250,100,butd,display_array1,0,0x0);
		  draw_indexed_graphic(530,300,250,100,butg,display_array1,0,0x0);	
		     
		     
		     get_cap_touch(); 
		     }

		    if((T1x>500) & (T1x<740) & (T1y>227) & (T1y<260))
		    {
			 unsigned int butbat2[250*100*2];
		     unsigned int bath[200*200*2];
		     
		     load_bitmap(250,100,"./img/Butbat2.bmp",butbat2,1);
		     load_bitmap(200,200,"./img/bath.bmp",bath,1);
		     
		     draw_indexed_graphic(530,200,250,100,butbat2,display_array1,0,0x0);
		     draw_indexed_graphic(305,150,200,200,bath,display_array1,0,0x0);
		    
		  draw_indexed_graphic(530,100,250,100,butb,display_array1,0,0x0);
		  draw_indexed_graphic(20,200,250,100,butk,display_array1,0,0x0);
		  draw_indexed_graphic(20,100,250,100,buts,display_array1,0,0x0);
		  draw_indexed_graphic(20,300,250,100,butd,display_array1,0,0x0);
		  draw_indexed_graphic(530,300,250,100,butg,display_array1,0,0x0);	
		    
		    
		     get_cap_touch(); 
		     }

		      if((T1x>30) & (T1x<260) & (T1y>330) & (T1y<360))
		    {
		     unsigned int butd2[250*100*2];
		     unsigned int sofa[200*200*2];
		     
		   
		     load_bitmap(250,100,"./img/Butd2.bmp",butd2,1);
		     load_bitmap(200,200,"./img/sofa.bmp",sofa,1);
		     
		     draw_indexed_graphic(20,300,250,100,butd2,display_array1,0,0x0);
		     draw_indexed_graphic(305,150,200,200,sofa,display_array1,0,0x0);
		     
		  draw_indexed_graphic(530,100,250,100,butb,display_array1,0,0x0);
		  draw_indexed_graphic(20,200,250,100,butk,display_array1,0,0x0);
		  draw_indexed_graphic(530,200,250,100,butbat,display_array1,0,0x0);
		  draw_indexed_graphic(20,100,250,100,buts,display_array1,0,0x0);
		  draw_indexed_graphic(530,300,250,100,butg,display_array1,0,0x0);	 
		     
		     
		     
		     get_cap_touch(); 
		     }		 
		 		     		 
		    if((T1x>540) & (T1x<730) & (T1y>330) & (T1y<360))
		    {
			 unsigned int butg2[250*100*2];
		     unsigned int garage[200*200*2];
		     
		     load_bitmap(250,100,"./img/Butg2.bmp",butg2,1);
		     load_bitmap(200,200,"./img/garage.bmp",garage,1);
		     
		     draw_indexed_graphic(530,300,250,100,butg2,display_array1,0,0x0);
		     draw_indexed_graphic(305,150,200,200,garage,display_array1,0,0x0);
		     
		  draw_indexed_graphic(530,100,250,100,butb,display_array1,0,0x0);
		  draw_indexed_graphic(20,200,250,100,butk,display_array1,0,0x0);
		  draw_indexed_graphic(530,200,250,100,butbat,display_array1,0,0x0);
		  draw_indexed_graphic(20,300,250,100,butd,display_array1,0,0x0);
		  draw_indexed_graphic(20,100,250,100,buts,display_array1,0,0x0);	

		     get_cap_touch(); 
		     }
		 
		   if((T1x>750) && (T1y>1) & (T1y<60))
		   {
			load_bitmap(800,480,"./img/Main.bmp",display_array1,1);
			draw_image(0,0,800,480,display_array1);
			c=0;
			bcm2835_delay(500);
		   }
	      }//while
		  
		  
		  
		 
	
	
	
}
	
	


void voice()
{
	
unsigned int display_array2[384000*2];
unsigned int slider1_array[69*120*2];
unsigned int bar_array[30*24*6*2];
unsigned int bar_black_array[30*24*6*2];


//long i;
unsigned int b;
b=1;
int ax=12+22,ay=350,bx=117+21,by=350, cx=230+20,cy=350,dx=330+17,dy=350,bar1,old_bar1,bar2,old_bar2,bar3,old_bar3,bar4,old_bar4;

	
		  load_bitmap(800,480,"./img/VC3.bmp",display_array2,1);		
		  load_bitmap(27,71,"./img/slider1_27x71.bmp",slider1_array,1);
		  load_bitmap(30,24,"./img/bar_30x24x6.bmp",bar_array,6);
		  load_bitmap(30,24,"./img/bar_black_30x24x6.bmp",bar_black_array,6);
			  
		  draw_image(0,0,800,480,display_array2);
		  draw_indexed_graphic(ax,ay-35,27,71,slider1_array,display_array2,0,0x0);		 
		  draw_indexed_graphic(bx,by-35,27,71,slider1_array,display_array2,0,0x0);		
		  draw_indexed_graphic(cx,cy-35,27,71,slider1_array,display_array2,0,0x0);		 
		  draw_indexed_graphic(dx,dy-35,27,71,slider1_array,display_array2,0,0x0);
		  bar1=5;
		  bar2=5;
		  bar3=5;
		  bar4=5;
		  draw_indexed_graphic(480,190+(bar1*30),30,24,bar_array,display_array2,bar1,0x0);
		  draw_indexed_graphic(550,190+(bar2*30),30,24,bar_array,display_array2,bar2,0x0);
		  draw_indexed_graphic(620,190+(bar3*30),30,24,bar_array,display_array2,bar3,0x0);
		  draw_indexed_graphic(690,190+(bar4*30),30,24,bar_array,display_array2,bar4,0x0);

		  bcm2835_delay(500);

		  
		  while(b==1)
		  {
			get_cap_touch();
	   
//First Slider/////////////////////////////////////////////////////////////////////	   
			if((T1x>20)&&(T1x<110)&&(T1y>130)&&(T1y<360))
			{
				while((ay/5)!=(T1y/5))
				{  
				 if(ay<T1y)
				   ay+=5;
				 if(ay>T1y)
				   ay-=5;
				 draw_indexed_graphic(ax,ay-35,27,71,slider1_array,display_array2,0,0x0);
				 bar1=(ay-100)/44;
				 if(bar1 != old_bar1)
				  {
				   draw_indexed_graphic(480,190+(bar1*30),30,24,bar_array,display_array2,bar1,0x0);	
				   draw_indexed_graphic(480,160+(bar1*30),30,24,bar_black_array,display_array2,bar1,0x0);
				  }	
				 old_bar1=bar1;
				}	 
			}
    
			    
		    if((T2x>20)&&(T2x<110)&&(T2y>130)&&(T2y<360))
		    {
			   while((ay/5)!=(T2y/5))
			   {  
				if(ay<T2y)
				  ay+=5;
			    if(ay>T2y)
				  ay-=5;
			    draw_indexed_graphic(ax,ay-35,27,71,slider1_array,display_array2,0,0x0);
			    bar1=(ay-100)/44;
				if(bar1 != old_bar1)
				 {
				  draw_indexed_graphic(480,190+(bar1*30),30,24,bar_array,display_array2,bar1,0x0);	
				  draw_indexed_graphic(480,160+(bar1*30),30,24,bar_black_array,display_array2,bar1,0x0);
				 }	
				old_bar1=bar1;
			   }
			}     
    
	    
//Second Slider/////////////////////////////////////////////////////////////////////
			if((T1x>120)&&(T1x<210)&&(T1y>130)&&(T1y<360))
			{
				while((by/5)!=(T1y/5))
				{  
				 if(by<T1y)
				   by+=5;
				 if(by>T1y)
				   by-=5;
				 draw_indexed_graphic(bx,by-35,27,71,slider1_array,display_array2,0,0x0);
				 bar2=(by-100)/44;
				 if(bar2 != old_bar2)
				  {
				   draw_indexed_graphic(550,190+(bar2*30),30,24,bar_array,display_array2,bar2,0x0);	
				   draw_indexed_graphic(550,160+(bar2*30),30,24,bar_black_array,display_array2,bar2,0x0);
				  }	
				 old_bar2=bar2;
				}	 
			}
    
			    
		    if((T2x>120)&&(T2x<210)&&(T2y>130)&&(T2y<360))
		    {
			   while((by/5)!=(T2y/5))
			   {  
				if(by<T2y)
				  by+=5;
			    if(by>T2y)
				  by-=5;
			    draw_indexed_graphic(bx,by-35,27,71,slider1_array,display_array2,0,0x0);
			    bar2=(by-100)/44;
				if(bar2 != old_bar2)
				 {
				  draw_indexed_graphic(550,190+(bar2*30),30,24,bar_array,display_array2,bar2,0x0);	
				  draw_indexed_graphic(550,160+(bar2*30),30,24,bar_black_array,display_array2,bar2,0x0);
				 }	
				old_bar2=bar2;
			   }
			}     
 	    
		 
//Third Slider/////////////////////////////////////////////////////////////////////
			if((T1x>220)&&(T1x<320)&&(T1y>130)&&(T1y<360))
			{
				while((cy/5)!=(T1y/5))
				{  
				 if(cy<T1y)
				   cy+=5;
				 if(cy>T1y)
				   cy-=5;
				 draw_indexed_graphic(cx,cy-35,27,71,slider1_array,display_array2,0,0x0);
				 bar3=(cy-100)/44;
				 if(bar3 != old_bar3)
				  {
				   draw_indexed_graphic(620,190+(bar3*30),30,24,bar_array,display_array2,bar3,0x0);	
				   draw_indexed_graphic(620,160+(bar3*30),30,24,bar_black_array,display_array2,bar3,0x0);
				  }	
				 old_bar3=bar3;
				}	 
			}
    
			    
		    if((T2x>220)&&(T2x<320)&&(T2y>130)&&(T2y<360))
		    {
			   while((cy/5)!=(T2y/5))
			   {  
				if(cy<T2y)
				  cy+=5;
			    if(cy>T2y)
				  cy-=5;
			    draw_indexed_graphic(cx,cy-35,27,71,slider1_array,display_array2,0,0x0);
			    bar3=(cy-100)/44;
				if(bar3 != old_bar3)
				 {
				  draw_indexed_graphic(620,190+(bar3*30),30,24,bar_array,display_array2,bar3,0x0);	
				  draw_indexed_graphic(620,160+(bar3*30),30,24,bar_black_array,display_array2,bar3,0x0);
				 }	
				old_bar3=bar3;
			   }
			}     
    		 
	 
//Fourth Slider/////////////////////////////////////////////////////////////////////
			if((T1x>340)&&(T1x<410)&&(T1y>130)&&(T1y<360))
			{
				while((dy/5)!=(T1y/5))
				{  
				 if(dy<T1y)
				   dy+=5;
				 if(dy>T1y)
				   dy-=5;
				 draw_indexed_graphic(dx,dy-35,27,71,slider1_array,display_array2,0,0x0);
				 bar4=(dy-100)/44;
				 if(bar4 != old_bar4)
				  {
				   draw_indexed_graphic(690,190+(bar4*30),30,24,bar_array,display_array2,bar4,0x0);	
				   draw_indexed_graphic(690,160+(bar4*30),30,24,bar_black_array,display_array2,bar4,0x0);
				  }	
				 old_bar4=bar4;
				}	 
			}
    
			    
		    if((T2x>340)&&(T2x<410)&&(T2y>130)&&(T2y<360))
		    {
			   while((dy/5)!=(T2y/5))
			   {  
				if(dy<T2y)
				  dy+=5;
			    if(dy>T2y)
				  dy-=5;
			    draw_indexed_graphic(dx,dy-35,27,71,slider1_array,display_array2,0,0x0);
			    bar4=(dy-100)/44;
				if(bar4 != old_bar4)
				 {
				  draw_indexed_graphic(690,190+(bar4*30),30,24,bar_array,display_array2,bar4,0x0);	
				  draw_indexed_graphic(690,160+(bar4*30),30,24,bar_black_array,display_array2,bar4,0x0);
				 }	
				old_bar4=bar4;
			   }
			}     
///////////////////////////////////////////////////////////////////////   		 
					 
		 if((T1x>750) && (T1y>1) & (T1y<60))
		   {
			load_bitmap(800,480,"./img/Main.bmp",display_array2,1);
			draw_image(0,0,800,480,display_array2);
			b=0;
			T1x=1;   
		   }
 
 
    
		}//while	 	

}			
	

