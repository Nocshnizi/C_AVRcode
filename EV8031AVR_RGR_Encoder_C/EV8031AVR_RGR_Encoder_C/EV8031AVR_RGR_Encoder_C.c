#define F_CPU 7372800L 
#include <avr/io.h>
#include <avr/iom8515.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define led_line 0xA006 

#define lcd_comm 0x8004

#define lcd_data 0x8005

volatile unsigned char temp;

volatile unsigned char encoder_data = 0x00;;

volatile unsigned char last_encoder_state;

volatile unsigned char next_encoder_state;

volatile unsigned int counter = 2;// for clockwise

volatile unsigned int againstCounter = 2;//for counterclockwise

volatile unsigned char little_letter = 'a';

volatile unsigned int permition = 0;

volatile unsigned char* c = (unsigned char *) lcd_comm;

volatile unsigned char* d = (unsigned char *) lcd_data;





ISR (TIMER0_COMP_vect) {
      	permition = 1;
  
}

int main (void) {

//  _delay_ms (1000);
  ACSR = 1 << ACD;  
  MCUCR = 1 << SRE; 

  TIMSK = 1 << OCIE0; 
  OCR0 = 0x1D;
        
  SFIOR = 1 << PSR10;  
 
  TCCR0 = 1 << WGM01 | 1 << CS02;

	*c = 0x38; //Function Set
    _delay_ms (10); 

    *c = 0x0E; //Display ON/OFF Control
    _delay_ms (10); 

    *c = 0x01; //Display clear
    _delay_ms (10); 

    *c = 0x06; //Entry Mode Set
    _delay_ms (10); 
	*c = 0xC8;
	_delay_ms (10);

    last_encoder_state = PINB; 
    last_encoder_state &= 0b1001000;

     sei();


   
     
while(1){  

	if(permition == 1){
	next_encoder_state = PINB; 
    next_encoder_state &= 0b10010000; 
	  if (next_encoder_state != last_encoder_state) { 	
		encoder_data = little_letter;
	  if(last_encoder_state == 0x00) { 
	        if (next_encoder_state == 0b00010000) { 
	          encoder_data--;
			  againstCounter--;
	          if(encoder_data < 'a'){
	             encoder_data = 'z';
				 
	          }
            
	        }
	        if (next_encoder_state == 0b10000000) { 
	          encoder_data++; 
			  counter--;
	          if(encoder_data > 'z'){
	               encoder_data = 'a';
				  
	          }
	        }
	      }
	  
	  	}	  
		


		if(counter == 0){
	      counter = 2;
	      little_letter = encoder_data;


	      *d = little_letter;
	      _delay_ms (10);
		  
		   
		 } 
		 
		 if(againstCounter == 0){
				againstCounter = 2;
				  little_letter = encoder_data;


	      *d = little_letter;
	       _delay_ms (10);

		 }
	     
	    temp = PINB; 
	    temp &= 0b00100000; 



		if (temp == 0x00) { 
		      *c = 0x01;
		      _delay_ms (10);
		 }

		  permition = 0;
		   
		  last_encoder_state = next_encoder_state;
	} 
}

 
  return 0;
}
