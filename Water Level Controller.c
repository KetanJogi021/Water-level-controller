/* library for 8051 */
#include <reg51.h>                      

/* defining PORT 2 as DATA for LCD */
#define DATA P2                         

/* initializing the output pins for LED */
sbit red= P3^0;                         
sbit yellow= P3^1;
sbit green= P3^2;
sbit blue= P3^3;

/* initializing the output pins for MOTOR */
sbit motor= P3^4;                       

/* initializing the water levels for input */
sbit full= P1^0;
sbit half= P1^1;
sbit quarter= P1^2;
sbit bottom= P1^3;

/* initializing pins for LCD */
sbit RS= P0^0;                          
sbit RW= P0^1;
sbit EN= P0^2;

/* Delay function */
void delay(int time)                    
{
	int j,k;
	
	for(j=0; j<time; j++)
	{
		for(k=0; k<1275; k++)
		{
		}
	}
}

/* Function to send commands to LCD */
void lcdcmd(char value)                
{
	P2=value;
	/* Making RW pin LOW to WRITE the data to LCD */
	RW=0;                                
	/* Making RS pin LOW to delect the COMMAND REGISTER */
	RS=0;                                
	/* Enabling the LCD */
	EN=1;                               
	/* Every instruction given to LCD takes some time for execution */ 
	delay(1);
	/* Disabling the LCD */                           
	EN=0;
	delay(1);
}

/* Funtion to display data on LCD */
void display(char value)               
{
	P2=value;
	/* Making RW pin LOW to WRITE the data to LCD */
	RW=0;                                
	/* Making RS pin HIGH to delect the DATA REGISTER */
	RS=1;                                
	EN=1;
	delay(1);
	EN=0;
	delay(1);
}

/* Function to initialize LCD */
void lcdint(void)                      
{
	P2=0x00;
	P0=0x00;
	
	delay(25);
	/* Function Set: 8 bit, 1 line, 5x7 Dots */
	display(0x30);                       
	delay(40);
	/* Function Set: 8 bit, 2 line, 5x7 Dots */
	display(0x38);                       
	delay(5);
	/* Display ON cursor OFF */
	lcdcmd(0x0C);                        
	delay(5);
	/* Clear displayv */
	lcdcmd(0x01);                        
	delay(5);
	/* Entry mode */
	lcdcmd(0x06);                        
	delay(5);
	/* Set DDRAM address or cursor postion on display ( 0x80+ add ) */
	lcdcmd(0x80);                        
	delay(5);
}

/* Function to shift the diplayed data to the left */
void shift_left(void)                     
{
	int j;
	
	for(j=0; j<15; j++)
	{
	 delay(25);
	 /* shift entire display to the LEFT */
	 lcdcmd(0x1B);                         
	}
}
	
/* Function to shift the diplayed data to the right */	
void shift_right(void)                   
{
	int j;
	
	for(j=0; j<15; j++)
	{
	 delay(25);
	 /* shift entire display to the RIGHT */
	 lcdcmd(0x1C);                         
	}
}

void main()
{
	
	int i=0, j=0, k=0, l=0, m=0;	
	
	/*  initializing the data to be printed on the LCD */
	char f[]= {"Tank is full"};            
	char h[]= {"Tank is half filled"};
	char q[]= {"Tank is quarterly filled"};
	char b[]= {"Tank is 10% filled"};
	char e[]= {"Tank is empty"};
	
	/* Initializing all the PORTS to logic LOW */
	P0=0x00;                               
	P1=0x00;
	P3=0x00;
	
	lcdint();
	lcdcmd(0x01);
	lcdcmd(0x80);
	
	while(1)
	
	{
		if(full==1)
		{
			red=1;
			yellow=0;
			green=0;
			blue=0;
			motor=0;
			
			lcdcmd(0x01);
			delay(1);
			
			/* logic to display the data on the LCD */
			while(full!=0)                   
			{
				while(f[i]!='\0')
			{
				display(f[i]);
				i++;
			}
			}
			
			
	}
		else if(half==1)
		{
			red=0;
			yellow=1;
			green=0;
			blue=0;
			motor=1;
			
			lcdcmd(0x01);
			delay(1);
			
			while(h[j]!='\0')
			{
				display(h[j]);
				j++;
			}
			while(full!=1 && half!=0)
			{
				shift_left();
				shift_right();
			}
		}
		else if(quarter==1)
		{
			red=0;
			yellow=0;
			green=1;
			blue=0;
			motor=1;
			
			lcdcmd(0x01);
			delay(1);
			
			while(q[k]!='\0')
			{
				display(q[k]);
				k++;
			}
			while(half!=1 && quarter!=0)
			{
				shift_left();
				shift_right();
			}
		}
		else if(bottom==1)
		{
			red=0;
			yellow=0;
			green=0;
			blue=1;
			motor=1;
			
			lcdcmd(0x01);
			delay(1);
			
			while(b[l]!='\0')
			{
				display(b[l]);
				l++;
			}
			while(quarter!=1 && bottom!=0)
			{
				shift_left();
				shift_right();
			}
		}
		else
		{
			red=0;
			yellow=0;
			green=0;
			blue=0;
			motor=1;
			
			
			lcdcmd(0x01);
			delay(1);
			
			while(bottom!=1)
			{
				while(e[m]!='\0')
			{
				display(e[m]);
				m++;
			}
			}
			
		}
	}
}
