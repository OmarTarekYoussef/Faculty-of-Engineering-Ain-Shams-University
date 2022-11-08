#include "mbed.h"
#include "LM35.h"
#include <string>
#include "float2str.h"

//function declerations 

void lamp_plug_on_off_from_latch(void);
void temp_buzzer(void);
void apply_uart_states(char state);
void display_temp(void);
//Global variables

//lamp and plug variables

char previous_latch_lamp_state=0;
char previous_latch_plug_state=0;
char current_latch_lamp_state = 0; 
char current_latch_plug_state = 0;
DigitalIn  latch_lamp_pin(PTD7); //      //
DigitalOut relay_lamp_pin(PTD6); //      //
DigitalIn  latch_plug_pin(PTA17); 
DigitalOut relay_plug_pin(PTA16);
DigitalOut buzzer(PTC16);
bool lamp_state = 0;
bool plug_state = 0;

//temp variables

float temp = 0;
LM35 temp_sensor(PTB0);
char*temp_value;
//uart

Serial uart(PTE0,PTE1,9600);//    //
char state = 0 ;

int main()
{
    while (1) {
        lamp_plug_on_off_from_latch();
        temp_buzzer();
        if(uart.readable()){
            state = uart.getc();
            apply_uart_states(state);
            display_temp();
            }
            //display_temp();        
}
}


void lamp_plug_on_off_from_latch(void){
        current_latch_lamp_state = latch_lamp_pin.read();
        current_latch_plug_state = latch_plug_pin.read();
        if(current_latch_lamp_state!=previous_latch_lamp_state){
            lamp_state = !lamp_state;
            previous_latch_lamp_state = current_latch_lamp_state;
            }
        if(current_latch_plug_state!=previous_latch_plug_state){
            plug_state = !plug_state;
            previous_latch_plug_state = current_latch_plug_state;
            }
        if(lamp_state){
            relay_lamp_pin = 1;
            }
        else{
            relay_lamp_pin = 0;
            }
       if(plug_state){
            relay_plug_pin = 1;
            }
        else{
            relay_plug_pin = 0;            
            }
    }
       
void temp_buzzer(void){
    temp = temp_sensor.get();
    if(temp > 50){
        buzzer = 1;
        }
    else{
        buzzer = 0;
        }
    }
    
    
void apply_uart_states(char state){
    switch(state){
        case 'A':
        relay_lamp_pin = 1; // normally open
        lamp_state = 1;
        break;
        case 'B':
        relay_lamp_pin = 0;
        lamp_state = 0;
        break;
        case 'C':
        relay_plug_pin = 1;
        plug_state = 1;
        break;
        case 'D':
        relay_plug_pin = 0;
        plug_state = 0;
        break; 
        }
    }
    
void display_temp(void){
    temp_value = toString(temp,3);
    uart.puts(temp_value);
    }