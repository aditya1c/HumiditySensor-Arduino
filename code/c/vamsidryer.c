/*
 * adccheck.c
 *
 * Created: 20-03-2013 20:46:14
 *  Author: Param
 */ 


#define F_CPU 14.7456e6
#include <util/delay.h>
#include <avr/io.h>
#include <math.h>
void InitADC()
{
	ADMUX=(1<<REFS0);                         // For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128
}

uint8_t ReadADC(uint8_t ch)
{
	//Select ADC Channel ch must be 0-7
	ch=ch&0b00000111;
	ADMUX|=ch;

	//Start Single conversion
	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete
	while (!(ADCSRA & (1<<ADIF)));

	//Clear ADIF by writing one to it
	ADCSRA|=(1<<ADIF);
	ADMUX|=(1<<ADLAR);

	return(ADCH);
}


int main(void)
{DDRA=0x00;
DDRB=0xff;  
uint8_t valir,refir=128,valhum;
int i;
float time;
int s=0;


InitADC();
  while(1)
    {InitADC();
		_delay_ms(10);
		valir=ReadADC(0);
		InitADC();
		_delay_ms(10);
		valhum=ReadADC(1);
		if (valir>refir)
		  {if(s==0)
		{
			time=5+((valhum-100)*0.2);
			PORTB=0xff;
			for(i=0;i<=time;i++)
			{_delay_ms(1000);}
		PORTB=0x00;
		s=1;		
		}}
		if (valir<refir)
		{PORTB=0x00;
			s=0;}	
		
		}		
		
		
        //TODO:: Please write your application code 
    }
	