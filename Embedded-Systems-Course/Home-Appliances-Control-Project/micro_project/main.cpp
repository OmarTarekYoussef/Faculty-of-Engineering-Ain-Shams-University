
#include "mbed.h"
#include "LM35.h"
#include <string>
#include "float2str.h"
#include "DFPlayerMini.h"
 
Serial pc (USBTX,USBRX);
 
//setup const array in flash with audio values 
//from free wav file conversion tool at
//http://ccgi.cjseymour.plus.com/wavtocode/wavtocode.htm
//see https://os.mbed.com/users/4180_1/notebook/using-flash-to-play-audio-clips/


#define sample_freq 11025.0

//get and set the frequency from wav conversion tool GUI
int i=0;
 
//interrupt routine to play next audio sample from array in flash

void lamp_plug_on_off_from_latch(void);
void temp_buzzer(void);
void apply_uart_states(char state);
void display_temp(void);
void door_open_pin(void);
void playAudio ( uint16_t Index , uint16_t volume );
void stopAudio (void);
void doorOpened();


//Global variables

//lamp and plug variables

char previous_latch_lamp_state=0;
char previous_latch_plug_state=0;
char current_latch_lamp_state = 0; 
char current_latch_plug_state = 0;
char current_door_state = 0;
char door_flag = 0;
bool lamp_state = 0;
bool plug_state = 0;

DigitalIn  door_pin(PTE5); //      //
DigitalIn  latch_lamp_pin(PTE4); //      //
DigitalOut relay_lamp_pin(PTD6); // in2       //
DigitalIn  latch_plug_pin(PTA17); 
DigitalOut relay_plug_pin(PTA16);// in1       //
DigitalOut buzzer(PTC16);                  


//InterruptIn Door(PTD4, PullUp);

DFPlayerMini speaker (PTE22,PTE23);

//temp variables

float temp = 0;
float open_value = 200.0;
float closed_value = 300.0;
LM35 temp_sensor(PTB0);
char*temp_value;
char*door_open_value;
char*door_closed_value;
//uart

Serial uart(PTE0,PTE1,9600);//    //
char state = 0 ;

int main()
{

    while (1) {
        door_open_pin();
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
    if(temp > 27){
        buzzer = 1;
        speaker.mp3_set_volume(30);
        speaker.mp3_play_physical(3);
        wait(0.25);
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
 

void door_open_pin(void){
    current_door_state = door_pin.read();
    if (current_door_state == 0 && door_flag == 0){
        door_open_value = toString(open_value,0);
        uart.puts(door_open_value);
        pc.printf("open");
        speaker.mp3_set_volume(30);
        speaker.mp3_play_physical(1);
        wait(0.25);
        door_flag = 1;
        }
    if (current_door_state == 1 && door_flag == 1){
        door_closed_value = toString(closed_value,0);
        uart.puts(door_closed_value);
        door_flag = 0;
//        speaker.mp3_set_volume(30);
//        speaker.mp3_play_physical(2);
        }
}
