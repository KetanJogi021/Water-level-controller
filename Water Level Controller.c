#include <reg51.h>                      // library for 8051

#define DATA P2                         // defining PORT 2 as DATA for LCD

sbit red= P3^0;                         // initializing the output pins for LED
sbit yellow= P3^1;
sbit green= P3^2;
sbit blue= P3^3;

sbit motor= P3^4;                       // initializing the output pins for MOTOR

sbit full= P1^0;
sbit half= P1^1;
sbit quarter= P1^2;
sbit bottom= P1^3;

sbit RS= P0^0;                          // initializing pins for LCD
sbit RW= P0^1;
sbit EN= P0^2;

void delay(int time)                    // Delay function
{
	int j,k;
	
	for(j=0; j<time; j++)
	{
		for(k=0; k<1275; k++)
		{
		}
	}
}

void lcdcmd(char value)                // Function to send commands to LCD
{
	P2=value;
	RW=0;                                // Making RW pin LOW to WRITE the data to LCD
	RS=0;                                // Making RS pin LOW to delect the COMMAND REGISTER
	EN=1;                                // Enabling the LCD
	delay(1);                           // Every instruction given to LCD takes certain amount of time for execution
	EN=0;                                //Disabling the LCD
	delay(1);
}

void display(char value)               //Funtion to display data on LCD
{
	P2=value;
	RW=0;                                // Making RW pin LOW to WRITE the data to LCD
	RS=1;                                // Making RS pin HIGH to delect the DATA REGISTER
	EN=1;
	delay(5);
	EN=0;
	delay(1);
}

void lcdint(void)                      // Function to initialize LCD
{
	P2=0x00;
	P0=0x00;
	
	delay(25);
	display(0x30);                       // Function Set: 8 bit, 1 line, 5x7 Dots
	delay(40);
	display(0x38);                       // Function Set: 8 bit, 2 line, 5x7 Dots
	delay(5);
	lcdcmd(0x0C);                        // Display ON cursor OFF
	delay(5);
	lcdcmd(0x01);                        // Clear display
	delay(5);
	lcdcmd(0x06);                        // Entry mode
	delay(5);
	lcdcmd(0x80);                        // Set DDRAM address or cursor postion on display ( 0x80+ add )
	delay(5);
}

void shift_left(void)                     // Function to shift the diplayed data to the left
{
	int j;
	
	for(j=0; j<15; j++)
	{
	 delay(25);
	 lcdcmd(0x1B);                         // shift entire display to the LEFT
	}
}
	
void shift_right(void)                   // Function to shift the diplayed data to the right
{
	int j;
	
	for(j=0; j<15; j++)
	{
	 delay(25);
	 lcdcmd(0x1C);                         // shift entire display to the RIGHT
	}
}

void main()
{
	
	int i=0, j=0, k=0, l=0, m=0;	
	
	char f[]= {"Tank is full"};            //  initializing the data to be printed on the LCD
	char h[]= {"Tank is half filled"};
	char q[]= {"Tank is quarterly filled"};
	char b[]= {"Tank is 10% filled"};
	char e[]= {"Tank is empty"};
	
	P0=0x00;                               // Initializing all the PORTS to logic LOW
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
			
			while(full!=0)                   // logic to display the data on the LCD
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